<?php

/**
 * @file
 * Provides instance interface.
 */

interface AjaxDeferInstanceManagerInterface {

  /**
   * Retrieves an instance.
   *
   * @param string $id
   *   The instance identifier.
   *
   * @return array
   *   An instance array.
   *
   */
  public function get($id);

  /**
   * Retrieves all instances.
   *
   * @return array
   *   An array of instances.
   *
   */
  public function getAll();

  /**
   * Retrieves an instance.
   *
   * @param string $id
   *   The instance identifier.
   * @param mixed $data
   *   The instance data.
   *
   * @return array
   *   An instance array.
   *
   */
  public function set($id, $data);

  /**
   * Clears an instance.
   *
   * @param string $id
   *   The instance identifier.
   *
   */
  public function clear($id);

  /**
   * Clears expired instances.
   *
   */
  public function clearExpired();


}