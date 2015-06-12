<?php

class views_chart_tools_handler_control_chart_range_filter extends views_chart_tools_handler_control {

  public function option_definition() {
    $options = parent::option_definition();
    $options['ui'] = array('default' => array());
    return $options;
  }

  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $this->ui_options_form($form, $form_state);
  }

}
