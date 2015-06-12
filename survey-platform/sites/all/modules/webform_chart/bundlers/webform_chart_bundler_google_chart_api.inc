<?php

/**
 * @file
 * webform_chart_bundler_google_chart_api.module
 *
 * This module provides a bundler between Webform Chart module and 
 * Google Chart API module. It let's Webform Chart module use the Google
 * Chart API to render the graphs.
 */

/*
 * ---------------------------------------------------------------------
 * HOOKS IMPLEMENTATIONS
 * ---------------------------------------------------------------------
 */

/**
 * Implements hook_wfc_backend_help().
 *
 * Display the information about this bundler (when activated) in the charting
 * configuration of a component.
 */
function webform_chart_bundler_google_chart_api_wfc_backend_help() {

  $help = array(
    t('<b>!chart_link</b> - a Drupal module that uses Google image charts API. (requires !chart_link, <b>!installed</b>)',
      array(
        '!chart_link' => l(t('Google Chart API'), 'http://drupal.org/project/chart'),
        '!installed' => module_exists('chart') ? t('Installed') : t('Not Installed'),
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
function webform_chart_bundler_google_chart_api_wfc_backend() {
  $backend = array();
  if (module_exists('chart')) {
    $backend['webform_chart_bundler_google_chart_api'] = t('Google Chart API');
  }
  return $backend;
}

/**
 * Implements hook_wfc_backend_configure().
 *
 * Google Chart API, charts-specific configuration form that is called 
 * from webform_chart_form in webform_chart.admin.inc
 */
function webform_chart_bundler_google_chart_api_wfc_backend_configure($default_values) {

  $types = chart_types();
  $items = array(
    'type' => array(
      '#type'             => 'select',
      '#title'            => t('Chart Type'),
      '#options'          => $types,
      '#default_value'    => isset($default_values['type']) ? $default_values['type'] : 'p3',
      '#description'      => '<b>' . t('Required') . ' :</b>' . t('Select a chart type for rendering webform charts'),
    ),
    'width' => array(
      '#type'             => 'textfield',
      '#title'            => t('Chart Width'),
      '#default_value'    => isset($default_values['width']) ? $default_values['width'] : 400,
      '#element_validate' => array('element_validate_integer_positive'),
      '#description'      => '<b>' . t('Required') . ' :</b>' . t('Enter the chart width as an integer'),
      '#size'             => 4,
    ),
    'height' => array(
      '#type'             => 'textfield',
      '#title'            => t('Chart Height'),
      '#default_value'    => isset($default_values['height']) ? $default_values['height'] : 300,
      '#element_validate' => array('element_validate_integer_positive'),
      '#description'      => '<b>' . t('Required') . ' :</b>' . t('Enter the chart height as an integer'),
      '#size'             => 4,
    ),

    'bar_size' => array(
      '#type'             => 'textfield',
      '#title'            => t('Chart Bar Width'),
      '#default_value'    => isset($default_values['bar_size']) ? $default_values['bar_size'] : 50,
      '#description'      => '<b>' . t('Optional') . ' :</b>' . t('Enter bar sizes as an integer (only applicable to bar-type charts)'),
      '#element_validate' => array('element_validate_integer_positive'),
      '#size'             => 4,
    ),
    'bar_spacing' => array(
      '#type'             => 'textfield',
      '#title'            => t('Chart Bar Spacing'),
      '#default_value'    => isset($default_values['bar_spacing']) ? $default_values['bar_spacing'] : 20,
      '#description'      => '<b>' . t('Optional') . ' :</b>' . t('Enter bar spacing as an integer (only applicable to bar-type charts)'),
      '#element_validate' => array('element_validate_integer_positive'),
      '#size'             => 4,
    ),
  );
  return $items;
}

/**
 * Implements hook_wfc_component_validate().
 *
 * Used to validate the component charting configuration form.
 */
function webform_chart_bundler_google_chart_api_wfc_component_validate(&$component) {

  $config = array();
  $config['type'] = $component['values']['type'];
  $config['width'] = $component['values']['width'];
  $config['height'] = $component['values']['height'];
  $config['bar_size'] = $component['values']['bar_size'];
  $config['bar_spacing'] = $component['values']['bar_spacing'];

  return $config;
}

/**
 * Implements hook_wfc_component_render().
 *
 * The main rendering function for charts that actually turns data into charts.
 */
function webform_chart_bundler_google_chart_api_wfc_component_render($chart) {

  $output = '';
  $config = $chart['#config']['config'];
  if (array_key_exists('#data', $chart)) {
    $chart['#title'] = '';
    $chart['#type'] = $config['type'];
    $chart['#size'] = chart_size($config['width'], $config['height']);
    $chart['#bar_size'] = chart_bar_size($config['bar_size'], $config['bar_spacing']);
    $output .= '<div class="webform-chart-container" id="webform-chart-' . check_plain($chart['#chart_id']) . '">' .
      theme('chart', array('chart' => $chart)) . "</div>";
  }

  return $output;
}
