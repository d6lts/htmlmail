<?php
/**
 * @file
 * Implementation of MailSystemInterface.
 * @see http://drupal.org/node/900794
 * @see http://api.drupal.org/api/drupal/includes--mail.inc/interface/MailSystemInterface/7
 */
class HTMLMailMailSystem implements MailSystemInterface {
  /**
   * Format emails according to module settings.
   */
  public function format(array $message) {
    // Collapse the message body array.
    $message['body'] =
      is_array($message['body'])
      ? implode("\n\n", $message['body'])
      : $message['body'];

    // Optionally apply an input filter.
    if ((isset($message['format']) && ($filter = $message['format'])) ||
        ($filter = variable_get('htmlmail_prefilter'))) {
      $message['body'] = check_markup($message['body'], $filter);
    }

    // Use the theme template to add header, footer and optional debug text.
    $message['body'] = theme('htmlmail', $message);

    // Store a plaintext version.
    $message['plaintext'] = drupal_html_to_text($message['body']);

    // Send plaintext-only if the recipient prefers it.
    $recipient = user_load_by_mail($message['to']);
    if ($recipient && !empty($recipient->data['htmlmail_plaintext'])) {
      $message['headers']['Content-Type'] = 'text/plain; charset=UTF-8; format=flowed';
      $message['body'] = $message['plaintext'];
      return $message;
    }

    // Optionally apply the selected theme via internal http request.
    if ($theme = htmlmail_get_selected_theme($message['theme'])) {
      $url = url('admin/config/system/htmlmail/email', array('absolute' => TRUE));
      $data = 'body=' . rawurlencode($message['body'])
        . '&subject=' . rawurlencode($message['subject'])
        . '&theme=' . rawurlencode($theme);
      $options = array(
        'method' => 'POST',
        'data' => $data,
        'headers' => array('Content-Type' => 'application/x-www-form-urlencoded'),
      );
      $response = drupal_http_request($url, $options);
      // Strip javascript as it doesn't work through email anyway.
      $message['body'] = preg_replace('@<script type="text/javascript".*</script>@Usi', '', $response->data);
    }

    // Optionally apply the selected output filter.
    if ($filter = variable_get('htmlmail_postfilter')) {
      $message['body'] = check_markup($message['body'], $filter);
    }

    // Store both plaintext and html versions.
    $boundary = uniqid(time(), 1);
    $message['headers']['Content-Type'] = "multipart/alternative; charset=utf-8; boundary=\"$boundary\"";
    $message['headers']['Content-Transfer-Encoding'] = '8bit';
    $message['headers']['MIME-Version'] = '1.0';
    $message['body'] = "This is a multi-part message in MIME format.
--$boundary
Content-Type: text/plain; charset=utf-8; format=flowed
Content-Transfer-Encoding: 8bit

" . $message['plaintext'] . "

--$boundary
Content-Type: text/html; charset=UTF-8; format=flowed
Content-Transfer-Encoding: 8bit

" . $message['body'] . "

--$boundary--
";
    return $message;
  }

  /**
   * Send an email message.
   */
  public function mail(array $message) {
    $mimeheaders = array();
    foreach ($message['headers'] as $name => $value) {
      $mimeheaders[] = $name . ': ' . mime_header_encode($value);
    }
    $line_endings = variable_get('mail_line_endings', MAIL_LINE_ENDINGS);
    if (isset($message['headers']['Return-Path']) &&
        !ini_get('safe_mode') &&
        !strpos(ini_get('sendmail_path'), ' -f')) {
      $extra = '-f ' . $message['headers']['Return-Path'];
    }
    else {
      $extra = '';
    }

    return mail(
      $message['to'],
      mime_header_encode($message['subject']),
      // Note: email uses CRLF for line-endings. PHP's API requires LF
      // on Unix and CRLF on Windows. Drupal automatically guesses the
      // line-ending format appropriate for your system. If you need to
      // override this, adjust $conf['mail_line_endings'] in settings.php.
      preg_replace('@\r?\n@', $line_endings, $message['body']),
      // For headers, PHP's API suggests that we use CRLF normally,
      // but some MTAs incorrectly replace LF with CRLF. See #234403.
      join("\n", $mimeheaders),
      $extra
    );
  }
}
