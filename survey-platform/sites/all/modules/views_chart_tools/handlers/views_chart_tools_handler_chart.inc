<?php

/**
 * Base chart handler.
*/
abstract class views_chart_tools_handler_chart extends views_chart_tools_handler_element {

  protected $element_wrapper = 'GoogleChartsChartWrapper';

  abstract public function chart_option_definition();

  public function option_definition() {
    return array_merge($this->chart_option_definition(), parent::option_definition());
  }

  /**
   * Note: the base chart handler doesn't really define any form. Rather,
   * it provides several helper functions below for building a chart form
   * based on the options available to that chart.
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    unset($form['exclude']);
    
    $element_info = views_chart_tools_element_info($this->element_type);
    
    $columns = $this->extender->display->get_option('fields');
    $field_names = $this->extender->display->get_field_labels();
    
    $form['overview'] = array(
      '#tree' => TRUE,
      '#theme' => 'views_chart_tools_data_table_overview',
      '#weight' => -110,
    );
    
    $form['overview']['description'] = array(
      '#markup' => '<div class="description form-item">' . t('This table depicts the data table structure for this element. Availability of data types and roles is dependent upon the various types of elements contained in the dashboard and the data structures they require. Items that are supported by this element but conflict with another element in the dashboard are crossed out. You can use this table to determine how you can structure your dashboard\'s data table in a manner that supports multiple charts. For more information on Google Chart Tools data structures visit the <a href="!google">Google Chart Tools documentation</a>.', array('!google' => 'https://developers.google.com/chart/')) . '</div>',
    );
    
    // Create the data table overview.
    foreach ($columns as $field => $column) {
      $safe = str_replace(array('][', '_', ' '), '-', $field);
    
      // Get the numeric index of the column. If this numeric index does not exist
      // in the element data format definition, get the last column from the data.
      $index = array_search($field, array_keys($columns));
      if (!isset($element_info['data format'][$index])) {
        // If the last column has unlimited cardinality then use its info.
        $last_index = end(array_keys($element_info['data format']));
        if ($element_info['data format'][$last_index]['cardinality'] == 'unlimited') {
          $index = $last_index;
        }
        else {
          break;
        }
      }
    
      $form['overview']['info'][$field]['name'] = array(
        '#markup' => $field_names[$field],
      );
    
      $form['overview']['info'][$field]['scope'] = array(
        '#markup' => $element_info['data format'][$index]['label'],
      );
    
      $form['overview']['info'][$field]['primary_role'] = array(
        '#markup' => ucfirst($element_info['data format'][$index]['default role']),
      );
    
      $types = array();
      $available_types = $this->extender->filter_field_options('type', $field);
      // Display any types that are applicable to this chart but not available
      // due to conflicts as strikethroughs.
      foreach ($element_info['data format'][$index]['type'] as $type) {
        if (in_array($type, $available_types)) {
          $types[] = google_charts_column_types($type);
        }
        else {
          $types[] = '<del>' . google_charts_column_types($type) . '</del>';
        }
      }
    
      $types_markup = !empty($types) ? implode(', ', $types) : '<em>' . t('Incompatible types') . '</em>';
      $types_markup .= '<br /><small>' . implode('<br />', $this->extender->get_field_conflicts($this->element_type, 'type', $field)) . '</small>';
      $form['overview']['info'][$field]['available_types'] = array(
        '#markup' => $types_markup,
      );
    
      $roles = array();
      $available_roles = $this->extender->filter_field_options('roles', $field);
      foreach ($element_info['data format'][$index]['roles'] as $role) {
        if (in_array($role, $available_roles)) {
          $roles[] = google_charts_column_roles($role);
        }
        else {
          $roles[] = '<del>' . google_charts_column_roles($role) . '</del>';
        }
      }
    
      $roles_markup = !empty($roles) ? implode(', ', $roles) : '<em>' . t('None') . '</em>';
      $roles_markup .= '<br /><small>' . implode('<br />', $this->extender->get_field_conflicts($this->element_type, 'roles', $field)) . '</small>';
      $form['overview']['info'][$field]['available_roles'] = array(
        '#markup' => $roles_markup,
      );
    }
  }

  /**
   * Provides an options form for general width/height settings.
   */
  protected function dimension_options_form(&$form, &$form_state) {
    $dimension_options = drupal_map_assoc(array('100', '200', '300', '400', '500', '600', '700', '800', '900', '1000'));

    $form['width'] = array(
      '#type' => 'select',
      '#title' => t('Width'),
      '#field_suffix' => 'px',
      '#options' => $dimension_options,
      '#default_value' => $this->options['width'],
      '#description' => t('The width of the chart\'s containing element, in pixels.'),
    );

    $form['height'] = array(
      '#type' => 'select',
      '#title' => t('Height'),
      '#field_suffix' => 'px',
      '#options' => $dimension_options,
      '#default_value' => $this->options['height'],
      '#description' => t('The height of the chart\'s containing element, in pixels.'),
    );
  }

