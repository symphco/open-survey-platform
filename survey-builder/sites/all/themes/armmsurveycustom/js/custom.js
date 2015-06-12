/* Script to de-inline-ify all labels for select items -- merely to save time */
jQuery(document).ready(function(){
	jQuery("div.form-item.webform-container-inline").removeClass("webform-container-inline");
});

/* Script to slide down FAQ answers when the question is clicked */
jQuery(document).ready(function(){
	jQuery(".view-faq .views-field-title").click(function(){
		jQuery(this).parent().find(".views-field-body").slideToggle();
	});
});

/* Script Takes Labels from Contact Us Form and puts them as Placeholders instead */
jQuery(document).ready(function(){
	jQuery("#webform-client-form-9 .webform-component--name input").attr("placeholder","Name");
	jQuery("#webform-client-form-9 .webform-component--email input").attr("placeholder","Email");
	jQuery("#webform-client-form-9 .webform-component--subject input").attr("placeholder","Subject");
	jQuery("#webform-client-form-9 .webform-component--message textarea").attr("placeholder","Message");
	
});

/* Chosenify dropdows on normal content */
jQuery(document).ready(function() {
	if (!jQuery('.form-item select').parents().hasClass('webform-conditional')) {
		jQuery(".form-item select").chosen({disable_search_threshold: 32});
	}
	
	jQuery('.left-off-canvas-toggle').on('click', function(){
		jQuery('.left-off-canvas-menu').slideToggle();
	});
	
//	jQuery(".webform-conditional-condition select").chosen(); 
	
});