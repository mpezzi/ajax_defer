(function ($, Drupal) {

// Hide these in a ready to ensure that Drupal.ajax is set up first.
$(function(){
  Drupal.ajax.prototype.commands.ajax_defer_reload = function (ajax, data, status) {
    location.href = $.param.querystring(location.href, { ajax_defer_reloaded: 1 });
  };
});

}) (jQuery, Drupal);