<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<?php $i = 1; ?>
<?php foreach ($rows as $id => $row): ?>
  <div class="orbit-caption" id="htmlCaption<?php echo $i; ?>">
    <?php print $row; ?>
  </div>
  <?php $i++; ?>
<?php endforeach; ?>
