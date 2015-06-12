jQuery(document).ready(function() {

	// filter dropdown.
	jQuery(".filtername").on("click", function(e){
		e.preventDefault();

		// reset everything

		if(jQuery(this).hasClass("open")){
			jQuery(".ddFilter").removeClass("open");
			jQuery(".filtername").removeClass("open");
		}else{
			jQuery(".ddFilter").removeClass("open");
			jQuery(".filtername").removeClass("open");

			jQuery(this).addClass("open").next(".ddFilter").addClass("open");	
		}
		
	});

});