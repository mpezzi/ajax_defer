(function ($){

/**
 * Provides ajax defer instance behavior.
 */
Drupal.behaviors.AjaxDeferTestSingleDeferred = {
  attach: function (context, settings) {
    $('ul.ajax-defer-test-single', context).once(function(){
      if (console && console.log) {
        console.log('Deferred: ul.ajax-defer-test-single');
      }
    });
  }
};

})(jQuery);