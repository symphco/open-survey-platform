<?php

/**
 * @file
 * views_aggregator.views.inc
 */

/**
 * Implements hook_views_plugins().
 */
function views_aggregator_views_plugins() {
  $base_path = drupal_get_path('module', 'views_aggregator');
  $plugins['style']['views_aggregator'] = array(
    'title' => t('Table with aggregation options'),
    'help' => t('Creates a tabular UI for the user to define aggregation functions.'),
    'handler' => 'views_aggregator_plugin_style_table',
    // 'theme' name implies views-aggregator-results-table.tpl.php
    // and template_preprocess_views_aggregator_results_table($vars)
    'theme' => 'views_aggregator_results_table',
    // 'theme path' applies to .tpl.php and 'theme file', unless overriden
    // by hook_theme().
    'theme path' => $base_path . '/views',
    // 'theme file' => 'theme_views_aggregator_plugin_style_table.inc',
    'uses row plugin' => FALSE,
    'uses row class' => TRUE,
    'uses fields' => TRUE,
    'uses options' => TRUE,
    'type' => 'normal',
    'help topic' => 'style-table',
  );
  return $plugins;
}
