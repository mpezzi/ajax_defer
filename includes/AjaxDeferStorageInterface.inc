<?php

/**
 * @file
 * Provides a storage interface for storage defered instances.
 */

interface AjaxDeferStorageInterface {

  /**
   * Retrieves an instance.
   *
   * @param string $id
   *   The id of the data to store.
   *
   * @return array
   *   An instance array.
   *
   */
  public function get($id);

  /**
   * Retrieves an instance.
   *
   * @param string $id
   *   The id of the data to store.
   * @param mixed $data
   *   The instance data.
   * @param int $expire
   *   A UNIX timestamp indicating when to store until.
   *
   * @return array
   *   An instance array.
   *
   */
  public function set($id, $data, $expire);

  /**
   * Clears an instance.
   *
   * @param string $id
   *   The instance identifier.
   *
   */
  public function clear($id);

  /**
   * Expire instances.
   *
   */
  public function expire();


}