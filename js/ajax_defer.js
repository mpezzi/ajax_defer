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
          id = callbacks[path][group].instances.join('-');
          url = $.param.querystring(path, { instances: callbacks[path][group].instances });
          Drupal.AjaxDefer.ajaxTrigger(id, url, callbacks[path][group].delay);
        }
      }

    });
  }
};

/**
 * Provides custom method to trigger ajax response.
 */
Drupal.ajax.prototype.ajaxDeferTrigger = function() {
  if (this.ajaxing) {
    return false;
  }

  try {
    $.ajax(this.options);
  }
  catch (err) {
    if (console && console.log) {
      console.log('An error occurred while attempting to process ' + this.options.url);
    }
  }

  return false;
};

/**
 * Provides Ajax Defer container object.
 */
Drupal.AjaxDefer = Drupal.AjaxDefer || {};

/**
 * Provides Ajax Defer ajaxTrigger method.
 */
Drupal.AjaxDefer.ajaxTrigger = function(id, url, delay) {

  Drupal.ajax[id] = new Drupal.ajax(null, $(document.body), {
    url: url,
    event: 'onload',
    keypress: false,
    prevent: false,
    progress: 'none'
  });

  $(document).ready(function(){
    setTimeout(function(){
      Drupal.ajax[id].ajaxDeferTrigger();
    }, delay || 0);
  });

};

})(jQuery);