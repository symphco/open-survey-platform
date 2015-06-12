<?php

/**
 * Base control handler.
 */
class views_chart_tools_handler_control extends views_chart_tools_handler_element {

  protected $element_wrapper = 'GoogleChartsControlWrapper';

  public function option_definition() {
    $options = parent::option_definition();
    $options['filter_column_label'] = array('default' => '');
    return $options;
  }

  public function options_form(&$form, &$form_state) {
    // All filters need to specify a column.
    $labels = $this->view->display_handler->get_field_labels();
    $form['filter_column_label'] = array(
      '#type' => 'select',
      '#title' => t('Filter column'),
      '#options' => array_combine(array_values($labels), array_values($labels)),
      '#default_value' => $this->options['filter_column_label'],
      '#required' => TRUE,
    );
    parent::options_form($form, $form_state);
    unset($form['exclude']);
  }

  /**
   * User interface options form.
   */
  protected function ui_options_form(&$form, &$form_state) {
    $form['ui'] = array(
      '#type' => 'fieldset',
      '#title' => t('UI'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['ui']['realtime_trigger'] = array(
      '#type' => 'checkbox',
      '#title' => t('Realtime trigger'),
      '#default_value' => !empty($this->options['ui']['realtime_trigger']),
      '#description' => t("Whether the control should match any time a key is pressed or only when the input field 'changes' (loss of focus or pressing the Enter key)."),
    );

    $form['ui']['label'] = array(
      '#type' => 'textfield',
      '#title' => t('Label'),
      '#default_value' => !empty($this->options['ui']['label']) ? $this->options['ui']['label'] : '',
      '#description' => t('The label to display next to the input field. If unspecified, the label of the column the control operates on will be used.'),
    );

    $form['ui']['label_separator'] = array(
      '#type' => 'textfield',
      '#title' => t('Label separator'),
      '#default_value' => !empty($this->options['ui']['label_separator']) ? $this->options['ui']['label_separator'] : '',
      '#description' => t('A separator string appended to the label, to visually separate the label from the input field.'),
    );

    $form['ui']['label_stacking'] = array(
      '#type' => 'select',
      '#title' => t('Label stacking'),
      '#options' => array(
        'vertical' => t('Vertical'),
        'horizonal' => t('Horizontal'),
      ),
      '#default_value' => !empty($this->options['ui']['label_stacking']) ? $this->options['ui']['label_stacking'] : '',
      '#description' => t('Whether the label should display above (vertical stacking) or beside (horizontal stacking) the input field. Use either <em>vertical</em> or <em>horizontal</em>.'),
    );

    $form['ui']['css_class'] = array(
      '#type' => 'textfield',
      '#title' => t('CSS class'),
      '#default_value' => !empty($this->options['ui']['css_class']) ? $this->options['ui']['css_class'] : '',
      '#description' => t('The CSS class to assign to the control, for custom styling.'),
    );
  }

}
