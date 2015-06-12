<?php

/**
 * @file
 * Defines a display extender for supporting chart dashboards.
 */

/**
 * Display extender supports rendering multiple charts in a dashboard.
 */
class views_chart_tools_plugin_display_dashboard extends views_plugin_display_extender {

  var $handlers = array();

  public function option_definition() {
    return array(
      'dashboard_elements' => array('default' => array()),
      'formats' => array('default' => array()),
    );
  }

  public function options_definition_alter(&$options) {
    // Don't call parent::options_definition_alter() here! The method is
    // not defined in earlier versions of Views (pre-February 2012), and
    // views_plugin_display_extender::options_definition_alter() does
    // nothing anyways.
    // See http://drupal.org/node/1674146 for more information.
    $options = array_merge($this->option_definition(), $options);
  }

  /**
   * Returns a display option value.
   *
   * This method replaces calling $this->display->get_option() since our
   * default values are not being properly applied to the display's options.
   * Here, we get the default options for this object and apply them ourselves
   * if the setting has not been saved on the parent display.
   */
  public function get_option($option) {
    if (isset($this->view->display['default'])) {
      $value = $this->view->display['default']->handler->get_option($option);
    }

    if (!isset($value)) {
      $options = array();
      $this->options_definition_alter($options);
      if (isset($options[$option])) {
        $value = $options[$option]['default'];
      }
    }

    if (isset($value)) {
      $this->options[$option] = $value;
      return $value;
    }
  }

  /**
   * Sets an option value on the default display.
   */
  public function set_option($option, $value) {
    if (isset($this->view->display['default'])) {
      $this->view->display['default']->handler->set_option($option, $value);
    }
  }

  /**
   * Provides available chart and control options.
   */
  public function options_summary(&$categories, &$options) {
    parent::options_summary($categories, $options);
    if ($this->get_option('style_plugin') != 'views_chart_tools_dashboard') {
      return;
    }

    $categories['dashboard_elements'] = array(
      'title' => t('Dashboard elements'),
      'column' => 'first',
    );

    $options['add_dashboard_element'] = array(
      'category' => 'dashboard_elements',
      'title' => t('No elements'),
      'value' => t('Add element'),
    );

    $element_options = $this->get_option('dashboard_elements');
    if (!empty($element_options) && is_array($element_options)) {
      $info = views_chart_tools_element_info();
      foreach ($element_options as $key => $value) {
        $handler = $this->create_element_handler($value['element_type'], $key);
        $label = !$handler ? t('Broken/missing handler') : (!empty($value['label']) ? $value['label'] : $handler->label());
        $options[$key . '_element_options'] = array(
          'category' => 'dashboard_elements',
          'title' => '', // Empty title - render the entire link as title.
          'value' => t('!type: !label (!title)', array('!type' => ucfirst($info[$value['element_type']]['type']), '!label' => $label, '!title' => $info[$value['element_type']]['title'])),
        );
      }
    }
  }

