<?php

/**
 * @file
 * Provides a handler for rendering a Google Map.
 */

/**
 * Map handler.
 */
class views_chart_tools_handler_map extends views_chart_tools_handler_chart {

  public function chart_option_definition() {
    $options['map_type'] = array('default' => 'normal');
    $options['use_map_type_control'] = array('default' => TRUE, 'bool' => TRUE);
    $options['show_tip'] = array('default' => TRUE, 'bool' => TRUE);
    return $options;
  }

  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['map_type'] = array(
      '#type' => 'select',
      '#title' => t('Map type'),
      '#options' => array(
        'normal' => t('Normal'),
        'terrain' => t('Terrain'),
        'satellite' => t('Satellite'),
        'hybrid' => t('Hybrid'),
      ),
      '#default_value' => $this->options['map_type'],
    );

    $form['use_map_type_control'] = array(
      '#type' => 'checkbox',
      '#title' => t('Display map type control'),
      '#return_value' => TRUE,
      '#default_value' => $this->options['use_map_type_control'],
    );

    $form['show_tip'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show description as tooltip'),
      '#return_value' => TRUE,
      '#default_value' => $this->options['show_tip'],
    );
  }

}
