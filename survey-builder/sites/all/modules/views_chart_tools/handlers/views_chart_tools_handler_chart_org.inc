<?php

/**
 * @file
 * Provides a handler for the organizational chart.
 */

/**
 * Organizational chart handler.
 */
class views_chart_tools_handler_chart_org extends views_chart_tools_handler_chart {

  public function chart_option_definition() {
    $options['size'] = array('default' => 'medium');
    return $options;
  }

  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['size'] = array(
      '#type' => 'select',
      '#title' => t('Size'),
      '#options' => array(
        'small' => t('Small'),
        'medium' => t('Medium'),
        'large' => t('Large'),
      ),
      '#default_value' => $this->options['size'],
    );
  }

}
