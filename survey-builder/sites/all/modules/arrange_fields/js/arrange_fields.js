// $Id$


// Some global variables we will need...
var arrangeFieldsStartupHeight;
var arrangeFieldsGreatestHeight;
var arrangeFieldsDragging;
var gridWidth;
var arrangeFieldsDialogConfigField;
var arrangeFieldsDialogConfigFieldId;
var arrangeFieldsDialogConfigFieldType;
var arrangeFieldsDialogMarkupId;
var arrangeFieldsDialogConfigObj = new Object();  // we will use this later like a 2d assoc array, for keeping up with dialog settings for fields.
var arrangeFieldsDialogMarkupObj = new Object();  // we will use this later like a 2d assoc array, for keeping up with dialog settings for markup elements.


Drupal.behaviors.arrangeFieldsStartup = {
 attach: function (context, settings) {
 
  // If we have any dialog config settings saved from a previous session,
  // let's load them.
  if (Drupal.settings.arrangeFieldsDialogConfigObj != null) {
    arrangeFieldsDialogConfigObj = Drupal.settings.arrangeFieldsDialogConfigObj;
  }
  if (Drupal.settings.arrangeFieldsDialogMarkupObj != null) {
    arrangeFieldsDialogMarkupObj = Drupal.settings.arrangeFieldsDialogMarkupObj;
  }
  
    
  // This section of code makes the "handle" appear for draggable items, which users
  // may use to drag the item, or for important links to appear there.
  jQuery(".arrange-fields-container .draggable-form-item").bind("mouseenter", function(event) {
    var hand = jQuery(this).find(".arrange-fields-control-handle");
    if (arrangeFieldsDragging != true) {
      jQuery(hand).show();
    }
  });

  jQuery(".arrange-fields-container .draggable-form-item").bind("mouseleave", function(event) {
    var hand = jQuery(this).find(".arrange-fields-control-handle");
    if (arrangeFieldsDragging != true) {
      jQuery(hand).hide();
    }
  });
  

  // Figure out what the gridWidth should be  (10,10 is default).
  gridWidth = 10;
  if (Drupal.settings.arrangeFieldsGridWidth != null) {
    gridWidth = Drupal.settings.arrangeFieldsGridWidth;
  }
  if (gridWidth < 1) gridWidth = 10;  
  
  
  arrangeFieldsAddDraggableAndResizable();
  
  

  
  // We do the "true" if this is a totally fresh new form, with no
  // position data already saved.  
  var startup = true;
  
  try {
    if (Drupal.settings.arrangeFieldsNotNewForm == true) {
      startup = false;
    }
  }
  catch (exception) {}
  
  // Make sure everything starts off on a grid line.
  arrangeFieldsRepositionToGrid(startup); 
  
 }
}



/**
  Add the appropriate draggable and resizable properties to our elements
*/
function arrangeFieldsAddDraggableAndResizable() {


  // This actually makes the draggable items draggable.
  jQuery(".arrange-fields-container .draggable-form-item").draggable({
    stop: function(event, ui) { arrangeFieldsRepositionToGrid(false); },
    containment: ".arrange-fields-container", 
    scroll: true,
    grid : [gridWidth,gridWidth],
    start: function(event, ui) {arrangeFieldsDragging = true;},
    stop:  function(event, ui) {arrangeFieldsDragging = false;}
  });

  jQuery(".arrange-fields-container fieldset.captcha").draggable({
    stop: function(event, ui) { arrangeFieldsRepositionToGrid(false); },
    containment: ".arrange-fields-container", 
    scroll: true,
    grid : [gridWidth,gridWidth],
    start: function(event, ui) {arrangeFieldsDragging = true;},
    stop:  function(event, ui) {arrangeFieldsDragging = false;}
  });
  
  
  arrangeFieldsStartupHeight = 0;
  arrangeFieldsGreatestHeight = 0; 
  
  var snapWidth = 1;
  if (Drupal.settings.arrangeFieldsSnapResize != null && Drupal.settings.arrangeFieldsSnapResize == 1) {
    snapWidth = gridWidth;
  }
  
  jQuery(".arrange-fields-container .draggable-form-item:not(.draggable-form-item-fieldset, .arrange-fields-vertical-tabs-wrapper, .arrange-fields-element-type-container) textarea").resizable({grid: [snapWidth,snapWidth]});
  jQuery(".arrange-fields-container .draggable-form-item:not(.draggable-form-item-fieldset, .arrange-fields-vertical-tabs-wrapper, .arrange-fields-element-type-container) .form-text").resizable({
        handles: 'e',
        grid: [snapWidth,snapWidth]
  });  
  jQuery(".arrange-fields-container .arrange-fields-draggable-markup").resizable({grid: [snapWidth,snapWidth]});
  
}


/**
  * Repositions all the draggable elements to the grid lines.
  */
