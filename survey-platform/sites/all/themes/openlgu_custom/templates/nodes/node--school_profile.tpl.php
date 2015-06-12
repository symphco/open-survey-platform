<?php

/**
 * @file
 * Default theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct URL of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type; for example, "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type; for example, story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode; for example, "full", "teaser".
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined; for example, $node->body becomes $body. When needing to
 * access a field's raw values, developers/themers are strongly encouraged to
 * use these variables. Otherwise they will have to explicitly specify the
 * desired field language; for example, $node->body['en'], thus overriding any
 * language negotiation rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 *
 * @ingroup themeable
 */
$latlong = $content['field_latlong']['#items'][0];
$division = $content['field_division']['#items'][0]['safe_value'];
$address = $content['field_address']['#items'][0]['safe_value'];
$municipality =  $content['field_municipality']['#items'][0]['safe_value'];
$school_id =  $content['field_school_id']['#items'][0]['safe_value'];
$school_head =  $content['field_school_head']['#items'][0]['safe_value'];
$region =  $content['field_sch_region']['#items'][0]['safe_value'];
$province =  $content['field_sch_province']['#items'][0]['safe_value'];
$body = $content['body']['#items'][0]['value'];
$school_name = $title;
$comment = $content["comments"];
$school_type = $content['field_sch_type']['#items'][0]['safe_value'];
$school_enrollment_data = $content['field_enrollment_data_']['#items'][0]['safe_value'];

?>

<?php
  // We hide the comments and links now so that we can render them later.
  hide($content['comments']);
  hide($content['links']);
