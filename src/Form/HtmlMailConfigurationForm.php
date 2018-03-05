<?php

namespace Drupal\htmlmail\Form;

use Drupal\Core\Config\ConfigFactoryInterface;
use Drupal\Core\Extension\ModuleHandlerInterface;
use Drupal\Core\Form\ConfigFormBase;
use Drupal\Core\Form\FormStateInterface;
use Symfony\Component\DependencyInjection\ContainerInterface;
use Drupal\htmlmail\Helper\HtmlMailHelper;

/**
 * Class HtmlMailConfigurationForm.
 *
 * @package Drupal\htmlmail\Form
 */
class HtmlMailConfigurationForm extends ConfigFormBase {

  protected $moduleHandler;
  protected $helperHandler;

  /**
   * Gets the configuration names that will be editable.
   *
   * @return array
   *   An array of configuration object names that are editable if called in
   *   conjunction with the trait's config() method.
   */
  protected function getEditableConfigNames() {
    return [
      'htmlmail.settings',
    ];
  }

  /**
   * Returns a unique string identifying the form.
   *
   * @return string
   *   The unique string identifying the form.
   */
  public function getFormId() {
    return 'htmlmail_general';
  }

  /**
   * Retrieves the filter format list.
   *
   * @return array
   *   An array with all filter formats from current user.
   */
  protected function getFilterFormatsList() {
    $formats = ['0' => $this->t('Unfiltered')];

    $filter_formats = filter_formats($this->currentUser());
    foreach ($filter_formats as $id => $format) {
      $formats[$id] = $format->label();
    }

    return $formats;
  }

  /**
   * Defines the settings form for HTML Mail.
   *
   * @param array $form
   *   An associative array containing the structure of the form.
   * @param \Drupal\Core\Form\FormStateInterface $form_state
   *   The current state of the form.
   *
   * @return array
   *   Form definition array.
   */
  public function buildForm(array $form, FormStateInterface $form_state) {

    $config = $this->config('htmlmail.settings');

    $form['template'] = [
      '#type' => 'fieldset',
      '#title' => $this->t('Step 1'),
    ];

    $form['template']['htmlmail_template'] = [
      '#type' => 'details',
      '#prefix' => '<strong>' . $this->t('Template file:') . '</strong><br />'
      . $this->t('TBD.'),
      '#title' => $this->t('Instructions'),
      '#open' => FALSE,
    ];

    $form['template']['htmlmail_template']['instructions'] = [
      '#type' => 'item',
      '#suffix' => $this->t('TBD'),
    ];

    $form['template']['htmlmail_debug'] = [
      '#type' => 'checkbox',
      '#prefix' => '<br />',
      '#title' => '<em>' . $this->t('(Optional)') . '</em> ' . $this->t('Debug'),
      '#default_value' => $config->get('htmlmail_debug', '0'),
      '#description' => $this->t('Add debugging info (Set <code>$debug</code> to <code>TRUE</code>).'),
    ];

    $form['theme'] = [
      '#type' => 'fieldset',
      '#title' => $this->t('Step 2'),
    ];

    $form['theme']['htmlmail_theme'] = [
      '#type' => 'select',
      '#title' => $this->t('Email theme'),
      '#default_value' => $config->get('htmlmail_theme', ''),
      '#options' => $this->helperHandler->getAllowedThemes(),
      '#suffix' => '<p>'
      . $this->t('Choose the theme that will hold your customized templates from Step 1 above.')
      . '</p>',
    ];

    $form['filter'] = [
      '#type' => 'fieldset',
      '#title' => $this->t('Step 3'),
    ];

    if (!$this->moduleHandler->moduleExists('mailmime')) {
      $form['filter']['htmlmail_html_with_plain'] = [
        '#type' => 'checkbox',
        '#title' => $this->t('Provide simple plain/text alternative of the HTML mail.'),
        '#default_value' => $config->get('htmlmail_html_with_plain', FALSE),
        '#description' => $this->t('This may increase the quality of your outgoing emails for the spam filters.'),
      ];
    }

    $form['filter']['htmlmail_postfilter'] = [
      '#type' => 'select',
      '#title' => $this->t('Post-filtering'),
      '#default_value' => $config->get('htmlmail_postfilter', ''),
      '#options' => $this->getFilterFormatsList(),
      '#suffix' => '<p>'
      . $this->t('You may choose a <a href=":formats">text format</a> to be used for filtering email messages <em>after</em> theming.  This allows you to use any combination of <a href=":filters">over 200 filter modules</a> to make final changes to your message before sending.',
          [
            ':formats' => '/admin/config/content/formats',
            ':filters' => 'https://www.drupal.org/project/modules/?filters=type%3Aproject_project%20tid%3A63%20hash%3A1hbejm%20-bs_project_sandbox%3A1%20bs_project_has_releases%3A1',
          ]
      )
      . '</p>',
    ];

    return parent::buildForm($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function submitForm(array &$form, FormStateInterface $form_state) {

    $this->configFactory->getEditable('htmlmail.settings')
      // Set the submitted configuration setting.
      ->set('htmlmail_debug', $form_state->getValue('htmlmail_debug'))
      ->set('htmlmail_theme', $form_state->getValue('htmlmail_theme'))
      ->set('htmlmail_html_with_plain', $form_state->getValue('htmlmail_html_with_plain'))
      ->set('htmlmail_postfilter', $form_state->getValue('htmlmail_postfilter'))
      ->save();

    parent::submitForm($form, $form_state);
  }

  /**
   * HtmlMailConfigurationForm constructor.
   *
   * @param \Drupal\Core\Config\ConfigFactoryInterface $config_factory
   *   Config factory service, injected into constructor.
   * @param \Drupal\Core\Extension\ModuleHandlerInterface $moduleHandler
   *   Module Handler service, injected into constructor.
   */
  public function __construct(ConfigFactoryInterface $config_factory, ModuleHandlerInterface $moduleHandler) {
    parent::__construct($config_factory);
    $this->moduleHandler = $moduleHandler;
    $this->helperHandler = new HtmlMailHelper();
  }

  /**
   * {@inheritdoc}
   */
  public static function create(ContainerInterface $container) {
    return new static (
      $container->get('config.factory'),
      $container->get('module_handler')
    );
  }

}
