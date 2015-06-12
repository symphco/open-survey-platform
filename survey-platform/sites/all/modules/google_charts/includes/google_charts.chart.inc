<?php

/**
 * @file
 * Base class for Google Chart.
 */

/**
 * Wrapper for chart objects.
 */
class GoogleChartsChartWrapper {

  /**
   * @var string
   *   The chart type. This must be set via GoogleChartsChart::setType() prior to render.
   */
  protected $chartType = NULL;

  /**
   * @var string
   *   The unique chart machine-name. This is used to build unique IDs for element
   *   wrappers in which the chart will be rendered.
   */
  protected $chartName = NULL;

  /**
   * @var string
   *   The html ID of the container.
   */
  protected $containerId = NULL;

  /**
   * @var GoogleChartsDataTable
   *   The chart's data table.
   */
  protected $data = NULL;

  /**
   * @var GoogleChartsOptionWrapper
   *   An options wrapper that allows chained selection of chart options.
   *
   * @see https://developers.google.com/chart/
   */
  protected $options;

  /**
   * Populates chart name and options.
   */
  public function __construct(array $options = array()) {
    // Create an options object and uset $options['options'] if it's set.
    if (isset($options['options']) && is_array($options['options'])) {
      $this->options = new GoogleChartsOptionWrapper($options['options']);
      unset($options['options']);
    }
    else {
      $this->options = new GoogleChartsOptionWrapper();
    }

    // All additional options are intended for the chart wrapper object.
    foreach ($options as $key => $value) {
      // Conver PHP's lower-case and underscores to camelCase.
      $key = $this->options->convertOption($key);
      $this->$key = $value;
    }
  }

  /**
   * Magic method: Sets a simple option value.
   */
  public function __set($name, $value) {
    return $this->setOption($name, $value);
  }

  /**
   * Magic method: Returns a simple option value.
   */
  public function __get($name) {
    // Allow direct read access to the options object.
    if ($name == 'options') {
      return $this->options;
    }

    // Otherwise, attempt to get an option value.
    $option = $this->getOption($name);
    if ($option instanceof GoogleChartsOption) {
      return $option->value();
    }
    return $option;
  }

  /**
   * Returns the chart type.
   */
  public function getChartType() {
    return $this->chartType;
  }

  /**
   * Sets the chart type.
   *
   * @param string $type
   *   The chart type.
   *
   * @return GoogleChartsChart
   *   The called object.
   */
  public function setChartType($type) {
    $this->chartType = $type;
    return $this;
  }

  /**
   * Returns the chart name.
   */
  public function getChartName() {
    return $this->chartName;
  }

  /**
   * Sets the chart name.
   *
   * @param string $name
   *   The chart name.
   */
  public function setChartName($name) {
    $this->chartName = $name;
    return $this;
  }

  /**
   * Returns the container ID of the chart.
   */
  public function getContainerId() {
    return $this->containerId;
  }

  /**
   * Sets the container ID of the chart.
   *
   * @param string $container_id
   *   The container ID to set.
   */
  public function setContainerId($container_id) {
    $this->containerId = $container_id;
    return $this;
  }

  /**
   * Returns the chart's data table.
   */
  public function getDataTable() {
    return $this->data;
  }

  /**
   * Sets the chart's data table.
   *
   * @param GoogleChartsDataTable $data
   *   The data table to be set.
   */
  public function setDataTable(GoogleChartsDataTable $data) {
    $this->data = $data;
    return $this;
  }

  /**
   * Sets an option value.
   *
   * @param string $option
   *   The option to set.
   * @param string|array $value
   *   The option value.
   */
  public function setOption($option, $value) {
    $this->options->set($option, $value);
  }

  /**
   * Sets the chart options object.
   *
   * @param GoogleChartsOptionWrapper $options
   *   The options object to set.
   *
   * @return GoogleChartsChart
   *   The called object.
   */
  public function setOptions(GoogleChartsOptionWrapper $options) {
    $this->options = $options;
    return $this;
  }

  /**
   * Returns an option value.
   *
   * @param string $option
   *   The option to return.
   */
  public function getOption($option) {
    return $this->options->get($option);
  }

  /**
   * Returns chart options object.
   */
  public function getOptions() {
    return $this->options;
  }

