<?php

/**
 * @file
 * Provides a wrapper for Google Chart Tools controls.
 */

/**
 * Wrapper class for controls.
 */
class GoogleChartsControlWrapper {

  // Define references to Google visualization classes (control types).
  const STRING_FILTER = 'StringFilter',
        NUMBER_RANGE_FILTER = 'NumberRangeFilter',
        CATEGORY_FILTER = 'CategoryFilter',
        CHART_RANGE_FILTER = 'ChartRangeFilter';

  /**
   * @var string
   *   The html id of the container element for this control.
   */
  protected $containerId;

  /**
   * @var string
   *   The type of control. This is used to instantiate the control class.
   */
  protected $controlType = NULL;

  /**
   * @var string
   *   A unique name for the control. This is not required.
   */
  protected $controlName = NULL;

  /**
   * @var GoogleChartsOptionWrapper
   *   The control's options object.
   */
  protected $options;

  /**
   * @var mixed
   *   Noramally a string or array of object state information.
   */
  protected $state = NULL;

  public function __construct(array $options = array()) {
    // Create an options object and uset $options['options'] if it's set.
    if (isset($options['options']) && is_array($options['options'])) {
      $this->options = new GoogleChartsOptionWrapper($options['options']);
      unset($options['options']);
    }
    else {
      $this->options = new GoogleChartsOptionWrapper();
    }

    // All additional options are intended for the control wrapper object.
    foreach ($options as $key => $value) {
      // Conver PHP's lower-case and underscores to camelCase.
      $key = $this->options->convertOption($key);
      $this->$key = $value;
    }
  }

  /**
   * Magic method: return the options object (read-only).
   */
  public function __get($name) {
    if ($name == 'options') {
      return $this->options;
    }
  }

  /**
   * Returns the value of an option.
   */
  public function getOption($option) {
    return $this->options->get($option);
  }

  /**
   * Returns the control's entire options object.
   */
  public function getOptions() {
    return $this->options;
  }

  /**
   * Sets the entire options object for the control.
   *
   * @param GoogleChartsOptionWrapper $options
   *   The options object.
   */
  public function setOptions(GoogleChartsOptionWrapper $options) {
    $this->options = $options;
    return $this;
  }

  /**
   * Sets the control type.
   *
   * @param string $type
   *   Any valid control type. This is actually a class name and is
   *   used to instantiate the control object.
   */
  public function setControlType($type) {
    $this->controlType = $type;
    return $this;
  }

  /**
   * Returns the control's type.
   */
  public function getControlType() {
    return $this->controlType;
  }

  /**
   * Sets the control's unique name.
   *
   * @param string $name
   *   The control's unique name.
   */
  public function setControlName($name) {
    $this->controlName = $name;
    return $this;
  }

  /**
   * Returns the control's name.
   */
  public function getControlName() {
    return $this->controlName;
  }

  /**
   * Sets the container ID.
   *
   * @param string $container_id
   *   The container element's html ID.
   */
  public function setContainerId($container_id) {
    $this->containerId = $container_id;
    return $this;
  }

  /**
   * Returns the control's container ID.
   */
  public function getContainerId() {
    return $this->containerId;
  }

  /**
   * Sets the control's state.
   *
   * @param string|array $state
   *   Either a state string or array of state information.
   */
  public function setState($state) {
    $this->state = $state;
    return $this;
  }

  /**
   * Returns the control's state.
   */
  public function getState() {
    return $this->state;
  }

  /**
   * Draws the control.
   */
  public function draw() {
    if (!isset($this->controlType)) {
      throw new GoogleChartsException(t('Attempt to render control of type <unknown>.'));
    }
    // Currently there is no handling for rendering a control by itself.
    // This is because controls should be rendered in a dashboard, not
    // as an individual element. Therefore, dashboards will handle the
    // rendering of the control in a control wrapper.
  }

}
