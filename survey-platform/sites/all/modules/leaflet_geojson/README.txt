
Leaflet GeoJSON
-----------

Leaflet GeoJSON is a set of modules for creating Leaflet maps backed by GeoJSON data.

Modules
-----------

Leaflet GeoJSON
- Provides API functionality as defining GeoJSON sources and adding a Leaflet bounding box strategy.

Leaflet GeoJSON Bean
- Allows you to create leaflet map blocks based on GeoJSON data and will automatically extend them with the bounding box strategy if supported.
  Custom blocks? Even better, we are using: Bean.

Leaflet GeoJSON API
-----------

leaflet_geojson_add_bbox_strategy($url).
- Adds a Bounding Box strategy for leaflet maps linking to a specified url.

hook_leaflet_geojson_source_info().
- Allows to specify geojson sources for inclusion in leaflet maps.
  See leaflet_geojson_leaflet_geojson_source_info() for an example that
  provides views_geojson page displays as geojson sources.
  You can actually use those by activating the leaflet_geojson_bean module.

TODO
-----------

- Attach the bbox strategy to a specific map.
- See @todo markers in code.

For sub-module specific documentation, see their folders.

Maintainers
-----------
- dasjo (Josef Dabernig)
