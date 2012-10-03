(function() {
  if (typeof Drupal.settings.kissmetrics != 'undefined') {
    _kmq.push(['identify', Drupal.settings.kissmetrics.identity]);
  }
})();
