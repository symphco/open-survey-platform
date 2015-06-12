/**
 * @file
 * Provides an API for making select list options dependent upon the
 * value of another form element.
 */
(function($) {
  Drupal.ViewsChartTools = Drupal.ViewsChartTools || {};
  Drupal.ViewsChartTools.helpers = Drupal.ViewsChartTools.helpers || {};
  Drupal.ViewsChartTools.dependentOptions = Drupal.ViewsChartTools.dependentOptions || {};
  Drupal.ViewsChartTools.dependentOptions.bindings = Drupal.ViewsChartTools.dependentOptions.bindings || {};

  /**
   * Helper function: converts an array to string (similar to print_r).
   */
  Drupal.ViewsChartTools.helpers.arrayToString = function(array, indent) {
    var output = '';
    for (var i in array) {
      output += indent + i + ': ';
      if (array[i] instanceof Array) {
        output += "\n";
        output += Drupal.ViewsChartTools.helpers.arrayToString(array[i], '  ' + indent);
      }
      else {
        output += array[i] + "\n";
      }
    }
    return output;
  }

  /**
   * Called upon attachment.
   */
  Drupal.ViewsChartTools.dependentOptions.autoAttach = function() {
    Drupal.ViewsChartTools.dependentOptions.bindings = {};

    if (!Drupal.settings.ViewsChartTools) {
      return;
    }

    // Loop through form elements implementing dependent options.
    for (id in Drupal.settings.ViewsChartTools.dependentOptions) {
      var trigger = Drupal.settings.ViewsChartTools.dependentOptions[id].trigger;

      // Ensure bindings arrays exist.
      if (!Drupal.ViewsChartTools.dependentOptions.bindings[trigger]) {
        Drupal.ViewsChartTools.dependentOptions.bindings[trigger] = [];
      }

      if (!Drupal.ViewsChartTools.dependentOptions.bindings[trigger][id]) {
        Drupal.ViewsChartTools.dependentOptions.bindings[trigger][id] = [];
      }

      // Get the bound element's default options and dependencies.
      var options = Drupal.settings.ViewsChartTools.dependentOptions[id].options;
      var dependencies = Drupal.settings.ViewsChartTools.dependentOptions[id].dependencies;

      // Loop through each default option and map its dependency to the triggering element.
      for (var option in options) {
        if (!dependencies[option]) {
          continue;
        }

        // Loop through each dependent value for the current option and store info.
        for (i in dependencies[option]) {
          var value = dependencies[option][i];
          if (!Drupal.ViewsChartTools.dependentOptions.bindings[trigger][id][value]) {
            Drupal.ViewsChartTools.dependentOptions.bindings[trigger][id][value] = [];
          }

          // This is an array of options that apply to a given trigger element value.
          Drupal.ViewsChartTools.dependentOptions.bindings[trigger][id][value][option] = options[option];
        }
      }
    }

    // Loop through all triggering elements and set change event handlers.
    for (trigger in Drupal.ViewsChartTools.dependentOptions.bindings) {
      // Build a trigger ID.
      if (trigger.substring(0, 6) == 'radio:') {
        var trigger_id = "input[name='" + trigger.substring(6) + "']";
      }
      else {
        var trigger_id = '#' + trigger;
      }

      /**
       * Returns the value of a triggering element.
       */
      var getValue = function(trigger, trigger_id) {
        if ($(trigger_id).size() == 0) {
          return null;
        }

        // Special handling for radio elements.
        if (trigger.substring(0, 6) == 'radio:') {
          var val = $(trigger_id + ':checked').val();
        }
        else {
          switch ($(trigger_id).attr('type')) {
            case 'checkbox':
              var val = $(trigger_id).attr('checked') || 0;
              break;
            default:
              var val = $(trigger_id).val();
          }
        }
        return val;
      };

      /**
       * Sets the change handler.
       */
      var setChangeTrigger = function(trigger_id, trigger) {
        // This is the actual change handler.
        var changeTrigger = function() {
          // Get the new value of the triggering element.
          var value = getValue(trigger, trigger_id);

          if (value == null) {
            return;
          }

          // Loop through each of our bindings for the triggering element.
          // 'id' represents an element whose options are bound to the triggering element.
          for (var id in Drupal.ViewsChartTools.dependentOptions.bindings[trigger]) { // edit-style-options-info-created-type
            if (typeof id != 'string') {
              continue;
            }

            var change_id = '#' + id;

            // Get the default options for the bound element.
            var options = Drupal.settings.ViewsChartTools.dependentOptions[id].options;

            // Save the existing value of this form element.
            var defaultVal = $(change_id).val();

            // Remove all options from the element before adding new options. This ensures
            // that we prevent duplicating options and that we are able to add the updated
            // options in the order in which they were defined in FAPI.
            $(change_id).children().remove();

            // Make sure bindings for this value are set. Note that setting this
            // value's bindings as an empty array will simply result in all options
            // that have no dependencies being displayed.
            if (!Drupal.ViewsChartTools.dependentOptions.bindings[trigger][id][value]) {
              Drupal.ViewsChartTools.dependentOptions.bindings[trigger][id][value] = [];
            }

            // If the current option is within the dependencies for this value then apply it.
            // If there is no binding for this value then the current option will be applied
            // so long as the option is not under dependency control by a different value.
            // If it is under dependency control by a different value - but not the current
            // value - then we know that this is an invalid option for the element.
            for (var option in options) {
              // If the option is dependent upon this value... or if there are no dependencies for this option...
              if (typeof Drupal.ViewsChartTools.dependentOptions.bindings[trigger][id][value][option] != 'undefined' || !Drupal.settings.ViewsChartTools.dependentOptions[id].dependencies[option]) {
                $(change_id).append('<option value="' + option + '">' + options[option] + '</option>');
              }
            }

            // Re-apply the value of the item that existed before processing.
            $(change_id).each(function(index) {
              $(this).val(defaultVal);
            });

            // Finally, trigger the change event on this element to ensure dependent options cascade.
            $(change_id).trigger('change');
          }
        };

        $(trigger_id).change(function() {
          // Trigger the internal change function.
          changeTrigger(trigger_id, trigger);
        });
        // Trigger initial reaction, called upon attachment.
        changeTrigger(trigger_id, trigger);
      };
      setChangeTrigger(trigger_id, trigger);
    }
  };

  Drupal.behaviors.viewsChart = {
    attach: function(context) {
      Drupal.ViewsChartTools.dependentOptions.autoAttach();

      // The CTools dependent API handles disabling aggregation select lists
      // if no grouping is taking place on the table. However, we want to reset
      // all aggregation fields back to - None - when grouping is disabled.
      $(".edit-style-options-info-group-enable").change(function() {
        // If all of the groups are disabled then set aggregation options back to - None -.
        var disabled = true;
        $(".edit-style-options-info-group-enable").each(function() {
          // If any option is still enabled then 'disabled' is false.
          var val = $(this).attr('checked') || 0;
          if (val == 1) {
            disabled = false;
            $(":input:eq(" + ($(":input").index(this) + 1) + ")").show('fast');
          }
          else {
            $(":input:eq(" + ($(":input").index(this) + 1) + ")").hide('fast');
          }
        });

        // Set all aggregation values to - None -.
        if (disabled) {
          $(".edit-style-options-info-aggregation-options").val('');
          $(".edit-style-options-info-aggregation-options").attr('disabled', true);
        }
        else {
          $(".edit-style-options-info-aggregation-options").attr('disabled', false);
        }
      });

      // Initialize the change function upon attachment.
      $(".edit-style-options-info-group-enable").trigger('change');
    }
  }
})(jQuery)
