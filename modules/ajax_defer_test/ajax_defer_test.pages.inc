<?php

/**
 * @file
 * Provides pages for ajax_defer_test.module
 */

/**
 * Page callback; Single defer element.
 */
function ajax_defer_test_single() {

  $data = array(
    'items' => array('one', 'two', 'three', 'four'),
  );

  $build = array();
  $build['single'] = array(
    '#type' => 'ajax_defer',
    '#ajax_defer' => array(
      'callback' => 'ajax_defer_test_single_defer',
      'data' => $data,
      // @todo: way to set module automagically?
      'module' => 'ajax_defer_test',
      'file' => 'ajax_defer_test.pages.inc',
    ),
  );
  $build['single']['content'] = array(
    '#theme' => 'item_list',
    '#type' => 'ol',
    '#items' => $data['items'],
  );

  return $build;

}

/**
 * Deferred callback; Single defer element.
 */
function ajax_defer_test_single_defer($element, $data) {

  // Change the ol to a ul!
  $element['content']['#type'] = 'ul';

  return $element;

}

/**
 * Page callback; Multi defer element.
 */
function ajax_defer_test_multi() {

  $build = array();
  $data  = array('created' => REQUEST_TIME);

  $build['multi1'] = array(
    '#type' => 'ajax_defer',
    '#ajax_defer' => array(
      'callback' => 'ajax_defer_test_multi1_defer',
      'data' => $data,
      // @todo: way to set module automagically?
      'module' => 'ajax_defer_test',
      'file' => 'ajax_defer_test.pages.inc',
    ),
  );
  $build['multi1']['time1'] = array(
    '#prefix' => '<p>',
    '#suffix' => '</p>',
    '#markup' => t('This time (@time) is awesome!', array('@time' => format_date($data['created']))),
  );

  $build['multi2'] = array(
    '#type' => 'ajax_defer',
    '#ajax_defer' => array(
      'callback' => 'ajax_defer_test_multi2_defer',
      'data' => $data,
      // @todo: way to set module automagically?
      'module' => 'ajax_defer_test',
      'file' => 'ajax_defer_test.pages.inc',
    ),
  );
  $build['multi2']['time2'] = array(
    '#prefix' => '<p>',
    '#suffix' => '</p>',
    '#markup' => t('This time (@time) is also awesome!', array('@time' => format_date($data['created']))),
  );

  $build['multi3'] = array(
    '#type' => 'ajax_defer',
    '#ajax_defer' => array(
      'callback' => 'ajax_defer_test_multi3_defer',
      'data' => $data,
      // @todo: way to set module automagically?
      'module' => 'ajax_defer_test',
      'file' => 'ajax_defer_test.pages.inc',
      'group' => 'different',
      'delay' => 5000,
    ),
  );
  $build['multi3']['time3'] = array(
    '#prefix' => '<p>',
    '#suffix' => '</p>',
    '#markup' => t('This time (@time) is also again awesome!', array('@time' => format_date($data['created']))),
  );

  return $build;

}

/**
 * Deferred callback; Multi defer element.
 */
function ajax_defer_test_multi1_defer($element, $data) {

  // Change the markup, but keep the same time as the original callback!
  $element['time1']['#markup'] = t('This time (@time) was awesome!', array('@time' => format_date($data['created'])));

  return $element;

}

/**
 * Deferred callback; Multi defer element.
 */
function ajax_defer_test_multi2_defer($element, $data) {

  // Change the markup, but keep the same time as the original callback!
  $element['time2']['#markup'] = t('This time (@time) was also awesome!', array('@time' => format_date($data['created'])));

  return $element;

}

/**
 * Deferred callback; Multi defer element.
 */
function ajax_defer_test_multi3_defer($element, $data) {

  // Change the markup, but keep the same time as the original callback!
  $element['time3']['#markup'] = t('This time (@time) was also again awesome!', array('@time' => format_date($data['created'])));

  return $element;

}
