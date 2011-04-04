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
'<p>When formatting an email message, Drupal determines the active template directory by looking for <code>htmlmail.tpl.php</code> file in the following locations:</p>
<ul>
  <li><a href="http://api.drupal.org/api/drupal/includes--theme.inc/function/path_to_theme/6">path_to_theme()</a></li>
  <li><a href="http://api.drupal.org/api/drupal/includes--common.inc/function/drupal_get_path/6">drupal_get_path(</a>"module", <a href="http://api.drupal.org/api/drupal/developer--globals.php/global/installed_profile/6">$installed_profile</a>)</li>
  <li><a href="http://api.drupal.org/api/drupal/includes--common.inc/function/drupal_get_path/6">drupal_get_path(</a>"module", <a href="http://drupal.org/project/htmlmail">"htmlmail"</a>)</li>
</ul>
<p>Once the active template directory is found, Drupal looks in that directory for template files in order from most specific to most general.</p>
<p>For example, if <code>example\_module</code> sends mail with:</p>
<p><code>drupal\_mail("example\_module", "outgoing\_message" ...)</code></p>
<p>the possible template file names would be:</p>
<ul>
  <li><code>htmlmail-example\_module\_outgoing\_message.tpl.php</code></li>
  <li><code>htmlmail-example\_module\_outgoing.tpl.php</code></li>
  <li><code>htmlmail-example\_module.tpl.php</code></li>
  <li><code>htmlmail.tpl.php</code></li>
</ul>
<p>The <code>$template\_files</code> variable contains an array of suggested <a href="http://api.drupal.org/api/drupal/includes--theme.inc/function/theme/6">theme</a> <a href="http://api.drupal.org/api/drupal/developer--hooks--core.php/function/hook_theme/6">hooks</a>, in reverse priority order. For the above example, it would contain:</p>
<ul>
  <li><code>htmlmail</code></li>
  <li><code>htmlmail-example\_module</code></li>
  <li><code>htmlmail-example\_module\_outgoing</code></li>
  <li><code>htmlmail-example\_module\_outgoing\_message</code></li>
</ul>
<p>For another example, to customize the <a href="http://api.drupal.org/api/drupal/modules--user--user.pages.inc/function/user_pass_submit/6">password reset</a> emails sent by the <a href="http://api.drupal.org/api/drupal/modules--user--user.module/6">user module</a>, copy <code>htmlmail.tpl.php</code> to your theme directory, and also copy it to <code>htmlmail-user\_password\_reset.tpl.php</code>, then modify the latter file. Remember that you will need to put <em>both</em> files in your theme directory for this to work.</p>
<p>Template files are cached, so remember to clear the cache by visiting <em>admin/settings/performance</em> after creating, copying, or editing any <code>.tpl.php</code> files.</p>
<p>The following variables are also available in this template:</p>
<dl>
  <dt><code>$body</code></dt>
  <dd>
    <p>The message body text.</p>
  </dd>
  <dt><code>$module</code></dt>
  <dd>
    <p>The sending module name, usually the first parameter to drupal_mail().</p>
  </dd>
  <dt><code>$key</code></dt>
  <dd>
    <p>The message key, usually the second parameter to drupal_mail().</p>
  </dd>
  <dt><code>\$message\_id</code></dt>
  <dd>
    <p>The email message id, usually "{$module}_{$key}".</p>
  </dd>
  <dt><code>$debug</code></dt>
  <dd>
    <p>TRUE if debugging info should be printed.</p>
  </dd>
  <dt><code>$directory</code></dt>
  <dd>
    <p>The relative path to the theme template directory.</p>
  </dd>
  <dt><code>$theme\_url</code></dt>
  <dd>
    <p>The absolute URL to the theme directory.</p>
  </dd>
</dl>
<p>The module calling <a href="http://api.drupal.org/api/drupal/includes--mail.inc/function/drupal_mail/6">drupal_mail()</a> may set other variables. For instance, the <a href="http://drupal.org/project/webform">Webform module</a> sets a <code>$node</code> variable which may be very useful.</p>
<p>Other modules may also add or modify theme variables by implementing a <code>MODULENAME\_preprocess\_htmlmail()</code> hook function.</p>'
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
    '#description' => t('Add debugging info to email.'),
  );
  return system_settings_form($form);
}

/**
 * Builds a form for sending a test message.
 */
function htmlmail_test_form($form_values = NULL) {
  $defaults = variable_get(
    'htmlmail_test',
    array(
      'to' => variable_get('site_mail'),
      'subject' => 'test',
      'body' => array(
        'value' => 'test',
      ),
    )
  );

  // Set the input format to be the same as the selected prefilter format.
  $defaults['body']['format'] = 
    variable_get('htmlmail_prefilter', filter_fallback_format());

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
  // Get the form values.
  $defaults = array(
    'to' => $form_state['values']['to'],
    'subject' => $form_state['values']['subject'],
    'body' => $form_state['values']['body'],
  );
  // Set the defaults for reuse.
  variable_set('htmlmail_test', $defaults);
  // @todo Get user feedback on this UI change?
  variable_set('htmlmail_prefilter', $defaults['body']['format']);
  // Send the email.
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
