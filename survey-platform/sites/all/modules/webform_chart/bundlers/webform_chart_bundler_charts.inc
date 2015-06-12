<?php

/**
 * @file
 * This module provides a bundler between Webform Chart module and Charts
 * module. It let's Webform Chart module use the Charts API to render the 
 * graphs.
 */

/*
 * -----------------------------------------------------------------------
 * HOOKS IMPLEMENTATIONS
 * -----------------------------------------------------------------------
 */

/**
 * Implemts hook_wfc_backend_help().
 *
 * Display the information about this bundler (when activated) in the charting
 * configuration of a component.
 */
function webform_chart_bundler_charts_wfc_backend_help() {
  $help = array(
    t('<b>!charts_link</b> - a Drupal module that uses either Google Visualization API or HighCharts. (requires !charts_link, <b>!installed</b>)',
      array(
        '!charts_link' => l(t('Charts module'), 'http://drupal.org/project/charts'),
        '!installed' => module_exists('charts') ? t('Installed') : t('Not Installed'),
      )
    ),
  );
  return $help;
}

/**
 * Implements hook_wfc_backend().
 *
 * Add an option in the backend select box for this option.
 * NOTE: the key value MUST be the name of this bundler module.
 */
function webform_chart_bundler_charts_wfc_backend() {
  $backend = array();
  if (module_exists('charts')) {
    $backend['webform_chart_bundler_charts'] = t('Charts module');
  }
  return $backend;
}

/**
 * Implements hook_wfc_backend_configure().
 *
 * Google Chart API, charts-specific configuration form that is called from
 * webform_chart_form in webform_chart.admin.inc
 */
function webform_chart_bundler_charts_wfc_backend_configure($default_values) {

  $chart_types = charts_type_info();
  $type_options = array();
  foreach ($chart_types as $chart_type => $chart_type_info) {
    $type_options[$chart_type] = $chart_type_info['label'];
  }
  $items = array(
    'charts_type' => array(
      '#type'             => 'select',
      '#title'            => t('Chart Type'),
      '#options'          => $type_options,
      '#default_value'    => isset($default_values['#chart_type']) ? $default_values['#chart_type'] : 0,
      '#description'      => '<b>' . t('Required') . ' :</b>' . t('Select a chart type for rendering webform charts'),
    ),
    'charts_width' => array(
      '#type'             => 'textfield',
      '#title'            => t('Chart Width'),
      '#default_value'    => isset($default_values['#width']) ? $default_values['#width'] : NULL,
      '#description'      => '<b>' . t('Optional') . ' :</b>' . t('Enter the chart width as an integer'),
      '#element_validate' => array('element_validate_integer_positive'),
      '#size'             => 4,
    ),
    'charts_height' => array(
      '#type'             => 'textfield',
      '#title'            => t('Chart Height'),
      '#default_value'    => isset($default_values['#height']) ? $default_values['#height'] : NULL,
      '#description'      => '<b>' . t('Optional') . ' :</b>' . t('Enter the chart height as an integer'),
      '#element_validate' => array('element_validate_integer_positive'),
      '#size'             => 4,
    ),
  );
  return $items;
}

/**
 * Implements hook_wfc_component_validate().
 *
 * Used to validate the component charting configuration form
 */
function webform_chart_bundler_charts_wfc_component_validate(&$component) {

  $config = array();
  $config['#chart_type'] = $component['values']['charts_type'];
  $config['#width'] = $component['values']['charts_width'];
  $config['#height'] = $component['values']['charts_height'];

  return $config;
}

/**
 * Implements hook_wfc_component_render().
 *
 * The main rendering function for charts that actually turns data into charts.
 */
function webform_chart_bundler_charts_wfc_component_render($chart) {

  $output = '';
  $item = $chart['#config']['config'];
  if (array_key_exists('#data', $chart)) {
    $item['data'] = $chart;
    $item['data']['#type'] = 'chart_data';
    $item['#type'] = 'chart';
    $item['#title'] = '';
    $item['#chart_type'] = $item['#chart_type'];
    $item['#chart_library'] = 'google';
    $item['#legend_position'] = 'right';
    $item['#data_labels'] = TRUE;
    $item['#tooltips'] = TRUE;

    $output .= '<div class="webform-chart-container" id="webform-chart-' . check_plain($chart['#chart_id']) . '">' .
      drupal_render($item) . "</div>";
  }

  return $output;
}
