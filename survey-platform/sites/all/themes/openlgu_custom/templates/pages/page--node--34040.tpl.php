	<div class="main_content">
	 <div class="container">
		 <div class="row-fluid content page-hdr">
		 	<div class="span12">
		 		 <div class="social">
				  	<a><img src="http://localhost/wb-opengov-armmdata/sites/all/themes/openlgu_custom/images/service-links/facebook.png"></a>
				  	<a><img src="http://localhost/wb-opengov-armmdata/sites/all/themes/openlgu_custom/images/service-links/twitter.png"></a>
				  	<a><img src="http://localhost/wb-opengov-armmdata/sites/all/themes/openlgu_custom/images/service-links/forward.png"></a>

				  </div>

			 <h1>Lorem ipsum dolor sit amet</h1>
			 
			 </div>
		</div>
		 <div class="row-fluid data-pg content">
	
         
         
	        <div class="span12">
				
				<!--Horizontal Tab-->
			   		<?php print $messages; ?>
			        <a id="main-content"></a>
			        <?php print render($page['help']); ?>
			        <div class="resp-tabs-container">
			        <?php // print render($page['content']); ?>
			        <?php print $feed_icons; ?>
					</div>
			 </div>
		

			<div class="mapContainer" style="float:left;">
				<div class="mapInfoSummary">
					<h3>PRAESENT</h3>
					<ul class="summaryList">
						<li class="schools"><span id="number_of_schools">Stet</span> At vero eos </li>
						<li><span id="number_of_actual"></span> At vero eos et </li>
						<li><span id="number_of_missing"></span> Accusam et Justo</li>
					</ul>
				</div><!-- mapInfoSummary -->
				<div id="map_canvas" style="height: 500px;"></div><!-- map_canvas -->
				<div class="mapFooter">
					<p class="desclaimer"><span class="bold">Duis:</span>Lorem ipsum dolor sit amet, consectetuer adipiscing elit, sed diam nonummy nibh euismod tincidunt ut laoreet dolore magna aliquam erat volutpat. Ut wisi enim ad minim veniam, quis nostrud exerci tation ullamcorper suscipit lobortis nisl ut aliquip ex ea commodo consequat.</p>
					<ul class="legend">
						<li><span class="mapMarker mapMarker1"></span> Ut wisi enim ad minim veniam.</li>
						<li><span class="mapMarker mapMarker2"></span> Quis nostrud exerci tation ullamcorper.</li>
					</ul>
					<div class="clear"></div><!-- clear -->
				</div><!-- mapFooter -->
				<div class="graphWrapper">
					<div id="pie1" class="graphWrap"></div>
					<div id="bar1" class="graphWrap"></div>
					<div class="clear"></div><!-- clear -->
				</div><!-- graphWrapper -->
			</div><!-- mapContainer -->
		
		 
	  </div>
	</div>


	<!-- google maps -->
	<script src="https://maps.googleapis.com/maps/api/js"></script>
	<script src="/sites/all/themes/openlgu_custom/js/markerclusterer.js"></script>
	<script>

		function get_final_lat_lng(latlng){
	      var finalLatLng = latlng;

	      if (window.all_markers.length != 0) {
	          for (i=0; i < window.all_markers.length; i++) {
	            if(window.all_markers[i]){
	              var existingMarker = window.all_markers[i];
	              var pos = existingMarker.getPosition();

	              //if a marker already exists in the same position as this marker
	              if (latlng.equals(pos)) {
	                  //update the position of the coincident marker by applying a small multipler to its coordinates
	                  var newLat = latlng.lat() + (Math.random() -.5) / 1500;// * (Math.random() * (max - min) + min);
	                  var newLng = latlng.lng() + (Math.random() -.5) / 1500;// * (Math.random() * (max - min) + min);
	                  finalLatLng = new google.maps.LatLng(newLat,newLng);
	              }
	            }
	          }
	      }
	      return finalLatLng;
	    }


		function initialize() {
			var mapCanvas = document.getElementById('map_canvas');
			var mapOptions = {
				center: new google.maps.LatLng(5.696342, 121.015843),
				zoom: 8,
				minZoom: 7,
				panControl: false,
				streetViewControl: false,
				zoomControl:true,
				mapTypeId: google.maps.MapTypeId.ROADMAP
			}

			window.this_map = new google.maps.Map(mapCanvas, mapOptions);

			var gps_style = [{
		        url: '/sites/all/themes/openlgu_custom/images/map_cluster1.png',
		        height: 50,
		        width: 50,
		        anchorIcon: [0,0],
		        anchorText: [0,0],
		        textColor: '#fefefe',
		        textSize: 11
		      }];

		    var missing_style = [{
		        url: '/sites/all/themes/openlgu_custom/images/map-cluster2.png',
		        height: 50,
		        width: 50,
		        anchorIcon: [0,0],
		        anchorText: [0,0],
		        textColor: '#fefefe',
		        textSize: 11
		      }];

			window.actual_gps_markers = new MarkerClusterer(window.this_map, [], {styles: gps_style, averageCenter: true, maxZoom: 17});
			window.missing_gps_markers = new MarkerClusterer(window.this_map, [], {styles: missing_style, averageCenter: true, maxZoom: 17});
			window.all_markers = new Array();
			window.markers_count = 0;

			window.gps_location_percentage = 0.0;
			window.gps_location_missing_percentage = 0.0;

			window.gps_location_count = 0;
			window.gps_location_missing_count = 0;

			window.basilan_count = 0;
			window.lanao_count = 0;
			window.maguindanao_count = 0;
			window.sulu_count = 0;
			window.tawi_tawi_count = 0;

			window.basilan_actual = 0;
			window.lanao_actual = 0;
			window.maguindanao_actual = 0;
			window.sulu_actual = 0;
			window.tawi_tawi_actual = 0;

			window.basilan_missing = 0;
			window.lanao_missing = 0;
			window.maguindanao_missing = 0;
			window.sulu_missing = 0;
			window.tawi_tawi_missing = 0;

			jQuery.getJSON('/api/v1/schools', function(data){
				for(var i=0; i<data.length; i++){
					var myLatLng = new google.maps.LatLng(parseFloat(data[i].lat), parseFloat(data[i].long));

					if(data[i].field_coordinate_type_value == 'Actual GPS'){
						var image_url = '/sites/all/themes/openlgu_custom/images/map_marker1.png';
						window.gps_location_count += 1;
					}
					else {
						var image_url = '/sites/all/themes/openlgu_custom/images/map_marker2.png';
						window.gps_location_missing_count += 1;
					}

					var image = {
			              url: image_url
			              /*size: new google.maps.Size(27, 45),
			              origin: new google.maps.Point(0,0),
			              anchor: new google.maps.Point(12, 33)*/
			        };

			        var marker = new google.maps.Marker({
					  position: get_final_lat_lng(myLatLng),
					  map: window.this_map,
					  icon: image,
					  title: data[i].title
					});

					google.maps.event.addListener(marker, 'click', function() {
			            open_window(this.marker_index);
			          });

					marker.node_url = data[i].uri;

					if(data[i].field_coordinate_type_value == 'Actual GPS'){
						window.actual_gps_markers.addMarker(marker);
						if(data[i].field_sch_province_value == 'Basilan'){
							window.basilan_actual += 1;
						}

						else if(data[i].field_sch_province_value == 'Lanao del Sur'){
							window.lanao_actual += 1;
						}

						else if(data[i].field_sch_province_value == 'Maguindanao'){
							window.maguindanao_actual += 1;
						}

						else if(data[i].field_sch_province_value == 'Sulu'){
							window.sulu_actual += 1;
						}

						else if(data[i].field_sch_province_value == 'Tawi-Tawi'){
							window.tawi_tawi_actual += 1;
						}
					}
					else {
						window.missing_gps_markers.addMarker(marker);
						if(data[i].field_sch_province_value == 'Basilan'){
							window.basilan_missing += 1;
						}

						else if(data[i].field_sch_province_value == 'Lanao del Sur'){
							window.lanao_missing += 1;
						}

						else if(data[i].field_sch_province_value == 'Maguindanao'){
							window.maguindanao_missing += 1;
						}

						else if(data[i].field_sch_province_value == 'Sulu'){
							window.sulu_missing += 1;
						}

						else if(data[i].field_sch_province_value == 'Tawi-Tawi'){
							window.tawi_tawi_missing += 1;
						}
					}


					window.all_markers.push(marker);

					marker.marker_index = i;

					window.markers_count = window.markers_count + 1;

					if(data[i].field_sch_province_value == 'Basilan'){
						window.basilan_count += 1;
					}

					else if(data[i].field_sch_province_value == 'Lanao del Sur'){
						window.lanao_count += 1;
					}

					else if(data[i].field_sch_province_value == 'Maguindanao'){
						window.maguindanao_count += 1;
					}

					else if(data[i].field_sch_province_value == 'Sulu'){
						window.sulu_count += 1;
					}

					else if(data[i].field_sch_province_value == 'Tawi-Tawi'){
						window.tawi_tawi_count += 1;
					}

				}

				jQuery("#number_of_schools").html(window.markers_count);

				jQuery("#number_of_actual").html(window.gps_location_count);
				jQuery("#number_of_missing").html(window.gps_location_missing_count);

				window.gps_location_percentage = window.gps_location_count / window.markers_count * 100.0;
				window.gps_location_missing_percentage = window.gps_location_missing_count / window.markers_count * 100.0;

				window.basilan_percentage = window.basilan_actual / window.basilan_count * 100.0;
				window.lanao_percentage = window.lanao_actual / window.lanao_count * 100.0;
				window.maguindanao_percentage = window.maguindanao_actual / window.maguindanao_count * 100.0;
				window.sulu_percentage = window.sulu_actual / window.sulu_count * 100.0;
				window.tawi_tawi_percentage = window.tawi_tawi_actual / window.tawi_tawi_count * 100.0;

				render_graph();
			});
		}

		function close_all_other_info_windows(){
			markers_length = window.all_markers.length;
			for(var i=0; i<markers_length; i++){
				try {
					window.all_markers[i].infowindow.close();
				}
				catch(e){
					// do nothing
				}
			}
		}

		function open_window(i){
			close_all_other_info_windows();
			window.all_markers[i].infowindow = new google.maps.InfoWindow({
			  	content: '<a href="' + window.all_markers[i].node_url + '"><img src="/sites/all/themes/openlgu_custom/images/school_icon_500.png" style="height: 50px;" /> <strong style="font-size: 20px; margin-top: 18px; float: right;">' + window.all_markers[i].title + '</strong></a>'
			});

			window.all_markers[i].infowindow.open(window.this_map,window.all_markers[i]);
		}


		function render_graph(){
		    jQuery('#pie1').highcharts({
		        chart: {
		            plotBackgroundColor: null,
		            plotBorderWidth: null,
		            plotShadow: false
		        },
		        title: {
		            text: 'Graph of GPS Location / No GPS Location'
		        },
		        tooltip: {
		            pointFormat: '<b style="font-size: 30px;">{point.percentage:.1f}%</b>'
		        },
		        plotOptions: {
		            pie: {
		                allowPointSelect: true,
		                cursor: 'pointer',
		                dataLabels: {
		                    enabled: true,
		                    format: '<b>{point.name}</b>: {point.percentage:.1f} %',
		                    style: {
		                        color: (Highcharts.theme && Highcharts.theme.contrastTextColor) || 'black'
		                    }
		                }
		            }
		        },
		        colors: ['#58bc26','#366A1C'],
		        series: [{
		            type: 'pie',
		            data: [
		                ['Actual GPS Location of School', window.gps_location_percentage],
		                ['Actual GPS Missing.<br/>Using Municipality GPS Location',window.gps_location_missing_percentage],
		            ]
		        }]
		    });

			jQuery('#bar1').highcharts({
								
				title: {
					text: 'Percentage of Schools that are GEO-Tagged in a Province'
				},
				xAxis: {
					categories: [
						'Basilan',
						'Lanao del Sur',
						'Maguindanao',
						'Sulu',
						'Tawi-Tawi',
					]
				},
				yAxis: {
					min: 0,
					max: 100,
					title: {
						text: ''
					}
				},
				tooltip: {
					headerFormat: '<span style="font-size:10px">{point.key}</span><table>',
					pointFormat: '<tr>' +
					'<td style="padding:0"><b>{point.y}%</b></td></tr>',
					footerFormat: '</table>',
					shared: true,
					useHTML: true
				},
				plotOptions: {
					column: {
						pointPadding: 0.2,
						borderWidth: 0,
					}
				},
				colors: ['#58bc26'],
				series: [{
					type: 'column',
					name: 'Provinces',
					data: [parseFloat(window.basilan_percentage.toFixed(2)), parseFloat(window.lanao_percentage.toFixed(2)), parseFloat(window.maguindanao_percentage.toFixed(2)), parseFloat(window.sulu_percentage.toFixed(2)), parseFloat(window.tawi_tawi_percentage.toFixed(2))]
				}]
			});
		}

		google.maps.event.addDomListener(window, 'load', initialize);
	</script>

	<script src="/sites/all/themes/openlgu_custom/js/main.js"></script>

	
	<div class="footer">
	 <div class="container">
	   <div class="row-fluid">
	   
		
		<div class="footer_right">
			<div class="images-container">
			 	<img src="/wb-opengov-armmdata/sites/all/themes/openlgu_custom/images/logo-default.png" alt="">
			 	<p>All content is in the public domain unless otherwise stated.</p>
			</div>
		</div>
		 
		<div class="footer_left">
		 
		 <div class="footer_link social-media" style="float: left; top: 0px;">
		  <h4>Social Media</h4>
		  <ul>
            <li id="menu-item-3278" class="menu-item">Facebook Page</li>
            <li id="menu-item-251" class="menu-item">Facebook News</li>
            <li id="menu-item-36581" class="menu-item">YouTube Channel</li>
            <li id="menu-item-18123" class="menu-item">Official Blog</li>
		 </ul>
		 </div>


		 <div class="footer_link resources" style="float: left; top: 0px;">
		  <h4>Official Link</h4>
		  <ul>
            <li id="menu-item-4168" class="menu-item">Official Website Link</li>
		 </ul>
		 </div>
		</div>
	   </div>
     </div>
	</div>
	

    <!--/.fluid-container-->

    <!-- Le javascript
    ================================================== -->
    <!-- Placed at the end of the document so the pages load faster -->
    <script src="<?php print $base_path; ?><?php print $directory; ?>/js/bootstrap-dropdown.js"></script>
    <script src="<?php print $base_path; ?><?php print $directory; ?>/js/bootstrap-collapse.js"></script>
    <script src="<?php print $base_path; ?><?php print $directory; ?>/js/bootstrap-typeahead.js"></script>
