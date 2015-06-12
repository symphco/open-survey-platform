<?php
/**
 * @file
 * Default template for progressbars.
 */

$vars['!current'] = '<strong>' . number_format($current, 0) . '</strong>';
$vars['!current-animated'] = '<strong class="pgbar-counter">' . number_format($current, 0) . '</strong>';
$vars['!target'] = '<strong>' . number_format($target, 0) . '</strong>';
$vars['!needed'] = number_format($target - $current, 0);

$intro_message  = t($goal_reached ? $texts['full_intro_message']  : $texts['intro_message'], $vars);
$status_message = t($goal_reached ? $texts['full_status_message'] : $texts['status_message'], $vars) . "\n";
?>
<div class="pgbar-wrapper" data-pgbar-current="<?php print $current; ?>" data-pgbar-target="<?php print $target; ?>">
  <p><?php print $intro_message; ?></p>
  <div class="pgbar-bg"><div class="pgbar-current" style="width:<?php echo $percentage; ?>%"></div></div>
  <div class="pgbar-percent"><?php print number_format($percentage, 2) . '%'; ?></div>
	<p><?php print $status_message; ?></p> 
</div>