  /**
   * Provides an options form for individual charts and controls.
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    switch ($form_state['section']) {
      // Element add form. Note that once an element is already defined its
      // edit form will need to be built separately.
      case 'add_dashboard_element':
        $this->element_select_form($form, $form_state);
        break;
      case 'rearrange_dashboard_elements':
        $this->element_rearrange_form($form, $form_state);
        break;
      default:
        // Check if this is an options form. If it is, extract the item name.
        // Items (charts and controls) will have _{$type}_options appended to
        // the form name.
        if (strpos($form_state['section'], '_element_options') == (strlen($form_state['section']) - 16)) {
          $name = substr($form_state['section'], 0, strlen($form_state['section']) - 16);
          $options = $this->get_option('dashboard_elements');
          if (is_array($options) && array_key_exists($name, $options)) {
            $this->element_options_form($form, $form_state, $options[$name]);
          }
        }
        // Handle the field format form on behalf of the style plugin.
        elseif (strpos($form_state['section'], 'dashboard_format_field_') === 0) {
          $field_name = substr($form_state['section'], 23);
          $this->display->get_plugin()->field_format_form($form, $form_state, $field_name);
        }
        break;
    }
  }

  /**
   * Form for selecting a chart or control type.
   */
  protected function element_select_form(&$form, &$form_state, array $options = array()) {
    // If this item has already been created then store its name for submit handling.
    if (!empty($options['name'])) {
      $form['name'] = array('#type' => 'value', '#value' => $options['name']);
      $form['#title'] = t('Change element');
    }
    else {
      $form['#title'] = t('Select element');
    }

    // Add default options. This form is used as an add and edit form.
    $options += array(
      'element_type' => '',
      'label' => $this->create_unique_label(),
      'name' => '',
    );

    $form['description'] = array(
      '#markup' => '<div class="description form-item">' . t('Select the type of element to add to the dashboard. Some options may not be available due to the requirements of certain charts in combination with the current structure of the view. You may need to alter the fields and data table before some options can become available.') . '</div>',
      '#weight' => -100,
    );

    // Create available element names.
    $available = $this->filter_element_options();
    $element_options = array();
    foreach ($available as $element => $info) {
      $title = $info['title'];
      if (!empty($info['alt'])) {
        $title .= ' (' . $info['alt'] . ')';
      }
      $element_options[ucfirst($info['type'])][$element] = $title;
    }

    // Display unavailable element information in the element_type suffix.
    $unavailable = array_diff_key(views_chart_tools_element_info(), $available);
    $suffix_options = array();
    foreach ($unavailable as $element => $info) {
      if (in_array('<em>' . $info['title'] . '</em>', $suffix_options)) {
        continue;
      }
      $suffix_options[] = '<em>' . $info['title'] . '</em>';
    }

    $suffix = '';
    if (!empty($suffix_options)) {
      $last = array_pop($suffix_options);
      $suffix = implode(', ', $suffix_options);
      $suffix .= ' ' . t('and') . ' ' . $last . ' ' . t('are incompatible with the current data table configuration.');
    }

    $form['element_type'] = array(
      '#type' => 'select',
      '#title' => t('Element'),
      '#options' => $element_options,
      '#default_value' => $options['element_type'],
      '#suffix' => '<small>' . $suffix . '</small>',
      '#weight' => -20,
    );

    $form['label'] = array(
      '#type' => 'textfield',
      '#title' => t('Administrative label'),
      '#default_value' => $options['label'],
    );
  }

  /**
   * Rearrange elements form.
   */
  protected function element_rearrange_form(&$form, &$form_state) {
    $view = &$form_state['view'];
    $display_id = $form_state['display_id'];

    $form['#theme'] = 'views_ui_rearrange_form';

    if (!$view->set_display($display_id)) {
      views_ajax_error(t('Invalid display id @display', array('@display' => $display_id)));
    }
    $display = &$view->display[$display_id];
    $form['#title'] = t('Rearrange dashboard elements');
    $form['#section'] = 'rearrange_dashboard_elements';

    $count = 0;

    foreach ($this->get_option('dashboard_elements') as $id => $element) {
      $info = views_chart_tools_element_info($element['element_type']);

      $form['fields'][$id] = array('#tree' => TRUE);
      $form['fields'][$id]['weight'] = array(
        '#type' => 'textfield',
        '#default_value' => ++$count,
      );
      $handler = $this->create_element_handler($element['element_type'], $element['name']);
      if ($handler) {
        $name = $handler->admin_summary();
        $form['fields'][$id]['name'] = array(
          '#markup' => $name,
        );
      }
      else {
        $form['fields'][$id]['name'] = array('#markup' => t('Broken chart @id', array('@id' => $id)));
      }
      $form['fields'][$id]['removed'] = array(
        '#type' => 'checkbox',
        '#id' => 'views-removed-' . $id,
        '#attributes' => array('class' => array('views-remove-checkbox')),
        '#default_value' => 0,
      );
    }

    // Add javascript settings that will be added via $.extend for tabledragging
    $form['#js']['tableDrag']['arrange']['weight'][0] = array(
      'target' => 'weight',
      'source' => NULL,
      'relationship' => 'sibling',
      'action' => 'order',
      'hidden' => TRUE,
      'limit' => 0,
    );

    $name = NULL;
    if (isset($form_state['update_name'])) {
      $name = $form_state['update_name'];
    }
  }

