<?php

/**
 * @file
 * Provides a base class for Views Chart Tools element handlers.
 */

/**
 * Common base class for all Views Chart Tools handlers.
 */
abstract class views_chart_tools_handler_element extends views_handler_field {

  var $element_type = NULL, $element_name = NULL, $element_info = array();

  protected $element_wrapper = NULL;

  protected $extender = NULL;

  public function init(&$view, &$options) {
    $options += array(
      'table' => '',
      'id' => '',
    );
    parent::init($view, $options);
    $this->extender = $view->display['default']->handler->extender['views_chart_tools_dashboard_extender'];
  }

  /**
   * Override views_handler_field::query(). We don't actually add
   * anything to the query.
   */
  public function query() {
    return;
  }
  
  /**
   * Builds an element object (GoogleChartsChartWrapper or GoogleChartsControlWrapper).
   */
  public function build_element() {
    if (!class_exists($this->element_wrapper)) {
      return;
    }

    $class = $this->element_wrapper;
    return new $class(array(
      $this->element_info['type'] . 'Type' => $this->element_type,
      $this->element_info['type'] . 'Name' => $this->element_name,
      'containerId' => 'views-chart-tools-' . $this->element_info['type'] . '-' . $this->element_name,
      'options' => $this->cleanse_options(),
    ));
  }

  /**
   * Returns an admin summary label.
   */
  public function admin_summary() {
    return ucfirst($this->element_info['type']) . ': ' . $this->options['label'];
  }

  /**
   * Removes non-chart related options from the options array prior
   * to populating a GoogleChartsControlWrapper object.
   */
  protected function cleanse_options() {
    $options = $this->options;
    $parent_options = parent::option_definition();
    foreach ($parent_options as $option => $definition) {
      if (isset($options[$option])) {
        unset($options[$option]);
      }
    }
    return $options;
  }

  /**
   * Renders the element.
   */
  public function render($values) {
    return '<div class="views-chart-tools-' . $this->element_info['type'] . '" id="views-chart-tools-' . $this->element_info['type'] . '-' . $this->element_name . '"></div>';
  }

}
