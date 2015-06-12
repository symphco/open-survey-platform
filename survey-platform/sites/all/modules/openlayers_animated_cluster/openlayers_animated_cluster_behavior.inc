<?php
/**
 * @file
 * Implementation of OpenLayers Cluster behavior.
 */

/**
 * Animated Cluster behavior
 */
class openlayers_animated_cluster_behavior extends openlayers_behavior {
  /**
   * Provide initial values for options.
   */
  function options_init() {
    return array(
      'clusterlayer' => array(),
      'distance' => '20',
      'low_color' => 'rgb(181, 226, 140)',
      'middle_color' => 'rgb(241, 211, 87)',
      'high_color' => 'rgb(253, 156, 115)',
      'middle_lower_bound' => '15',
      'middle_upper_bound' => '50',
    );
  }

  /**
   * Provide form for configurations per map.
   */
  function options_form($defaults = array()) {
    // Only prompt for vector layers
    $vector_layers = array();
    foreach ($this->map['layers'] as $id => $name) {
      $layer = openlayers_layer_load($id);
      if (isset($layer->data['vector']) && $layer->data['vector'] == TRUE) {
        $vector_layers[$id] = $name;
      }
    }

    return array(
      'clusterlayer' => array(
        '#title' => t('Layers'),
        '#type' => 'checkboxes',
        '#options' => $vector_layers,
        '#description' => t('Select layers to cluster.'),
        '#default_value' => isset($defaults['clusterlayer']) ?
        $defaults['clusterlayer'] : array(),
      ),
      'distance' => array(
        '#type' => 'textfield',
        '#default_value' => (isset($defaults['distance'])) ?
        $defaults['distance'] : 20,
        '#size' => 5,
        '#title' => t('Distance'),
        '#description' => t('Pixel distance between features that should ' .
        'be considered a single cluster'),
      ),
      'low_color' => array(
        '#type' => 'textfield',
        '#default_value' => (isset($defaults['low_color'])) ?
          $defaults['low_color'] : 'rgb(181, 226, 140)',
        '#size' => 5,
        '#title' => t('Low color'),
        '#description' => t(''),
      ),
      'middle_color' => array(
        '#type' => 'textfield',
        '#default_value' => (isset($defaults['middle_color'])) ?
          $defaults['middle_color'] : 'rgb(241, 211, 87)',
        '#size' => 5,
        '#title' => t('Middle color'),
        '#description' => t(''),
      ),
      'high_color' => array(
        '#type' => 'textfield',
        '#default_value' => (isset($defaults['high_color'])) ?
          $defaults['high_color'] : 'rgb(253, 156, 115)',
        '#size' => 5,
        '#title' => t('High color'),
        '#description' => t(''),
      ),
      'middle_lower_bound' => array(
        '#type' => 'textfield',
        '#default_value' => (isset($defaults['middle_lower_bound'])) ?
          $defaults['middle_lower_bound'] : 15,
        '#size' => 5,
        '#title' => t('Middle lower bound'),
        '#description' => t(''),
      ),
      'middle_upper_bound' => array(
        '#type' => 'textfield',
        '#default_value' => (isset($defaults['middle_upper_bound'])) ?
          $defaults['middle_upper_bound'] : 50,
        '#size' => 5,
        '#title' => t('Middle upper bound'),
        '#description' => t(''),
      ),
    );
  }

  /**
   * Render.
   */
  function render(&$map) {
    $animated_cluster_path = libraries_get_path('AnimatedCluster');
    drupal_add_js($animated_cluster_path . '/AnimatedCluster.js');
    drupal_add_js(drupal_get_path('module', 'openlayers_animated_cluster') . '/openlayers_animated_cluster_behavior.js');
    return $this->options;
  }
}
