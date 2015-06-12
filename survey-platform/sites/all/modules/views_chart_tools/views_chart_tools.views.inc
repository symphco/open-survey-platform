<?php

/**
 * @file
 * Implements Views hooks for Views Chart Tools module.
 */

/**
 * Implements hook_views_plugins().
 */
function views_chart_tools_views_plugins() {
  return array(
    'style' => array(
      'views_chart_tools_dashboard' => array(
        'title' => t('Google Charts Dashboard'),
        'help' => t('Renders view results as a Google Chart Tools dashboard.'),
        'handler' => 'views_chart_tools_plugin_style_dashboard',
        'theme' => 'views_chart_tools_dashboard',
        'theme path' => drupal_get_path('module', 'views_chart_tools') . '/theme',
        'theme file' => 'theme.inc',
        'uses options' => TRUE,
        'uses grouping' => FALSE,
        'uses row plugin' => FALSE,
        'uses row class' => FALSE,
        'uses fields' => TRUE,
        'even empty' => FALSE,
        'js' => array(drupal_get_path('module', 'google_charts') . '/js/google_charts.js'),
        'type' => 'normal',
      ),
    ),
    'display_extender' => array(
      'views_chart_tools_dashboard_extender' => array(
        'title' => t('Google Charts Dashboard Assistant'),
        'help' => t('Assists the Dashboard style plugin in rendering view results in an interactive dashboard.'),
        'handler' => 'views_chart_tools_plugin_display_dashboard',
      ),
    ),
  );
}
