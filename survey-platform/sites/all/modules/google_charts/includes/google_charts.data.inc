<?php

/**
 * @file
 * Classes for defining and altering Google Chart Tools data tables.
 */

/**
 * Represents a data table from which the chart is rendered.
 */
class GoogleChartsDataTable {

  /**
   * @var array
   *   An array of column information.
   *   - type: The column type (number, string, date, etc)
   *   - label: The human-readable column label.
   *   - role: An optional overriding role.
   */
  protected $columns = array();

  /**
   * @var array
   *   An associative array of rows that directly correspond to the order
   *   of columns.
   */
  protected $rows = array();

  /**
   * @var array
   *   An associative array of group information.
   */
  protected $groups = array();

  /**
   * Converts an array to a data table.
   *
   * @param array $array
   *   The multidimensional, associative array.
   *
   * @return GoogleChartsDataTable
   *   The created table.
   */
  public static function arrayToDataTable(array $array, $first_row_data = FALSE) {
    $data_table = new GoogleChartsDataTable();
    if (!count($array)) {
      $data_table;
    }

    // Add the columns to the table.
    if (!$first_row_data) {
      $columns = array_shift($array);
      $sample = reset($array);
      foreach ($columns as $key => $column) {
        $data_table->addColumn(isset($sample[$key]) ? self::guessColumnType($sample[$key]) : GoogleChartsDataColumn::NUMBER, is_numeric($key) ? NULL : $key, $column);
      }
    }

    // Add the rows to the table
    foreach ($array as $key => $row) {
      $data_table->addRow($row);
    }

    return $data_table;
  }

  /**
   * Guesses the column type given its value.
   *
   * @param unknown_type $column
   */
  protected function guessColumnType($column) {
    if (is_numeric($column)) {
      return GoogleChartsDataColumn::NUMBER;
    }
    return GoogleChartsDataColumn::STRING;
  }

  /**
   * Magic method: Handles calling of getters and setters within
   * table columns and rows.
   */
  public function __call($method, $args) {
    // If no arguments were passed then this was not a call we were looking for.
    if (empty($args)) {
      return;
    }

    // Automatically handle column and row getters and setters.
    if (strpos('et', $method) === 1) {
      // Check that the requested item is set. Index will always be
      // passed first in column and row geters and setters.
      $index = reset($args);
      // Get the type of request being made (get or set).
      $type = substr($method, 0, 3);

      foreach (array('Column' => 'columns', 'Row' => 'rows') as $name => $var) {
        if (strpos($name, $method) === 3) {
          if (!isset($this->{$var}[$index])) {
            return;
          }

          // Create the method to call. For example, 'setType', by extracting
          // the method parts from the method called on this object.
          $call = $type . substr($method, strlen($name) + 3);
          if (method_exists($this->{$var}[$index], $call)) {
            return call_user_func_array(array($this->{$var}[$index], $method), $args);
          }
        }
      }
    }
  }

  /**
   * Adds a column to the data table.
   *
   * @param string $name
   *   The unique column machine-name.
   * @param string|null $type
   *   The column type (string, number, etc).
   * @param string|null $label
   *   The column label.
   * @param string|null $role
   *   An optional column role.
   *
   * @return GoogleChartsDataColumn
   *   The new column object.
   */
  public function addColumn($name, $type = NULL, $label = NULL, $role = NULL) {
    $column = new GoogleChartsDataColumn($name, $type, $label, $role);
    $this->columns[] = $column;
    return $column;
  }

  /**
   * Adds an array of columns to the data table.
   *
   * @param array $columns
   *   A columns array with subarrays of the following options:
   *   - type: The data type (number or string).
   *   - label: A label for the column.
   *
   * @return GoogleChartsDataTable
   *   The called object.
   */
  public function addColumns(array $columns) {
    foreach ($columns as $column) {
      $column += array('name' => NULL, 'type' => NULL, 'label' => NULL, 'role' => NULL);
      $this->addColumn($column['name'], $column['type'], $column['label'], $column['role']);
    }
    return $this;
  }

  /**
   * Removes a column from the data table.
   *
   * @param int $name
   *   The index of the column to remove.
   */
  public function removeColumn($name) {
    if (isset($this->columns[$name])) {
      unset($this->columns[$name]);
    }
    return $this;
  }

  /**
   * Removes columns starting from the indicated index.
   *
   * @param int $name
   *   The starting index.
   * @param int $length
   *   The number of columns to remove.
   */
  public function removeColumns($name, $length) {
    $offset = array_search($name, array_keys($this->columns));
    if (is_string($length)) {
      $length = array_search($length, array_keys($this->columns)) - $offset;
    }
    
    $columns = array_slice($this->columns, $offset, $length, TRUE);
    foreach ($columns as $name => $column) {
      $this->removeColumn($name);
    }
    return $this;
  }

  /**
   * Returns a data column object.
   *
   * @param string $name
   *   The unique name of the column.
   *
   * @return GoogleChartsDataColumn
   *   The requested column object.
   */
  public function getColumn($name) {
    if (isset($this->columns[$name])) {
      return $this->columns[$name];
    }
    return NULL;
  }

  /**
   * Adds a row to the data table.
   *
   * @param array $row
   *   The row array. The row's values should correspond directly to available columns.
   *
   * @return GoogleChartsDataRow
   *   The created data row.
   */
  public function addRow(array $row) {
    $row = new GoogleChartsDataRow($row);
    $this->rows[] = $row;
    return $row;
  }

