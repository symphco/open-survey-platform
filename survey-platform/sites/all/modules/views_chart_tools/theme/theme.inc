<?php

/**
 * @file
 * Preprocess callbacks for Views Charts.
 */

/**
 * Preprocess callback for theming Views Chart dashboard style.
 */
function template_preprocess_views_chart_tools_dashboard(&$vars) {
  if (!isset($vars['view']->display_handler->extender['views_chart_tools_dashboard_extender'])) {
    return;
  }

  drupal_add_css(drupal_get_path('module', 'views_chart') . '/css/views_chart_tools.css');

  // Get the display extender.
  $view = &$vars['view'];
  $display_extender = $view->display_handler->extender['views_chart_tools_dashboard_extender'];

  $elements = $display_extender->get_option('dashboard_elements');
  $info = views_chart_tools_element_info();

  $vars['elements'] = array();
  $items = array('control' => array(), 'chart' => array());
  foreach ($elements as $name => $element) {
    $handler = $display_extender->get_handler($element['element_type'], $name, !empty($element['options']) ? $element['options'] : array());
    if (!$handler || !isset($info[$element['element_type']]['type']) || !in_array($info[$element['element_type']]['type'], array('chart', 'control'))) continue;
    // Render the element using the field handler. This should allow users
    // to wrap charts and controls in custom CSS, etc.
    $vars['elements'][$name] = $handler->theme('');

    // Create the actual element object - chart or control - used for binding elements together later.
    $items[$info[$element['element_type']]['type']][] = $handler->build_element();
  }

  // Build the data table.
  $data = $view->style_plugin->build_data_table($vars['rows']);
  
  // Create the dashboard ID. This will be used regardless of whether a
  // dashboard is actually created (see below). This ensures that CSS
  // and jQuery selectors will still work as expected.
  $vars['dashboard_id'] = 'views-chart-tools-dashboard-' . $view->name;

  // If $items['control'] is empty then we need to render each chart individually.
  if (empty($items['control'])) {
    foreach ($items['chart'] as $name => $chart_wrapper) {
      $chart_wrapper->setDataTable($data)->draw();
    }
  }
  // If the view has at least one control and one chart then we need
  // to create a dashboard.
  elseif (!empty($items['chart'])) {
    $dashboard = new GoogleChartsDashboard($vars['dashboard_id']);

    // Bind all controls and charts.
    if (!empty($items['control']) || !empty($items['chart'])) {
      $dashboard->bind($items['control'], $items['chart']);
    }

    // Finally, draw the dashboard. This won't actually output anything, but it will
    // pass our data table and bindings to Javascript for actual assembly.
    $dashboard->draw($data);
  }
  // If we've made it this far then we know that no charts have been defined,
  // though there may be some controls, but *both are required*.
  else {
    drupal_set_message(t('Failed to render dashboard. No charts have been defined.'));
  }
}
