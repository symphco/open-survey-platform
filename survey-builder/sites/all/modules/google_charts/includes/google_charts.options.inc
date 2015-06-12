<?php

/**
 * @file
 * Defines classes for setting and preparing options for Google Chart Tools.
 */

/**
 * Represents a set of chart options.
 */
class GoogleChartsOptionWrapper {

  /**
   * @var array
   *   An associative array of options keyed by name.
   */
  protected $options = array();

  public function __construct(array $options = array()) {
    foreach ($options as $option => $value) {
      $this->set($option, $value);
    }
  }

  /**
   * Magic method: Return an option value.
   */
  public function __get($option) {
    return $this->get($option);
  }

  /**
   * Returns an option value. If the option has not yet been set then
   * a new GoogleChartsOptionWrapper is returned.
   *
   * @param string $option
   *   The option to return.
   */
  public function get($option) {
    // If we were passed a reference to a nested option then parse
    // the dot syntax and get the nested option. This will recursively
    // call the get() method without the dot syntax.
    if (strpos($option, '.') !== FALSE) {
      $option = explode('.', $option);
      foreach ($option as $key) {
        $value = $this->get($option);
      }
      return $value;
    }

    // We were passed a normal option. If it doesn't exist then create a wrapper.
    if (!isset($this->options[$option])) {
      $this->options[$option] = new GoogleChartsOptionWrapper();
    }
    return $this->options[$option];
  }

  /**
   * Magic method: Set an option.
   */
  public function __set($option, $value) {
    return $this->set($option, $value);
  }

  /**
   * Sets an option value.
   * 
   * @param string $option
   *   The option to set. The option may be passed in dot synatax to indicate
   *   the structure of the option to be set. This will be converted to an
   *   array and prepended to the $value.
   * @param mixed $value
   *   The value of the option. If an array is passed then the option
   *   will be populated recursively. For example, these two are equivalent:
   *   $chart->set('vAxis', array('maxValue' => '100', 'minValue' => '100'));
   *   $chart->vAxis->set('maxValue', '100') AND $chart->vAxis->set('minValue', '100');
   *
   * @return GoogleChartsOptionWrapper
   *   The called object.
   */
  public function set($option, $value) {
    $parts = explode('.', $option);

    // If we were passed a single option to set then set it now.
    if (count($parts) == 1) {
      return $this->setOption(array_shift($parts), $value);
    }

    // Get the option key to be used from the first array value.
    $current = array_shift($parts);

    // If there are parts left then we're not setting a single value.
    if (count($parts) == 1) { // false
      $final = array_pop($parts);
      $array = array($final => $value);
    }
    // Finally, if we had more than three parts then this was a deeply
    // nested array. We need to traverse it and populate sub-arrays.
    elseif (!empty($parts)) {
      // $options is a reference to the current position in $array.
      $array = array();
      $options = &$array;
      foreach ($parts as $part) {
        $options[$part] = array();
        $options = &$options[$part];
      }
      $options[$final] = $value;
    }

    // We want to set the entire array with first value as $option.
    return $this->setOption($current, $array);
  }

  /**
   * Sets a chart option.
   *
   * @param string $option
   *   An option string.
   * @param mixed $value
   *   The value to set.
   */
  protected function setOption($option, $value) {
    $option = $this->convertOption($option);

    // If we were passed an array or object then wrap the values.
    if (is_array($value) || $value instanceof stdClass) {

      // We need to make sure this option's value is a wrapper.
      // If it isn't, create a new wrapper for the options.
      if (!isset($this->options[$option]) || !$this->options[$option] instanceof GoogleChartsOptionWrapper) {
        $this->options[$option] = new GoogleChartsOptionWrapper();
      }

      $value = (array) $value;
      foreach ($value as $name => $option_value) {
        // If $option_value is an array or object then it will populate
        // the wrapper recursively.
        $this->options[$option]->set($name, $option_value);
      }
      return $this;
    }

    // If we've made it this far then set the option as a value.
    if (!isset($this->options[$option]) || !$this->options[$option] instanceof GoogleChartsOption) {
      $this->options[$option] = new GoogleChartsOption($option);
    }
    $this->options[$option]->set($value);

    return $this;
  }

  /**
   * Converts a key from php_syntax to objectSyntax.
   *
   * @param string $key
   *   The key to convert, in lowercase and underscores.
   *
   * @return string
   *   The converted key, in camelCase format.
   */
  public function convertOption($key) {
    $parts = explode('_', $key);
    $first = array_shift($parts);
    return lcfirst($first) . implode('', array_map('ucfirst', $parts));
  }

  /**
   * Builds an options array.
   */
  public function build() {
    $options = array();
    foreach ($this->options as $option => $value) {
      if ($value instanceof GoogleChartsOptionWrapper) {
        $options[$option] = $value->build();
      }
      elseif ($value instanceof GoogleChartsOption) {
        $options[$option] = $value->value();
      }
    }
    return $options;
  }

}

/**
 * Represents a single value option.
 */
class GoogleChartsOption {

  /**
   * @var string
   *   The option name.
   */
  protected $name;

  /**
   * @var string
   *   The option value.
   */
  protected $value = NULL;

  public function __construct($name, $value = NULL) {
    $this->name = $name;
    $this->value = $value;
  }

  /**
   * Sets the option value.
   *
   * @param mixed $value
   *   The option value to set.
   *
   * @return GoogleChartsOption
   *   The called object.
   */
  public function set($value) {
    $this->value = $value;
    return $this;
  }

  /**
   * Returns the option value.
   */
  public function value() {
    return $this->value;
  }

}
