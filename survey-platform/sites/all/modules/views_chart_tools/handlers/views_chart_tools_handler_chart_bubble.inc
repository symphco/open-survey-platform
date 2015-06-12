<?php

/**
 * @file
 * Provides a handler for the Bubble chart.
 */

/**
 * Bubble chart handler.
 */
class views_chart_tools_handler_chart_bubble extends views_chart_tools_handler_chart {
  
  public function chart_option_definition() {
    $options['width'] = array('default' => '400');
    $options['height'] = array('default' => '400');
    $options['animation'] = array('default' => array());
    $options['chart_area'] = array('default' => array());
    $options['background_color'] = array('default' => array());
    $options['bubble'] = array('default' => array());
    $options['h_axis'] = array('default' => array());
    $options['v_axis'] = array('default' => array());
    $options['legend'] = array('default' => array());
    $options['tooltip'] = array('default' => array());
    return $options;
  }
  
  /**
   * Defines an options form for the chart type.
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $this->dimension_options_form($form, $form_state);
    $this->animation_options_form($form, $form_state);
    $this->chart_area_options_form($form, $form_state);
    $this->background_color_options_form($form, $form_state);

    $form['bubble'] = array(
      '#type' => 'fieldset',
      '#title' => t('Bubble'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['bubble']['opacity'] = array(
      '#type' => 'select',
      '#title' => t('Opacity'),
      '#options' => array(
        0.0 => '0%',
        0.1 => '10%',
        0.2 => '20%',
        0.3 => '30%',
        0.4 => '40%',
        0.5 => '50%',
        0.6 => '60%',
        0.7 => '70%',
        0.8 => '80%',
        0.9 => '90%',
        1.0 => '100%',
      ),
      '#default_value' => isset($this->options['bubble']['opacity']) ? $this->options['bubble']['opacity'] : 0.8,
    );

    $this->horizontal_axis_options_form($form, $form_state);
    $this->vertical_axis_options_form($form, $form_state);
    $this->legend_options_form($form, $form_state);
    $this->tooltip_options_form($form, $form_state);
  }
  
}
