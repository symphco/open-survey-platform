<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php global $base_path; foreach ($rows as $id => $row): ?>
  <div class="recently">
	  <h2><img src="<?php print $base_path; ?><?php print $directory; ?>/images/ico_news-2.jpg" class="news-ico"> Featured News</h2>
	  <?php print $row;?>
  </div>
<?php endforeach; ?>
