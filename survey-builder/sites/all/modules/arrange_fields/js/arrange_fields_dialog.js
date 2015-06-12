
// This script is always meant to be loaded in conjunction with arrange_fields.js.
// It contains the functions dealing with jquery dialogs, which, because of their
// size, makes more sense to have in its own script file.

// This script will be making use of global variables defined in arrange_fields.js.
// Make sure it is loaded *after* arrange_fields.js.


  Drupal.behaviors.arrangeFieldsDialogStartup = {
   attach: function (context, settings) {
  
      //Set up the config dialog....
    jQuery("#arrange-fields-config-dialog").dialog({
      autoOpen: false,
      height: 300,
      width: 300,
      buttons: {
        "Apply" : function() {
          arrangeFieldsApplyDialogConfigChanges();
        },
        "Cancel" : function() { jQuery(this).dialog("close"); }
      }  
    });
    
      //Set up the markup dialog....
    jQuery("#arrange-fields-markup-dialog").dialog({
      autoOpen: false,
      height: 400,
      width: 400,
      buttons: {
        "Apply" : function() {
          arrangeFieldsApplyDialogMarkupChanges();
        },
        "Cancel" : function() { jQuery(this).dialog("close"); }      
      }  
    });
    
   }  
  };
  
  
  /**
   * We are opening the config dialog.  Let's reset the values
   *
   **/ 
  function arrangeFieldsDialogConfigureField(field, fieldType) {
    var dia = jQuery("#arrange-fields-config-dialog");
    dia.dialog("option", "title", "Configure " + field);
    
    arrangeFieldsDialogConfigField = field;
    var fieldId = "edit-" + field + "-draggable-wrapper";
    // if this is a fieldset, the fieldId is slightly different.
    if (fieldType == "fieldset") {
      fieldId = "edit-" + field + "-fieldset-draggable-wrapper";
    }
    arrangeFieldsDialogConfigFieldId = fieldId;
    arrangeFieldsDialogConfigFieldType = fieldType;
    
    // Is this field in the dialog config obj yet?
    if (arrangeFieldsDialogConfigObj[fieldId] == null) {
      arrangeFieldsDialogConfigObj[fieldId] = new Object();
    }
  
    // Make sure the properties have initial, non-null values.
    if (arrangeFieldsDialogConfigObj[fieldId]["wrapperHeight"] == null) {
      arrangeFieldsDialogConfigObj[fieldId]["wrapperHeight"] = "";
    }
    if (arrangeFieldsDialogConfigObj[fieldId]["wrapperWidth"] == null) {
      arrangeFieldsDialogConfigObj[fieldId]["wrapperWidth"] = "";
    }
    if (arrangeFieldsDialogConfigObj[fieldId]["labelDisplay"] == null) {
      arrangeFieldsDialogConfigObj[fieldId]["labelDisplay"] = "";
    }
    if (arrangeFieldsDialogConfigObj[fieldId]["labelVerticalAlign"] == null) {
      arrangeFieldsDialogConfigObj[fieldId]["labelVerticalAlign"] = "";
    }
    
  
    // Let's reset the inputs in the dialog to use whatever is in the
    // config obj.
    dia.find("input[name=af-dialog-width]").val(arrangeFieldsDialogConfigObj[fieldId]["wrapperWidth"]);
    dia.find("input[name=af-dialog-height]").val(arrangeFieldsDialogConfigObj[fieldId]["wrapperHeight"]);
    dia.find("input[name=af-dialog-label-display]").each(function() {
      if (jQuery(this).val() == arrangeFieldsDialogConfigObj[fieldId]["labelDisplay"]
          || jQuery(this).val() == arrangeFieldsDialogConfigObj[fieldId]["labelDisplay"] + "-block") {
        jQuery(this).attr("checked", "checked");
      }
    });
    
    
    // Should we hide the label config controls (based on what field type this is)?
    if (fieldType == "vertical_tabs" || fieldType == "fieldset") {
      jQuery("#arrange-fields-config-dialog-labels").hide();
    }
    else {
      jQuery("#arrange-fields-config-dialog-labels").show();
    }
    
    
    dia.dialog('open');
  }
  
  
  
  /**
   * Apply the changes the user has entered into the config dialog.
   **/
  function arrangeFieldsApplyDialogConfigChanges() {
    var dia = jQuery("#arrange-fields-config-dialog");
    
    var wrapperWidth = dia.find("input[name=af-dialog-width]").val();
    var wrapperHeight = dia.find("input[name=af-dialog-height]").val();
    var labelDisplay = dia.find("input[name=af-dialog-label-display]:checked").val();
       
    // Remove trouble characters, if they exist.
    wrapperWidth = wrapperWidth.replace(";", "");
    wrapperHeight = wrapperHeight.replace(";", "");
    
    // Save these values to the config obj
    var field = arrangeFieldsDialogConfigField;
    var fieldId = arrangeFieldsDialogConfigFieldId;
    var fieldType = arrangeFieldsDialogConfigFieldType;
    
    arrangeFieldsDialogConfigObj[fieldId]["wrapperWidth"] = wrapperWidth;
    arrangeFieldsDialogConfigObj[fieldId]["wrapperHeight"] = wrapperHeight;
    if (wrapperWidth == "") { wrapperWidth = "auto"; }
    if (wrapperHeight == "") { wrapperHeight = "auto"; }
    
    if (fieldType != "vertical_tabs" && fieldType != "fieldset") {
      arrangeFieldsDialogConfigObj[fieldId]["labelDisplay"] = labelDisplay;
      if (labelDisplay == "") { labelDisplay = "block"; }  
    }
      
    // Let's actually affect these changes on the page.
    jQuery("#" + fieldId).css("width", wrapperWidth);
    jQuery("#" + fieldId).css("height", wrapperHeight);
    
    
    var valign = "top";
    // Because of the way IE handles inline-block displays with radio buttons,
    // we have to change inline-block to simply inline for radios and checkboxes.
    // Isn't IE great?
    var radioDisplay = labelDisplay;
    if (labelDisplay == "inline-block") { 
      radioDisplay = "inline"; 
    }
    if (radioDisplay == "block") {
      // Unset the style for radio buttons/checkboxes, so it goes back to default
      radioDisplay = "";
    }
    
    var boolRadio = false;
    
    // Grab all the sibling elements under the wrapper and make them
    // have this display property.
    jQuery("#" + fieldId + " .form-item").children(":not(.description)").each(function() {
      
      // If these are radios/checkboxes, then also apply this style to the div's there.
      jQuery("#" + fieldId + " .form-item .form-radios, #" + fieldId + " .form-item .form-checkboxes").children().each(function () {
        jQuery(this).css("display", radioDisplay);
        valign = "middle";
        boolRadio = true;
      });
  
      if (!boolRadio) {
        jQuery(this).css("display", labelDisplay);
      }
      else { // we are dealing with radio buttons or checkboxes.
        jQuery(this).css("display", radioDisplay);
        arrangeFieldsDialogConfigObj[fieldId]["labelDisplay"] = radioDisplay;
      }
         
    });
      
    // Make the label look right...  
    jQuery("#" + fieldId + " .form-item label").css("vertical-align", valign);
  
    
    arrangeFieldsDialogConfigObj[fieldId]["labelVerticalAlign"] = valign;
  
    dia.dialog('close');
  }
  
  
  /**
   * This function opens the dialog to let us edit a particular markup element.
   **/
  function arrangeFieldsDialogEditMarkup(markupId) {
    var dia = jQuery("#arrange-fields-markup-dialog");
  
    // Make sure we have properties have initial, non-null values.
    if (arrangeFieldsDialogMarkupObj[markupId] == null) {
      arrangeFieldsDialogMarkupObj[markupId] = new Object();
    }
    if (arrangeFieldsDialogMarkupObj[markupId]["markupBody"] == null) {
      arrangeFieldsDialogMarkupObj[markupId]["markupBody"] = "";
    }
    if (arrangeFieldsDialogMarkupObj[markupId]["wrapperStyle"] == null) {
      arrangeFieldsDialogMarkupObj[markupId]["wrapperStyle"] = "";
    }
    if (arrangeFieldsDialogMarkupObj[markupId]["zIndex"] == null) {
      arrangeFieldsDialogMarkupObj[markupId]["zIndex"] = "201";
    }
    
    
    // Clear or re-load the dialog's inputs with values from our
    // obj.
    dia.find("textarea[name=af-markup-body]").val(arrangeFieldsUnconvertUnsafeChars(arrangeFieldsDialogMarkupObj[markupId]["markupBody"]));
    dia.find("input[name=af-wrapper-style]").val(arrangeFieldsUnconvertUnsafeChars(arrangeFieldsDialogMarkupObj[markupId]["wrapperStyle"]));
    dia.find("input[name=af-markup-z-index]").each(function() {
      if (jQuery(this).val() == arrangeFieldsDialogMarkupObj[markupId]["zIndex"]) {
        jQuery(this).attr("checked", "checked");
      }
    });
      
    
    arrangeFieldsDialogMarkupId = markupId;
    dia.dialog('open'); 
  }
  
  
  /**
   * Applies the changes from the markup dialog.
   **/
  function arrangeFieldsApplyDialogMarkupChanges() {
    var dia = jQuery("#arrange-fields-markup-dialog");
  
    var markupId = arrangeFieldsDialogMarkupId;
    
    if (markupId == "new") {
      // This is a new field!  So, create a random ID for it.
      markupId = "markup_element_" + arrangeFieldsRandomString();
      arrangeFieldsDialogMarkupObj[markupId] = new Object();
      
      // Create this element on the form itself, as a draggable, resizable div.
      // Give it a random-ish top and left position, so if you add several at a time,
      // they won't all be on top of each other.
      var ptop = 10 + Math.floor(Math.random() * 20);
      var pleft = 10 + Math.floor(Math.random() * 20);
      
      var newElements = "<div class='draggable-form-item arrange-fields-draggable-markup' id='" + markupId + "' style='top: " + ptop + "px; left: " + pleft + "px; z-index: 201;'>";
      newElements += "<div class='arrange-fields-control-handle arrange-fields-control-handle-markup'><span class='arrange-fields-handle-region'> &nbsp; &nbsp; </span>";
      newElements += "  <a href='javascript: arrangeFieldsDialogEditMarkup(\"" + markupId + "\");' class='arrange-fields-config-markup-link' title='Configure this markup'>&nbsp;</a>";
      newElements += "</div>";
      newElements += "<div class='arrange-fields-markup-body form-item' id='" + markupId + "_body'></div>";
      newElements += "</div>";
      
      jQuery(".arrange-fields-container").append(newElements);
          
      // Now, make the new element draggable.
      // This is the same code from arrange_fields.js.
      jQuery(".arrange-fields-container #" + markupId).draggable({
        stop: function(event, ui) { arrangeFieldsRepositionToGrid(false); },
        containment: ".arrange-fields-container", 
        scroll: true,
        grid : [10,10],
        start: function(event, ui) {arrangeFieldsDragging = true;},
        stop:  function(event, ui) {arrangeFieldsDragging = false;}    
      });
        
      
      // Let's also make it resizable.
      jQuery(".arrange-fields-container #" + markupId).resizable();      
     
       
      // Add in the hide/show behavior for the handle...
      jQuery(".arrange-fields-container #" + markupId).bind("mouseenter", function(event) {
        var hand = jQuery(this).find(".arrange-fields-control-handle");
        if (arrangeFieldsDragging != true) {
          jQuery(hand).show();
        }
      });
    
      jQuery(".arrange-fields-container #" + markupId).bind("mouseleave", function(event) {
        var hand = jQuery(this).find(".arrange-fields-control-handle");
        if (arrangeFieldsDragging != true) {
          jQuery(hand).hide();
        }
      });
  
      // Snap everything back to the grid.
      arrangeFieldsRepositionToGrid();
      
    }
    
    
    var markupBody = dia.find("textarea[name=af-markup-body]").val();
    var safeMarkupBody = arrangeFieldsConvertUnsafeChars(markupBody);
    
    var wrapperStyle = dia.find("input[name=af-wrapper-style]").val();
    var safeWrapperStyle = arrangeFieldsConvertUnsafeChars(wrapperStyle);
    
    var zIndex = dia.find("input[name=af-markup-z-index]:checked").val();
    
    // Save into the obj.
    arrangeFieldsDialogMarkupObj[markupId]["markupBody"] = safeMarkupBody;
    arrangeFieldsDialogMarkupObj[markupId]["wrapperStyle"] = safeWrapperStyle;
    arrangeFieldsDialogMarkupObj[markupId]["zIndex"] = zIndex;
  
    // Apply it to the page.
    jQuery(".arrange-fields-container #" + markupId + "_body").html(markupBody);
    var tempStyle = jQuery(".arrange-fields-container #" + markupId).attr("style");
    jQuery(".arrange-fields-container #" + markupId).attr("style", tempStyle + " ; " + wrapperStyle);
    jQuery(".arrange-fields-container #" + markupId).css("z-index", zIndex);
    
    dia.dialog('close');   
  }
  
  
  function arrangeFieldsDialogMarkupDelete() {
    var x = confirm("Are you sure you wish to delete this markup element?  This action cannot be undone.");
    if (!x) {return;}
    
    var markupId = arrangeFieldsDialogMarkupId;
    // Remove it from our object.
    arrangeFieldsDialogMarkupObj[markupId] = null;
    
    // Also, remove it from the page!
    jQuery(".arrange-fields-container #" + markupId).remove();
    
    var dia = jQuery("#arrange-fields-markup-dialog");
    dia.dialog('close');
    
  }
  
  /**
   * Replace "unsafe" characters with codes which we can decode later.
   * I am trying to make the codes random enough so that no one would actually
   * have typed them into the field.
   **/
  function arrangeFieldsConvertUnsafeChars(str) {
  
    // Must use regex with the "g" to replace all occurances (like in PHP)
    str = str.replace(/,/g, "_~!co%~_");
    str = str.replace(/;/g, "_~!sc%~_");
    str = str.replace(/'/g, "_~!sq%~_");  //'
    str = str.replace(/"/g, "_~!dq%~_");  //"
    str = str.replace(/\n/g, "_~!nl%~_");
  
  
    return str;
  }
  
  /**
   * The opposite of ConvertUnsafeChars
   **/
  function arrangeFieldsUnconvertUnsafeChars(str) {
  
    // Must use regex with the "g" to replace all occurances (like in PHP)
    str = str.replace(/_~!co%~_/g, ",");
    str = str.replace(/_~!sc%~_/g, ";");
    str = str.replace(/_~!sq%~_/g, "'");
    str = str.replace(/_~!dq%~_/g, '"');
    str = str.replace(/_~!nl%~_/g, "\n");
    
    return str;
  }
  
  
  function arrangeFieldsRandomString() {
  	var chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXTZabcdefghiklmnopqrstuvwxyz";
  	var length = 10;
  	var randomstring = '';
  	for (var i = 0; i < length; i++) {
  		var rnum = Math.floor(Math.random() * chars.length);
  		randomstring += chars.substring(rnum,rnum+1);
  	}
  	return randomstring;
  }
  

