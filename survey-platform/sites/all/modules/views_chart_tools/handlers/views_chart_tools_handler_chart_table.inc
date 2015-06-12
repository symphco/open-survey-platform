<?php

/**
 * @file
 * Provides a handler for table charts.
 */

/**
 * Table chart handler.
 */
class views_chart_tools_handler_chart_table extends views_chart_tools_handler_chart {

  public function chart_option_definition() {
    $options['sort'] = array('default' => 'enable');
    $options['page'] = array('default' => 'enable');
    $options['show_row_number'] = array('default' => '');
    $options['first_row_number'] = array('default' => 1);
    $options['sort_column'] = array('default' => 0);
    $options['sort_ascending'] = array('default' => TRUE);
    return $options;
  }

  /**
   * Defines an options form for the chart type.
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['sort_column']['none'] = array(
      '#type' => 'radio',
      '#parents' => array('options', 'sort_column'),
      '#return_value' => '',
      '#id' => 'edit-options-sort-column-empty',
      '#default_value' => !empty($this->options['sort_column']) ? $this->options['sort_column'] : '',
    );

    $form['sort'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable sorting'),
      '#return_value' => 'enable',
      '#default_value' => $this->options['sort'],
    );
    
    $form['page'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable paging'),
      '#return_value' => 'enable',
      '#default_value' => $this->options['page'],
    );

    $form['show_row_number'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show row number'),
      '#default_value' => $this->options['show_row_number'],
    );

    $form['first_row_number'] = array(
      '#type' => 'textfield',
      '#title' => t('First row number'),
      '#default_value' => $this->options['first_row_number'],
      '#dependency' => array('edit-options-show-row-number' => array(1)),
    );

    $field_names = $this->view->display_handler->get_field_labels();
    $form['sort_column'] = array(
      '#type' => 'select',
      '#title' => t('Sort column'),
      '#options' => array_values($field_names),
      '#default_value' => $this->options['sort_column'],
      '#description' => t('The field by which the table should be initially sorted.'),
    );

    $form['sort_ascending'] = array(
      '#type' => 'select',
      '#title' => t('Sort direction'),
      '#options' => array(TRUE => t('Ascending'), FALSE => t('Descending')),
      '#default_value' => $this->options['sort_ascending'],
    );
  }

  public function options_submit(&$form, &$form_state) {
    $form_state['values']['options']['sort_column'] = (int) $form_state['values']['options']['sort_column'];
  }

}
