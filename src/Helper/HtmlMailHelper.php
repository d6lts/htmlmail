<?php

namespace Drupal\htmlmail\Helper;

use Drupal\Component\Utility\Html;

/**
 * Class HtmlMailHelper.
 *
 * @package Drupal\htmlmail\Helper
 */
class HtmlMailHelper {

  /**
   * Returns an associative array of allowed themes.
   *
   * Based on code from the og_theme module.
   *
   * @return array
   *   The keys are the machine-readable names and the values are the .info file
   *   names.
   */
  public function &getAllowedThemes() {
    $allowed = &drupal_static(__FUNCTION__);

    if (!isset($allowed)) {
      $allowed = ['' => t('No theme')];
      $themes = \Drupal::service('theme_handler')->listInfo();
      uasort($themes, 'system_sort_modules_by_info_name');
      foreach ($themes as $key => $value) {
        if ($value->status) {
          $allowed[$key] = Html::escape($value->info['name']);
        }
      }
    }
    return $allowed;
  }

}
