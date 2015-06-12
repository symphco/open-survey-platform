
/*
  This js file is meant to be used on the node/edit page of the form.  Meaning, this is not
  a user who is arranging fields, but is actually entering data into the form.
*/



  var arrangeFieldsFSZI;
  var tabval;
  
  Drupal.behaviors.arrangeFieldsNodeEditStartup = {
   attach: function (context, settings) {
  
    // In order to get the CSS to work correctly for textareas, we need to wrap a div around them.
    // Happens when we try to make the labels be inline.
    jQuery("textarea").wrap("<div></div>");
    
    // Make it so when you click on a fieldset, it's z-index goes up (so it
    // is in the foreground).
    arrangeFieldsFSZI = 300;  
    jQuery(".arrange-fields-container .draggable-form-item-fieldset").bind("mousedown", function (event, ui) {
      jQuery(this).css("z-index", arrangeFieldsFSZI);    
      arrangeFieldsFSZI++;
    });
  
    ////////////////////////////////////
    // We want to adjust the tabindex's of all the elements so that they are more logical.
    // Tab index will be based calculated by: (top x multiplier) + left.
    var multiplier = 10000;
    var tabvalArray = new Array();
    var elementArray = new Array();
  
    jQuery(".arrange-fields-container .draggable-form-item").each(function (index, element) {
  
      var postop = jQuery(element).css("top");
      var posleft = jQuery(element).css("left");
          
      postop = jQuery(element).css("top").replace("px", "");
      posleft = jQuery(element).css("left").replace("px", "");
  
      if (postop == "auto") postop = 0;  
      if (posleft == "auto") posleft = 0;
      
      var tabval = (parseInt(postop) * multiplier) + parseInt(posleft);
  
      if (tabval == 0) tabval = 1;
      // Now, grab the form element within this element, and assign this tabval.
      jQuery(element).find("input,textarea,select,a").each(function (sindex, sub_element) {
        tabvalArray.push(tabval);
        elementArray[tabval] = jQuery(sub_element);
        tabval++;  // in case there were more than one here.
      });
     
    });
  
    // Now, let's sort the tabvalArray.
    tabvalArray.sort(function(a,b){return a - b}); // have to do this because of the way JS sorts numerical values.
    // Okay, with the tabvalArray sorted, let's go through and assign each
    // element in the elementArray a tabindex (based on the index that their tabval
    // appeard in the tabvalArray).
    jQuery(tabvalArray).each(function (index, value) {
      var sub_element = elementArray[value];
      jQuery(sub_element).attr("tabindex", (index+1)); 
    });
  
   }  
  }
  

