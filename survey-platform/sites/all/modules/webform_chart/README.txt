AUTHORS
--------------------------------------------------------------------------------
 
 * Dominique CLAUSE ("Miroslav", https://drupal.org/user/801982)
 
Required Modules
--------------------------------------------------------------------------------

Webform (Version used: 7.x-4.0-alpha10) - http://drupal.org/project/webform

Recommended Modules (this will not create charts without at least one of these)
--------------------------------------------------------------------------------

Chart API - http://drupal.org/project/chart
Charts - http://drupal.org/project/charts

Configuration
--------------------------------------------------------------------------------

 node/%/webform/configure
   Here, you can select a back end for rendering charts. You can also select the 
   configuration mode: either global settings or per component settings.
    - global settings: 
      > select a backend-end charting API to render all chart in this webform
      > choose a unique chart type for all components within the webform
      > apply backend's settings to all components within the webform.
    - per component settings:
      > select a backend-end charting API to render all chart in this webform
      > choose a different chart type for each component within the webform
        in the component setting page.
      > apply backend's settings individually to each components.

Usage
--------------------------------------------------------------------------------

 node/%/webform-results/chart
   At this URL (substituting % for the node # of the webform), you may access
   the results of your webform, presented with charts


Notes
--------------------------------------------------------------------------------

 Note that many of the chart types available will make no sense and may not even
 work because of the types of data passed in. Eventually we will filter out
 chart types that do not work.

 Bar charts, column charts, and pie charts should all operate correctly for
 both of the rendering libraries.

 Not all components are currently supported but a hard work is put on improving 
 this.
 Grid-type components are rendered as individual questions instead of as a 
 group.
 Support was added for the webform table element module
 (http://drupal.org/project/webform_table_element) that again will take each
 constituent question and render it as stand-alone.

API
--------------------------------------------------------------------------------

 This was designed to be extensible so other charting libraries can be used
 besides the two mentioned. To implement another charting library, assuming your
 module is named 'my_module', you will need to add a hook to include the name of
 the library in the configuration section, named
 "my_module_webform_chart_backends". See webform_chart_webform_chart_backends()
 in webform_chart.admin.inc for this module's implementation.

 To render using your own charting library, you will need to write and register
 a theming implementation, again assuming your back end is called 'my_module',
 named "theme_webform_chart_render_my_module".

 To provide configuration specific to your module, you will need to provide the
 form elements for configuring your module in a function named
 "_webform_chart_backend_config_my_module", and make sure the file containing
 the function is included as is done in webform_chart_webform_chart_backends().
 See _webform_chart_backend_config_googleapilibs and
 _webform_chart_backend_config_chart in includes/googleapilibs.inc and
 includes/chart.inc.

 You can also provide configuration help specific to your chart library using
 "my_module_webform_chart_help"