?>

  
  <div class="mapContainerSingle">
    <h3 class="schoolName"><?php print $title; ?></h3>
    <ul class="info">
      <li class="location">
        <span class="bold">LOCATION:</span> Province: <span class="bold"><?php print $province; ?></span> Municipality: <span class="bold"><?php print $municipality; ?></span> Address: <span class="bold"><?php print $address; ?></span></li>
      <li class="schoolID"><span class="bold">SCHOOL ID:</span> <?php print $school_id; ?></li>
      <li class="enrollmentData"><span class="bold">ENROLLMENT DATA:</span> <?php print $school_enrollment_data; ?></li>
      
    </ul>
    <div id="survey_table_container"></div>
    
    <div class="mapContainer">
      <div id="map_canvas" style="height: 500px;"></div><!-- map_canvas -->
    </div><!-- mapContainer -->
    <p class="disclaimer"><span class="bold">Disclaimer:</span> This map is for data illustration purposes only. The geographical coordinates of ARMM Schools are an approximation based on the centroid of a municipality. The boundaries, names shown and designations used on this map do not imply official endorsement or acceptance by the Govt. of the Philippines.</p>
    <div class="colContainer">
      <div class="colLeft">
      	<h3 class="sectionHeading">SCHOOL IMAGES</h3>
        <div class="imageWrapper generalImageSection">
          <?php print views_embed_view('image_gallery', 'block_2', $node->nid); ?>
          <?php print views_embed_view('image_gallery', 'block_1', $node->nid); ?>
          
          <div class="clear"></div><!-- clear -->
        </div>
        
      </div><!-- colLeft -->

      <div class="colRight">
        <!-- <h4>Provide Comments/Leave Feedback</h4> -->
        <!-- <h4>Feedback</h4> -->
        <?php 
          if ($user->uid ) {
            print render($content['links']);
            print render($content['comments']);
          }
          else {
            print render($content['comments']);
            print render($content['links']);
            $elements = drupal_get_form("user_login"); 
            $form = drupal_render($elements);
            echo $form;
          }
        ?>
      </div><!-- colRight -->
      <div class="clear"></div><!-- clear -->
    </div><!-- colContainer -->
  </div><!-- mapContainerSingle -->


  <!-- google maps -->
  <script src="https://maps.googleapis.com/maps/api/js"></script>
  <script src="/sites/all/themes/openlgu_custom/js/markerclusterer.js"></script>
  <script>



    function initialize() {
      var mapCanvas = document.getElementById('map_canvas');
      var mapOptions = {
        center: new google.maps.LatLng(<?php print $latlong['lat']?>, <?php print $latlong['lon'] ?>),
        zoom: 8,
        minZoom: 7,
        panControl: false,
        streetViewControl: false,
        zoomControl:true,

        mapTypeId: google.maps.MapTypeId.ROADMAP
      }

      window.this_map = new google.maps.Map(mapCanvas, mapOptions);


      var image_url = '/sites/all/themes/openlgu_custom/images/map_marker1.png';
      var image = {
            url: image_url
            /*size: new google.maps.Size(27, 45),
            origin: new google.maps.Point(0,0),
            anchor: new google.maps.Point(12, 33)*/
      };

      var marker = new google.maps.Marker({
        position: new google.maps.LatLng(<?php print $latlong['lat']?>, <?php print $latlong['lon'] ?>),
        map: window.this_map,
        icon: image,
        title: "<?php print $title; ?>"
      });

      google.maps.event.addListener(marker, 'click', function() {
          var marker_info = new google.maps.InfoWindow({
              content: '<img src="/sites/all/themes/openlgu_custom/images/school_icon_500.png" style="height: 50px;" /> <strong style="font-size: 20px; margin-top: 18px; float: right;"><?php print $title; ?></strong>'
          });
          marker_info.open(window.this_map, marker);
        });
    }


    google.maps.event.addDomListener(window, 'load', initialize);
  </script>

  <script>
    jQuery(document).ready(function(){
      var survey_ids = [];
      jQuery.getJSON("/api/v1/surveys", function(survey_data){
        for(var x=0; x<survey_data.length; x++){
          var survey_id = survey_data[x]["nid"].toString();
          
          html = '<table class="table_row '+ survey_id +'_table_item"><thead><tr><th>Survey ID</th><th>Survey Title</th><th>Year</th><th>School Type</th><th># Students</th><th># Teachers</th><th>% of Teachers Present</th></tr></thead><tbody><tr><td>'+ survey_id +'</td><td id="'+ survey_id +'_survey_title">Survey title</td><td id="'+ survey_id +'_academic_year_value"></td><td><?php print $school_type; ?></td><td id="'+ survey_id +'_number_of_students_value"></td><td id="'+ survey_id +'_number_of_teachers_value"></td><td id="'+ survey_id +'_percentage_of_teachers_present_value"></td></tr><tr><td colspan="7"><ul class="info"><li class="access"><span class="labelWater">Water:</span>&nbsp;<span id="'+survey_id+'_water_value" class="labelData"></span>&nbsp;<span class="labelElectric">Electricity:</span>&nbsp;<span id="'+ survey_id +'_electricity_value" class="labelData"></span>&nbsp;<span class="labelWindow">Windows:</span>&nbsp;<span id="'+ survey_id +'_windows_value" class="labelData"></span></li></ul></td></tr></tbody></table>';
          jQuery("#survey_table_container").append(html);
          survey_ids.push(survey_id);
        }
        add_data();
      });
      function add_data(){
        if(!survey_ids){
          return;
        }
        survey_ids = survey_ids.reverse();
        for(var x=0; x<survey_ids.length; x++){
            var survey_id = survey_ids[x];
            jQuery.getJSON("/api/v1/surveys/" + survey_id, function(survey_content){
              html = '<a href="/node/' + survey_content["node"]["nid"] + '">'+ survey_content["node"]["title"] +'</a>'
              jQuery("#"+ survey_content["node"]["nid"] +"_survey_title").html(html);
            });

            jQuery.getJSON("/api/v1/schooldetails?school_id=<?php print $school_id; ?>&survey_id=" + survey_id, function(data){
              var water = false;
              var electricity = false;
              var windows = false;
              var academic_year = false;
              var number_of_students = false;
              var number_of_teachers = false;
              var percentage_of_teachers_present = false;
              if(data){
                survey_id = data[data.length-1]["data"];
                for(var i=0; i<data.length; i++){
                  if(data[i].name == 'Does the school have access to clean/drinking water?'){
                    water = true;
                    jQuery("#"+ survey_id +"_water_value").html(data[i].data);
                    if(data[i].data.toLowerCase() == 'yes'){
                      jQuery("#"+ survey_id +"_water_value").removeClass('no');
                      jQuery("#"+ survey_id +"_water_value").addClass('yes');
                    }
                    else {
                      jQuery("#"+ survey_id +"_water_value").removeClass('yes');
                      jQuery("#"+ survey_id +"_water_value").addClass('no');
                    }
                  }

                  if(data[i].name == 'Does this school have access to electricity'){
                    electricity = true;
                    jQuery("#"+ survey_id +"_electricity_value").html(data[i].data);
                    if(data[i].data.toLowerCase() == 'yes'){
                      jQuery("#"+ survey_id +"_electricity_value").removeClass('no');
                      jQuery("#"+ survey_id +"_electricity_value").addClass('yes');
                    }
                    else {
                      jQuery("#"+ survey_id +"_electricity_value").removeClass('yes');
                      jQuery("#"+ survey_id +"_electricity_value").addClass('no');
                    }
                  }

                  if(data[i].name == 'Window condition'){
                    windows = true;
                    jQuery("#"+ survey_id +"_windows_value").html(data[i].data);
                    if(data[i].data.toLowerCase() == 'good'){
                      jQuery("#"+ survey_id +"_windows_value").removeClass('no');
                      jQuery("#"+ survey_id +"_windows_value").addClass('yes');
                    }
                    else {
                      jQuery("#"+ survey_id +"_windows_value").removeClass('yes');
                      jQuery("#"+ survey_id +"_windows_value").addClass('no');
                    }
                  }

                  if(data[i].name == 'Academic Year'){
                    academic_year = true;
                    jQuery("#"+ survey_id +"_academic_year_value").html(data[i].data);
                  }

                  if(data[i].name == 'Number of enrolled students'){
                    number_of_students = true;
                    jQuery("#"+ survey_id +"_number_of_students_value").html(data[i].data);
                  }

                  if(data[i].name == 'Total Number of Teachers'){
                    number_of_teachers = true;
                    jQuery("#"+ survey_id +"_number_of_teachers_value").html(data[i].data);
                  }

                  if(data[i].name == 'Percentage of teachers present'){
                    percentage_of_teachers_present = true;
                    ave = parseFloat((data[i].data * 100).toFixed(2))
                    jQuery("#"+ survey_id +"_percentage_of_teachers_present_value").html(ave + "%");
                  }

                }
              }

              if(!water && !electricity && !windows && !academic_year && !number_of_students && !number_of_teachers && !percentage_of_teachers_present){
                jQuery("."+ survey_id +"_table_item").remove();
              }

              if(!water){
                jQuery("#"+ survey_id +"_water_value").html("Data Unavailable");
                jQuery("#"+ survey_id +"_water_value").removeClass('yes');
                jQuery("#"+ survey_id +"_water_value").removeClass('no');
              }

              if(!electricity){
                jQuery("#"+ survey_id +"_electricity_value").html("Data Unavailable");
                jQuery("#"+ survey_id +"_electricity_value").removeClass('yes');
                jQuery("#"+ survey_id +"_electricity_value").removeClass('no');
              }

              if(!windows){
                jQuery("#"+ survey_id +"_windows_value").html("Data Unavailable");
                jQuery("#"+ survey_id +"_windows_value").removeClass('yes');
                jQuery("#"+ survey_id +"_windows_value").removeClass('no');
              }

              if(!academic_year){
                jQuery("#"+ survey_id +"_academic_year_value").html("-");
              }

              if(!number_of_students){
                jQuery("#"+ survey_id +"_number_of_students_value").html("-");
              }

              if(!number_of_teachers){
                jQuery("#"+ survey_id +"_number_of_teachers_value").html("-");
              }

              if(!percentage_of_teachers_present){
                jQuery("#"+ survey_id +"_percentage_of_teachers_present_value").html("-");
              }


            });
        }
      }
      
		
		// images = jQuery(".file");
		// for( var i=0; i<images.length; i++){
		// 	jQuery(".generalImageSection").append(images[i].find("a").attr("href"));
		// }
    jQuery(".ctools-use-modal-processed").remove();
		html = '<div class="field-content">';
		    jQuery.getJSON("/api/v1/surveyimages?school_id=<?php print $content['field_school_id']['#items'][0]['safe_value'];?>", function(data){
			   image_lists = ""
            for(var i=0; i<data.length; i++){
                image_lists += '<a href="/sites/default/files/webform/'+ data[i]["filename"].replace(" ", "%20") +'?format=simple" rel="lightbox[field_images][<p><a href=&quot;/sites/default/files/webform/'+ data[i]["filename"].replace(" ", "%20") +'&quot;>Download Original</a></p>]" title="" class="">';
				        image_lists += '<img typeof="foaf:Image" src="/sites/default/files/webform/'+ data[i]["filename"].replace(" ", "%20") +'" width="56" height="100"></a> &nbsp;';
            }
        	html += image_lists;
        	add_comment_image();
        });
        
        function add_comment_image(){
        	jQuery(".file").each(function(e){
  				item = jQuery(this).find("a").attr("href");
  				  html += '<a href="'+ item +'?format=simple" rel="lightbox[field_images][<p><a href=&quot;'+ item +'&quot;>Download Original</a></p>]" title="" class="">';
  				  html += '<img typeof="foaf:Image" src="'+ item +'" width="56" height="100"></a> &nbsp;';
          });
          html += '</div>';
          jQuery(".views-field-field-images .field-content").append(html);
          Lightbox.initList();
        }

    }); 

    msg_content = jQuery(".comment_forbidden").html();
    new_msg_content = "Please " + msg_content;
    jQuery(".comment_forbidden").html(new_msg_content);
    
  </script>

  
