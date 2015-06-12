/**
 * @file
 * OpenLayers Behavior implementation for animated clustering.
 */

/**
 * OpenLayers Animated Cluster Behavior.
 */
Drupal.openlayers.addBehavior('openlayers_animated_cluster_behavior', function (data, options) {
  options.animationMethod = OpenLayers.Easing.Expo.easeOut;
  options.animationDuration = 10;

  // Define three rules to style the cluster features.
  var lowRule = new OpenLayers.Rule({
    filter: new OpenLayers.Filter.Comparison({
      type: OpenLayers.Filter.Comparison.LESS_THAN,
      property: "count",
      value: options.middle_lower_bound
    }),
    symbolizer: {
      fillColor: options.low_color,
      fillOpacity: 0.9,
      strokeColor: options.low_color,
      strokeOpacity: 0.5,
      strokeWidth: 12,
      pointRadius: 10,
      label: "${count}",
      labelOutlineWidth: 1,
      fontColor: "#ffffff",
      fontOpacity: 0.8,
      fontSize: "12px"
    }
  });
  var middleRule = new OpenLayers.Rule({
    filter: new OpenLayers.Filter.Comparison({
      type: OpenLayers.Filter.Comparison.BETWEEN,
      property: "count",
      lowerBoundary: options.middle_lower_bound,
      upperBoundary: options.middle_upper_bound
    }),
    symbolizer: {
      fillColor: options.middle_color,
      fillOpacity: 0.9,
      strokeColor: options.middle_color,
      strokeOpacity: 0.5,
      strokeWidth: 12,
      pointRadius: 15,
      label: "${count}",
      labelOutlineWidth: 1,
      fontColor: "#ffffff",
      fontOpacity: 0.8,
      fontSize: "12px"
    }
  });
  var highRule = new OpenLayers.Rule({
    filter: new OpenLayers.Filter.Comparison({
      type: OpenLayers.Filter.Comparison.GREATER_THAN,
      property: "count",
      value: options.middle_upper_bound
    }),
    symbolizer: {
      fillColor: options.high_color,
      fillOpacity: 0.9,
      strokeColor: options.high_color,
      strokeOpacity: 0.5,
      strokeWidth: 12,
      pointRadius: 20,
      label: "${count}",
      labelOutlineWidth: 1,
      fontColor: "#ffffff",
      fontOpacity: 0.8,
      fontSize: "12px"
    }
  });

  var map = data.openlayers;
  var layers = [];
  for (var i in options.clusterlayer) {
    var selectedLayer = map.getLayersBy('drupalID', options.clusterlayer[i]);
    if (typeof selectedLayer[0] != 'undefined') {
      layers.push(selectedLayer[0]);
    }
  }

  // Go through chosen layers
  for (var i in layers) {
    var layer = layers[i];
    // Ensure vector layer
    if (layer.CLASS_NAME == 'OpenLayers.Layer.Vector') {
      var cluster =  new OpenLayers.Strategy.AnimatedCluster(options);

      var style = new OpenLayers.Style(null, {
        rules: [lowRule, middleRule, highRule]
      });

      var styleMap =  new OpenLayers.StyleMap(style);

      layer.styleMap =  styleMap;

      layer.addOptions({ 'strategies': [cluster] });
      cluster.setLayer(layer);
      cluster.features = layer.features.slice();
      cluster.activate();
      cluster.cluster();
    }
  }
});


/**
 * Override of callback used by 'popup' behaviour to support clusters
 */
Drupal.theme.openlayersPopup = function (feature) {
  if (feature.cluster) {
    var output = '';
    var visited = []; // to keep track of already-visited items
    var classes = [];

    for (var i = 0; i < feature.cluster.length; i++) {
      var pf = feature.cluster[i]; // pseudo-feature
      if (typeof pf.drupalFID != 'undefined') {
        var mapwide_id = feature.layer.drupalID + pf.drupalFID;
        if (mapwide_id in visited) continue;
        visited[mapwide_id] = true;
      }

      classes = ['openlayers-popup', 'openlayers-popup-feature'];
      if (i == 0) {
        classes.push('first');
      }
      if (i == (feature.cluster.length - 1)) {
        classes.push('last');
      }

      output += '<div class="'+classes.join(' ')+'">' +
        Drupal.theme.prototype.openlayersPopup(pf) + '</div>';
    }
    return output;
  }
  else {
    return Drupal.theme.prototype.openlayersPopup(feature);
  }
};
