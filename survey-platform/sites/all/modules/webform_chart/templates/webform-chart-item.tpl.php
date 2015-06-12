<?php

/**
 * @file
 * Implementation of a single webform chart item template.
 *
 *
 * Available variables:
 *
 * General utility variables:
 * - $user :   The user accessing the page
 * - $classes: The rendered classes form classes_array build from theme 
 * function for this page
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Page content (in the default webform-chart-item.tpl.php):
 * - $raw_item : an array of the none rendered, non-computed item values such 
 * as given by webform module
 * - $raw_item['row_data']  : the raw data of this component such as computed
 * by webform module for analysis page
 * - $raw_item['component_data'] : the raw data of this component. Contains all
 * values and data.
 * - $item : the computed (by webform chart module) non-rendered values of this
 * item.
 *   - $item['#chart_id'] : the item chart ID
 *   - $item['#title'] : the item chart title
 *   - $item['#description'] : the item chart description
 *   - $item['#component'] : 
 *   - $item['#data'] : An array of the results data, rendered as key/value
 * where key is the value label
 *   - $item['#labels'] : An array of the results label
 *   - $item['#total_responses'] : The total number of response for this item
 * - $rendered_item : the rendered chart display (such as rendered by the 
 * selected charting backend).
 *
 * @see template_preprocess_webform_chart_item()
 * @see template_process()
 */
?>

<div class="<?php print $classes ?>">
  
  <?php if($item['#title']) : ?>
    <h3><?php print $item['#title'] ?></h3>
  <?php endif; ?>

  <?php if($item['#description']) : ?>
    <div class="description"><?php print $item['#description'] ?></div>
  <?php endif; ?>

  <?php if($rendered_item) : ?>
    <?php print $rendered_item ?>
  <?php endif; ?>
  
  <div class="webform-chart-total-responses" id="webform-chart-responses-<?php print check_plain($item['#chart_id']); ?>">
    <?php print (t('Number of responses: @total_responses', array('@total_responses' => $item['#total_responses']))); ?>
  </div>
        
</div>
