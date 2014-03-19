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
   *   The instance identifier.
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
   * @param int $expire
   *   The expiration time for instances to be cleared.
   *
   */
  public function clearExpired($expire);


}