  /**
   * Generates an item options form.
   */
  protected function element_options_form(&$form, &$form_state, array $options) {
    // We *have* to have an item type in order to get the correct handler.
    if (empty($options['element_type'])) {
      return;
    }

    $form['element_type'] = array('#type' => 'value', '#value' => $options['element_type']);

    // If this item has already been created then store its name for submit handling.
    if (!empty($options['name'])) {
      $form['name'] = array('#type' => 'value', '#value' => $options['name']);
      $form['#title'] = t('Edit element');
    }

    $form['#tree'] = TRUE;

    $element_type = $options['element_type'];
    $element_info = views_chart_tools_element_info($element_type);

    $handler = $this->create_element_handler($element_type, $options['name'], !empty($options['options']) ? $options['options'] : array());

    if (!$handler) {
      return;
    }

    $handler->options_form($form, $form_state);
  }

  /**
   * Submit handler for various options forms.
   */
  public function options_submit(&$form, &$form_state) {
    switch ($form_state['section']) {
      case 'add_dashboard_element':
        // Create a unique name for the new chart.
        $this->element_select_submit($form, $form_state);
        break;
      case 'rearrange_dashboard_elements':
        $this->element_rearrange_submit($form, $form_state);
        break;
      default:
        // Check if this is an options form. If it is, extract the item name.
        // Items (charts and controls) will have _{$type}_options appended to
        // the form name.
        if (strpos($form_state['section'], '_element_options') == (strlen($form_state['section']) - 16)) {
          $name = substr($form_state['section'], 0, strlen($form_state['section']) - 16);
          $options = $this->get_option('dashboard_elements');
          if (is_array($options) && array_key_exists($name, $options)) {
            $this->element_options_submit($form, $form_state, $name, $options[$name]);
          }
        }
        // Handle the field format form on behalf of the style plugin.
        elseif (strpos($form_state['section'], 'dashboard_format_field_') === 0) {
          $field_name = substr($form_state['section'], 23);
          $this->display->get_plugin()->field_format_submit($form, $form_state, $field_name);
        }
        break;
    }
  }

  /**
   * Submit handler for the item selection form.
   */
  protected function element_select_submit(&$form, &$form_state) {
    // Load item options.
    $options = $this->get_option('dashboard_elements');

    // Create a unique name for the item if it's new.
    if (empty($form_state['values']['name'])) {
      $form_state['values']['name'] = $this->create_machine_name(!empty($form_state['values']['label']) ? $form_state['values']['label'] : 'Element', array_keys($options));
    }

    // Indicate whether this is a new element (for form stacking).
    if (!isset($options[$form_state['values']['name']])) {
      $options[$form_state['values']['name']] = array();
    }

    // Try to set options without overriding the 'options' array which may already be set.
    foreach (array('name', 'element_type', 'label') as $field) {
      $options[$form_state['values']['name']][$field] = $form_state['values'][$field];
    }

    $this->options['dashboard_elements'] = $options;
    $this->set_option('dashboard_elements', $options);

    // Add the element's options and style options forms to the stack (redirecting upon submit).
    views_ui_add_form_to_stack('display', $this->view, $this->display->display->id, array($form_state['values']['name'] . '_element_options'));
  }

  /**
   * Submit handler for the rearrange elements form.
   */
  protected function element_rearrange_submit(&$form, &$form_state) {
    $display = &$form_state['view']->display[$form_state['display_id']];

    $old_elements = $this->get_option('dashboard_elements');
    $new_elements = $order = array();

    // Make an array with the weights
    foreach ($form_state['values'] as $element => $info) {
      // add each value that is a field with a weight to our list, but only if
      // it has had its 'removed' checkbox checked.
      if (is_array($info) && isset($info['weight']) && empty($info['removed'])) {
        $order[$element] = $info['weight'];
      }
    }

    // Sort the array
    asort($order);

    // Create a new list of fields in the new order.
    foreach (array_keys($order) as $element) {
      $new_elements[$element] = $old_elements[$element];
    }
    $this->set_option('dashboard_elements', $new_elements);
  }

