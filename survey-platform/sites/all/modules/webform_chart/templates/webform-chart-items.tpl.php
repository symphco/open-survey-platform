<?php

/**
 * @file
 * Implementation of a webform chart items template.
 *
 *
 * Available variables:
 *
 * General utility variables:
 * - $user :   The user accessing the page
 * - $classes: The rendered classes form classes_array build from theme 
 * function for this page
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Page content (in the default webform-chart-items.tpl.php):
 * - $raw_items : an array of the none rendered, non-computed items values 
 * such as given by webform module
 * - $items : a render chart array of each item from webform-chart-item.tpl.php 
 *
 * @see template_preprocess_webform_chart_items()
 * @see template_process()
 */
?>

<div class="<?php print $classes ?>">
  <?php foreach ($items as $item) : ?>
    <?php print ($item); ?>
  <?php endforeach; ?>
</div>
