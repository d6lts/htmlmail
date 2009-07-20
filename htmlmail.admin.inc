<?php
// $Id$

/**
 * @file
 * Admin forms for HTML Mail
 */

function htmlmail_admin_settings() {
  $form['htmlmail_autop'] = array(
    '#type' => 'checkbox',
    '#title' => t('Line break converter'),
    '#default_value' => variable_get('htmlmail_autop', '1'),
    '#description' => t('Converts line breaks into HTML (i.e. &lt;br&gt; and &lt;p&gt; tags).'),
  );
  $form['htmlmail_urlfilter'] = array(
    '#type' => 'checkbox',
    '#title' => t('URL Filter'),
    '#default_value' => variable_get('htmlmail_urlfilter', '1'),
    '#description' => t('Turns web and e-mail addresses into clickable links. URLs longer than 72 characters will be truncated.'),
  );
  $form['htmlmail_emogrifier'] = array(
    '#type' => 'checkbox',
    '#title' => t('Emogrifier'),
    '#default_value' => variable_get('htmlmail_emogrifier', '0'),
    '#description' => t('Insert your CSS definitions as inline styles into HTML tags for Outlook 2007 and Google Gmail.'),
    '#disabled' => !extension_loaded('dom'),
  );
  return system_settings_form($form);
}

function htmlmail_template_settings() {
  $form['htmlmail_template'] = array(
    '#type' => 'select',
    '#title' => t('Template'),
    '#default_value' => variable_get('htmlmail_template', ''),
    '#description' => t('Select from default or HTML Mail templates installed in the current themes\'s directory.'),
    '#options' => _htmlmail_get_templates(),
  );
  $form['htmlmail_header'] = array(
    '#type' => 'textarea',
    '#title' => t('Header HTML'),
    '#default_value' => variable_get('htmlmail_header', ''),
  );
  $form['htmlmail_footer'] = array(
    '#type' => 'textarea',
    '#title' => t('Footer HTML'),
    '#default_value' => variable_get('htmlmail_footer', ''),
  );
  $form['htmlmail_css'] = array(
    '#type' => 'textarea',
    '#title' => t('CSS'),
    '#default_value' => variable_get('htmlmail_css', ''),
  );
  return system_settings_form($form);
}

function htmlmail_test_form($form_values = NULL) {
  $defaults = variable_get('htmlmail_test', array());
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
    '#type' => 'textarea',
    '#title' => t('Body'),
    '#rows' => 20,
    '#default_value' => $defaults['body'],
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  return $form;
}

function htmlmail_test_form_submit($form, &$form_state) {
  // Save form values
  $defaults = array(
    'to' => $form_state['values']['to'],
    'subject' => $form_state['values']['subject'],
    'body' => $form_state['values']['body'],
  );
  variable_set('htmlmail_test', $defaults);
  // Send email
  $params = array(
    'subject' => $form_state['values']['subject'],
    'body' => $form_state['values']['body'],
  );
  if (drupal_mail('htmlmail', 'htmlmail_test', $form_state['values']['to'], language_default(), $params)) {
    drupal_set_message(t('HTML Mail test message sent.'));
  }
}