  /**
   * Submit handler for an item options form.
   *
   * @param array $form
   *   The form array.
   * @param array $form_state
   *   The form state array.
   * @param string $name
   *   The unique machine-name of the item being saved.
   */
  protected function element_options_submit(&$form, &$form_state, $name, $options) {
    $handler = $this->create_element_handler($options['element_type'], $name, $options);
    if ($handler) {
      $handler->options_submit($form, $form_state);
    }
    $options = $this->get_option('dashboard_elements');
    $options[$name]['options'] = $form_state['values']['options'];
    $this->set_option('dashboard_elements', $options);
  }

  /**
   * Removes an element by name.
   */
  public function remove_element($name) {
    $options = $this->get_option('dashboard_elements');
    if (isset($options[$name])) {
      unset($options[$name]);
      $this->set_option('dashboard_elements', $options);
    }
  }

  /**
   * Filters available dashboard elements by matching data tables
   * between different types of elements.
   *
   * @param array $elements
   *   An optional associative array of elements to filter. Eeach value
   *   should be keyed by the element type - corresponding to elements
   *   defined in hook_views_chart_tools_element_info().
   */
  public function filter_element_options(array $elements = NULL) {
    if (!isset($elements)) {
      $elements = views_chart_tools_element_info();
    }

    $options = array();
    foreach ($elements as $type => $value) {
      if ($this->is_valid_element($type)) {
        $options[$type] = $value;
      }
    }
    return $options;
  }

  /**
   * Returns a boolean value indicating whether the given element type
   * is valid for this view.
   */
  public function is_valid_element($element_type) {
    $columns = $this->display->get_option('fields');
    $element_info = views_chart_tools_element_info();
    $elements = $this->get_option('dashboard_elements');

    // If the element does not require any data then always return TRUE.
    if (empty($element_info[$element_type]['data format'])) {
      return TRUE;
    }

    // Ensure that the view has at least as many columns as are required.
    $required_count = 0;
    foreach ($element_info[$element_type]['data format'] as $index => $definition) {
      if (!empty($definition['required'])) {
        $required_count++;
      }
    }

    if (count($columns) < $required_count) {
      return FALSE;
    }

    // Compare the element's data definition to current view elements.
    foreach ($elements as $name => $element) {
      // Only compare against chart type elements.
      if ($element_info[$element['element_type']]['type'] != 'chart') {
        continue;
      }

      // Check each data column in the element being evaluated.
      foreach ($element_info[$element_type]['data format'] as $index => $definition) {
        // If the current element doesn't have this column then skip it.
        if (!isset($element_info[$element['element_type']]['data format'][$index])) {
          // Get the last column of the element, which may have unlimited cardinality.
          $last_index = end(array_keys($element_info[$element['element_type']]['data format']));

          // If the last column of the element's data has unlimited cardinality then
          // trick the code below into thinking the last column is the current column.
          if ($element_info[$element['element_type']]['data format'][$last_index]['cardinality'] == 'unlimited') {
            $index = $last_index;
          }
          // Otherwise, skip this column as it will not apply to the current element.
          else {
            continue;
          }
        }

        // If none of this element's column types are present in the given
        // element's available types then this element is invalid.
        // Note that we don't perform the same check for column roles because
        // roles are never required for a column, while data types are.
        $types = array_intersect($definition['type'], $element_info[$element['element_type']]['data format'][$index]['type']);
        if (empty($types)) {
          return FALSE;
        }
      }
    }

    return TRUE;
  }

  /**
   * Filters field options (type and role).
   */
  public function filter_field_options($type, $field) {
    $fields = $this->display->get_option('fields');
    $index = array_search($field, array_keys($fields));

    $element_info = views_chart_tools_element_info();
    $elements = $this->get_option('dashboard_elements');

    // Loop through all charts and filter options by this type.
    foreach ($elements as $name => $element) {
      // Skip if this is not a chart.
      if ($element_info[$element['element_type']]['type'] != 'chart') {
        continue;
      }
  
      if (!isset($element_info[$element['element_type']]['data format'][$index])) {
        // Get the last column of the element, which may have unlimited cardinality.
        $last_index = end(array_keys($element_info[$element['element_type']]['data format']));
      
        // If the last column of the element's data has unlimited cardinality then
        // trick the code below into thinking the last column is the current column.
        if ($element_info[$element['element_type']]['data format'][$last_index]['cardinality'] == 'unlimited') {
          $index = $last_index;
        }
        // Otherwise, skip this column as it will not apply to the current element.
        else {
          continue;
        }
      }

      // Ensure the types array has been initialized.
      if (!isset($items)) {
        $items = $element_info[$element['element_type']]['data format'][$index][$type];
        continue;
      }

      // Otherwise, intersect existing types with this chart's available types.
      // This ensures that we only show options that are available to all charts.
      $items = array_intersect($items, $element_info[$element['element_type']]['data format'][$index][$type]);
    }
    return isset($items) ? $items : array();
  }

