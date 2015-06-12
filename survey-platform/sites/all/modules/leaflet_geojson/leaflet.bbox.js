(function ($) {

  Drupal.leafletBBox = {

    map: null,
    markerGroup: null,

    onMapLoad: function(event) {
      var map = this;
      Drupal.leafletBBox.map = map;

      Drupal.leafletBBox.markerGroup = new L.LayerGroup();
      Drupal.leafletBBox.markerGroup.addTo(map);

      map.on('moveend', Drupal.leafletBBox.moveEnd);
      Drupal.leafletBBox.moveEnd();
    },

    moveEnd: function(e) {
      var map = Drupal.leafletBBox.map;
      if (!map._popup) {
        Drupal.leafletBBox.makeGeoJSONLayer(map);
      }
    },

    makeGeoJSONLayer: function(map, url) {
      url = typeof url !== 'undefined' ? url : Drupal.settings.leafletBBox.url;

      var bbox_arg_id = ('bbox_arg_id' in Drupal.settings.leafletBBox) ?
        Drupal.settings.leafletBBox.bbox_arg_id : 'bbox';

      // Add bbox and zoom parameters as get params.
      url += "?" + bbox_arg_id +"=" + map.getBounds().toBBoxString();
      url += "&zoom=" + map.getZoom();

      $.getJSON(url, function(data) {
        //New GeoJSON layer
        var geojsonLayer = new L.GeoJSON(data, Drupal.leafletBBox.geoJSONOptions);
        Drupal.leafletBBox.markerGroup.clearLayers();
        Drupal.leafletBBox.markerGroup.addLayer(geojsonLayer);
      });
    }

  };

  Drupal.leafletBBox.geoJSONOptions = {

    onEachFeature: function(feature, layer) {
      if (feature.properties) {
        if (feature.properties.description) {
          layer.bindPopup(feature.properties.description);
        } else if (feature.properties.name) {
          layer.bindPopup(feature.properties.name);
        }
      }
    }

  };

  // Inject into leaflet initialize.
  // @todo: there should be a nicer way to do that?
  _leaflet_bbox_old_leaflet_initialize = L.Map.prototype.initialize;
  L.Map.include({
    initialize: function(/*HTMLElement or String*/ id, /*Object*/ options) {
      _leaflet_bbox_old_leaflet_initialize.apply(this, [id, options]);
      this.on('load', Drupal.leafletBBox.onMapLoad, this);
    }
  });

})(jQuery);
