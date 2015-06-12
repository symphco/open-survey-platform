<?php 

/**
 * @file
 * Implementation webform chart page template.
 *
 * Available variables:
 *
 * General utility variables:
 * - $node :   The node these charts are attached to
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
 * Page content (in the default webform-chart-page.tpl.php):
 * - $charting : the rendered items from webform-chart-items.tpl.php
 *
 * @see template_preprocess_webform_chart_page()
 * @see template_process()
 */
?>

<?php if (isset($charting) && $charting) :?>
  <?php if ($page_title || $node->title) :?>
    <div id="<?php print $classes ?>-title-block">
      <?php if ($page_title) : ?>
        <h1 class="page-title" id="<?php print $classes ?>-title"><?php print $page_title ?></h1>
      <?php endif; ?>

      <?php if($node->title) : ?>
        <div class="subtitle" id="<?php print $classes ?>-subtitle"><?php print check_plain($node->title) ?></div>
      <?php endif; ?>
      <span class="separator"></span>
    </div>
    
    <div class="<?php print $classes ?>">
      <?php print $charting; ?>
    </div>
  <?php endif; ?>
<?php endif; ?>
