<?php

/**
 * @file
 * Includes only functions used in administration pages.
 */

/**
 * Configuration page.
 */
function form_placeholder_admin_settings() {
  $form = array();

  $rows = array(
    array('input, textarea', t('Use all single line text fields and textareas on site.')),
    array('.your-form-class *', t('Use all text fields in given form class.')),
    array('#your-form-id *', t('Use all text fields in given form id.')),
    array('#your-form-id *:not(textarea)', t('Use all single line text fields but  not textareas in given form id.')),
    array('#your-form-id input:not(input[type=password])', t('Use all single line text fields but not password text fields in given form id.')),
  );

  $table = array(
    'header' => array(t('CSS selector'), t('Description')),
    'rows' => $rows,
  );

  $form['selectors'] = array(
    '#type' => 'fieldset',
    '#title' => t('Visibility settings'),
  );
  $form['selectors']['form_placeholder_include'] = array(
    '#type' => 'textarea',
    '#title' => t('Include text fields matching the pattern'),
    '#description' => t('CSS selectors (one per line).'),
    '#default_value' => variable_get('form_placeholder_include', ''),
  );
  $form['selectors']['form_placeholder_exclude'] = array(
    '#type' => 'textarea',
    '#title' => t('Exclude text fields matching the pattern'),
    '#description' => t('CSS selectors (one per line).'),
    '#default_value' => variable_get('form_placeholder_exclude', ''),
  );
  $form['selectors']['examples'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Examples'),
  );
  $form['selectors']['examples']['content'] = array(
    '#markup' => theme('table', $table),
  );
  $form['form_placeholder_required_indicator'] = array(
    '#type' => 'radios',
    '#title' => t('Required field marker'),
    '#options' => array(
      'append' => t('Append star after text field'),
      'leave' => t('Leave star inside placeholder'),
      'remove' => t('Remove star'),
      'text' => t('Instead of star append text "(required)" to placeholder'),
    ),
    '#default_value' => variable_get('form_placeholder_required_indicator', 'append'),
  );

  return system_settings_form($form);
}
