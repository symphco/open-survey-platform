<?php

/**
 * @file
 * Template to display a view as a table.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $header: An array of header labels keyed by field id.
 * - $caption: The caption for this table. May be empty.
 * - $header_classes: An array of header classes keyed by field id.
 * - $fields: An array of CSS IDs to use for each field id.
 * - $classes: A class or classes to apply to the table, based on settings.
 * - $row_classes: An array of classes to apply to each row, indexed by row
 *   number. This matches the index in $rows.
 * - $rows: An array of row items. Each row is an array of content.
 *   $rows are keyed by row number, fields within rows are keyed by field ID.
 * - $field_classes: An array of classes to apply to each field, indexed by
 *   field id, then row number. This matches the index in $rows.
 * @ingroup views_templates
 */
?>

<div class="surveyContainer">
	<h3 class="sectionHeading">LIST OF SURVEYS</h3>
	<table class="survey_table">
		<thead>
			<tr>
				<th class="surid">survey id</th>
				<th class="surdate">survey date</th>
				<th class="surname">survey name</th>
				<th class="sursubmissions">survey submissions</th>
			</tr>
		</thead>
		<tbody>
			<?php foreach ($rows as $row_count => $row): ?>
				<tr>
					<td class="surid"><?php print $row["nid"]; ?></td>
					<td class="surdate"><?php print $row["created"]; ?></td>
					<td class="surname"><a href="/node["nid"]"><?php print $row["title"]; ?></a></td>
					<td class="sursubmissions"><?php print $row["webform_submission_count_node"]; ?></td>
				</tr>
			<?php endforeach; ?>
			
				

		</tbody>
	</table>
</div><!-- surveyContainer -->