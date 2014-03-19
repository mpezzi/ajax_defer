<?php

/**
 * @file
 * Provides a session based storage object for saving defered instances.
 */

class AjaxDeferCacheStorage implements AjaxDeferStorageInterface {

  /**
   * The cache bin.
   *
   * @var string
   *
   */
  protected $bin = 'cache';

  /**
   * The cache key.
   *
   * @var string
   *
   */
  protected $key = 'ajax_defer_instance';

  /**
   * The user uid.
   *
   * @var int
   *
   */
  protected $uid = NULL;

  /**
   * Constructor
   *
   * @param int $uid (optional)
   *   The user uid.
   * @param string $bin (optional)
   *   The cache bin.
   *
   */
  public function __construct() {
    $this->uid = $GLOBALS['user']->uid;
  }

  /**
   * @copydoc AjaxDeferStorageInterface::get()
   *
   */
  public function get($id) {
    $cache = cache_get($this->getCacheId($id), $this->bin);
    return $cache ? $cache->data : NULL;
  }

  /**
   * @copydoc AjaxDeferStorageInterface::get()
   *
   */
  public function set($id, $data, $expire) {
    cache_set($this->getCacheId($id), $data, $this->bin, $expire);
  }

  /**
   * @copydoc AjaxDeferStorageInterface::clear()
   *
   */
  public function clear($id) {
    cache_clear_all($this->getCacheId($id), $this->bin);
  }

  /**
   * @copydoc AjaxDeferStorageInterface::expire()
   *
   */
  public function expire() {
    cache_clear_all($this->getCacheId(), $this->bin, TRUE);
  }

  /**
   * Returns a cache id.
   *
   * @param string $id
   *   The storage id.
   *
   * @return string
   *   The cache id.
   *
   */
  public function getCacheId($id = NULL) {
    return $this->key . ':' . $this->uid . ':' . $id;
  }

}