  /**
   * Generates field conflict information.
   */
  public function get_field_conflicts($element_type, $type, $field) {
    $element_info = views_chart_tools_element_info();
    $elements = $this->get_option('dashboard_elements');

    $fields = $this->display->get_option('fields');
    $original_index = array_search($field, array_keys($fields));
    $index = $original_index;

    if (!isset($element_info[$element_type]['data format'][$index])) {
      // If the last column has unlimited cardinality then use its info.
      $last_index = end(array_keys($element_info[$element_type]['data format']));
      if ($element_info[$element_type]['data format'][$last_index]['cardinality'] == 'unlimited') {
        $index = $last_index;
      }
      else {
        return array();
      }
    }

    $items = $element_info[$element_type]['data format'][$index][$type];

    $conflicts = array();
    foreach ($elements as $name => $element) {
      $element_index = $original_index;
      // Skip if this is not a chart.
      if ($element_info[$element['element_type']]['type'] != 'chart') {
        continue;
      }

      if (!isset($element_info[$element['element_type']]['data format'][$element_index])) {
        $last_element_index = end(array_keys($element_info[$element['element_type']]['data format']));
        if ($element_info[$element['element_type']]['data format'][$last_element_index]['cardinality'] == 'unlimited') {
          $element_index = $last_element_index;
        }
        else {
          continue;
        }
      }

      $results = array_diff($items, $element_info[$element['element_type']]['data format'][$element_index][$type]);
      if (!empty($results)) {
        $function = $type == 'type' ? 'google_charts_column_types' : 'google_charts_column_roles';
        $last = '<em>' . $function(array_pop($results)) . '</em>';
        $conflict = array();
        foreach ($results as $result) {
          $conflict[] = '<em>' . $function($result) . '</em>';
        }
        $conflicts[] = '<em>' . $element_info[$element['element_type']]['title'] . '</em> ' . t('does not support') . ' ' . implode(', ', $conflict) . ' ' . t('or') . ' ' . $last . ' ' . t('for this column.');
      }
    }
    return $conflicts;
  }

  /**
   * Creates a unique label.
   */
  protected function create_unique_label() {
    $options = $this->get_option('dashboard_elements');
    $labels = array();
    foreach ($options as $name => $option) {
      if (isset($option['label'])) {
        $labels[] = $option['label'];
      }
    }

    $i = 1;
    $label = t('Element');
    while (in_array($label . ' ' . $i, $labels)) {
      $i++;
    }
    return $label . ' ' . $i;
  }

  /**
   * Creates a unique name from a label.
   */
  protected function create_machine_name($label, array $existing) {
    $name = preg_replace('/[^a-z0-9]+/', '_', strtolower($label));
    $original = $name;
    $i = 1;
    while (in_array($name, $existing)) {
      $name = $original . '_' . $i;
      $i++;
    }
    return $name;
  }

  /**
   * Creates an item handler (chart or control).
   */
  protected function create_element_handler($type_name, $name = NULL, array $options = array()) {
    $handler = views_chart_tools_get_handler($type_name, $this->view, $this->display);

    if (!$handler) {
      return FALSE;
    }

    if (empty($options) && isset($name)) {
      $type_options = $this->get_option('dashboard_elements');
      $options = isset($type_options[$name]) ? $type_options[$name] : array();
    }

    $handler->init($this->view, $options);

    $handler->element_type = $type_name;
    $handler->element_name = isset($options['name']) ? $options['name'] : $name;
    return $handler;
  }

  /**
   * Returns an item handler.
   */
  public function get_handler($type_name, $name, array $options = NULL) {
    if (!isset($this->handlers[$name])) {
      $this->handlers[$name] = $this->create_element_handler($type_name, $name, $options);
    }
    return $this->handlers[$name];
  }

}
