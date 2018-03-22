<?php

namespace Drupal\htmlmail\Plugin\Mail;

use Drupal\Core\Extension\ModuleHandlerInterface;
use Drupal\Core\Logger\LoggerChannelFactoryInterface;
use Drupal\Core\Mail\MailInterface;
use Drupal\Core\Mail\MailFormatHelper;
use Drupal\Core\Plugin\ContainerFactoryPluginInterface;
use Drupal\Core\Site\Settings;
use Drupal\Core\File\FileSystemInterface;
use Drupal\Core\Mail;
use Drupal\Core\Render\Renderer;
use Drupal\Component\Utility\Unicode;
use Drupal\htmlmail\Helper\HtmlMailHelper;
use Symfony\Component\DependencyInjection\ContainerInterface;
use Egulias\EmailValidator\EmailValidator;
use Drupal\htmlmail\Utility\HTMLMailMime;
use Symfony\Component\HttpFoundation\File\MimeType\MimeTypeGuesserInterface;

/**
 * Modify the Drupal mail system to use HTMLMail when sending emails.
 *
 * @Mail(
 *   id = "htmlmail",
 *   label = @Translation("HTMLMail mailer"),
 *   description = @Translation("Sends the message using HTMLMail.")
 * )
 */
class HTMLMailSystem implements MailInterface, ContainerFactoryPluginInterface {

  protected $emailValidator;
  protected $systemConfig;
  protected $moduleHandler;
  protected $logger;
  protected $configVariables;
  protected $siteSettings;
  protected $fileSystem;
  protected $renderer;
  protected $mimeType;

  /**
   * HTMLMailSystem constructor.
   *
   * @param array $configuration
   *   The configuration array.
   * @param int $plugin_id
   *   Plugin ID.
   * @param string $plugin_definition
   *   Plugin definition.
   * @param \Egulias\EmailValidator\EmailValidator $emailValidator
   *   The email validator service.
   * @param \Drupal\Core\Extension\ModuleHandlerInterface $moduleHandler
   *   The module handler service.
   * @param \Drupal\Core\File\FileSystemInterface $fileSystem
   *   The file system service.
   * @param \Drupal\Core\Logger\LoggerChannelFactoryInterface $logger
   *   The logger service.
   * @param \Drupal\Core\Site\Settings $settings
   *   The site settings service.
   * @param \Drupal\Core\Render\Renderer $renderer
   *   The render service.
   * @param \Symfony\Component\HttpFoundation\File\MimeType\MimeTypeGuesserInterface $mimeTypeGuesser
   *   The mime guesser service.
   */
  public function __construct(
    array $configuration,
    $plugin_id,
    $plugin_definition,
    EmailValidator $emailValidator,
    ModuleHandlerInterface $moduleHandler,
    FileSystemInterface $fileSystem,
    LoggerChannelFactoryInterface $logger,
    Settings $settings,
    Renderer $renderer,
    MimeTypeGuesserInterface $mimeTypeGuesser
  ) {
    $this->emailValidator = $emailValidator;
    $this->moduleHandler = $moduleHandler;
    $this->fileSystem = $fileSystem;
    $this->logger = $logger;
    $this->systemConfig = \Drupal::config('system.site');
    $this->configVariables = \Drupal::config('htmlmail.settings');
    $this->siteSettings = $settings;
    $this->renderer = $renderer;
    $this->mimeType = $mimeTypeGuesser;
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container, array $configuration, $plugin_id, $plugin_definition) {
    return new static(
      $configuration,
      $plugin_id,
      $plugin_definition,
      $container->get('email.validator'),
      $container->get('module_handler'),
      $container->get('file_system'),
      $container->get('logger.factory'),
      $container->get('settings'),
      $container->get('renderer'),
      $container->get('file.mime_type.guesser')
    );
  }

  /**
   * Retrieves the logger.
   *
   * @return \Drupal\Core\Logger\LoggerChannelInterface
   *   The htmlmail logger.
   */
  public function getLogger() {
    return $this->logger->get('htmlmail');
  }

  /**
   * Retrieves the default site mail.
   *
   * First from Drupal configuration and then PHP configuration.
   *
   * @return string
   *   The email to be used.
   */
  public function getDefaultFromMail() {
    $site_mail = $this->systemConfig->get('mail');
    return $site_mail ?: ini_get('sendmail_from');
  }

