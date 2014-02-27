(function ($){

/**
 * Provides ajax defer instance behavior.
 */
Drupal.behaviors.AjaxDeferTestSingle = {
  attach: function (context, settings) {
    $('ol.ajax-defer-test-single', context).once(function(){
      if (console && console.log) {
        console.log('Original: ol.ajax-defer-test-single');
      }
    });
  }
};

})(jQuery);