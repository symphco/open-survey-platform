<?php

/**
 * @file
 * Provides administration functions for the webform_chart module.
 */


/**
 * Provides an administration form for the webform_chart module.
 *
 * Enabling administrator roles to specify a back end to use for rendering
 * charts and configure those back ends. This invokes all 
 * #module_name#_webform_chart_backends functions so other modules may provide
 * additional back ends and configuration data.
 */
function _webform_chart_form_configure(&$form, &$form_state) {

  // Retrieve existing configuration (if existing).
  $config = unserialize($form['#node']->webform['charting']);

  // Get all possible rendering back-ends.
  $backends = array_merge(array('none' => t('None')), module_invoke_all('wfc_backend'));

  $form['charting'] = array(
    '#type' => 'fieldset',
    '#title' => t('Webform Chart Back-end'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  // Choose the rendering backend.
  $form['charting']['backend'] = array(
    '#type' => 'select',
    '#title' => t('Select Back-end'),
    '#options'       => $backends,
    '#default_value' => isset($config['backend']) ? $config['backend'] : 'none',
    '#description' => t('Select a back-end to use for rendering webform charts'),
  );

  // Display the help section: the available backends.
  $form['charting']['help'] = array(
    '#markup' => theme('webform_chart_form_help'),
  );

  // Choose the setting mode: either global or per component.
  $methods = array(0 => t('Global settings'), 1 => t('Per component settings'));
  $form['charting']['config_method'] = array(
    '#type' => 'radios',
    '#title' => t('Configuration method'),
    '#default_value' => isset($config['config_method']) ? $config['config_method'] : 1,
    '#options' => $methods,
    '#description' => t('Choose either to activate a per component setting for the charts or global settings for this form to be replicated on all components.'),
    '#states' => array(
      'invisible' => array(
        'select[id="edit-backend"]' => array(
          'value' => 'none',
        ),
      ),
    ),
  );

  // Display backend configuration (only if global settings mode).
  foreach ($backends as $backend => $display) {
    if ($backend && $backend != 'none') {
      $fn = $backend . '_wfc_backend_configure';
      $form['charting']['backend_config_' . $backend] = array(
        '#type' => 'fieldset',
        '#title' => t('@display Configuration', array('@display' => $display)),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#states' => array(
          'expanded' => array(
            ':input[name="config_method"]' => array(
              'value' => '0',
            ),
            'select[id="edit-backend"]' => array(
              'value' => $backend,
            ),
          ),
          'visible' => array(
            ':input[name="config_method"]' => array(
              'value' => '0',
            ),
            'select[id="edit-backend"]' => array(
              'value' => $backend,
            ),
          ),
        ),
      );
      if (function_exists($fn)) {
        // If the form was previously saved as a
        // "per component" setting mode, index config does not exist.
        if (!isset($config['config'])) {
          $config['config'] = array();
        }
        $backend_config = $fn($config['config']);
        $form['charting']['backend_config_' . $backend] = array_merge($form['charting']['backend_config_' . $backend], $backend_config);
      }
    }
  }
}

/**
 * Provides a validation handler for administration form.
 *
 * Enable backend configuration validation if necessay.
 * This invokes all *module_name*_wbc_backends_configuration_validate functions
 * so other modules may provide additional back ends validation process.
 *
 * The *module_name*_wbc_backends_configuration_validate must return an array 
 * "key/value" to be display in form_set_error function using form_set_error
 */
function _webform_chart_form_configure_validate(&$form, &$form_state) {

  $node = &$form['#node'];
  // Get the global configuration.
  $config = array();
  $config['backend'] = $form_state['values']['backend'];
  $config['config_method'] = $form_state['values']['config_method'];

  // Call the backend specific form validation.
  if ($form_state['values']['config_method'] == 0) {
    $backend = $form_state['values']['backend'];
    $fn = $backend . '_wfc_component_validate';
    if (function_exists($fn)) {
      $config['config'] = $fn($form_state);
    }
  }
  $node->webform['charting'] = serialize($config);
}

/**
 * Provides a saving handler for administration form.
 *
 * Enable backend configuration saving if necessay.
 * This invokes all *module_name*_wfc_backend_configuration_save functions
 * so other modules may provide additional backends saving process.
 *
 * The *module_name*_wfc_backend_configuration_save must return an array of:
 *    "key/value" to be display in form_set_error function using form_set_error
 */
function _webform_chart_form_configure_save(&$form, &$form_state) {
  // Save the global confirmation.
  node_save($form['#node']);
}

/**
 * Theme function for administration help. 
 *
 * This checks for the existence / installation of requisite modules 
 * and provides download links as well.
 */
function theme_webform_chart_form_help() {
  $basic_help = '<p>' . t('Chose a back-end to render webform data with. Available back ends include:') . '</p>';

  $helps = module_invoke_all('wfc_backend_help');
  array_unshift($helps, $basic_help);
  $output = '';
  foreach ($helps as $help) {
    $output .= '<div class="webform_chart_help_section">' . $help . '</div>';
  }

  return $output;
}

/**
 * Ajax callback implementation.
 *
 * Used in each component edit form to render the backend config.
 */
function webform_chart_form_configure_ajax_callback($form, $form_state) {
  return $form['charting']['backend_config'];
}


/*
 * ------------------------------------------------------------------------
 * HOOKS IMPLEMENTATIONS
 * ------------------------------------------------------------------------
 */

/**
 * Implements hook_wfc_backend().
 */
function webform_chart_wfc_backend() {
  $backends = array();
  $bundlers = file_scan_directory(drupal_get_path('module', 'webform_chart') . '/bundlers', '/.*\.inc$/');
  foreach ($bundlers as $bundler) {
    $fn = $bundler->name . '_wfc_backend';
    if (function_exists($fn)) {
      $backends = array_merge($backends, $fn());
    }
  }
  return $backends;
}

/**
 * Implements hook_wfc_backend_help().
 */
function webform_chart_wfc_backend_help() {
  $backends = array();
  $bundlers = file_scan_directory(drupal_get_path('module', 'webform_chart') . '/bundlers', '/.*\.inc$/');
  foreach ($bundlers as $bundler) {
    $fn = $bundler->name . '_wfc_backend_help';
    if (function_exists($fn)) {
      $backends = array_merge($backends, $fn());
    }
  }
  return $backends;
}
