	<div class="main_content">
	 <div class="container">
		  <div class="social">
		  	<a><img src="http://localhost/wb-opengov-armmdata/sites/all/themes/openlgu_custom/images/service-links/facebook.png"></a>
		  	<a><img src="http://localhost/wb-opengov-armmdata/sites/all/themes/openlgu_custom/images/service-links/twitter.png"></a>
		  	<a><img src="http://localhost/wb-opengov-armmdata/sites/all/themes/openlgu_custom/images/service-links/forward.png"></a>

		  </div>
		 <div class="row-fluid content">
		 
		 <?php if($node->nid == "page-user") {
		 	echo '<div class="span11">';
		 	}
		 	else if($node->nid == "25856") {
			 	echo '<div class="span9">';
		 	}
		 	else { ?>
		 
		   <div class="span12">
		   
		    <?php } ?>
		   		<?php print $messages; ?>
		        <a id="main-content"></a>
		        <?php // Print the Slideshow if it's node 10 
		        	if(false) { print views_embed_view('about_page_slideshow','block'); } 
		        ?>
		
                        <?php if($node->type != 'school_profile'): ?>
                        <?php print render($title_prefix); ?>
		        <?php if ($title): ?><h1 class="title" id="page-title"><?php print $title; ?></h1><?php endif; ?>
		        <?php print render($title_suffix); ?>
                        <?php endif; ?>
	        
                        <?php if ($tabs): ?><div class="tabs"><?php print render($tabs); ?></div><?php endif; ?>
		        <div style="clear:both"></div>
		        <?php print render($page['help']); ?>
<!-- 		        <?php if ($action_links): ?><ul class="action-links"><?php // print render($action_links); ?></ul><?php endif; ?> -->

				<div class="surveyContainer">
			        <?php print render($page['content']); ?>
			    </div><!-- surveyContainer -->

			    
		        <?php print $feed_icons; ?>
           </div>
         
		   <div class="span1"></div>
			         
		   <?php print render($page['sidebar_first']); ?>
		   
		  
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





