(function($){ 
  $(document).ready(function(){
  $(".hs_container").css({left: (($(document).width() - ($(".hs_container").width()))/2 - $(".hs_container").offset().left)});
  $(".hs_area").hover(function(){ 
  	$(".artisancover", this).stop().animate({top: $(this).height() - 30 },{queue:false,duration:200});
  	$(".pricecover", this).stop().animate({top: 0},{queue:false,duration:200});
    $(".descriptioncover", this).stop().animate({top: $(this).height() - $(".descriptioncover",$(this)).height()},{queue:false,duration:200});
  }, function() {
    $(".artisancover", this).stop().animate({top:$(this).height()},{queue:false,duration:200});
    $(".pricecover", this).stop().animate({top:-40},{queue:false,duration:200});
    $(".descriptioncover", this).stop().animate({top:$(this).height()},{queue:false,duration:200});
  });
  });
  $(document).resize(function(){$(".hs_area").css({left: $(document).width() - ($(".hs_area").width()/2)})});
  $(window).load(function(){$(".hs_artisan img:first-child").each(function(i, img) { 
  $(img).css({ 
  position: "relative", 
  left: ($(img).parent().parent().width()/2) - ($(img).width()/2) 
  });
  });
  $(".hs_artwork img:first-child").each(function(i, img) { 
  $(img).css({ 
  position: "relative", 
  left: ($(img).parent().parent().width()/2) - ($(img).width()/2), 
  top: ($(img).parent().parent().height()/2) - ($(img).height()/2)
  }); 
  });
  $(".descriptioncover").each(function(i, div) { 
  $(div).css({ 
  position: "absolute", 
  width: $(div).parent().parent().width(),
  top: $(div).parent().parent().height(), 
  left: 0,
  display: "inline", 
  }); 
  });
  $(".pricecover").each(function(i, div) { 
  $(div).css({ 
  position: "absolute", 
  top: -40, 
  left: $(div).parent().parent().width()-$(div).width(), 
  display: "inline", 
  }); 
  });
  $(".artisancover").each(function(i, div) { 
  $(div).css({ 
  position: "absolute", 
  left: 0,
  width: $(div).parent().parent().width(),
  top: $(div).parent().parent().height(), 
  display: "inline", 
  }); 
  });
  
  
  });})(jQuery);
