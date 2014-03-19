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
  protected $session_key = 'ajax_defer_instance';

  /**
   * The expire time.
   *
   * @var int
   *
   */
  protected $expire = 3600;

  /**
   * @copydoc AjaxDeferStorageInterface::get()
   *
   */
  public function get($id) {
    return isset($_SESSION[$this->session_key][$id]) ? $_SESSION[$this->session_key][$id] : FALSE;
  }

  /**
   * @copydoc AjaxDeferStorageInterface::set()
   *
   */
  public function set($id, $data) {
    $_SESSION[$this->session_key][$id] = (object) array(
      'id' => $id,
      'created' => REQUEST_TIME,
      'data' => $data,
    );
  }

  /**
   * @copydoc AjaxDeferStorageInterface::clear()
   *
   */
  public function clear($id) {
    unset($_SESSION[$this->session_key][$id]);
  }

  /**
   * @copydoc AjaxDeferStorageInterface::clearExpired()
   *
   */
  public function clearExpired($expire = NULL) {
    if (!$expire) {
      $expire = $this->expire;
    }

    $instances = isset($_SESSION[$this->session_key]) ? $_SESSION[$this->session_key] : array();

    foreach ($instances as $id => $instance) {
      if ($instance->created < REQUEST_TIME - $expire) {
        $this->clear($id);
      }
    }
  }

}