function arrangeFieldsRepositionToGrid(startup) {

  // Figure out what the gridWidth should be  (10,10 is default).
  gridWidth = 10;
  if (Drupal.settings.arrangeFieldsGridWidth != null) {
    gridWidth = Drupal.settings.arrangeFieldsGridWidth;
  }
  if (gridWidth < 1) gridWidth = 10;
    
  jQuery(".arrange-fields-container .draggable-form-item").each(function (index, element) {
    var postop = jQuery(element).css("top");
    var posleft = jQuery(element).css("left");

    postop = jQuery(element).css("top").replace("px", "");
    posleft = jQuery(element).css("left").replace("px", "");
    
    if (postop == "auto") postop = 0; 
    if (posleft == "auto") posleft = 0;
    
    if (startup == true && postop == 0) {
      // Since this is a new form, with values not set yet,
      // let's assign the postop based on the running startupHeight
      // value.
      postop = arrangeFieldsStartupHeight;
      arrangeFieldsStartupHeight += jQuery(element).height() + 20; 
    }
      
    if (parseInt(postop) > parseInt(arrangeFieldsGreatestHeight)) {
      arrangeFieldsGreatestHeight = parseInt(postop);
    }
    
    // We want to round the top and left positions to the nearest X (gridWidth)
    var newTop = Math.round(postop/gridWidth) * gridWidth;
    var newLeft = Math.round(posleft/gridWidth) * gridWidth;
    
    var diffLeft = "-" + (posleft - newLeft);
    var diffTop = "-" + (postop - newTop);
    
    if (posleft < newLeft) { diffLeft = newLeft - posleft; }
    if (postop < newTop) { diffTop = newTop - postop; }

    if (newTop < 0) newTop = 0;
    if (newLeft < 0) newLeft = 0;
    
   jQuery(element).css("top", newTop + "px");
   jQuery(element).css("left", newLeft + "px");

   // We want to resize the container as we go to make sure we don't run out of
   // room, and to make sure the user can always drag things below the rest of
   // the items on the form.
   jQuery(".arrange-fields-container").css("height", (parseInt(arrangeFieldsGreatestHeight) + 500) + "px");
 
  });
  
}

/**
  * This method will save the position, width, and height, and other important
  * information of the draggable items on the page.
  *
  */
function arrangeFieldsSavePositions() {
  
  var dataString = "";
  var maxBottom = 0;
  
  jQuery(".arrange-fields-container .draggable-form-item").each(function (index, element) {
   var id = jQuery(element)[0].id;
   var top = jQuery(element).css("top");
   var left = jQuery(element).css("left");
   
   // Now, we want to find the element inside...
   var inner_element_type = "";
   var inner_element_id = "";
   
   var width = 0;
   var height = 0;
   
   // Attempt to find either a text area or a textfield...
   // But, only do this if we are NOT within a fieldset!
   if (jQuery(element).hasClass("draggable-form-item-fieldset") == false) {
     var test = jQuery(element).find("textarea");

     width = jQuery(test).width();
     height = jQuery(test).height();
     
     
     if (width != null) inner_element_type = "textarea";
     
     if (width == null) {
       test = jQuery(element).find("input:text");       
           
       width = jQuery(test).width();
       height = jQuery(test).height();
       if (width != null) inner_element_type = "input";
     }
     
     // Attempt to get the inner element's CSS id, if we can.
     try {
       inner_element_id = test[0].id;
     } catch (e) {}
          
   }

   if (width == null) {
     width = height = 0;
   }   
   
   dataString += id + "," + top + "," + left + "," + inner_element_type + "," +inner_element_id + "," + width + "px," + height + "px,";
   
   // Do we have any extra data for this element?  Perhaps data from the config dialog?
   if (arrangeFieldsDialogConfigObj[id] != null) {
     dataString += arrangeFieldsDialogConfigObj[id]["wrapperWidth"] + ",";
     dataString += arrangeFieldsDialogConfigObj[id]["wrapperHeight"] + ",";
     dataString += arrangeFieldsDialogConfigObj[id]["labelDisplay"] + ",";
     dataString += arrangeFieldsDialogConfigObj[id]["labelVerticalAlign"] + ",";
   }
   
   // Is this field a piece of custom markup which the user has added?  If so,
   // add whatever information we can about it from the object.
   if (arrangeFieldsDialogMarkupObj[id] != null) {
     dataString += "~~markup_element~~,";
     dataString += jQuery(element).width() + "px,";
     dataString += jQuery(element).height() + "px,";
     dataString += arrangeFieldsDialogMarkupObj[id]["markupBody"] + ",";
     dataString += arrangeFieldsDialogMarkupObj[id]["wrapperStyle"] + ",";
     dataString += arrangeFieldsDialogMarkupObj[id]["zIndex"] + ",";
   }
   
   dataString += ";";
    
   var bottom = parseInt(top) + jQuery(element).height();
   if (bottom > maxBottom) {
     maxBottom = bottom;
   }
   
  });

  // This maxBottom value tells us how tall the container needs to be on the node/edit page
  // for this form.
  dataString += "~~maxBottom~~," + maxBottom + "px";
  jQuery("#edit-arrange-fields-position-data").val(dataString);

}

function arrangeFieldsConfirmReset() {
  var x = confirm("Are you sure you want to reset the position data for these fields?  This action cannot be undone.");
  return x;
}

function arrangeFieldsPopupEditField(type, field) {
  // Using the ?q= syntax is better, as it works for people
  // who do not have clean URLs enabled, as well as those who do.
  var popup_url = Drupal.settings.basePath + "?q=arrange-fields/popup-edit-field&type_name=" + type + "&field=" + field;
  var win_title = "myPopupWin";
  var win_options = "height=700,width=700,scrollbars=yes";
  
  var myWin = window.open(popup_url, win_title, win_options);
  myWin.focus();

}

function arrangeFieldsClosePopup() {
  // Closes the popup and saves the form in the opener window.

  opener.arrangeFieldsSavePositions();
  
  opener.document.getElementById("arrange-fields-position-form").submit();
  window.close();
}



