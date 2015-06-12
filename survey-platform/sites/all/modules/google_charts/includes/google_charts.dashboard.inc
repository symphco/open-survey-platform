<?php

/**
 * @file
 * Wrapper for Google Chart Tools dashboard feature.
 */

/**
 * Provides a public API for creating dashboards.
 */
class GoogleChartsDashboard {

  /**
   * @var string
   *   The element ID of the container element that will hold this dashboard.
   */
  protected $container;

  /**
   * @var array
   *   An associative array of bindings between control and charts.
   */
  protected $bindings = array();

  public function __construct($container) {
    $this->container = $container;
  }

  /**
   * Returns container IDs for all bindings of the given type (controls or charts).
   */
  public function getContainerIds($type) {
    $ids = array();
    foreach ($this->bindings as $binding) {
      if (isset($binding[$type])) {
        $ids += array_keys($binding[$type]);
      }
    }
    return $ids;
  }

  /**
   * Returns an array of container IDs for all controls bound in this dashboard.
   */
  public function getControlContainerIds() {
    $ids = array();
    foreach ($this->bindings as $binding) {
      $ids = array_merge($ids, array_keys($binding['controls']));
    }
    return $ids;
  }

  /**
   * Returns an array of container IDs for all charts bound in this dashboard.
   */
  public function getChartContainerIds() {
    $ids = array();
    foreach ($this->bindings as $binding) {
      $ids = array_merge($ids, array_keys($binding['charts']));
    }
    return $ids;
  }

  /**
   * Returns the dashboard's container ID.
   */
  public function getContainerId() {
    return $this->container;
  }

  /**
   * Binds control(s) to chart(s).
   *
   * @param GoogleChartsControl|array $controls
   *   A control object or array of control objects.
   * @param GoogleChartsChart|array $charts
   *   A chart object or array of chart objects.
   */
  public function bind($controls, $charts) {
    // Convert controls to array if we were passed a single control.
    if (!is_array($controls)) {
      $controls = array($controls);
    }

    if (!is_array($charts)) {
      $charts = array($charts);
    }

    $binding = array(
      'controls' => array(),
      'charts' => array(),
    );

    // Add controls to the binding.
    foreach ($controls as $control) {
      if (!$control instanceof GoogleChartsControlWrapper) {
        throw new GoogleChartsException(t('Invalid control wrapper.'));
      }
      $binding['controls'][$control->getContainerId()] = $control;
    }

    // Add charts to the binding.
    foreach ($charts as $chart) {
      if (!$chart instanceof GoogleChartsChartWrapper) {
        throw new GoogleChartsException(t('Invalid control wrapper.'));
      }
      $binding['charts'][$chart->getContainerId()] = $chart;
    }

    // Finally, add the binding to the bindings array.
    $this->bindings[] = $binding;

    return $this;
  }

  /**
   * Draws the dashboard.
   */
  public function draw(GoogleChartsDataTable $data) {
    // Prepare data table arrays for theming.
    $settings = array(
      'container' => $this->container,
      'columns' => $data->buildColumns(),
      'rows' => $data->buildRows(),
      'groups' => $data->buildGroups(),
    );

    // Add binding information.
    $settings['bindings'] = array();
    foreach ($this->bindings as $binding) {
      $definition = array();

      // Add control information.
      foreach ($binding['controls'] as $container_id => $control) {
        $definition['controls'][] = array(
          'containerId' => $control->getContainerId(),
          'controlType' => $control->getControlType(),
          'controlName' => $control->getControlName(),
          'options' => $control->getOptions()->build(),
        );
      }

      // Add chart information.
      foreach ($binding['charts'] as $container_id => $chart) {
        $definition['charts'][] = array(
          'containerId' => $chart->getContainerId(),
          'chartType' => $chart->getChartType(),
          'chartName' => $chart->getChartName(),
          'options' => $chart->getOptions()->build(),
        );
      }

      $settings['bindings'][] = $definition;
    }

    google_charts_add_js('dashboard', $this->container, $settings);

    return '';
  }

  /**
   * Renders the dashboard via print or echo.
   */
  public function __toString() {
    return $this->draw();
  }

}