  /**
   * Retrieves the site name.
   *
   * First from Drupal configuration and then set as Drupal.
   *
   * @return string
   *   The site name.
   */
  public function getDefaultSiteName() {
    $site_name = $this->systemConfig->get('site_name');
    return $site_name ?: 'Drupal';
  }

  /**
   * Format emails according to module settings.
   *
   * Parses the message headers and body into a MailMIME object.  If another
   * module subsequently modifies the body, then format() should be called again
   * before sending.  This is safe because the $message['body'] is not modified.
   *
   * @param array $message
   *   An associative array with at least the following parts:
   *   - headers: An array of (name => value) email headers.
   *   - body: The text/plain or text/html message part.
   *
   * @return array
   *   The formatted $message, ready for sending.
   */
  public function format(array $message) {
    $eol = $this->siteSettings->get('mail_line_endings', PHP_EOL);
    $default_from = $this->getDefaultFromMail();
    $force_plain = $this->configVariables->get('htmlmail_html_with_plain');

    if (!empty($message['headers']['From'])
      && $message['headers']['From'] == $default_from
      && $this->emailValidator->isValid($default_from)
    ) {
      $message['headers']['From'] = '"'
        . str_replace('"', '', $this->getDefaultSiteName())
        . '" <' . $default_from . '>';
    }

    // Collapse the message body array.
    if (class_exists('HTMLMailMime')) {
      $body = $this->formatMailMime($message);
      $plain = $message['MailMIME']->getTXTBody();
    }
    else {

      // Collapse the message body array.
      if (is_array($message['body'])) {
        // Join the body array into one string.
        $message['body'] = implode("$eol$eol", $message['body']);
        // Convert any HTML to plain-text.
        $message['body'] = MailFormatHelper::htmlToText($message['body']);
        // Wrap the mail body for sending.
        $message['body'] = MailFormatHelper::wrapMail($message['body']);
      }

      $theme = [
        '#theme' => 'htmlmail',
        '#message' => $message,
      ];
      $body = $this->renderer->render($theme);
      if ($message['body'] && !$body) {
        $this->getLogger()->warning('The %theme function did not return any text.  Please check your template file for errors.', [
          '%theme' => "Drupal::service('renderer')->render([\$theme])",
        ]);

        $body = $message['body'];
      }

      $plain = MailFormatHelper::htmlToText($body);
      if ($body && !$plain) {
        $this->getLogger()->warning('The %convert function did not return any text. Please report this error to the %mailsystem issue queue.', [
          '%convert' => 'MailFormatHelper::htmlToText()',
          '%mailsystem' => 'Mail system',
        ]);
      }
    }
    // Check to see whether recipient allows non-plaintext.
    if ($body && HtmlMailHelper::htmlMailIsAllowed($message['to']) && !$force_plain) {
      // Optionally apply the selected web theme.
      if ($this->moduleHandler->moduleExists('echo') && $theme = HtmlMailHelper::getSelectedTheme($message)) {
        $themed_body = echo_themed_page($message['subject'], $body, $theme);
        if ($themed_body) {
          $body = $themed_body;
        }
        else {
          $this->getLogger()->warning('The %echo function did not return any text. Please check the page template of your %theme theme for errors.', [
            '%echo' => 'echo_themed_page()',
            '%theme' => $theme,
          ]);
        }
      }
      // Optionally apply the selected output filter.
      if ($filter = $this->configVariables->get('htmlmail_postfilter')) {
        $filtered_body = check_markup($body, $filter);
        if ($filtered_body) {
          $body = $filtered_body;
        }
        else {
          $this->getLogger()->warning('The %check function did not return any text. Please check your %filter output filter for errors.', [
            '%check' => 'check_markup()',
            '%filter' => $filter,
          ]);
        }
      }

      // Store the fully-themed HTML body.
      if (isset($message['MailMIME'])) {
        $mime = &$message['MailMIME'];
        $mime->setHTMLBody($body);
        if (isset($message['params']['attachments'])) {
          foreach ($message['params']['attachments'] as $attachment) {
            $mime->addAttachment($this->fileSystem->realpath($attachment['uri']), $attachment['filemime'], $attachment['filename'],
              TRUE, 'base64', 'attachment', 'UTF-8', '', '');
          }
        }
        list($message['headers'], $message['body']) = $mime->toEmail($message['headers']);
        if (!$message['body']) {

          $this->getLogger()->warning('The %toemail function did not return any text. Please report this error to the %mailmime issue queue.', [
            '%toemail' => 'HTMLMailMime::toEmail()',
            '%mailmime' => 'Mail MIME',
          ]);
        }
      }
      else {
        $message['headers']['Content-Type'] = 'text/html; charset=utf-8';
        $message['body'] = $body;
        if ($this->configVariables->get('htmlmail_html_with_plain')) {
          $boundary = uniqid('np');
          $message['headers']['Content-Type'] = 'multipart/alternative;boundary="' . $boundary . '"';
          $html = $message['body'];
          $raw_message = 'This is a MIME encoded message.';
          $raw_message .= $eol . $eol . "--" . $boundary . $eol;
          $raw_message .= "Content-Type: text/plain;charset=utf-8" . $eol . $eol;
          $raw_message .= MailFormatHelper::htmlToText($html);
          $raw_message .= $eol . $eol . "--" . $boundary . $eol;
          $raw_message .= "Content-Type: text/html;charset=utf-8" . $eol . $eol;
          $raw_message .= $html;
          $raw_message .= $eol . $eol . "--" . $boundary . "--";
          $message['body'] = $raw_message;
        }
      }
    }
    else {
      if (isset($message['MailMIME'])) {
        $mime = &$message['MailMIME'];
        $mime->setHTMLBody('');
        $mime->setContentType('text/plain', ['charset' => 'utf-8']);
        if (isset($message['params']['attachments'])) {
          foreach ($message['params']['attachments'] as $attachment) {
            $mime->addAttachment($this->fileSystem->realpath($attachment['uri']), $attachment['filemime'], $attachment['filename'],
              TRUE, 'base64', 'attachment', 'UTF-8', '', '');
          }
        }
        list($message['headers'], $message['body']) = $mime->toEmail($message['headers']);
        if (!$message['body']) {
          $this->getLogger()->warning('The %toemail function did not return any text. Please report this error to the %mailmime issue queue.', [
            '%toemail' => 'HTMLMailMime::toEmail()',
            '%mailmime' => 'Mail MIME',
          ]);
        }
      }
      else {
        $message['body'] = $plain;
        $message['headers']['Content-Type'] = 'text/plain; charset=utf-8';
      }
    }
    return $message;
  }