  /**
   * Provides an options form for animation settings.
   */
  protected function animation_options_form(&$form, &$form_state) {
    $form['animation'] = array(
      '#type' => 'fieldset',
      '#title' => t('Animation'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['animation']['duration'] = array(
      '#type' => 'select',
      '#title' => t('Duration'),
      '#options' => array(
        '0' => '0ms',
        '200' => '200ms',
        '400' => '400ms',
        '600' => '600ms',
        '800' => '800ms',
        '1000' => '1000ms',
      ),
      '#default_value' => isset($this->options['animation']['duration']) ? $this->options['animation']['duration'] : 0,
      '#description' => t('The duration of the animation, in milliseconds.'),
    );

    $form['animation']['easing'] = array(
      '#type' => 'select',
      '#title' => t('Easing'),
      '#options' => array(
        'linear' => t('Linear'),
        'in' => t('In'),
        'out' => t('Out'),
        'inAndout' => t('In and out'),
      ),
      '#default_value' => isset($this->options['animation']['easing']) ? $this->options['animation']['easing'] : 'linear',
      '#description' => t('The easing function applied to the animation.'),
    );
  }

  /**
   * Provides an options form for chart area supporting charts.
   */
  protected function chart_area_options_form(&$form, &$form_state) {
    $dimension_options = drupal_map_assoc(array('100', '200', '300', '400', '500', '600', '700', '800', '900', '100'));

    $form['chart_area'] = array(
      '#type' => 'fieldset',
      '#title' => t('Size'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    
    $form['chart_area']['width'] = array(
      '#type' => 'select',
      '#title' => t('Width'),
      '#field_suffix' => 'px',
      '#options' => $dimension_options,
      '#default_value' => !empty($this->options['chart_area']['width']) ? $this->options['chart_area']['width'] : '300',
      '#description' => t('The width of the chart, in pixels.'),
    );
    
    $form['chart_area']['height'] = array(
      '#type' => 'select',
      '#title' => t('Height'),
      '#field_suffix' => 'px',
      '#options' => $dimension_options,
      '#default_value' => !empty($this->options['chart_area']['height']) ? $this->options['chart_area']['height'] : '300',
      '#description' => t('The height of the chart, in pixels.'),
    );
  }

  /**
   * Provides an options form for vertical axis supporting charts.
   */
  protected function vertical_axis_options_form(&$form, &$form_state) {
    $number_options = array();
    for ($i = 2; $i <= 10; $i++) {
      $number_options[$i] = $i;
    }

    $form['v_axis'] = array(
      '#type' => 'fieldset',
      '#title' => t('Vertical axis'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    
    $form['v_axis']['title'] = array(
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#default_value' => !empty($this->options['v_axis']['title']) ? $this->options['v_axis']['title'] : '',
      '#description' => t('The title of the vertical axis.'),
    );
    
    $form['v_axis']['direction'] = array(
      '#type' => 'select',
      '#title' => t('Direction'),
      '#options' => array(1 => t('Normal'), -1 => t('Reverse')),
      '#default_value' => !empty($this->options['v_axis']['direction']) ? $this->options['v_axis']['direction'] : '',
      '#description' => t('The direction in which the values along the vertical axis grow.'),
    );
    
    $form['v_axis']['format'] = array(
      '#type' => 'textfield',
      '#title' => t('Format'),
      '#default_value' => !empty($this->options['v_axis']['format']) ? $this->options['v_axis']['format'] : '#,###',
      '#description' => t('A format for numeric or date axis labels. For number axis labels, this is a subset of the decimal formatting ICU pattern set. For instance, {format:\'#,###%\'} will display values "1,000%", "750%", and "50%" for values 10, 7.5, and 0.5. For date axis labels, this is a subset of the date formatting ICU pattern set. For instance, {format:\'MMM d, y\'} will display the value "Jul 1, 2011" for the date of July first in 2011.'),
    );
    
    $form['v_axis']['gridlines'] = array(
      '#type' => 'fieldset',
      '#title' => t('Gridlines'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    
    $form['v_axis']['gridlines']['color'] = array(
      '#title' => t('Color'),
      '#default_value' => !empty($this->options['v_axis']['gridlines']['color']) ? $this->options['v_axis']['gridlines']['color'] : '',
      '#description' => t('The color of the vertical gridlines inside the chart area.'),
    );
    
    $form['v_axis']['gridlines']['color']['#type'] = module_exists('jquery_colorpicker') ? 'jquery_colorpicker' : 'textfield';
    
    $form['v_axis']['gridlines']['count'] = array(
      '#type' => 'select',
      '#title' => t('Count'),
      '#options' => $number_options,
      '#default_value' => !empty($this->options['v_axis']['gridlines']['count']) ? $this->options['v_axis']['gridlines']['count'] : '',
      '#description' => t('The number of vertical gridlines inside the chart area.'),
    );
    
    $form['v_axis']['minor_gridlines'] = array(
      '#type' => 'fieldset',
      '#title' => t('Minor gridlines'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    
    $form['v_axis']['minor_gridlines']['color'] = array(
      '#title' => t('Color'),
      '#default_value' => !empty($this->options['v_axis']['minor_gridlines']['color']) ? $this->options['v_axis']['minor_gridlines']['color'] : '',
      '#description' => t('The color of the vertical minor gridlines inside the chart area.'),
    );
    
    $form['v_axis']['minor_gridlines']['color']['#type'] = module_exists('jquery_colorpicker') ? 'jquery_colorpicker' : 'textfield';
    
    $form['v_axis']['minor_gridlines']['count'] = array(
      '#type' => 'select',
      '#title' => t('Count'),
      '#options' => $number_options,
      '#default_value' => !empty($this->options['v_axis']['minor_gridlines']['count']) ? $this->options['v_axis']['minor_gridlines']['count'] : '',
      '#description' => t('The number of vertical minor gridlines between two regular gridlines.'),
    );
  }

  /**
   * Provides an options form for horizontal axis supporting charts.
   */
  protected function horizontal_axis_options_form(&$form, &$form_state) {    
    $number_options = array();
    for ($i = 0; $i <= 10; $i++) {
      $number_options[$i] = $i;
    }

    $form['h_axis'] = array(
      '#type' => 'fieldset',
      '#title' => t('Horizontal axis'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    
    $form['h_axis']['title'] = array(
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#default_value' => !empty($this->options['h_axis']['title']) ? $this->options['h_axis']['title'] : '',
      '#description' => t('The title of the horizontal axis.'),
    );
    
    $form['h_axis']['direction'] = array(
      '#type' => 'select',
      '#title' => t('Direction'),
      '#options' => array(1 => t('Normal'), -1 => t('Reverse')),
      '#default_value' => !empty($this->options['h_axis']['direction']) ? $this->options['h_axis']['direction'] : '',
      '#description' => t('The direction in which the values along the horizontal axis grow.'),
    );
    
    $form['h_axis']['format'] = array(
      '#type' => 'textfield',
      '#title' => t('Format'),
      '#default_value' => !empty($this->options['h_axis']['format']) ? $this->options['h_axis']['format'] : '#,###',
      '#description' => t('A format for numeric or date axis labels. For number axis labels, this is a subset of the decimal formatting ICU pattern set. For instance, {format:\'#,###%\'} will display values "1,000%", "750%", and "50%" for values 10, 7.5, and 0.5. For date axis labels, this is a subset of the date formatting ICU pattern set. For instance, {format:\'MMM d, y\'} will display the value "Jul 1, 2011" for the date of July first in 2011.'),
    );
    
    $form['h_axis']['gridlines'] = array(
      '#type' => 'fieldset',
      '#title' => t('Gridlines'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    
    $form['h_axis']['gridlines']['color'] = array(
      '#title' => t('Color'),
      '#default_value' => !empty($this->options['h_axis']['gridlines']['color']) ? $this->options['h_axis']['gridlines']['color'] : '',
      '#description' => t(''),
    );
    
    $form['h_axis']['gridlines']['color']['#type'] = module_exists('jquery_colorpicker') ? 'jquery_colorpicker' : 'textfield';
    
    $form['h_axis']['gridlines']['count'] = array(
      '#type' => 'select',
      '#title' => t('Count'),
      '#options' => $number_options,
      '#default_value' => !empty($this->options['h_axis']['gridlines']['count']) ? $this->options['h_axis']['gridlines']['count'] : '',
      '#description' => t('The color of the horizontal gridlines inside the chart area.'),
    );
    
    $form['h_axis']['minor_gridlines'] = array(
      '#type' => 'fieldset',
      '#title' => t('Minor gridlines'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    
    $form['h_axis']['minor_gridlines']['color'] = array(
      '#title' => t('Color'),
      '#default_value' => !empty($this->options['h_axis']['minor_gridlines']['color']) ? $this->options['h_axis']['minor_gridlines']['color'] : '',
      '#description' => t('The color of the horizontal minor gridlines inside the chart area.'),
    );
    
    $form['h_axis']['minor_gridlines']['color']['#type'] = module_exists('jquery_colorpicker') ? 'jquery_colorpicker' : 'textfield';
    
    $form['h_axis']['minor_gridlines']['count'] = array(
      '#type' => 'select',
      '#title' => t('Count'),
      '#options' => $number_options,
      '#default_value' => !empty($this->options['h_axis']['minor_gridlines']['count']) ? $this->options['h_axis']['minor_gridlines']['count'] : '',
      '#description' => t('The number of horizontal minor gridlines between two regular gridlines.'),
    );
  }

  /**
   * Provides an options form for background color supporting charts.
   */
  protected function background_color_options_form(&$form, &$form_state) {
    $width_options = array();
    for ($i = 0; $i <= 10; $i++) {
      $width_options[$i] = $i;
    }

    if (module_exists('jquery_colorpicker')) {
      $form['background_color'] = array(
        '#type' => 'fieldset',
        '#title' => t('Background color'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
    
      $form['background_color']['stroke'] = array(
        '#type' => 'jquery_colorpicker',
        '#title' => t('Stroke'),
        '#default_value' => !empty($this->options['background_color']['stroke']) ? $this->options['background_color']['stroke'] : '',
        '#description' => t('The color of the chart border, as an HTML color string.'),
      );
    
      $form['background_color']['stroke_width'] = array(
        '#type' => 'select',
        '#title' => t('Stroke width'),
        '#field_suffix' => 'px',
        '#options' => $width_options,
        '#default_value' => !empty($this->options['background_color']['stroke_width']) ? $this->options['background_color']['stroke_width'] : '',
        '#description' => t('The border width, in pixels.'),
      );
    
      $form['background_color']['fill'] = array(
        '#type' => 'jquery_colorpicker',
        '#title' => t('Fill'),
        '#default_value' => !empty($this->options['background_color']['fill']) ? $this->options['background_color']['fill'] : '',
        '#description' => t('The chart fill color, as an HTML color string.'),
      );
    }
  }

  /**
   * Provides an options form for legend supporting charts.
   */
  protected function legend_options_form(&$form, &$form_state) {
    $form['legend'] = array(
      '#type' => 'fieldset',
      '#title' => t('Legend'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    
    $form['legend']['position'] = array(
      '#type' => 'select',
      '#title' => t('Position'),
      '#options' => array(
        'right' => t('Right'),
        'left' => t('Left'),
        'top' => t('Top'),
        'bottom' => t('Bottom'),
        'none' => t('None'),
      ),
      '#default_value' => !empty($this->options['legend']['position']) ? $this->options['legend']['position'] : '',
      '#description' => t('The legend position within the chart.'),
    );
    
    $form['legend']['alignment'] = array(
      '#type' => 'select',
      '#title' => t('Alignment'),
      '#options' => array(
        'start' => t('Start'),
        'center' => t('Center'),
        'end' => t('End'),
      ),
      '#default_value' => !empty($this->options['legend']['alignment']) ? $this->options['legend']['alignment'] : '',
      '#description' => t('The alignment of the legend within its position.'),
    );
  }

  /**
   * Provides an options form for tooltip supporting charts.
   */
  protected function tooltip_options_form(&$form, &$form_state) {
    $form['tooltip'] = array(
      '#type' => 'fieldset',
      '#title' => t('Tooltip'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    
    $form['tooltip']['trigger'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable'),
      '#return_value' => 'hover',
      '#default_value' => isset($this->options['tooltip']['trigger']) && $this->options['tooltip']['trigger'] == 'hover',
      '#description' => t('Display a tooltip when hovering over a chart item.'),
    );
    
    $form['tooltip']['text'] = array(
      '#type' => 'select',
      '#title' => t('Tooltip text'),
      '#options' => array(
        'value' => t('Value'),
        'percentage' => t('Percentage'),
        'both' => t('Both'),
      ),
      '#default_value' => !empty($this->options['tooltip']['text']) ? $this->options['tooltip']['text'] : '',
      '#description' => t('The text to display when hovering over a chart item.'),
      '#dependency' => array('edit-chart-options-tooltip-trigger' => array('1')),
    );
  }

  /**
   * Removes non-chart related options from the options array prior
   * to populating a GoogleChartsChartWrapper object.
   *
   * @see views_chart_tools_handler_element::cleanse_options()
   */
  protected function cleanse_options() {
    $chart_options = $this->chart_option_definition();
    $options = array();
    foreach ($chart_options as $option => $definition) {
      if (isset($this->options[$option])) {
        $options[$option] = $this->options[$option];
      }
    }
    // Set the title option.
    $options['title'] = $this->options['label'];
    $options['allowHtml'] = TRUE;
    return $options;
  }

}
