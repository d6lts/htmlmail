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
  $form['Step 1'] = array(
    '#type' => 'fieldset',
    '#title' => '<h3>' . t('Step 1') . '</h3>',
    '#collapsible' => FALSE,
  );
  $form['Step 1']['htmlmail_template'] = array(
    '#type' => 'fieldset',
    '#prefix' => '<strong>' . t('Template file:') . '</strong><br />'
    . t(
      'A template file is applied to your message header, subject, and body '
      . 'text.  You may copy the <a href="!uri">!template</a> file to your '
      . 'default theme directory and use it to customize your messages.',
      array(
        '!uri' => url('http://drupalcode.org/project/htmlmail.git/blob/refs/heads/6.x-2.x:/htmlmail.tpl.php'),
        '!template' => '<code>htmlmail.tpl.php</code>'
      )
    ),
    '#title' => t('Instructions'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['Step 1']['htmlmail_template']['instructions'] = array(
    '#type' => 'item',
    '#suffix' => t(
      // Begin instructions.
'<p>When formatting an email message, Drupal determines the active template directory by looking for <code>htmlmail.tpl.php</code> file in the following locations:</p>
<ul>
  <li><a href="http://api.drupal.org/api/drupal/includes--theme.inc/function/path_to_theme/6"><code>path_to_theme()</code></a></li>
  <li><a href="http://api.drupal.org/api/drupal/includes--common.inc/function/drupal_get_path/6"><code>drupal_get_path(</code></a>"module", <a href="http://api.drupal.org/api/drupal/developer--globals.php/global/installed_profile/6">$installed_profile</a>)</li>
  <li><a href="http://api.drupal.org/api/drupal/includes--common.inc/function/drupal_get_path/6"><code>drupal_get_path(</code></a>"module", <a href="http://drupal.org/project/htmlmail">"htmlmail"</a>)</li>
</ul>
<p>Once the active template directory is found, Drupal looks in that directory for template files in order from most specific to most general.</p>
<p>For example, if <code>example_module</code> sends mail with:</p>
<pre>
<code>drupal_mail("example_module", "outgoing_message" ...)
</code>
</pre>
<p>the possible template file names would be:</p>
<ul>
  <li><code>htmlmail-example_module_outgoing_message.tpl.php</code></li>
  <li><code>htmlmail-example_module_outgoing.tpl.php</code></li>
  <li><code>htmlmail-example_module.tpl.php</code></li>
  <li><code>htmlmail.tpl.php</code></li>
</ul>
<p>The <code>$theme_hook_suggestions</code> variable contains an array of suggested <a href="http://api.drupal.org/api/drupal/includes--theme.inc/function/theme/6">theme</a> <a href="http://api.drupal.org/api/drupal/developer--hooks--core.php/function/hook_theme/6">hooks</a>, in reverse priority order. For the above example, it would contain:</p>
<ul>
  <li><code>htmlmail</code></li>
  <li><code>htmlmail-example_module</code></li>
  <li><code>htmlmail-example_module_outgoing</code></li>
  <li><code>htmlmail-example_module_outgoing_message</code></li>
</ul>
<p>For another example, to customize the <a href="http://api.drupal.org/api/drupal/modules--user--user.pages.inc/function/user_pass_submit/6">password reset</a> messages sent by the <a href="http://api.drupal.org/api/drupal/modules--user--user.module/6">user module</a>, copy <code>htmlmail.tpl.php</code> to your theme directory, and also copy it to <code>htmlmail-user_password_reset.tpl.php</code>, then modify the latter file. Remember that you will need to put <em>both</em> files in your theme directory for this to work.</p>
<p>Template files are cached, so remember to clear the cache by visiting <u>admin/settings/performance</u> after creating, copying, or editing any <code>.tpl.php</code> files.</p>
<p>The following variables are also available in this template:</p>
<dl>
  <dt><strong><code>$body</code></strong></dt>
  <dd>
    <p>The message body text.</p>
  </dd>
  <dt><strong><code>$module</code></strong></dt>
  <dd>The sending module name, usually the first parameter to</dd>
</dl>
<p><a href="http://api.drupal.org/api/drupal/includes--mail.inc/function/drupal_mail/6"><code>drupal_mail()</code></a>.</p>
<dl>
  <dt><strong><code>$key</code></strong></dt>
  <dd>The message key, usually the second parameter to</dd>
</dl>
<p><a href="http://api.drupal.org/api/drupal/includes--mail.inc/function/drupal_mail/6"><code>drupal_mail()</code></a>.</p>
<dl>
  <dt><strong><code>$id</code></strong></dt>
  <dd>
    <p>The email message id, usually <code>"{$module}_{$key}"</code>.</p>
  </dd>
  <dt><strong><code>$theme</code></strong></dt>
  <dd>
    <p>The name of the email-specific theme used to embed the message body into a fully-themed webpage.</p>
    <p><strong>Note:</strong> This may be different from the default website theme. Theme suggestion templates such as <code>html.tpl.php</code> should be copied to the <em>website theme directory</em>, not the <em>email theme directory</em>.</p>
  </dd>
  <dt><strong><code>$directory</code></strong></dt>
  <dd>
    <p>The relative path to the website theme template directory.</p>
  </dd>
  <dt><strong><code>$theme_url</code></strong></dt>
  <dd>
    <p>The absolute URL to the website theme directory.</p>
  </dd>
  <dt><strong><code>$debug</code></strong></dt>
  <dd>
    <p><code>TRUE</code> if debugging info should be printed.</p>
  </dd>
</dl>
<p>The module calling <a href="http://api.drupal.org/api/drupal/includes--mail.inc/function/drupal_mail/6"><code>drupal_mail()</code></a> may set other variables. For instance, the <a href="http://drupal.org/project/webform">Webform module</a> sets a <code>$node</code> variable which may be very useful.</p>
<p>Other modules may also add or modify theme variables by implementing a <code>MODULENAME_preprocess_htmlmail(&amp;$variables)</code> hook function.</p>'
      // End instructions.
    ),
  );
  $form['Step 1']['htmlmail_debug'] = array(
    '#type' => 'checkbox',
    '#prefix' => '<br />',
    '#title' => '<em>' . t('(Optional)') . '</em> ' . t('Debug'),
    '#default_value' => variable_get('htmlmail_debug', '0'),
    '#description' => t('Add debugging info.'),
  );
  $form['Step 2'] = array(
    '#type' => 'fieldset',
    '#title' => '<h3>' . t('Step 2') . '</h3>',
    '#collapsible' => FALSE,
  );
  $form['Step 2']['htmlmail_theme'] = array(
    '#type' => 'select',
    '#title' => t('Theming'),
    '#default_value' => variable_get('htmlmail_theme', ''),
    '#options' => htmlmail_get_allowed_themes(),
    '#disabled' => !module_exists('echo'),
    '#prefix' => module_exists('echo') ? '': '<em>' . t(
      'Disabled: requires the <a href="!echo">Echo</a> module.',
      array('!echo' => url('http://drupal.org/project/echo'))
    ) . '</em>',
    '#suffix' => t(
      'The templated text may be wrapped in a website theme.  This lets you '
      . 'use any one of <a href="%themes">over 800</a> themes to style your '
      . 'messages.  Creating an email-specific sub-theme lets you use the full '
      . 'power of the <a href="%theme_system">drupal theme system</a> to '
      . 'format your messages.',
      array(
        '%themes' => 'http://drupal.org/project/themes',
        '%theme_system' => 'http://drupal.org/documentation/theme',
      )
    ),
  );
  $form['Step 3'] = array(
    '#type' => 'fieldset',
    '#title' => '<h3>' . t('Step 3') . '</h3>',
    '#collapsible' => FALSE,
  );
  $form['Step 3']['htmlmail_postfilter'] = array(
    '#type' => 'select',
    '#title' => t('Post-filtering'),
    '#default_value' => variable_get('htmlmail_postfilter', ''),
    '#options' => $formats,
    '#suffix' => '<p>' . t(
      'You may choose a <a href="!formats">input format</a> to be used for '
      . 'filtering email messages <em>after</em> theming.  This allows you to '
      . 'use any combination of <a href="!filters">over 200 filter modules</a> '
      . 'to make final changes to your message before sending.',
      array(
        '!formats' => url('admin/settings/filters'),
        '!filters' => url('http://drupal.org/project/modules/?filters=type%3Aproject_project%20tid%3A63%20hash%3A1hbejm%20-bs_project_sandbox%3A1%20bs_project_has_releases%3A1'),
      )
    ) . '</p><p>' . t(
      'Here is a recommended configuration:'
    ) . '</p><ul><li><dl><dt>' . t(
      '<a href="!emogrifier">Emogrifier</a>',
      array('!emogrifier' => url('http://drupal.org/project/emogrifier'))
    ) . '</dt><dd>' . t(
      'Converts stylesheets to inline style rules for consistent display on '
      . 'mobile devices and webmail.'
    ) . '</dd></dl></li><li><dl><dt>' . t(
      '<a href="!transliteration">Transliteration</a>',
      array('!transliteration' => url('http;//drupal.org/project/filter_transliteration'))
    ) . '</dt><dd>' . t(
      'Converts non-ASCII text to US-ASCII equivalents. This helps prevent '
      . 'Microsoft <q>smart-quotes</q> from appearing as question-marks in '
      . 'Mozilla Thunderbird.'
    ) . '</dd></dl></li><li><dl><dt>' . t(
      '<a href="!pathologic">Pathologic</a>',
      array('!pathologic' => url('http://drupal.org/project/pathologic'))
    ) . '</dt><dd>' . t(
      'Converts relative URLS to absolute URLS so that clickable links in your '
      . 'message will work as intended.'
    ) . '</dd></dl></ul>'
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
      'to' => variable_get('site_mail', 'user@example.com'),
      'subject' => 'test',
      'body' => array(
        'value' => 'test',
      ),
    )
  );

  // Set the input format to be the same as the selected prefilter format.
  $defaults['body']['format'] =
    variable_get('htmlmail_prefilter', FILTER_FORMAT_DEFAULT);

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
    '#type' => 'item',
    '#tree' => TRUE,
    'value' => array(
      '#type' => 'textarea',
      '#title' => t('Body'),
      '#rows' => 20,
      '#default_value' => $defaults['body']['value'],
      '#required' => TRUE,
    ),
    'format' => filter_form(
      $defaults['body']['format'], NULL,
      array('body', 'format')
    ),
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
    'body' => check_markup(
      $form_state['values']['body']['value'],
      $form_state['values']['body']['format']
    ),
  );
  if (
    drupal_mail(
      'htmlmail',
      'test',
      $form_state['values']['to'],
      language_default(),
      $params
    )
  ) {
    drupal_set_message(t('HTML Mail test message sent.'));
  }
}