  /**
   * Send an email message.
   *
   * @param array $message
   *   An associative array containing at least:
   *   - headers: An associative array of (name => value) email headers.
   *   - body: The text/plain or text/html message body.
   *   - MailMIME: The message, parsed into a MailMIME object.
   *
   * @return bool
   *   TRUE if the mail was successfully accepted or queued, FALSE otherwise.
   *
   * @see drupal_mail()
   * @see https://documentation.mailgun.com/api-sending.html#sending
   */
  public function mail(array $message) {
    $eol = $this->siteSettings->get('mail_line_endings', PHP_EOL);
    $params = [];
    // Ensure that subject is non-null.
    $message += ['subject' => t('(No subject)')];
    // Check for empty recipient.
    if (empty($message['to'])) {
      if (empty($message['headers']['To'])) {
        $this->getLogger()->error('Cannot send email about %subject without a recipient.', [
          '%subject' => $message['subject'],
        ]);
        return FALSE;
      }
      $message['to'] = $message['headers']['To'];
    }

    if (class_exists('MailMIME')) {
      $mime = new HTMLMailMime($this->logger, $this->siteSettings, $this->mimeType, $this->fileSystem);
      $to = $mime->mimeEncodeHeader('to', $message['to']);
      $subject = $mime->mimeEncodeHeader('subject', $message['subject']);
      $txt_headers = $mime->mimeTxtHeaders($message['headers']);
    }
    else {
      $to = Unicode::mimeHeaderEncode($message['to']);
      $subject = Unicode::mimeHeaderEncode($message['subject']);
      $txt_headers = $this->txtHeaders($message['headers']);
    }

    $body = preg_replace('#(\r\n|\r|\n)#s', $eol, $message['body']);
    // Check for empty body.
    if (empty($body)) {
      $this->getLogger()->warning('Refusing to send a blank email to %recipient about %subject.', [
        '%recipient' => $message['to'],
        '%subject' => $message['subject'],
      ]);
      return FALSE;
    }
    if ($this->configVariables->get('htmlmail_debug')) {
      $params = [
        $to,
        $subject,
        Unicode::substr($body, 0, min(80, strpos("\n", $body))) . '...',
        $txt_headers,
      ];
    }
    if (isset($message['headers']['Return-Path'])) {
      // A return-path was set.
      if (isset($_SERVER['WINDIR']) || strpos($_SERVER['SERVER_SOFTWARE'], 'Win32') !== FALSE) {
        // On Windows, PHP will use the value of sendmail_from for the
        // Return-Path header.
        $old_from = ini_get('sendmail_from');
        ini_set('sendmail_from', $message['headers']['Return-Path']);
        $result = @mail($to, $subject, $body, $txt_headers);
        ini_set('sendmail_from', $old_from);
      }
      elseif (ini_get('safe_mode')) {
        // If safe mode is in effect, passing the fifth parameter to @mail
        // will cause it to return FALSE and generate a PHP warning, even
        // if the parameter is NULL.
        $result = @mail($to, $subject, $body, $txt_headers);
      }
      else {
        // On most non-Windows systems, the "-f" option to the sendmail command
        // is used to set the Return-Path.
        $extra = '-f' . $message['headers']['Return-Path'];
        $result = @mail($to, $subject, $body, $txt_headers, $extra);
        if ($this->configVariables->get('htmlmail_debug')) {
          $params[] = $extra;
        }
      }
    }
    else {
      // No return-path was set.
      $result = @mail($to, $subject, $body, $txt_headers);
    }
    if (!$result && $this->configVariables->get('htmlmail_debug')) {
      $call = '@mail(' . implode(', ', $params) . ')';
      foreach ($params as $i => $value) {
        $params[$i] = var_export($value, 1);
      }
      if (defined('DEBUG_BACKTRACE_IGNORE_ARGS')) {
        $trace = print_r(debug_backtrace(DEBUG_BACKTRACE_IGNORE_ARGS), 1);
      }
      else {
        $trace = debug_backtrace(0);
        for ($i = count($trace) - 1; $i >= 0; $i--) {
          unset($trace[$i]['args']);
        }
        $trace = print_r($trace);
      }
      $this->getLogger()->info('Mail sending failed because:<br /><pre>@call</pre><br />returned FALSE.<br /><pre>@trace</pre>', [
        '@call' => $call,
        '@trace' => $trace,
      ]);
    }
    return $result;
  }

