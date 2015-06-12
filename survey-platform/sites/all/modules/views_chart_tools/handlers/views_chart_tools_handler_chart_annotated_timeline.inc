<?php

/**
 * @file
 * Provides a handler for the annotated timeline chart.
 */

/**
 * Annotated timeline chart handler.
 */
class views_chart_tools_handler_chart_annotated_timeline extends views_chart_tools_handler_chart {

  public function chart_option_definition() {
    $options['width'] = array('default' => '400');
    $options['height'] = array('default' => '400');
    return $options;
  }

  /**
   * Defines an options form for the chart type.
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $this->dimension_options_form($form, $form_state);
  }

  /**
   * Renders the element.
   */
  public function render($values) {
    return '<div class="views-chart-tools-' . $this->element_info['type'] . '" id="views-chart-tools-' . $this->element_info['type'] . '-' . $this->element_name . '" style="width:' . $this->options['width'] . 'px;height:' . $this->options['height'] . 'px"></div>';
  }

}
