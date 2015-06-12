<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php $i = 0; ?>
<?php foreach ($rows as $id => $row): ?>
  <div class="span12" <?php if ($i == 0) { echo "style='margin-left:0px'"; } ?>>
  	<div class="post">
    	<?php print $row; $i++;?>
  	</div>
  </div>
<?php endforeach; ?>
