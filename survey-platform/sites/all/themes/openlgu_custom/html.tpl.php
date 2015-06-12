<?php

/**
 * @file
 * Default theme implementation to display the basic html structure of a single
 * Drupal page.
 *
 * Variables:
 * - $css: An array of CSS files for the current page.
 * - $language: (object) The language the site is being displayed in.
 *   $language->language contains its textual representation.
 *   $language->dir contains the language direction. It will either be 'ltr' or 'rtl'.
 * - $rdf_namespaces: All the RDF namespace prefixes used in the HTML document.
 * - $grddl_profile: A GRDDL profile allowing agents to extract the RDF data.
 * - $head_title: A modified version of the page title, for use in the TITLE
 *   tag.
 * - $head_title_array: (array) An associative array containing the string parts
 *   that were used to generate the $head_title variable, already prepared to be
 *   output as TITLE tag. The key/value pairs may contain one or more of the
 *   following, depending on conditions:
 *   - title: The title of the current page, if any.
 *   - name: The name of the site.
 *   - slogan: The slogan of the site, if any, and if there is no title.
 * - $head: Markup for the HEAD section (including meta tags, keyword tags, and
 *   so on).
 * - $styles: Style tags necessary to import all CSS files for the page.
 * - $scripts: Script tags necessary to load the JavaScript files and settings
 *   for the page.
 * - $page_top: Initial markup from any modules that have altered the
 *   page. This variable should always be output first, before all other dynamic
 *   content.
 * - $page: The rendered page content.
 * - $page_bottom: Final closing markup from any modules that have altered the
 *   page. This variable should always be output last, after all other dynamic
 *   content.
 * - $classes String of classes that can be used to style contextually through
 *   CSS.
 *
 * @see template_preprocess()
 * @see template_preprocess_html()
 * @see template_process()
 *
 * @ingroup themeable
 */
?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML+RDFa 1.0//EN"
  "http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" version="XHTML+RDFa 1.0" dir="<?php print $language->dir; ?>"<?php print $rdf_namespaces; ?>>

<head profile="<?php print $grddl_profile; ?>">
  <?php // print $head; ?>
  <title>Open Data<?php // print $head_title; ?></title>
  
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta name="description" content="">
    <meta name="author" content="">
<meta property="og:type" content="website" />
<meta property="og:title" content="ARMM OPEN DATA PLATFORM FOR EDUCATION" />
<meta property="og:image" content="http://opened.urls.ph/sites/all/themes/openlgu_custom/images/og-share-image.JPG" />
<meta property="og:description" content="The ARMM government is committed to disclosing the exact geographic location of every school in the region, and taking stock of basic infrastructure conditions and presence of teachers and students." />

    <!-- HTML5 shim, for IE6-8 support of HTML5 elements -->
    <!--[if lt IE 9]>
      <script src="http://html5shim.googlecode.com/svn/trunk/html5.js"></script>
    <![endif]-->
	
	<link href='http://fonts.googleapis.com/css?family=Roboto:400,100,100italic,300italic,300,400italic,500,500italic,700,700italic,900,900italic' rel='stylesheet' type='text/css'>
	<link href='http://fonts.googleapis.com/css?family=Roboto+Condensed:400,300,300italic,400italic,700,700italic' rel='stylesheet' type='text/css'>

  <!-- Leaflet -->
  <link rel="stylesheet" href="http://cdn.leafletjs.com/leaflet-0.7.2/leaflet.css" />
  <script src="http://cdn.leafletjs.com/leaflet-0.7.2/leaflet.js"></script>
  <link rel="stylesheet" href="/sites/all/themes/openlgu_custom/css/template.css" />

  <?php print $styles; ?>

  <?php print $scripts; ?>
  
  <!-- HighCharts -->
  <script src="http://code.highcharts.com/highcharts.js"></script>
  <script src="http://code.highcharts.com/modules/exporting.js"></script>
  
	<script type="text/javascript">
			jQuery(document).ready(function() {
				jQuery('#featured').orbit({bullets: true});
				jQuery('#featured2').orbit({bullets: true});
				jQuery('#responsive').orbit({bullets: true, fluid: true});
			});
		</script>

</head>
<body class="<?php print $classes; ?>" <?php print $attributes;?>>
    <div class="navbar navbar-inverse navbar-fixed-top">
      <div class="navbar-inner">
        <div class="container">
		
          <a class="btn btn-navbar" data-toggle="collapse" data-target=".nav-collapse">
		    <p class="menu_link">Menu</p>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
          </a>
          <a class="brand" href="<?php global $base_path; print $base_path; ?>"><img src="<?php print $base_path; ?><?php print $directory; ?>/images/logo_top.png" alt=""></a>
          <div class="nav-collapse collapse">
			 <?php 
			 $main_menu = menu_navigation_links('main-menu');
			 print theme('links__system_main_menu', array(
			 'links' => $main_menu,
			 'attributes' => array(
			 'id' => 'main-menu',
			 'class' => array('nav', 'clearfix'),
			 ),
			 'heading' => array(
			 'text' => t('Main menu'),
			 'level' => 'h2',
			 'class' => array('element-invisible'),
			 ),)); ?>
			<div class="search_box">
			<?php
				  $block = module_invoke('search_api_page', 'block_view', 'pages_search');
				  print render($block['content']);
			  ?>
			</div>
          </div><!--/.nav-collapse -->
        </div>
      </div>
    </div>
	
	<div class="main_header">
	  
	  <div class="container">
	   <div class="row-fluid">
        <div class="span10"><a href="<?php print $base_path; ?>" class="logo"><img src="<?php print $base_path; ?><?php print $directory; ?>/images/openEd-logo.png" alt=""></a></div>
		<div class="span2">
		 <?php if($logged_in) : ?>
		 	<div class="login logout"><a href="<?php print $base_path; ?>user/logout" class="login-link">LOGOUT</a></div>
		 <?php else: ?>
		 	<div class="login">
		 		<a href="<?php print $base_path; ?>user/login" class="login-link">LOGIN</a>
		 		<p>No account yet?</p>
		 		<p><a href="<?php print $base_path; ?>user/register">Sign up here!</a></p>
		 	</div>
		 <?php endif; ?>
		</div>
	  </div>	
	  
	  </div>
	
	</div>
	
	
	
  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $page_bottom; ?>
</body>
</html>
