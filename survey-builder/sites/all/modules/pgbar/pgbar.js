(function ($) {
$(document).ready(function() {

$('.pgbar-wrapper').each(function() {
  var wrapper = $(this);
  var current = parseFloat(wrapper.attr('data-pgbar-current'));
  var target  = parseFloat(wrapper.attr('data-pgbar-target'));
  var bars    = $('.pgbar-current', wrapper);
  var counter = $('.pgbar-counter', wrapper);

  if (wrapper.attr('data-pgbar-inverted') == 'true') {
    var from = 1;
    var to = 1 - current / target;
    var diff = from - to;
  } else {
    var from = 0;
    var to = current / target;
    var diff = to - from;
  }
  
  counter.html('0');
  
  function resetCounters(now, fx) {
    var num = '';
    // Add thousand separators to the number
    var end = 0;
    now = Math.round(now);
    while (now > 0) {
      for (i=1; i<=end; i++) {
	num = '0' + num;
      }
      var rest = now % 1000;
      end = 3 - rest.toString().length;
      num = rest + ',' + num;
      now = (now - rest) / 1000;
    }
    num = num.slice(0, num.length-1); // cut last thousand separator from output.
    counter.html(num)
  }
  
  var duration = 500+1000*diff;
  
  if (wrapper.attr('data-pgbar-direction') == 'vertical') {
    bars.height(from*100 + '%');
    var initial_animation = function() {
      wrapper.animate({val:current}, {duration: duration, step: resetCounters});
      bars.animate({height: to*100 + '%'}, {duration: duration});
    }
  } else {
    bars.width(from*100 + '%');
    var initial_animation = function() {
      wrapper.animate({val:current}, {duration: duration, step: resetCounters});
      bars.animate({width: to*100 + '%'}, {duration: duration});
    }
  }

  window.setTimeout(initial_animation, 2000);
});

});
})(jQuery);
