<?php
/**
 * @file
 * theme_views_aggregator_plugin_style_table.inc
 *
 * Themes the View UI created in the class views_aggregator_plugin_style_table.
 * Based on similar functions in both Views and Views Calc modules.
 */

/**
 * Theme the form for the table style plugin.
 */
function theme_views_aggregator_plugin_style_table($variables) {
  $form = $variables['form'];

  $output = drupal_render($form['description_markup']);

  // Note these are currently in the Views Calc rather than Views table order.
  $header = array(
    t('Field'),
    t('Align'),
    t('Group aggregation'),
    t('Column aggregation'),
    t('Render column'),
    t('Separator'),
    array(
      'data' => t('Sortable'),
      'align' => 'center',
    ),
    array(
      'data' => t('Default sort'),
      'align' => 'center',
    ),
    array(
      'data' => t('Default order'),
      'align' => 'center',
    ),
    array(
      'data' => t('Hide empty column'),
      'align' => 'center',
    ),
  );

  $rows = array();
  foreach (element_children($form['columns']) as $id) {
    $row = array();
    $row[] = drupal_render($form['info'][$id]['name']);
    $row[] = drupal_render($form['info'][$id]['align']);
    $row[]
      = drupal_render($form['info'][$id]['has_aggr'])
      . drupal_render($form['info'][$id]['aggr'])
      . drupal_render($form['info'][$id]['aggr_par']);
    $row[]
      = drupal_render($form['info'][$id]['has_aggr_column'])
      . drupal_render($form['info'][$id]['aggr_column'])
      . drupal_render($form['info'][$id]['aggr_par_column']);
    $row[] = drupal_render($form['columns'][$id]);
    $row[] = drupal_render($form['info'][$id]['separator']);
    if (!empty($form['info'][$id]['sortable'])) {
      $row[] = array(
        'data' => drupal_render($form['info'][$id]['sortable']),
        'align' => 'center',
      );
      $row[] = array(
        'data' => drupal_render($form['default'][$id]),
        'align' => 'center',
      );
      $row[] = array(
        'data' => drupal_render($form['info'][$id]['default_sort_order']),
        'align' => 'center',
      );
    }
    else {
      $row[] = '';
      $row[] = '';
      $row[] = '';
    }
    $row[] = array(
      'data' => drupal_render($form['info'][$id]['empty_column']),
      'align' => 'center',
    );
    $rows[] = $row;
  }
  // Add the special 'None' row.
  $rows[] = array(
    t('None'),
    '',
    '',
    '',
    '',
    '',
    '',
    array(
      'align' => 'center',
      'data' => drupal_render($form['default'][-1]),
    ),
    '',
    '',
  );
  $output .= theme('table', array('header' => $header, 'rows' => $rows));
  $output .= drupal_render_children($form);
  return $output;
}
