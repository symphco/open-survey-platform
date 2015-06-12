// Clear Value on Search input field on focus
jQuery(document).ready(function(){
	jQuery("#views-exposed-form-projects-search-results-page input[type=text]").focus(function(){
		jQuery("#views-exposed-form-projects-search-results-page input[type=text]").val("");
	});
});

/* In Projects "Refine By" form, make 2015 and 2016 checkboxes unclickable */
jQuery(document).ready(function(){
	jQuery("input#edit-field-gaa-year-value-2015").prop('disabled',true);
	jQuery("input#edit-field-gaa-year-value-2016").prop('disabled',true);

	jQuery("#edit-submit-schools").click(function(e){
		e.preventDefault();
		frm = jQuery("#views-exposed-form-schools-page-1").serialize();
		
		window.location = "/schools?"+ frm;
	});
});
jQuery(window).load(function(){
jQuery("#views-exposed-form-schools-page-1 .views-widget-filter-data_1 .views-widget").hide(); 
});
// Collapse tabs on exposed project filter; expand on click 
jQuery(document).ready(function(){
	jQuery("#views-exposed-form-schools-page-1 input").removeAttr("checked");
	
	jQuery("#views-exposed-form-schools-page-1 .views-widget-filter-data_3 .views-widget").hide(); 
	jQuery("#views-exposed-form-schools-page-1 .views-widget-filter-data_2 .views-widget").hide(); 
	jQuery("#views-exposed-form-schools-page-1 .views-widget-filter-data_5 .views-widget").hide();

	jQuery("#views-exposed-form-schools-page-1 label").click(function(){
			//jQuery("#views-exposed-form-schools-page-1 .expanded .views-widget").slideToggle();
			//jQuery("#views-exposed-form-schools-page-1 div.expanded").removeClass("expanded");
			var filteridentity = jQuery(this).parent().attr("id");
			jQuery("#views-exposed-form-schools-page-1 #"+filteridentity+" .views-widget").slideToggle();
			jQuery("#views-exposed-form-schools-page-1 #"+filteridentity+" .views-widget").parent().addClass("expanded");	
	});
});

/* Open Facebook Share Links in New window */
jQuery(document).ready(function($) {
    jQuery('a.service-links-facebook').live('click', function(){
        newwindow=window.open($(this).attr('href'),'','height=300,width=620');
        if (window.focus) {newwindow.focus()}
        return false;
    });
    jQuery('a.service-links-twitter').live('click', function(){
        newwindow=window.open($(this).attr('href'),'','height=250,width=620');
        if (window.focus) {newwindow.focus()}
        return false;
    });
});


