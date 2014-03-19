<?php

/**
 * @file
 * Provides a session based storage object for saving defered instances.
 */

class AjaxDeferSessionStorage implements AjaxDeferStorageInterface {

  /**
   * The session key.
   *
   * @var string
   *
   */
  protected $key = 'ajax_defer_instance';

  /**
   * @copydoc AjaxDeferStorageInterface::get()
   *
   */
  public function get($id) {
    if (isset($_SESSION[$this->key][$id])) {
      return $_SESSION[$this->key][$id]->data;
    }
    return FALSE;
  }

  /**
   * @copydoc AjaxDeferStorageInterface::set()
   *
   */
  public function set($id, $data, $expire) {
    $_SESSION[$this->key][$id] = (object) array(
      'id' => $id,
      'created' => REQUEST_TIME,
      'expire' => $expire,
      'data' => $data,
    );
  }

  /**
   * @copydoc AjaxDeferStorageInterface::clear()
   *
   */
  public function clear($id) {
    unset($_SESSION[$this->key][$id]);
  }

  /**
   * @copydoc AjaxDeferStorageInterface::expire()
   *
   */
  public function expire() {
    $instances = isset($_SESSION[$this->key]) ? $_SESSION[$this->key] : array();
    foreach ($instances as $id => $instance) {
      if (REQUEST_TIME > $instance->expire) {
        $this->clear($id);
      }
    }
  }

}
