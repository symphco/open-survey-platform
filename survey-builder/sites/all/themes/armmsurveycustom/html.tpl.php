<!DOCTYPE html>
<!--[if IE 9]><html class="lt-ie10" lang="en"><![endif]-->
<html class="no-js" lang="en">
<head>
  <?php print $head; ?>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>
<body class="<?php print $classes; ?>" <?php print $attributes;?>>
	<div class="off-canvas-wrap">
		<div class="inner-wrap">
			<!-- header of the page -->
			<header id="header">
				<div class="row">
					<aside class="left-off-canvas-menu">
						<ul>
							<li><a href="<?php global $base_path; print $base_path; ?>" class="ico ico-home">HOME</a></li>
							<li><a href="<?php global $base_path; print $base_path; ?>about" class="ico ico-about">ABOUT</a></li>
							<li><a href="<?php print $base_path; ?>surveys" class="ico ico-surveys">SURVEYS</a></li>
							<li><a href="<?php print $base_path; ?>faq" class="ico ico-faq">FAQ</a></li>
							<li><a href="<?php print $base_path; ?>contact" class="ico ico-contact">CONTACT</a></li>
						</ul>
						<ul>
							<?php if(!(user_is_logged_in())) : ?>
								<li><a href="<?php print $base_path; ?>user/login" class="ico ico-login">LOGIN</a></li>
							<?php else : ?>
								<li><a href="<?php print $base_path; ?>user/edit" class="ico ico-profile">EDIT PROFILE</a></li>							
								<li><a href="<?php print $base_path; ?>dashboard" class="ico ico-dashboard">DASHBOARD</a></li>
								<li><a href="<?php print $base_path; ?>user/logout" class="ico ico-logout">LOGOUT</a></li>
						
							<?php endif; ?>
						</ul>
					</aside>
					<a class="left-off-canvas-toggle menu-icon show-for-small" href="#"><p class="menu">Menu</p><span class="navicon"></span></a>
					<nav class="hide-for-small">
						<ul class="right">
							<?php if(!(user_is_logged_in())) : ?>
								<li><a href="<?php print $base_path; ?>user/login" class="ico ico-login">LOGIN</a></li>
							<?php else : ?>
								<li><a href="<?php print $base_path; ?>user" class="ico ico-profile">EDIT PROFILE</a></li>							
								<li><a href="<?php print $base_path; ?>dashboard" class="ico ico-dashboard">DASHBOARD</a></li>
								<li><a href="<?php print $base_path; ?>user/logout" class="ico ico-logout">LOGOUT</a></li>
							<?php endif; ?>
						</ul>
						<ul>
							<li><a href="<?php print $base_path; ?>" class="ico ico-home">HOME</a></li>
							<li><a href="<?php print $base_path; ?>about" class="ico ico-about">ABOUT</a></li>
							<li><a href="<?php print $base_path; ?>surveys" class="ico ico-surveys">SURVEYS</a></li>
							<li><a href="<?php print $base_path; ?>faq" class="ico ico-faq">FAQ</a></li>
							<li><a href="<?php print $base_path; ?>contact" class="ico ico-contact">CONTACT</a></li>
						</ul>
					</nav>
				</div>
			</header>

    <?php print $page_top; ?>
    <?php print $page; ?>
    <?php print $page_bottom; ?>
			<!-- footer of the page -->
			<div id="footer">
				<div class="row">
					<div class="large-12 columns">
						<ul class="right">
							<li><a href="<?php print $base_path; ?>">Home</a></li>
							<li><a href="<?php print $base_path; ?>contact">Contact Us</a></li>
							<li><a href="<?php print $base_path; ?>privacy">Privacy Policy</a></li>
							<li><a href="<?php print $base_path; ?>terms-of-use">Terms of Use</a></li>
						</ul>
						<p>© All Rights Reserved.</p>
					</div>
				</div>
			</div>
		</div>
	</div>
	<script src="<?php print $directory; ?>/js/foundation.min.js"></script>
	<!-- include custom JavaScript -->
	<script>jQuery(document).foundation();</script>
</body>
</html>