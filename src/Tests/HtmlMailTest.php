<?php

namespace Drupal\htmlmail\Tests;

/**
 * @file
 * Tests for the HTML Mail module.
 */

use Drupal\simpletest\WebTestBase;

/**
 * Test case for the HTML Mail module.
 */
class HTMLMailTest extends WebTestBase {

  /**
   * Modules to install.
   *
   * @var array
   */
  public static $modules = ['htmlmail'];

  /**
   * Implements getInfo().
   */
  public static function getInfo() {
    return [
      'name' => 'HTML Mail hello',
      'description' => 'Dummy test to satisfy DrupalCI.',
      'group' => 'HTML Mail',
    ];
  }

  /**
   * Implements setUp().
   */
  public function setUp() {
    parent::setUp();
  }

  /**
   * Just an empty test.
   */
  public function testHello() {
  }

}
