(function($){ 
  var defaultBoxLeft = [];
  var defaultBoxWidth = [];
  var defaultCorrection = 0;
  
  function adjustSlider() {
	  var windowWidth = $(window).width();
	  
	  var MIN_WINDOW_WIDTH = 960;
	  var MAX_WINDOW_WIDTH = 1450;
	  
	  var DEFAULT_SLIDER_WIDTH = 1420.0;
	  

	  // Enforce minimum window size
	  if(windowWidth < MIN_WINDOW_WIDTH){
		windowWidth = MIN_WINDOW_WIDTH;
	  }else if(windowWidth > MAX_WINDOW_WIDTH){
		windowWidth = MAX_WINDOW_WIDTH;
	  }
	  
	  
	  // Lets compute the proper sizes for the individual windows.
	  var proportion = (windowWidth) / DEFAULT_SLIDER_WIDTH;
	  
	  /*$(".descriptioncover_text").each(function(i, div) { 
		div.style.fontSize = 12*proportion + "pt";
	  });*/
	  
	  // If the default slider is larger than the window, lets resize the slider (just scale all widths by the proportion)
	  //if(proportion < 1.0)  {
		boxes = $(".artisan_item_box");
		artisans = $(".artisan_img_frame>img");
		artworks = $(".artwork_img_frame>img");
		for(i = 0;i<boxes.length;i++){
			
	  
			//console.log("i = " + i + " Box Width: " + $(boxes[i]).width());
			$(boxes[i]).css({width: defaultBoxWidth[i] * proportion});
			$(boxes[i]).css({left: defaultBoxLeft[i] * proportion});
			//$(artisans[i]).css({width: $(artisans[i]).width(),height: $(artisans[i]).height()});
			
			//console.log("Artisan: " + $(artisans[i]).height() + " " + $(artisans[i]).width());
			
			$(artisans[i]).parent().css({height: $(artisans[i]).height(),width: $(artisans[i]).width() * proportion});
			$(artworks[i]).parent().css({height: $(artworks[i]).height(),width: $(artworks[i]).width() * proportion});
			//$(artworks[i]).css({width: $(artworks[i]).width() * proportion,height: $(artworks[i]).height() * proportion});
		}
		$(".hs_container").css({width: DEFAULT_SLIDER_WIDTH * proportion });
	  //}
	  
	  //console.log("OffsetLeft = " + $(".hs_container").offset().left + " Left = " + $(".hs_container")[0].style.left + " parsed int = " + parseInt($(".hs_container")[0].style.left));
      offsetLeft = $(".hs_container").offset().left;
	  
      if(isNaN(offsetLeft)) {
		offsetLeft = 0;
 	  }
	  //console.log(windowWidth + " " + $(".hs_container").width() + " " + proportion + " " + offsetLeft + " " + ((windowWidth - ($(".hs_container").width()))/2 - offsetLeft));
	  //$(".hs_container").css({left: ((windowWidth - ($(".hs_container").width()))/2 - offsetLeft)});
		  $(".hs_container")[0].style.left = ((windowWidth - ($(".hs_container").width()))/2 + defaultCorrection) + "px";
          offsetLeft = $(".hs_container").offset().left;
          if(isNaN(offsetLeft)) {
		offsetLeft = 0;
 	  }
	  //console.log(windowWidth + " " + $(".hs_container").width() + " " + proportion + " " + offsetLeft + " " + ((windowWidth - ($(".hs_container").width()))/2 - offsetLeft ));
	  
	  //console.log("Offset.left: " + $(".hs_container")[0].style.left);
	  
	  $(".descriptioncover").each(function(i, div) { 
		//console.log("description.width = " + $(div).parent().parent().width() + " " + $(div).parent().width() + " " + $(div).width());
		  $(div).css({ 
			position: "absolute", 
			width: $(div).parent().parent().width(),
			height: $(".artisancover",$(div).parent().parent().parent().parent()).height(),
			top: $(div).parent().parent().parent().height(), 
			left: $(div).parent().parent().width(),
			display: "inline"
		  }); 
	  });

	  $(".pricecover").each(function(i, div) { 
		  $(div).css({top: 0,left: 0});
		  $(div).css({ 
			  top: 0, 
			  left: parseInt($(div).parent().parent().parent().parent().width() - $(div).width()-1) 
		  }); 
	  });
  }
  
  $(window).resize(function() {
	adjustSlider();
  });
  
  $(document).ready(function(){
    boxes = $(".artisan_item_box");
	for(i = 0;i<boxes.length;i++){
		defaultBoxLeft[i] = $(boxes[i]).offset().left;
		defaultBoxWidth[i] = $(boxes[i]).width();
	}
	$(".hs_container")[0].style.left = "0px";
	
	defaultCorrection = parseInt($(".hs_container")[0].style.left) - $(".hs_container").offset().left;
  
	adjustSlider();
	$(".hs_area").hover(function(){ 
	//	$(".artisancover", this).stop().animate({top: $(this).height() - 30 },{queue:false,duration:200});
	// 	$(".pricecover", this).stop().animate({top: 0},{queue:false,duration:200});
		$(".descriptioncover", this).stop().animate({top: $(this).height() - $(".descriptioncover",$(this)).height()},{queue:false,duration:200});
	}, function() {
//    $(".artisancover", this).stop().animate({top:$(this).height()},{queue:false,duration:200});
    //$(".pricecover", this).stop().animate({top:-40},{queue:false,duration:200});
		$(".descriptioncover", this).stop().animate({top:$(this).height()},{queue:false,duration:200});
	});
  });
  
  /*$(window).load(function(){
  $(".hs_artisan img:first-child").each(function(i, img) { 
  $(img).css({ 
  position: "relative", 
  left: ($(img).parent().parent().width()/2) - ($(img).width()/2) 
  }); 
  }); */
/*
  $(".hs_artwork img:first-child").each(function(i, img) { 
  $(img).css({ 
  position: "relative", 
  left: ($(img).parent().parent().width()/2) - ($(img).width()/2), 
  top: ($(img).parent().parent().height()/2) - ($(img).height()/2)
  }); 
  });
*/
/*
	  $(".descriptioncover").each(function(i, div) { 
	  $(div).css({ 
		position: "absolute", 
		width: $(div).parent().parent().width(),
		height: $(".artisancover",$(div).parent().parent().parent().parent()).height(),
		top: $(div).parent().parent().parent().height(), 
		left: $(div).parent().parent().width(),
		display: "inline", 
	  }); 
  });
*/
/*
  $(".pricecover").each(function(i, div) { 
  $(div).css({ 
  position: "absolute", 
  top: 0, 
  left: parseInt($(div).parent().parent().parent().parent().width() - $(div).width()), 
  display: "inline", 
  }); 
  });
  */
/*
  $(".artisancover").each(function(i, div) { 
  $(div).css({ 
  position: "absolute", 
  left: 0,
  width: $(div).parent().width(),
  top: $(div).parent().parent().parent().parent().height() - $(this).height(), 
  display: "inline", 
  }); 
  });
  
  
  });
  
  */
  })(jQuery);
