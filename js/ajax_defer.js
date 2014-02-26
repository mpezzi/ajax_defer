(function ($){

/**
 * Provides ajax defer instance behavior.
 */
Drupal.behaviors.AjaxDeferInstance = {
  attach: function (context, settings) {
    $('.ajax-defer-instance', context).once('ajax-defer-instance', function(){

      var instances = Drupal.settings.ajax_defer.instances || {}, callbacks = {};

      // Collect all instances for each defined path.
      for (i in instances) {
        if ($('.ajax-defer-instance[data-instance="' + i + '"]', context).length > 0) {
          if (typeof callbacks[instances[i].path] == 'undefined') {
            callbacks[instances[i].path] = [];
          }
          callbacks[instances[i].path].push(i);
        }
      }

      // @todo: Provide ability to group instances?
      // Fire off each ajax callback.
      for (path in callbacks) {
        Drupal.AjaxDefer.ajax_url(path + '/' + callbacks[path].join('-'), 2000, true);
      }

    });
  }
};

Drupal.AjaxDefer = Drupal.AjaxDefer || {};
Drupal.AjaxDefer.ajax_url = function(url, delay, hide_error) {
  delay = delay || 0;
  setTimeout(function () {
    var element_settings = {};
    // Execute URL pull and then ajax commands
    // Create ajax element
    var $a = $('<a href="' + url + '" class="use-ajax"></a>');

    // Clicked links look better with the throbber than the progress bar.
    element_settings.progress = { 'type': 'throbber' };

    // For anchor tags, these will go to the target of the anchor rather
    // than the usual location.
    if ($a.attr('href')) {
      element_settings.url = $a.attr('href');
      element_settings.event = 'click';
    }
    var base = $a.attr('id');
    Drupal.ajax[base] = new Drupal.ajax(base, $a, element_settings);
    // Override default Drupal error handler
    if (hide_error) {
      Drupal.ajax[base].error = function (response, uri) {
        if (console && console.log) {
          console.log(Drupal.ajaxError(response, uri));
        }
        // Remove the progress element.
        if (this.progress.element) {
          $(this.progress.element).remove();
        }
        if (this.progress.object) {
          this.progress.object.stopMonitoring();
        }
        // Undo hide.
        $(this.wrapper).show();
        // Re-enable the element.
        $(this.element).removeClass('progress-disabled').removeAttr('disabled');
        // Reattach behaviors, if they were detached in beforeSerialize().
        if (this.form) {
          var settings = response.settings || this.settings || Drupal.settings;
          Drupal.attachBehaviors(this.form, settings);
        }
      };
    }

    // Trigger ajax
    $a.click();
  }, delay);
};

})(jQuery);