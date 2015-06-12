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
		<div id="data-sb" class="span3">
			  <h3>Refine by</h3>

			  		<?php print render($page['sidebar_filter']); ?>

           </div>
         
         
        <div class="span9">
			
			<!--Horizontal Tab-->
		   		<?php print $messages; ?>
		        <a id="main-content"></a>
<!--
	            <ul class="resp-tabs-list tabs primary">
	                <li><a href="<?php print $base_path; ?>projects-overview">Overview</a></li>
	                <li class="active"><a href="<?php print $base_path; ?>projects">GPB Projects</a></li>
	                <li><a href="<?php print $base_path; ?>map">Map</a></li>
	                <li><a href="<?php print $base_path; ?>dashboard">Dashboard</a></li>
	            </ul>
	            <div style="clear:both"></div>
-->
		        <?php print render($page['help']); ?>
		        <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
		        <div class="resp-tabs-container">
		        <?php // print render($page['content']); ?>
		        <?php print $feed_icons; ?>

					
                <div>
					<div class="span12">
						<h4>School Survey Results</h3>
						<form id="views-exposed-form-projects-search-results-page" accept-charset="UTF-8"><div><div class="views-exposed-form">
						  <div class="views-exposed-widgets clearfix">
						          <div id="edit-search-api-views-fulltext-wrapper" class="views-exposed-widget views-widget-filter-search_api_views_fulltext">
						                  <label for="edit-search-api-views-fulltext">
						            Fulltext Search          </label>
						                        <div class="views-widget">
						          <div class="form-item form-type-textfield form-item-search-api-views-fulltext">
						 <input type="text" id="edit-search-api-views-fulltext" value=" Search by School ID or School Name" size="30" maxlength="128" class="form-text" />
						</div>
						        </div>
						              </div>
						                    <div class="views-exposed-widget views-submit-button">
						      <input type="submit" id="edit-submit-projects-search-results" name="" value="Search" class="form-submit" />    </div>
						      </div>
						</div>
						</div></form>					  						  	
						<div id="header-items-per-page">
						  	<p><span>Display:</span>
							  	<select name="display-how-many">
							  		<option value="10" <?php if(isset($_GET['items_per_page']) && $_GET['items_per_page'] == 10) { echo "selected"; } ?>>10 at a time</option>
							  		<option value="20" <?php if(isset($_GET['items_per_page']) && $_GET['items_per_page'] == 20) { echo "selected"; } ?><?php if (!(isset($_GET['items_per_page']))) { echo "selected"; } ?>>20 at a time</option>
							  		<option value="50" <?php if(isset($_GET['items_per_page']) && $_GET['items_per_page'] == 50) { echo "selected"; } ?>>50 at a time</option>
							  		<option value="100" <?php if(isset($_GET['items_per_page']) && $_GET['items_per_page'] == 100) { echo "selected"; } ?>>100 at a time</option>
							  	</select>
						  	</p>
					  	</div>
					  	<p id="noResultTxt"></p>
					  	<?php print views_embed_view('schools','page_1'); ?>
					</div>
				</div>                
			</div>
		 </div>
		
		
		 
	  </div>
	</div>
	
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


    <script type="text/javascript">
    	rows = jQuery(".table_row");
    	if(rows.length == 0){
    		jQuery("#noResultTxt").html("No results for your search.");
    	}
    </script>

