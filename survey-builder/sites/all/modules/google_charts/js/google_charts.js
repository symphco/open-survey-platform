
/**
 * @file
 * Renders Views Chart charts.
 */
(function($) {

  // Note that the table package is loaded separately from core charts.
  google.load('visualization', '1.1', {packages:['corechart', 'table', 'controls', 'annotatedtimeline', 'map']});

  /**
   * Core Google Chart class.
   */
  Drupal.GoogleCharts = Drupal.GoogleCharts || {};
  Drupal.GoogleCharts.data = null;
  Drupal.settings.GoogleCharts = Drupal.settings.GoogleCharts || {};

  /**
   * Primary Google Charts class.
   */
  Drupal.GoogleCharts = {
    charts: {},
    dashboards: {},

    /**
     * Helper function: converts an array to string (similar to print_r).
     */
    helpers: {
      arrayToString:  function(array, indent) {
        if (typeof indent == 'undefined') {
          indent = '';
        }

        var output = '';
        for (var i in array) {
          output += indent + i + ': ';
          if (array[i] instanceof Object) {
            output += "\n";
            output += this.arrayToString(array[i], '  ' + indent);
          }
          else {
            output += (typeof array[i]) + ' ' + array[i] + "\n";
          }
        }
        return output;
      }
    },

    modifiers: {

      months: [
        'January',
        'February',
        'March',
        'April',
        'May',
        'June',
        'July',
        'August',
        'September',
        'October',
        'November',
        'December',
      ],

      month: function(date) {
        return Drupal.GoogleCharts.modifiers.months[date.getMonth()] + ' ' + date.getFullYear();
      },

      quarters: [
        '1st',
        '2nd',
        '3rd',
        '4th',
      ],

      quarter: function(date) {
        return Math.floor(date.getMonth() / 3) + 'Q ' + date.getFullYear();
      },

      year: function(date) {
        return date.getFullYear();
      },
    },

    /**
     * Handles building of data tables from PHP settings arrays.
     *
     * When building a data table it is recommended that you just use
     * the Drupal.GoogleChart.buildData() method. If you choose to avoid
     * that method, know that it is critical that you call the methods
     * contained herein in specific order - .addColumns(), .addRows(),
     * and .addGroups(), before retrieving the completed data table object
     * with .getDataTable(). Alternatively, you could grab the data table
     * at any point in the process and use the Google Visualization API
     * to complete the work.
     */
    DataTable: function() {
      this.columns = {};
      Drupal.GoogleCharts.data = this;

      /**
       * Adds columns to the data table.
       *
       * @param columns
       *   An object whose properties are column names and whose values
       *   are object column definitions.
       */
      this.addColumns = function(columns) {
        for (var name in columns) {
          this.addColumn(name, columns[name]);
        }
        return this;
      }

      /**
       * Adds a single column to the data table.
       *
       * @param name
       *   The machine-readable name of the column.
       * @param column
       *   An object defining the column's properties. The object should reflect
       *   the structure required by google.visualization.DataTable.addColumn().
       */
      this.addColumn = function(name, column) {
        // Allow columns to specify their own format. However, internally we set
        // and process the format separately from the column.
        if (column.format) {
          this.addFormat(column.format);
        }
        this.columns[name] = column;
        return this;
      }

      this.rows = [];

      /**
       * Adds rows to the data table.
       */
      this.addRows = function(rows) {
        for (var i in rows) {
          this.addRow(rows[i]);
        }
        return this;
      }

      /**
       * Adds a single row to the data table.
       */
      this.addRow = function(row) {
        this.rows.push(row);
        return this;
      }

      this.groups = [];

      /**
       * Adds groups to the data table.
       */
      this.addGroups = function(groups) {
        for (var i in groups) {
          this.addGroup(groups[i]);
        }
        return this;
      }

      /**
       * Adds a single group to the data table.
       */
      this.addGroup = function(group) {
        return this.groups.push(group);
      }

      this.formats = [];

      /**
       * Adds formats to the data table.
       */
      this.addFormats = function(formats) {
        for (var i in formats) {
          this.addFormat(formats[i]);
        }
      }

      /**
       * Adds a single format to the data table.
       *
       * @param format
       *   An object definiing the format. The object should have the following keys:
       *   - format: A string identifying the class of the format to use. This class
       *     should be available in the google.visualization object.
       *   - column: The name of the column to format.
       *   - options: An object defining options to be passed to the format's constructor.
       */
      this.addFormat = function(format) {
        this.formats.push(format);
      }

      /**
       * Builds the data table from stored table information.
       */
      this.build = function() {
        if (!google.visualization.DataTable) {
          return;
        }

        var data = new google.visualization.DataTable();

        var columnMap = {};

        /**
         * Forces a number from string.
         */
        var forceNumber = function(number) {
          return number * 1;
        };
      
        /**
         * Forces a string from number.
         */
        var forceString = function(string) {
          return string + '';
        };

        /**
         * Creates a date from timestamp.
         */
        var forceDate = function(timestamp) {
          // Convert unix timestamp (seconds) to Date format (miliseconds).
          return new Date(timestamp * 1000);
        };

        /**
         * Returns the column index of a named column.
         */
        var getColumnIndex = function(column) {
          if (typeof column == 'string' && typeof columnMap[column] != 'undefined') {
            return columnMap[column];
          }
          return column;
        }

        /**
         * Builds column data.
         *
         * @param columns
         *   An array of column objects. Each object should define a
         *   type, label, and optionally id, role, and pattern. See the
         *   Google Chart Tools API documentation for more information.
         */
        var buildColumns = function(columns) {
          var i = 0;
          for (var name in columns) {
            definition = {};
            for (var property in columns[name]) {
              // Skip the 'format' property. Columns are allowed to specify their
              // format in the column definition, but we have separate handling for that.
              if (property == 'format') {
                continue;
              }
              // Only add properties that are not empty.
              if (columns[name][property]) {
                definition[property] = columns[name][property];
              }
            }
            // Store the index of the new column.
            columnMap[name] = data.addColumn(definition);
          }
        }

        buildColumns(this.columns);

        /**
         * Builds row data.
         *
         * @param rows
         *   An array of rows whose keys should correspond *directly* to the
         *   order in which columns were added to the data table. Internally,
         *   columns are numerically indexed arrays, not objects. If a column
         *   is of type 'string', 'number', 'date', or 'datetime' it will
         *   be forced to be such. For dates and datetime columns, this method
         *   expects field values to be a unix timestamp that will be converted
         *   into milliseconds.
         */
        var buildRows = function(columns, rows) {
          // Loop through each of the rows and ensure their values match their data types.
          // Convert string keys to numeric indices if necessary.
          var cleansed = [];
          for (var rowIndex in rows) {
            var row = rows[rowIndex];

            // Create a separate 'item' for the row with numeric indexes.
            var item = [];
            // We loop through columnMap here instead of the row definition to ensure that
            // we are *only* adding cell data from a column that has already been mapped.
            for (var columnName in columnMap) {
              var columnIndex = columnMap[columnName];

              // Get the column definition. If the column is a number then we need to
              // force it to be so with a mathematical expression.
              var definition = columns[columnName];
              if (definition.type == 'number') {
                item[columnIndex] = forceNumber(row[columnName]);
              }
              else if (definition.type == 'string') {
                item[columnIndex] = forceString(row[columnName]);
              }
              else if (definition.type == 'date' || definition.type == 'datetime') {
                item[columnIndex] = forceDate(row[columnName]);
              }
              else {
                item[columnIndex] = row[columnName];
              }
            }
            cleansed[rowIndex] = item;
          }
          data.addRows(cleansed);
        }

        buildRows(this.columns, this.rows);

        /**
         * Builds group data.
         *
         * @param groups
         *   An array of group information structured in precisely the same
         *   way as is expected by the Google Visualization API. Each group
         *   object should have a keys: and optionally columns: member. See
         *   the Google Chart Tools API documentation for more information
         *   on grouping.
         */
        var buildGroups = function(groups) {
          for (var i in groups) {
            var group = groups[i];

            for (var key in group.keys) {
              // Convert the group key column name to a numeric index.
              // Note that we may be passed a column name rather than object, so we need
              // to handle for converting both a name or object with the 'column' key.
              if (typeof group.keys[key] == 'number' || typeof group.keys[key] == 'string') {
                group.keys[key] = getColumnIndex(group.keys[key]);
              }
              else {
                group.keys[key].column = getColumnIndex(group.keys[key].column);
              }

              // Now check if we need to reference a modifier class.
              if (!group.keys[key].modifier || !Drupal.GoogleCharts.modifiers[group.keys[key].modifier]) {
                continue;
              }
              // Add a reference to the modifier.
              group.keys[key].modifier = Drupal.GoogleCharts.modifiers[group.keys[key].modifier];
            }

            // We may have been passed a string for aggregation. Add the actual aggregation callback to columns.
            for (var column in group.columns) {
              // Convert the group column name to a numeric index.
              group.columns[column].column = getColumnIndex(group.columns[column].column);

              // If this column uses aggregation then we need to reference the aggregation class.
              if (!group.columns[column].aggregation || !google.visualization.data[group.columns[column].aggregation]) {
                continue;
              }
              // Add a reference to the Google aggregation function.
              group.columns[column].aggregation = google.visualization.data[group.columns[column].aggregation];
            }
            // The group method returns a new data table, so we just override this table.
            data = google.visualization.data.group(data, group.keys, group.columns);
          }
        }

        buildGroups(this.groups);

        /**
         * Formats columns in the data table.
         *
         * @param formats
         *   An array of format objects containing the following values:
         *
         * @param format
         *   A string that identifies the formatter class to be used.
         *   This must be a class that is available in the Google
         *   Visualization API in the google.visualization object.
         * @param column
         *   The index of the column in the data table to format.
         * @param options
         *   An optional options object. Options are specific to
         *   the individual formatter.
         */
        var buildFormats = function(formats) {
          for (var i in formats) {
            var format = formats[i];
            if (typeof google.visualization[format.format] == 'undefined') {
              continue;
            }
            // Ensure the options object is set.
            if (!format.options) {
              format.options = {};
            }
  
            var formatter = new google.visualization[format.format](format.options);

            formatter.format(data, forceNumber(getColumnIndex(format.column)));
          }
        }

        buildFormats(this.formats);

        return data;
      }
    },

    /**
     * Handles building and drawing an individual chart.
     *
     * @param type
     *   The chart type (class). This must directly correspond to
     *   a chart class in the google.visualization object.
     * @param container
     *   The HTML ID of the container element that the chart will
     *   be drawn in.
     * @param definition
     *   A chart definition as expected by google.visualization.ChartWrapper.
     */
    Chart: function(container, definition) {
      this.container = container;
      this.definition = definition;

      this.chart = new google.visualization.ChartWrapper(this.definition);

      /**
       * Draws the chart in a similar fashion to the dashboard,
       * passing the data table in.
       */
      this.draw = function(data) {
        if (!this.chart) {
          return;
        }
        this.chart.setDataTable(data);
        this.chart.draw();
      }
    },

    /**
     * Handles compilation and drawing of a dashboard.
     *
     * @param container
     *   The HTML ID of the dashboard's containing element.
     */
    Dashboard: function(container) {
      this.container = container;

      this.dashboard = new google.visualization.Dashboard(document.getElementById(this.container));

      /**
       * Adds bindings to the dashboard.
       */
      this.addBindings = function(bindings) {
        for (var i in bindings) {
          this.addBinding(bindings[i]);
        }
      }

      /**
       * Adds a single binding to the dashboard.
       * 
       *
       * TODO: Perhaps we may want to use the Chart class to create
       * and bind charts. It will provide more flexibility in the event
       * that the Chart class is updated with more features.
       *
       * @param binding
       *   A binding object describing the charts and controls
       *   to be created and bound. Each object should have controls: and
       *   charts:, each of which define *all* options for each control and
       *   chart, including additional options under the options: key.
       *   Example:
       *   binding = {
       *     controls: {
       *       control-container-id: {
       *         controlType: 'StringFilter',
       *         containerId: 'control-container-id',
       *         options: {ui: {}}
       *       }
       *     },
       *     charts: {
       *       chart-container-id: {
       *         chartType: 'PieChart',
       *         containerId: 'chart-container-id',
       *         options: {
       *           chartArea: {
       *             width: 600,
       *             height 600,
       *           },
       *           tooltip: {
       *             hover: 'both',
       *           }
       *         }
       *       }
       *     }
       *   };
       */
      this.addBinding = function(binding) {
        // Create an array of controls to bind to the charts.
        var bind_controls = [];
        for (var container_id in binding.controls) {
          var definition = binding.controls[container_id];
          wrapper = new google.visualization.ControlWrapper(definition);
          bind_controls.push(wrapper);
        }

        // Create an array of charts to bind.
        var bind_charts = [];
        for (var container_id in binding.charts) {
          var definition = binding.charts[container_id];
          wrapper = new google.visualization.ChartWrapper(definition);
          bind_charts.push(wrapper);
        }

        // Finally, bind the controls/charts.
        this.dashboard.bind(bind_controls, bind_charts);
        return this;
      }

      /**
       * Draws the dashboard.
       *
       * @param data
       *   A google.visualization.DataTable object. This can be built with
       *   the Drupal.GoogleCharts.DataTable class.
       */
      this.draw = function(data) {
        this.dashboard.draw(data);
      }

    },
  };

  // Callbacks for attachBehaviors() - loading settings and drawing the charts.
  Drupal.GoogleCharts.attach = function(context) {

    /**
     * Builds the data table.
     */
    var buildData = function(definition) {
      var data = new Drupal.GoogleCharts.DataTable();
      return data.addColumns(definition.columns)
        .addRows(definition.rows)
        .addGroups(definition.groups)
        .build();
    };

    // Loop through available dashboards and draw them.
    var drawDashboards = function(settings) {
      for (var container in settings) {
        // Don't draw the dashboard if the container doesn't exist in this context.
        if ($('#' + container).length == 0) {
          continue;
        }
        var dashboard = new Drupal.GoogleCharts.Dashboard(container);
        dashboard.addBindings(settings[container].bindings);
        dashboard.draw(buildData(settings[container]));
      }
    };

    if (Drupal.settings.GoogleCharts.dashboard) {
      drawDashboards(Drupal.settings.GoogleCharts.dashboard);
    }

    // Loop through available charts and draw them.
    var drawCharts = function(settings) {
      for (var container in settings) {
        // Don't draw the chart if the container doesn't exist in this context.
        if ($('#' + container).length == 0) {
          continue;
        }
        var chart = new Drupal.GoogleCharts.Chart(container, settings[container].definition);
        chart.draw(buildData(settings[container]));
      }
    };

    if (Drupal.settings.GoogleCharts.chart) {
      drawCharts(Drupal.settings.GoogleCharts.chart);
    }

  };

  google.setOnLoadCallback(Drupal.GoogleCharts.attach(document));

  /**
   * TODO: This attachment does not seem to actually work. Although the script
   * is properly executed when Drupal.attachBehaviors() is called, charts and
   * dashboards do not actually seem to be rendered in the newly attached context.
   * For example, the Views preview in Views Chart Tools does not work, though we
   * can see that the proper data is getting passed through this behavior.
   */
  Drupal.behaviors.GoogleCharts = {
    attach: function(context) {
      Drupal.GoogleCharts.attach(context);
    }
  };

})(jQuery);
