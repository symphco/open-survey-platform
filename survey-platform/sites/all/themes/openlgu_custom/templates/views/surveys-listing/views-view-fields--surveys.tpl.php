	<div class="row-wrapper" style="cursor:pointer" onclick="window.location='http://'+window.location.host+'<?php print $fields['path']->content; ?>'">
		<?php foreach ($fields as $id => $field): ?>
		  <?php if (!empty($field->separator)): ?>
		    <?php print $field->separator; ?>
		  <?php endif; ?>
		
		  <?php print $field->wrapper_prefix; ?>
		    <?php print $field->label_html; ?>
			<?php print $field->content; ?>
		  <?php print $field->wrapper_suffix; ?>
		<?php endforeach; ?>
	</div>
