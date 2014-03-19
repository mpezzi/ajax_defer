<?php

/**
 * @file
 * Provides ajax functionality for ajax_defer.module
 */

/**
 * Force a reload of the current page.
 */
function ajax_defer_command_reload() {
  drupal_add_js(drupal_get_path('module', 'ajax_defer') . '/js/ajax.js');
  return array(
    'command' => 'ajax_defer_reload',
  );
}
