(function ($){

/**
 * Provides ajax defer instance behavior.
 */
Drupal.behaviors.AjaxDeferInstance = {
  attach: function (context, settings) {
    $('body', context).once('ajax-defer-instance', function(){

      var instances = settings.ajax_defer.instances || {}, instance,
          callbacks = {}, callback, url, id;

      // Collect required callbacks.
      for (i in instances) {
        if ($('.ajax-defer-instance[data-instance="' + i + '"]', context).length > 0) {
          instance = instances[i];
          if (typeof callbacks[instance.path] == 'undefined') {
            callbacks[instance.path] = {};
          }
          if (typeof callbacks[instance.path][instance.group] == 'undefined') {
            callbacks[instance.path][instance.group] = { instances: [], delay: 0 };
          }
          callbacks[instance.path][instance.group].instances.push(i);
          callbacks[instance.path][instance.group].delay = instance.delay;
        }
      }

      // Collect all instances for each defined path and group.
      for (path in callbacks) {
        for (group in callbacks[path]) {
          params = $.deparam.querystring();
          params.instances = callbacks[path][group].instances;
          id = callbacks[path][group].instances.join('-');
          url = $.param.querystring(path, params);
          Drupal.AjaxDefer.ajaxTrigger(id, url, callbacks[path][group].delay);
        }
      }

    });
  }
};

/**
 * Provides Ajax Defer container object.
 */
Drupal.AjaxDefer = Drupal.AjaxDefer || {};

/**
 * Provides Ajax Defer ajaxTrigger method.
 */
Drupal.AjaxDefer.ajaxTrigger = function(id, url, delay) {
  setTimeout(function(){
    var $this = $('<a id="' + id + '" href="' + url + '"></a>');
    var element_settings = {};
    if ($this.attr('href')) {
      element_settings.url = $this.attr('href');
      element_settings.event = 'click';
      element_settings.progress = { type: 'none' };
    }
    Drupal.ajax[id] = new Drupal.ajax(id, $this, element_settings);
    $this.trigger('click');
  }, delay || 0);
};

})(jQuery);