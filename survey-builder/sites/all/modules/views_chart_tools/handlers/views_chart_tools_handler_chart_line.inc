<?php

/**
 * @file
 * Provides a handler for line charts.
 */

/**
 * Line chart handler.
 */
class views_chart_tools_handler_chart_line extends views_chart_tools_handler_chart {

  public function chart_option_definition() {
    $options['width'] = array('default' => '400');
    $options['height'] = array('default' => '400');
    $options['animation'] = array('default' => array());
    $options['chart_area'] = array('default' => array());
    $options['background_color'] = array('default' => array());
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
    $this->horizontal_axis_options_form($form, $form_state);
    $this->vertical_axis_options_form($form, $form_state);
    $this->legend_options_form($form, $form_state);
    $this->tooltip_options_form($form, $form_state);
  }

}