  /**
   * Use the MailMime class to format the message body.
   *
   * @see http://drupal.org/project/mailmime
   */
  public function formatMailMime(array &$message) {
    $eol = $this->siteSettings->get('mail_line_endings', PHP_EOL);

    $message['body'] = HTMLMailMime::concat($message['body']);
    // Build a full email message string.
    $email = HTMLMailMime::encodeEmail($message['headers'], $message['body']);
    // Parse it into MIME parts.
    if (!($mime = HTMLMailMime::parse($email))) {
      $this->getLogger()->error('Could not parse email message.');
      return $message;
    }

    // Work on a copy so that the original $message['body'] remains unchanged.
    $email = $message;
    if (!($email['body'] = $mime->getHtmlBody())
      && !($email['body'] = $mime->getTxtBody())
    ) {
      $email['body'] = '';
    }
    else {
      // Wrap formatted plaintext in <pre> tags.
      if ($email['body'] === strip_tags($email['body'])
        && preg_match('/.' . $eol . './', $email['body'])
      ) {
        // In condition:
        // No html tags.
        // At least one embedded newline.
        $email['body'] = '<pre>' . $email['body'] . '</pre>';
      }
    }
    // Theme with htmlmail.html.twig.
    $theme = [
      '#theme' => 'htmlmail',
      '#message' => $email,
    ];
    $body = $this->renderer->render($theme);

    $mime->setHtmlBody($body);
    $mime->setTxtBody(MailFormatHelper::htmlToText($body));
    $message['MailMIME'] = &$mime;
    return $body;
  }

  /**
   * Converts an array of email headers to a text string.
   *
   * @param array $headers
   *   An associative array of ('HeaderName' => 'header value') pairs.
   *
   * @return string
   *   The concatenated headers as a single string.
   */
  public function txtHeaders(array $headers) {
    $output = [];
    foreach ($headers as $name => $value) {
      if (is_array($value)) {
        foreach ($value as $val) {
          $output[] = "$name: $val";
        }
      }
      else {
        $output[] = "$name: $value";
      }
    }
    return implode("\n", $output);
  }

}
