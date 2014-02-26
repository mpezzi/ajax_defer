<?php

/**
 * @file
 * Provides session instance interface.
 */

class AjaxDeferSessionInstanceManager implements AjaxDeferInstanceManagerInterface {

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
   * @copydoc AjaxDeferInstanceManagerInterface::get()
   *
   */
  public function get($id) {
    return isset($_SESSION[$this->session_key][$id]) ? $_SESSION[$this->session_key][$id] : FALSE;
  }

  /**
   * @copydoc AjaxDeferInstanceManagerInterface::getAll()
   *
   */
  public function getAll() {
    return isset($_SESSION[$this->session_key]) ? $_SESSION[$this->session_key] : array();
  }

  /**
   * @copydoc AjaxDeferInstanceManagerInterface::set()
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
   * @copydoc AjaxDeferInstanceManagerInterface::clear()
   *
   */
  public function clear($id) {
    unset($_SESSION[$this->session_key][$id]);
  }

  /**
   * @copydoc AjaxDeferInstanceManagerInterface::clear()
   *
   */
  public function clearExpired($expire = NULL) {
    if (!$expire) {
      $expire = $this->expire;
    }
    foreach ($this->getAll() as $id => $instance) {
      if ($instance->created < REQUEST_TIME - $expire) {
        $this->clear($id);
      }
    }
  }

}
