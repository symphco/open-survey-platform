<?php

/**
 * @file
 * Hooks provided by the Leaflet GeoJSON Bean module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Alter a leaflet geojson features array before being viewed in a bean.
 *
 * @params array $features
 *   The features to be passed to the leaflet map.
 * @params array $context
 *   An associative array containing contextual information as
 *   - array $map
 *     The leaflet map definition.
 *   - array source_info
 *     The leaflet map geojson source definition.
 *   - Bean bean
 *     The bean that renders the map based on the source.
 */
function hook_leaflet_geojson_bean_view_features_alter(array &$features, array &$context) {
  // Add bbox js.
  if (isset($context['source_info']['bbox'])) {
    leaflet_geojson_add_bbox_strategy($context['source_info']['url']);
  }
}
