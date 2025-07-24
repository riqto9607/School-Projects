(function($) {
  $(document).ready(function() {
    var s = $('.slider'),
      sWrapper = s.find('.slider-wrapper'),
      sItem = s.find('.slide'),
      btn = s.find('.slider-link'),
      sWidth = sItem.width(),
      sCount = sItem.length,
      slide_date = s.find('.slide-date'),
      slide_title = s.find('.slide-title'),
      slide_text = s.find('.slide-text'),
      slide_more = s.find('.slide-more'),
      slide_image = s.find('.slide-image img'),
      sTotalWidth = sCount * sWidth;

    sWrapper.css('width', sTotalWidth);

    var clickCount = 0;

    btn.on('click', function(e) {
      e.preventDefault();

      if ($(this).hasClass('next')) {
        (clickCount < (sCount - 1)) ? clickCount++ : clickCount = 0;
      } else if ($(this).hasClass('prev')) {
        (clickCount > 0) ? clickCount-- : (clickCount = sCount - 1);
      }

      // Calculate animation distance based on screen width
      var screenWidth = $(window).width();
      var animationDistance = sWidth * clickCount;

      TweenMax.to(sWrapper, 0.4, {
        x: '-' + animationDistance
      });


      //CONTENT ANIMATIONS

      var fromProperties = {autoAlpha:0, x:'-50', y:'-10'};
      var toProperties = {autoAlpha:2, x:'3', y:'0'};

      TweenLite.fromTo(slide_image, 1, {autoAlpha:0, y:'40'}, {autoAlpha:3, y:'0'});
      TweenLite.fromTo(slide_date, 0.4, fromProperties, toProperties);
      TweenLite.fromTo(slide_title, 0.6, fromProperties, toProperties);
      TweenLite.fromTo(slide_text, 0.8, fromProperties, toProperties);
      TweenLite.fromTo(slide_more, 1, fromProperties, toProperties);

    });
          
  });
})(jQuery);

$('.overlay').addClass('overlay-blue');