// Narrow Down Refine by Municipality on Projects and Maps pages Using Lookup Tables */
jQuery(document).ready(function(){
	// Append extra selects to normal municipality filter
	jQuery("#edit-data-1").remove();
	jQuery(".bef-select-as-checkboxes").remove();
	jQuery("#edit-select-province-wrapper").remove();
	jQuery("#edit-select-municipality-wrapper").remove();
	jQuery("#edit-nid").hide();
	jQuery("#edit-school-type").remove();

	school_type = '<div class="form-checkboxes bef-select-as-checkboxes"><div class="bef-checkboxes"><div class="form-item form-type-bef-checkbox form-item-edit-data-2-1"><input type="checkbox" name="school_type" id="edit-data-2-1" value="Primary" multiple="multiple"> <label class="option" for="edit-data-2-1">Primary</label></div><div class="form-item form-type-bef-checkbox form-item-edit-data-2-2"><input type="checkbox" name="school_type" id="edit-data-2-2" value="Secondary" multiple="multiple"> <label class="option" for="edit-data-2-2">Secondary</label></div></div></div>';
	jQuery("#edit-school-type-wrapper").append(school_type);

	
	jQuery.getJSON('/api/v1/surveys', function(data){
		var option_data = "";
		for(var i=0; i<data.length; i++){
			option_data += "<option value='"+ data[i]["nid"] +"'>"+ data[i]["title"] +"</option>"
		}
		jQuery(".views-widget-filter-nid div.views-widget").append("<select name='nid'>"+ option_data +"</select>")
    	
    });  

	jQuery(".form-item-data-3").hide();
	jQuery("#edit-data-10-wrapper").hide();
	jQuery(".views-widget-filter-data_1 div.views-widget").append("<div class='select-province'><select name='select-province'><option disabled='disabled' value=''>Select Province</option></select></div><div class='select-municipality'><select name='select-municipality'><option disabled='disabled' value=''>Select Municipality</option></select></div></div>");
	// jQuery("select[name=select-region]").chosen();
	jQuery("select[name=select-province]").hide();
	jQuery("select[name=select-municipality]").hide();

	jQuery.ajax({
		url: '/ajax/get_provinces?region=150000000',
		success: function(data) {
			jQuery(".views-widget-filter-data_1 select[name=select-province]").show();
			jQuery("select[name=select-province]").html("<option value=''>Select Province</option>"+data);
			jQuery(".views-widget-filter-data_1 select[name=select-province]").chosen({width: "100%"});
		}			
	});

	// jQuery("select[name=select-region]").change(function(){
	// 	var selectedRegion = jQuery(this).val();
	// 	jQuery.ajax({
	// 		url: '/ajax/get_provinces?region='+selectedRegion,
	// 		success: function(data) {
	// 			jQuery(".views-widget-filter-data_1 select[name=select-province]").show();
	// 			jQuery("select[name=select-province]").html("<option>Select Province</option>"+data);
	// 			jQuery(".views-widget-filter-data_1 select[name=select-province]").chosen({width: "100%"});
	// 		}			
	// 	});
		
	// });
	jQuery("select[name=display-how-many]").change(function(){
		var pageCount = jQuery(this).val();
		window.location = "/schools?items_per_page=" + pageCount;
	})
	jQuery("select[name=select-province]").change(function(){
		var selectedProvince = jQuery(this).val();
		jQuery.ajax({
			url: '/ajax/get_municipalities?province='+selectedProvince,
			success: function(data) {
				// console.log(data);
				jQuery(".views-widget-filter-data_1 select[name=select-municipality]").show();
				jQuery("select[name=select-municipality]").html("<option value=''>Select Municipality</option>"+data);
				jQuery(".views-widget-filter-data_1 select[name=select-municipality]").chosen({width: "100%"});
			}			
		});
		
		
	});

	jQuery("#views-exposed-form-projects-search-results-page").submit(function(e){
		e.preventDefault();
		var dataValue = jQuery("#edit-search-api-views-fulltext").val();

		if (jQuery.isNumeric(dataValue)) {
			window.location = "/schools?data_4=" + dataValue.toString();
		}else{
			window.location = "/schools?data_10=" + dataValue;
		}
	});

	jQuery("select[name=select-municipality]").change(function(){
		var selectedMunicipality = jQuery(this).val();
		jQuery("input[name=data_1]").val(selectedMunicipality);		
		
	});
});

// Submit Hidden "Items Per Page" filter in sidebar when fake filter is submitted above table 
jQuery(document).ready(function(){
	jQuery("#header-items-per-page select").change(function(){
		var itemsPerPage = jQuery("#header-items-per-page select").val();
		jQuery(".views-exposed-widgets select[name=items_per_page]").val(itemsPerPage);
		jQuery("form#views-exposed-form-project-list-leaflet-map-page").submit();
	});
});

jQuery(document).ready(function() {
	// Clear out "Name of School" filter in Sidebar Filters on load
	jQuery("#views-exposed-form-schools-page-1 input[name=data_4]").val("");
	jQuery("#views-exposed-form-schools-page-1 div#edit-data-4-wrapper").hide();
	
});
// Chosen the "display num" dropdown on the Projects page 
jQuery(document).ready(function(){
	jQuery("#header-items-per-page select").chosen();
	jQuery(".views-widget-filter-field_psgc_code_value select[name=select-region]").chosen({width: "100%"});
	jQuery(".views-widget-filter-field_psgc_code_value select[name=select-province]").hide();
	jQuery(".views-widget-filter-field_psgc_code_value select[name=select-municipality]").hide();
});

// Chosen the select menus in the webform 
jQuery(document).ready(function(){
	jQuery(".webform-component select.form-select").chosen({width:"100%"});
	jQuery("#edit-submitted-before-now-were-you-informed-about-this-survey-").click(function(){
		jQuery(".webform-component select.form-select").trigger("chosen:updated");
	});
	jQuery("#ui-datepicker-div").click(function(){
		jQuery(".webform-component select.form-select").trigger("chosen:updated");
		
	});
	jQuery("input.wfm-add").click(function(){
		jQuery(".webform-component select.form-select").trigger("chosen:updated");
		
	});
});
