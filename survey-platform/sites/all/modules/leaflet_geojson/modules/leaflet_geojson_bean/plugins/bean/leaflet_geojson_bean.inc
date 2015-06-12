<?php
/**
 * @file
 * Leaflet GeoJSON bean plugin.
 */

class LeafletGeoJSONBean extends BeanPlugin {
  /**
   * Declares default block settings.
   */
  public function values() {
    $values = array(
      'settings' => array(
        'map' => NULL,
        'height' => '400',
        'source' => NULL,
      ),
    );
    return array_merge(parent::values(), $values);
  }
  /**
   * Builds extra settings for the block edit form.
   */
  public function form($bean, $form, &$form_state) {
    $form = array();
    $form['settings'] = array(
      '#type' => 'fieldset',
      '#tree' => 1,
      '#title' => t('Settings'),
    );
    // Choose a geojson source.
    $source_options = $this->getSourceOptions();
    $default_source = isset($bean->settings['source']) ? $bean->settings['source'] : key($source_options);
    $form['settings']['source'] = array(
      '#type' => 'select',
      '#title' => t('GeoJSON source'),
      '#options' => $source_options,
      '#default_value' => $default_source,
      '#required' => TRUE,
      '#description' => t("Choose the GeoJSON source that will provide the map data.") . "<br/>" .
                        t("Views GeoJSON page displays are automatically exposed.") . " " .
                        t("Implement <code>hook_leaflet_geojson_source_info()</code> to define custom geojson sources."),
    );
    // Choose a map preset.
    $map_options = $this->getMapOptions();
    $default_map = isset($bean->settings['map']) ? $bean->settings['map'] : key($map_options);
    $form['settings']['map'] = array(
      '#title' => t('Leaflet map'),
      '#type' => 'select',
      '#options' => $map_options,
      '#default_value' => $default_map,
      '#required' => TRUE,
      '#description' => t("Select the Leaflet map that will display the data.") . " " .
        t("Implement <code>hook_leaflet_map_info()</code> to define custom leaflet maps."),

    );
    // Optionally set map height.
    $default_height = isset($bean->settings['height']) ? $bean->settings['height'] : 400;
    $form['settings']['height'] = array(
      '#title' => t('Map height'),
      '#type' => 'textfield',
      '#field_suffix' => t('px'),
      '#size' => 4,
      '#default_value' => $default_height,
      '#required' => FALSE,
      '#description' => t("Set the map height in pixels."),
    );
    // Optionally override map settings.
    $default_override_map_settings = isset($bean->settings['override_map_settings']) ? $bean->settings['override_map_settings'] : FALSE;
    $form['settings']['override_map_settings'] = array(
      '#type' => 'checkbox',
      '#title' => 'Override map settings',
      '#default_value' => $default_override_map_settings,
      '#description' => t("Choose to override settings as zoom level & center of the map."),
    );
    $form['settings']['map_settings'] = array(
      '#type' => 'fieldset',
      '#title' => 'Map settings overrides',
      '#tree' => TRUE,
      '#states' => array(
        'visible' => array(
          ':input[name="settings[override_map_settings]"]' => array('checked' => TRUE),
        ),
      ),
    );
    $default_zoom = isset($bean->settings['map_settings']['zoom']) ? $bean->settings['map_settings']['zoom'] : 1;
    $form['settings']['map_settings']['zoom'] = array(
      '#title' => t('Zoom'),
      '#type' => 'textfield',
      '#size' => 20,
      '#default_value' => $default_zoom,
      '#required' => FALSE,
    );
    $form['settings']['map_settings']['center'] = array(
      '#type' => 'fieldset',
      '#title' => 'Map center',
      '#tree' => TRUE,
      '#description' => t("Provide a default map center especially when using the bounding box strategy."),
    );
    $default_center = isset($bean->settings['map_settings']['center']) ? $bean->settings['map_settings']['center'] : array('lon' => 0, 'lat' => 0);
    $form['settings']['map_settings']['center']['lon'] = array(
      '#title' => t('Center longitude'),
      '#type' => 'textfield',
      '#size' => 20,
      '#default_value' => $default_center['lon'],
      '#required' => FALSE,
    );
    $form['settings']['map_settings']['center']['lat'] = array(
      '#title' => t('Center latitude'),
      '#type' => 'textfield',
      '#size' => 20,
      '#default_value' => $default_center['lat'],
      '#required' => FALSE,
    );
    return $form;
  }

  /**
   * Displays the bean.
   */
  public function view($bean, $content, $view_mode = 'default', $langcode = NULL) {
    // Prepare leaflet map settings.
    $map = leaflet_map_get_info($bean->settings['map']);
    $height = $bean->settings['height'];

    // Prepare source and fetch json.
    $source_info = leaflet_geojson_source_get_info($bean->settings['source']);
    $features = array();

    $context = array(
      'map' => &$map,
      'source_info' => &$source_info,
      'bean' => &$bean,
    );
    drupal_alter('leaflet_geojson_bean_view_features', $features, $context);

    $content['map'] = array(
      '#markup' => leaflet_render_map($map, $features, $height . 'px'),
    );
    return $content;
  }

  protected function getMapOptions() {
    $map_options = array();
    foreach (leaflet_map_get_info() as $key => $map) {
      $map_options[$key] = t($map['label']);
    }
    return $map_options;
  }

  protected function getSourceOptions() {
    $sources = leaflet_geojson_source_get_info(NULL, TRUE);
    $source_options = array();
    foreach ($sources as $id => $source) {
      $source_options[$id] = $source['title'];
    }
    return $source_options;
  }

}
