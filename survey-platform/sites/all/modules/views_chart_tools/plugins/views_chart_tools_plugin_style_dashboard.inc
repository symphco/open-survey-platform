<?php

/**
 * @file
 * Provides a style plugin for Views Chart dashboards.
 */

/**
 * Style plugin for Views Chart dashboard.
 */
class views_chart_tools_plugin_style_dashboard extends views_plugin_style {

  protected $extender = NULL;

  public function init(&$view, &$display, $options = NULL) {
    parent::init($view, $display, $options);
    $this->extender = $view->display['default']->handler->extender['views_chart_tools_dashboard_extender'];
    $this->options['format'] = $this->extender->get_option('formats');
  }

  /**
   * Defines options for the style plugin.
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['info'] = array('default' => array());
    return $options;
  }

  /**
   * Renders the style plugin's options form.
   */
  public function options_form(&$form, &$form_state) {
    $form['#title'] = t('Configure data table');
    $form['description'] = array(
      '#markup' => '<div class="description form-item">' . t('Use this form to configure the global data table that will be used by the dashboard to render charts. The data table is built using view fields. All charts and controls will be rendered from a single data table. For more information on Google Chart Tools data structures visit the <a href="!google">Google Chart Tools documentation</a>.', array('!google' => 'https://developers.google.com/chart/')) . '</div>',
    );

    $columns = $this->display->handler->get_option('fields');
    $field_names = $this->display->handler->get_field_labels();

    $handlers = $this->display->handler->get_handlers('field');
    if (empty($handlers)) {
      $form['error_markup'] = array(
        '#markup' => '<div class="error messages">' . t('You need at least one field before you can configure data table settings') . '</div>',
      );
      return;
    }

    $form['#tree'] = TRUE;
    $form['#theme'] = 'views_chart_tools_data_table';

    // Create the columns table.
    foreach ($columns as $field => $column) {
      if (!empty($column['exclude'])) {
        continue;
      }

      $safe = str_replace(array('][', '_', ' '), '-', $field);

      $form['info'][$field]['type'] = array(
        '#type' => 'select',
        '#options' => google_charts_column_types(),
        '#default_value' => !empty($this->options['info'][$field]['type']) ? $this->options['info'][$field]['type'] : '',
        '#field_suffix' => l(t('Format'), "admin/structure/views/nojs/display/{$this->view->name}/{$this->display->id}/dashboard_format_field_$field", array('attributes' => array('title' => t('Format'), 'class' => array('views-ajax-link')))),
      );

      // If either roles or column types are empty then roles are always unavailable.
      $role_options = array('' => t('- Default -'));
      $roles = google_charts_column_roles();
      $dependencies = array();
      foreach ($roles as $role => $label) {
        $dependencies[$role][] = google_charts_column_roles_data_types($role);
        $role_options[$role] = $label;
      }

      $form['info'][$field]['role'] = array(
        '#type' => 'select',
        '#options' => $role_options,
        '#default_value' => !empty($this->options['info'][$field]['role']) ? $this->options['info'][$field]['role'] : '',
        '#dependent_options' => array(
          'trigger' => 'edit-style-options-info-' . $safe . '-type',
          'dependencies' => $dependencies,
        ),
        '#pre_render' => array('views_chart_tools_dependent_pre_render'),
      );

      $form['info'][$field]['group'] = array(
        '#type' => 'checkbox',
        '#default_value' => !empty($this->options['info'][$field]['group']) ? $this->options['info'][$field]['group'] : '',
        '#attributes' => array('class' => array('edit-style-options-info-group-enable')),
      );

      $form['info'][$field]['modifier'] = array(
        '#type' => 'select',
        '#options' => array(
          '' => t('- Default -'),
          'month' => t('Month'),
          'quarter' => t('Quarter'),
          'year' => t('Year'),
        ),
        '#default_value' => !empty($this->options['info'][$field]['modifier']) ? $this->options['info'][$field]['modifier'] : '',
        '#dependency' => array('edit-style-options-info-' . $safe . '-group' => array(1)),
        '#dependent_options' => array(
          'trigger' => 'edit-style-options-info-' . $safe . '-type',
          'dependencies' => array(
            'month' => array('date', 'datetime'),
            'quarter' => array('date', 'datetime'),
            'year' => array('date', 'datetime'),
          ),
        ),
        '#pre_render' => array('views_chart_tools_dependent_pre_render'),
      );

      // TODO: We're going to have to use some jQuery magic to disable this option
      // of no groupings are being performed.
      $form['info'][$field]['aggregation'] = array(
        '#type' => 'select',
        '#options' => array(
          '' => t('- None -'),
          'avg' => t('Average'),
          'count' => t('Count'),
          'min' => t('Minimum value'),
          'max' => t('Maximum value'),
          'sum' => t('Sum'),
        ),
        '#default_value' => !empty($this->options['info'][$field]['aggregation']) ? $this->options['info'][$field]['aggregation'] : '',
        '#attributes' => array('class' => array('edit-style-options-info-aggregation-options')),
        // Only some values may be available depending on the data type selected.
        '#dependent_options' => array(
          'trigger' => 'edit-style-options-info-' . $safe . '-type',
          'dependencies' => array(
            'avg' => array('number'),
            'min' => array('number', 'string', 'date'),
            'max' => array('number', 'string', 'date'),
            'sum' => array('number'),
          ),
        ),
        '#pre_render' => array('views_chart_tools_dependent_pre_render'),
      );

      $form['info'][$field]['name'] = array(
        '#markup' => $field_names[$field],
      );
    }

    $form['help'] = array(
      '#type' => 'fieldset',
      '#title' => t('Help'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    $form['help']['display'] = array(
      '#markup' => t('<small><strong>Type:</strong> <em>Indicates the data type of chart data for that column.</em><br />' .
        '<strong>Role:</strong> <em>Assigns a role to data from the column. Roles will be filtered based on the roles available to all dashboard elements.<br />' .
        '<strong>Aggregation:</strong> <em>Indicates the type of calculation that should be performed on grouped column results.</em><br />' .
        '<strong>Note: options are limited based on the data structures required by each element in the dashboard. See the <a href="!google">Google Chart Tools documentation</a> for more information on each of these topics.</strong></small>', array('!google' => 'https://developers.google.com/chart/')),
    );

    // Attach javascript.
    $form['#attached']['js'] = array(
      drupal_get_path('module', 'views_chart_tools') . '/js/views_chart_tools.js',
    );
  }

  /**
   * Field format form.
   */
  public function field_format_form(&$form, &$form_state, $field) {
    $fields = $this->display->handler->get_field_labels();
    $form['#title'] = t('Format field: !field', array('!field' => $fields[$field]));
    $this->options['format'] = $this->extender->get_option('formats');

    $form['field'] = array('#type' => 'value', '#value' => $field);

    $form['format'] = array(
      '#type' => 'select',
      '#title' => t('Format'),
      '#options' => google_charts_column_formats(),
      '#required' => TRUE,
      '#default_value' => !empty($this->options['format'][$field]['format']) ? $this->options['format'][$field]['format'] : '',
    );

    // ArrowFormat and BarFormat option.
    $form['base'] = array(
      '#type' => 'textfield',
      '#title' => t('Base value'),
      '#default_value' => !empty($this->options['format'][$field]['options']['base']) ? $this->options['format'][$field]['options']['base'] : '',
      '#dependency' => array('edit-format' => array('ArrowFormat', 'BarFormat')),
    );

    // BarFormat options.
    $colors = array(
      'red' => t('Red'),
      'green' => t('Green'),
      'blue' => t('Blue'),
    );
    $form['colorNegative'] = array(
      '#type' => 'select',
      '#title' => t('Color: negative'),
      '#options' => $colors,
      '#default_value' => !empty($this->options['format'][$field]['options']['color_negative']) ? $this->options['format'][$field]['options']['color_negative'] : '',
      '#dependency' => array('edit-format' => array('BarFormat')),
    );
    $form['colorPositive'] = array(
      '#type' => 'select',
      '#title' => t('Color: positive'),
      '#options' => $colors,
      '#default_value' => !empty($this->options['format'][$field]['options']['color_positive']) ? $this->options['format'][$field]['options']['color_positive'] : '',
      '#dependency' => array('edit-format' => array('BarFormat')),
    );
    $form['max'] = array(
      '#type' => 'textfield',
      '#title' => t('Range: maximum'),
      '#default_value' => !empty($this->options['format'][$field]['options']['max']) ? $this->options['format'][$field]['options']['max'] : '',
      '#description' => t('The maximum number value for the bar range. Default value is the highest value in the table.'),
      '#dependency' => array('edit-format' => array('BarFormat')),
    );
    $form['min'] = array(
      '#type' => 'textfield',
      '#title' => t('Range: minimum'),
      '#default_value' => !empty($this->options['format'][$field]['options']['min']) ? $this->options['format'][$field]['options']['min'] : '',
      '#description' => t('The minimum number value for the bar range. Default value is the lowest value in the table.'),
      '#dependency' => array('edit-format' => array('BarFormat')),
    );
    $form['width'] = array(
      '#type' => 'textfield',
      '#title' => t('Width'),
      '#default_value' => !empty($this->options['format'][$field]['options']['width']) ? $this->options['format'][$field]['options']['width'] : '100',
      '#dependency' => array('edit-format' => array('BarFormat')),
    );

    // DateFormat options.
    $form['pattern'] = array(
      '#type' => 'textfield',
      '#title' => t('Format'),
      '#default_value' => !empty($this->options['format'][$field]['options']['pattern']) ? $this->options['format'][$field]['options']['pattern'] : 'MMM d, y',
      '#description' => t('A custom format pattern to apply to the value, similar to the <a href="http://userguide.icu-project.org/formatparse/datetime">ICU date and time format</a> (see <a href="https://developers.google.com/chart/interactive/docs/reference#dateformatter">documentation</a>).'),
      '#dependency' => array('edit-format' => array('DateFormat')),
    );

    // NumberFormat options.
    $form['groupingSymbol'] = array(
      '#type' => 'textfield',
      '#title' => t('Grouping symbol'),
      '#default_value' => !empty($this->options['format'][$field]['options']['grouping_symbol']) ? $this->options['format'][$field]['options']['grouping_symbol'] : ',',
      '#description' => t('A character to be used to group digits to the left of the decimal into sets of three.'),
      '#dependency' => array('edit-format' => array('NumberFormat')),
    );
    $form['fractionDigits'] = array(
      '#type' => 'select',
      '#title' => t('Decimal points'),
      '#options' => array(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10),
      '#default_value' => !empty($this->options['format'][$field]['options']['fraction_digits']) ? $this->options['format'][$field]['options']['fraction_digits'] : 2,
      '#description' => t('Specify how many digits to display after the decimal.'),
      '#dependency' => array('edit-format' => array('NumberFormat')),
    );
    $form['prefix'] = array(
      '#type' => 'textfield',
      '#title' => t('Suffix'),
      '#default_value' => !empty($this->options['format'][$field]['options']['prefix']) ? $this->options['format'][$field]['options']['prefix'] : '',
      '#description' => t('A prefix for the value, for example "$".'),
      '#dependency' => array('edit-format' => array('NumberFormat')),
    );
    $form['suffix'] = array(
      '#type' => 'textfield',
      '#title' => t('Suffix'),
      '#default_value' => !empty($this->options['format'][$field]['options']['suffix']) ? $this->options['format'][$field]['options']['suffix'] : '',
      '#description' => t('A suffix for the value, for example "%".'),
      '#dependency' => array('edit-format' => array('NumberFormat')),
    );
  }

  /**
   * Submit handler for the field format form.
   */
  public function field_format_submit(&$form, &$form_state, $field) {
    $this->options['format'][$field]['format'] = $form_state['values']['format'];
    $this->options['format'][$field]['column'] = $form_state['values']['field'];

    // Define the options to be saved by each format.
    switch ($form_state['values']['format']) {
      case 'ArrowFormat':
        $values = array('base');
        if (isset($form_state['values']['base'])) {
          $form_state['values']['base'] = (int) $form_state['values']['base'];
        }
        break;
      case 'BarFormat':
        $values = array('base', 'colorNegative', 'colorPositive', 'width');
        foreach (array('base', 'max', 'mix', 'width') as $key) {
          if (isset($form_state['values'][$key])) {
            $form_state['values'][$key] = (int) $form_state['values'][$key];
          }
        }
        // Only store min and max values if they're empty to ensure defaults are applied.
        if (!empty($form_state['values']['min'])) {
          $values[] = 'min';
        }
        if (!empty($form_state['values']['max'])) {
          $values[] = 'max';
        }
        break;
      case 'DateFormat':
        $values = array('pattern');
        break;
      case 'NumberFormat':
        $values = array('groupingSymbol', 'fractionDigits', 'prefix', 'suffix');
        if (isset($form_state['values']['fractionDigits'])) {
          $form_state['values']['fractionDigits'] = (int) $form_state['values']['fractionDigits'];
        }
        break;
      default:
        $values = array();
        break;
    }

    // Loop through defined options and set them.
    $this->options['format'][$field]['options'] = array();
    foreach ($values as $key) {
      if (isset($form_state['values'][$key])) {
        $this->options['format'][$field]['options'][$key] = $form_state['values'][$key];
      }
    }

    // Save the format information.
    $this->extender->set_option('formats', $this->options['format']);
  }

  /**
   * Builds a data table from view results.
   */
  public function build_data_table(array &$results) {
    $columns = $this->view->field;

    $data = new GoogleChartsDataTable();

    // Loop through all columns and add them to the data table.
    $groups = array();
    foreach ($columns as $field => $column) {
      if (!empty($column->options['exclude'])) {
        continue;
      }

      $roles = $this->extender->filter_field_options('roles', $field);
      $types = $this->extender->filter_field_options('type', $field);

      // Skip this column if there are no compatible types. The GoogleCharts.DataTable
      // class will handle only rendering cell values for columns that exist in the chart.
      // We also must to have settings information for any column added to the table.
      if (empty($types) || empty($this->options['info'][$field])) {
        continue;
      }

      $label = check_plain(!empty($columns[$field]) ? $columns[$field]->label() : '');

      $type = !empty($this->options['info'][$field]['type']) ? $this->options['info'][$field]['type'] : reset($types);
      $data_column = $data->addColumn(
        $field,
        $type,
        $label,
        !empty($this->options['info'][$field]['role']) ? $this->options['info'][$field]['role'] : ''
      );

      // Format the column if necessary.
      if (!empty($this->options['format'][$field])) {
        $data_column->format($this->options['format'][$field]);
      }

      // Check for grouping and aggregation information.
      // This process creates an array similar to as follows:
      // $group = array(
      //   'keys' => array(
      //     0 => array(
      //       'column' => 'column_name_1',
      //       'modifier' => 'month',
      //       'type' => 'date',
      //     ),
      //   ),
      //   'columns' => array(
      //     0 => array(
      //       'column' => 'column_name_2',
      //       'aggregation' => 'sum',
      //       'type' => 'number',
      //     ),
      //     1 => array(
      //       'column' => 'column_name_3',
      //       'aggregation' => 'count',
      //       'type' => 'number',
      //     ),
      //   ),
      // );

      if (!empty($this->options['info'][$field]['group'])) {
        $group = array('keys' => array(), 'columns' => array());
        // If a modifier is being used we need to pass an object.
        if (!empty($this->options['info'][$field]['modifier'])) {
          $key = array(
            'column' => $field,
            'modifier' => $this->options['info'][$field]['modifier'],
            'type' => google_charts_column_modifiers_data_types($this->options['info'][$field]['modifier']),
          );
        }
        // If no modifier is being used then we can just set the column index.
        else {
          $key = $field;
        }
        $group['keys'][] = $key;

        // Add columns to the grouping output (all columns with aggregation for now).
        // Only add columns that are *not* the grouping column (the current column).
        foreach (array_diff(array_keys($columns), array($field)) as $group_field) {
          $data_type = google_charts_group_aggregation_data_types($this->options['info'][$group_field]['aggregation']);
          $group_output = array(
            'column' => $group_field,
            'type' => !is_array($data_type) ? $data_type : $this->options['info'][$group_field]['type'],
          );
          $group_output['aggregation'] = !empty($this->options['info'][$group_field]['aggregation']) ? $this->options['info'][$group_field]['aggregation'] : 'count';
          $group['columns'][] = $group_output;
        }
        $groups[] = $group;
      }
    }

    // Render each row individually.
    $renders = $this->render_fields($results);
    foreach ($results as $num => $item) {
      $row = array();
      foreach ($columns as $field => $column) {
        $type = !empty($this->options['info'][$field]['type']) ? $this->options['info'][$field]['type'] : reset($types);

        // If this is a date/datetime/timeofday column, use the raw value (timestamp) so
        // we can create a date object from it.
        switch ($type) {
          case 'date':
          case 'datetime':
          case 'timeofday':
            $row[$field] = $this->get_field_value($num, $field);
            break;
          // In all other cases, get the rendered value.
          default:
            $row[$field] = $renders[$num][$field];
            break;
        }
      }
      $data->addRow($row);
    }

    // Finally, add the groups to the table.
    foreach ($groups as $group) {
      $data->group($group['keys'], $group['columns']);
    }
    return $data;
  }

}
