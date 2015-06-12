<?php

/**
 * @file
 * Provides a base handler for image charts.
 */

/**
 * Base image chart handler.
 */
class views_chart_tools_handler_chart_image extends views_chart_tools_handler_chart {

  public function chart_option_definition() {
    $options['height'] = array('default' => '');
    $options['width'] = array('default' => '');
    $options['legend'] = array('default' => '');
    $options['show_category_labels'] = array('default' => TRUE);
    $options['show_value_labels'] = array('default' => TRUE);
    return $options;
  }

  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $dimension_options = drupal_map_assoc(array(100, 200, 300, 400, 500, 600, 700, 800, 900, 1000));
    $form['height'] = array(
      '#type' => 'select',
      '#title' => t('Height'),
      '#options' => $dimension_options,
      '#default_value' => $this->options['height'],
    );
  
    $form['width'] = array(
      '#type' => 'select',
      '#title' => t('Width'),
      '#options' => $dimension_options,
      '#default_value' => $this->options['width'],
    );
  
    $form['legend'] = array(
      '#type' => 'select',
      '#title' => t('Legend'),
      '#options' => array(
        'right' => t('Right'),
        'left' => t('Left'),
        'top' => t('Top'),
        'bottom' => t('Bottom'),
        'none' => t('None'),
      ),
      '#default_value' => $this->options['legend'],
    );

    $form['show_category_labels'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show category labels'),
      '#return_value' => TRUE,
      '#default_value' => $this->options['show_category_labels'],
    );

    $form['show_value_labels'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show value labels'),
      '#return_value' => TRUE,
      '#default_value' => $this->options['show_value_labels'],
    );
  }

}