  /**
   * Adds an array of rows to the data table.
   *
   * @param array $rows
   *   An array of rows to add. Each field within rows should directly
   *   correspond to a column in the table.
   *
   * @return GoogleCharts
   *   The called object.
   */
  public function addRows(array $rows) {
    foreach ($rows as $row) {
      $this->addRow($row);
    }
    return $this;
  }

  /**
   * Removes a single row by index.
   */
  public function removeRow($index) {
    if (isset($this->rows[$index])) {
      unset($this->rows[$index]);
    }
    return $this;
  }

  /**
   * Adds a group by clause to the data table.
   *
   * @param array $keys
   *   An array of keys as required by google.visualization.data.group().
   * @param array $columns
   *   An array of columns as required by google.visualization.data.group().
   *   Use a string to identify the aggregation type. Available types:
   *   - avg: The average of all cells in the group.
   *   - count: The total count of all cells in the group.
   *   - max: The maximum cell in the group.
   *   - min: The minimum cell in the group.
   *   - sum: The sum of all cells in the group.
   */
  public function group(array $keys, array $columns = array()) {
    $this->groups[] = array(
      'keys' => $keys,
      'columns' => $columns,
    );
    return $this;
  }

  /**
   * Builds a columns array suitable for theme_google_chart().
   */
  public function buildColumns() {
    $columns = array();
    foreach ($this->columns as $name => $column) {
      $columns[$column->getName()] = $column->build();
    }
    return $columns;
  }

  /**
   * Builds a rows array suitable for theme_google_chart().
   */
  public function buildRows() {
    $rows = array();
    foreach ($this->rows as $row) {
      // Rows should follow the order of columns if no column names were assigned.
      // Otherwise, rows will be mapped by column names.
      $rows[] = $row->build();
    }
    return $rows;
  }

  /**
   * Returns the groups for this data table.
   */
  public function buildGroups() {
    return $this->groups;
  }

}

/**
 * Represents a chart data column.
 */
class GoogleChartsDataColumn {

  /**
   * Column types.
   */
  const DATE = 'date',
        DATE_TIME = 'datetime',
        NUMBER = 'number',
        STRING = 'string',
        TIME_OF_DAY = 'timeofday';

  /**
   * Column roles.
   */
  const ANNOTATION = 'annotation',
        ANNOTATION_TEXT = 'annotationText',
        CERTAINTY = 'certainty',
        EMPHASIS = 'emphasis',
        INTERVAL = 'interval',
        SCOPE = 'scope',
        TOOLTIP = 'tooltip';

  /**
   * @var string|int
   *   The column name.
   */
  protected $name;

  /**
   * @var string
   *   The column type.
   */
  protected $type = 'number';
  
  /**
   * @var string|null
   *   The column label.
   */
  protected $label = NULL;
  
  /**
   * @var string|null
   *   The column role.
   */
  protected $role = NULL;

  /**
   * @var array|null
   *   The column format.
   */
  protected $format = NULL;

  public function __construct($name, $type = NULL, $label = NULL, $role = NULL) {
    $this->name = $name;
    $this->type = $type;
    $this->label = $label;
    $this->role = $role;
  }

  /**
   * Sets the column name.
   *
   * @param string|int $name
   *   The column name.
   */
  public function setName($name) {
    $this->name = $name;
    return $this;
  }

  /**
   * Returns the column name.
   */
  public function getName() {
    return $this->name;
  }

  /**
   * Sets the column type.
   *
   * @param string $type
   *   The column type.
   */
  public function setType($type) {
    $this->type = $type;
    return $this;
  }

  /**
   * Returns the type of the column.
   */
  public function getType() {
    return $this->type;
  }

  /**
   * Sets the column ID.
   *
   * @param string|int $id
   *   The column ID.
   */
  public function setId($id) {
    $this->name = $id;
    return $this;
  }

  /**
   * Returns the ID of the column.
   */
  public function getId() {
    return $this->id;
  }

  /**
   * Sets the column label.
   *
   * @param string $label
   *   The column label.
   */
  public function setLabel($label) {
    $this->label = $label;
    return $this;
  }

  /**
   * Returns the label of the column.
   */
  public function getLabel() {
    return $this->label;
  }

  /**
   * Sets the column role.
   *
   * @param string $role
   *   The column role.
   */
  public function setRole($role) {
    $this->role = $role;
    return $this;
  }

  /**
   * Returns the label of the column.
   */
  public function getRole() {
    return $this->role;
  }

  /**
   * Sets the pattern for the column.
   *
   * @param string $pattern
   *   The pattern to set.
   */
  public function setPattern($pattern) {
    $this->pattern = $pattern;
    return $this;
  }

  /**
   * Returns the column's pattern.
   */
  public function getPattern() {
    return $this->pattern;
  }

  /**
   * Formats the column.
   *
   * @param array $format
   *   The column format.
   */
  public function format(array $format) {
    $this->format = $format;
    return $this;
  }

  /**
   * Builds the column array.
   */
  public function build() {
    $column = array('id' => $this->name);
    foreach (array('type', 'label', 'role', 'pattern', 'format') as $property) {
      if (isset($this->$property)) {
        $column[$property] = $this->$property;
      }
    }
    return $column;
  }

}

/**
 * Represents a chart data row.
 */
class GoogleChartsDataRow {

  /**
   * @var array
   *   The data array.
   */
  protected $data = array();

  public function __construct(array $row) {
    $this->data = $row;
  }

  /**
   * Builds the data array.
   */
  public function build() {
    // We no longer need to sort this data since this module now
    // supports named column indices.
    return $this->data;
  }

}
