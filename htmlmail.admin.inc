<?php

/**
 * @file
 * Admin forms for HTML Mail
 */

/**
 * Implements hook_admin_settings().
 */
function htmlmail_admin_settings() {
  $formats = array('0' => 'Unfiltered');
  foreach (filter_formats() as $id => $filter) {
    $formats[$id] = $filter->name;
  }
  $form['htmlmail_prefilter'] = array(
    '#type' => 'select',
    '#title' => t('Text format pre-filter'),
    '#default_value' => variable_get('htmlmail_prefilter'),
    '#options' => $formats,
    '#description' => t('Choose a <a href="/admin/config/content/formats">text format</a> to be used for filtering email messages <em>before</em> the selected theme or template is applied.'),
  );
  $form['htmlmail_template'] = array(
    '#type' => 'fieldset',
    '#title' => t('Template file documentation'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['htmlmail_template']['info'] = array(
    '#markup' => t(
      // Begin instructions.
'<p>When formatting an email message, Drupal determines the active template directory by looking for <cite>htmlmail.tpl.php</cite> file in the following locations:</p>
<ul>
  <li><a href="http://api.drupal.org/api/drupal/includes--theme.inc/function/path_to_theme/7">path_to_theme()</a></li>
  <li><a href="http://api.drupal.org/api/drupal/includes--common.inc/function/drupal_get_path/7">drupal_get_path(</a>"module", <a href="http://api.drupal.org/api/drupal/developer--globals.php/global/installed_profile/7">$installed_profile</a>)</li>
  <li><a href="http://api.drupal.org/api/drupal/includes--common.inc/function/drupal_get_path/7">drupal_get_path(</a>"module", <a href="http://drupal.org/project/htmlmail">"htmlmail"</a>)</li>
</ul>
<p>Once the active template directory is found, Drupal looks in that directory for template files in order from most specific to most general.</p>
<p>For example, if <cite>foo_module</cite> sends mail with:</p>
<p><code>drupal_mail("foo_module", "outgoing_message" ...)</code></p>
<p>the possible template file names would be:</p>
<ul>
  <li><code>htmlmail-foo_module_outgoing_message.tpl.php</code></li>
  <li><code>htmlmail-foo_module_outgoing.tpl.php</code></li>
  <li><code>htmlmail-foo_module.tpl.php</code></li>
  <li><code>htmlmail.tpl.php</code></li>
</ul>
<p>The <code>$theme_hook_suggestions</code> variable contains an array of suggested <a href="http://api.drupal.org/api/drupal/includes--theme.inc/function/theme/7">theme</a> <a href="http://api.drupal.org/api/drupal/modules--system--system.api.php/function/hook_theme/7">hooks</a>, in reverse priority order. For the above example, it would contain:</p>
<ul>
  <li><code>htmlmail</code></li>
  <li><code>htmlmail-foo_module</code></li>
  <li><code>htmlmail-foo_module_outgoing</code></li>
  <li><code>htmlmail-foo_module_outgoing_message</code></li>
</ul>
<p>For another example, to customize the <a href="http://api.drupal.org/api/drupal/modules--user--user.pages.inc/function/user_pass_submit/7">password reset</a> emails sent by the <a href="http://api.drupal.org/api/drupal/modules--user--user.module/7">user module</a>, copy <code>htmlmail.tpl.php</code> to your theme directory, and also copy it to <code>htmlmail-user_password_reset.tpl.php</code>, then modify the latter file. Remember that you will need to put <em>both</em> files in your theme directory for this to work.</p>
<p>Template files are cached, so remember to clear the cache by visiting <cite>admin/settings/performance</cite> after creating, copying, or editing any <code>.tpl.php</code> files.</p>
<p>The following variables are also available in this template:</p>
<p><code>$body</code> : The message body text.</p>
<p><code>$module</code> : The sending module name, usually the first parameter to drupal_mail().</p>
<p><code>$key</code> : The email message id.</p>
<p><code>$header</code> : The header text.</p>
<p><code>$footer</code> : The footer text.</p>
<p><code>$css</code> : The css text.</p>
<p><code>$debug</code> : TRUE if debugging info should be printed.</p>
<p><code>$directory</code> : The relative path to the theme template directory.</p>
<p><code>$path</code> : The absolute URL to the theme directory.</p>
<p>The module calling <a href="http://api.drupal.org/api/drupal/includes--mail.inc/function/drupal_mail/7">drupal_mail()</a> may set other variables. For instance, the <a href="http://drupal.org/project/webform">Webform module</a> sets a <code>$node</code> variable which may be very useful.</p>
<p>Other modules may also add or modify theme variables by implementing a <code>MODULENAME_preprocess_htmlmail()</code> <a href="http://api.drupal.org/api/drupal/modules--system--theme.api.php/function/hook_preprocess_HOOK/7">hook function</a>.</p>'
      // End instructions.
    ),
  );
  $form['htmlmail_theme'] = array(
    '#type' => 'select',
    '#title' => t('Theme to use for emails'),
    '#default_value' => variable_get('htmlmail_theme', ''),
    '#options' => htmlmail_get_allowed_themes(),
    '#description' => t(
      'You may use a template or a website theme to format your emails. See !readme for details.',
      array('!readme' => l('README.txt', drupal_get_path('module', 'htmlmail') . '/README.txt'))
    ),
  );
  $form['htmlmail_postfilter'] = array(
    '#type' => 'select',
    '#title' => t('Text format post-filter'),
    '#default_value' => variable_get('htmlmail_postfilter'),
    '#options' => $formats,
    '#description' => t('Choose a <a href="/admin/config/content/formats">text format</a> to be used for filtering email messages <em>after</em> the selected theme or template is applied.'),
  );
  $form['htmlmail_debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('Debug'),
    '#default_value' => variable_get('htmlmail_debug', '0'),
    '#description' => t('Add module name to bottom of email. Useful for theme template suggestion or exclusion settings.'),
  );
  return system_settings_form($form);
}

/**
 * Builds a form for setting Header, Footer, and CSS content to be included in
 * sent emails.
 */
function htmlmail_template_settings() {
  $defaults = array('value' => '', 'format' => filter_default_format());
  $header = variable_get('htmlmail_header', $defaults);
  $form['htmlmail_header'] = array(
    '#type' => 'text_format',
    '#title' => t('Header HTML'),
    '#rows' => 6,
    '#default_value' => $header['value'],
    '#format' => $header['format'],
    '#description' => 'Extra HTML markup to add at the top of emails.',
  );
  $footer = variable_get('htmlmail_footer', $defaults);
  $form['htmlmail_footer'] = array(
    '#type' => 'text_format',
    '#title' => t('Footer HTML'),
    '#rows' => 6,
    '#default_value' => $footer['value'],
    '#format' => $footer['format'],
    '#description' => 'Extra HTML markup to add at the bottom of emails.',
  );
  $form['htmlmail_css'] = array(
    '#type' => 'textarea',
    '#title' => t('CSS'),
    '#default_value' => variable_get('htmlmail_css', ''),
    '#description' => 'Extra CSS rules to be added to emails.',
  );
  return system_settings_form($form);
}

/**
 * Builds a form for sending a test message.
 */
function htmlmail_test_form($form_values = NULL) {
  // set up some defaults for test mail
  $defaults = variable_get(
    'htmlmail_test',
    array(
      'to' => variable_get('site_mail'),
      'subject' => 'test',
      'body' => array(
        'value' => 'test',
        'format' => filter_fallback_format(),
      ),
    )
  );

  $form['to'] = array(
    '#type' => 'textfield',
    '#title' => t('To'),
    '#default_value' => $defaults['to'],
    '#maxlength' => 128,
    '#required' => TRUE,
  );
  $form['subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#default_value' => $defaults['subject'],
    '#maxlength' => 128,
    '#required' => TRUE,
  );
  $form['body'] = array(
    '#type' => 'text_format',
    '#title' => t('Body'),
    '#rows' => 20,
    '#default_value' => $defaults['body']['value'],
    '#format' => $defaults['body']['format'],
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Send test message'),
  );
  return $form;
}

/**
 * Sends the test messsage and saves the contents for re-use.
 */
function htmlmail_test_form_submit($form, &$form_state) {
  // save form values
  $defaults = array(
    'to' => $form_state['values']['to'],
    'subject' => $form_state['values']['subject'],
    'body' => $form_state['values']['body'],
  );
  // set the defaults for reuse
  variable_set('htmlmail_test', $defaults);
  // send email
  $params = array(
    'subject' => $form_state['values']['subject'],
    'body' => check_markup($form_state['values']['body']['value'], $form_state['values']['body']['format']),
  );
  if (drupal_mail('htmlmail', 'test', $form_state['values']['to'], language_default(), $params)) {
    drupal_set_message(t('HTML Mail test message sent.'));
  }
}

/**
 * Displays the email message body passed via POST as a themed page.
 */
function htmlmail_show_email() {
  if ($css = variable_get('htmlmail_css', '')) {
    drupal_add_css($css, array('type' => 'inline'));
  }
  return isset($_POST['body']) ? $_POST['body'] : '(Empty)';
}

/**
 * Returns the email message subject passed via POST for a title callback.
 */
function htmlmail_get_post_subject($subject) {
  return check_plain(isset($_POST['subject']) ? $_POST['subject'] :  t($subject));
}