  /**
   * Draws the chart.
   */
  public function draw() {
    if (!isset($this->chartType) || !isset($this->data)) {
      throw new GoogleChartsException(t('Incomplete chart data.'));
    }

    $options = $this->options->build();

    // Ensure that container dimensions are set.
    if (!isset($options['width']) && isset($options['chartArea']['width']) && is_numeric($options['chartArea']['width'])) {
      $options['width'] = $options['chartArea']['width'] + 100;
    }
    
    if (!isset($options['height']) && isset($options['chartArea']['height']) && is_numeric($options['chartArea']['height'])) {
      $options['height'] = $options['chartArea']['height'] + 100;
    }

    $settings = array(
      'container' => $this->containerId,
      'columns' => $this->data->buildColumns(),
      'rows' => $this->data->buildRows(),
      'groups' => $this->data->buildGroups(),
    );

    $settings['definition'] = array(
      'chartType' => $this->chartType,
      'chartName' => $this->chartName,
      'containerId' => $this->containerId,
      'options' => $options,
    );

    google_charts_add_js('chart', $this->containerId, $settings);

    return '';
  }

  /**
   * Renders the chart via print or echo.
   */
  public function __toString() {
    return $this->draw();
  }

}

/**
 * Base chart class.
 */
abstract class GoogleChartsChart {

  // Define references to Google visualization classes (chart types).
  const AREA_CHART = 'AreaChart',
  BAR_CHART = 'BarChart',
  COLUMN_CHART = 'ColumnChart',
  LINE_CHART = 'LineChart',
  PIE_CHART = 'PieChart',
  SCATTER_CHART = 'ScatterChart',
  TABLE = 'Table',
  ANNOTATED_TIMELINE = 'AnnotatedTimeline';

  /**
   * @var string
   *   The Google Visualization API chart class. This must be set
   *   in the constructor of classes that extend this class.
   */
  protected $type;

  /**
   * @var string
   *   The HTML element ID of the container of this chart.
   */
  protected $container;

  public function __construct($container) {
    $this->container = $container;
  }

  /**
   * Draws the chart.
   */
  public function draw(GoogleChartsDataTable $data, array $options = array()) {
    if (!isset($this->type)) {
      throw new GoogleChartsException(t('Attempt to draw chart of type <unknown>.'));
    }

    $wrapper = new GoogleChartsChartWrapper(array('options' => $options));
    $wrapper->setChartType($this->type);
    $wrapper->setContainerId($this->container);
    $wrapper->setDataTable($data);

    return $wrapper->draw();
  }

}

/**
 * Area chart.
 */
class GoogleChartsAreaChart extends GoogleChartsChart {
  public function __construct($container) {
    $this->type = GoogleChartsChart::AREA_CHART;
    parent::__construct($container);
  }
}

/**
 * Bar chart.
 */
class GoogleChartsBarChart extends GoogleChartsChart {
  public function __construct($container) {
    $this->type = GoogleChartsChart::BAR_CHART;
    parent::__construct($container);
  }
}

/**
 * Column chart.
 */
class GoogleChartsColumnChart extends GoogleChartsChart {
  public function __construct($container) {
    $this->type = GoogleChartsChart::COLUMN_CHART;
    parent::__construct($container);
  }
}

/**
 * Line chart.
 */
class GoogleChartsLineChart extends GoogleChartsChart {
  public function __construct($container) {
    $this->type = GoogleChartsChart::LINE_CHART;
    parent::__construct($container);
  }
}

/**
 * Pie chart.
 */
class GoogleChartsPieChart extends GoogleChartsChart {
  public function __construct($container) {
    $this->type = GoogleChartsChart::PIE_CHART;
    parent::__construct($container);
  }
}

/**
 * Scatter chart.
 */
class GoogleChartsScatterChart extends GoogleChartsChart {
  public function __construct($container) {
    $this->type = GoogleChartsChart::SCATTER_CHART;
    parent::__construct($container);
  }
}

/**
 * Table.
 */
class GoogleChartsTableChart extends GoogleChartsChart {
  public function __construct($container) {
    $this->type = GoogleChartsChart::TABLE;
    parent::__construct($container);
  }
}

/**
 * Annotated timeline.
 */
class GoogleChartsAnnotatedTimelineChart extends GoogleChartsChart {
  public function __construct($container) {
    $this->type = GoogleChartsChart::ANNOTATED_TIMELINE;
    parent::__construct($container);
  }
}

/**
 * Exception class for GoogleCharts.
 */
class GoogleChartsException extends Exception {}
