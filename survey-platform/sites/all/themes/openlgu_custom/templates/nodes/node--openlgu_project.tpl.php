<?php

/**
 * @file
 * Default theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct URL of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type; for example, "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type; for example, story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode; for example, "full", "teaser".
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined; for example, $node->body becomes $body. When needing to
 * access a field's raw values, developers/themers are strongly encouraged to
 * use these variables. Otherwise they will have to explicitly specify the
 * desired field language; for example, $node->body['en'], thus overriding any
 * language negotiation rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 *
 * @ingroup themeable
 */
?>
  <?php if (!$page): ?>
  	<div class="project teaser <?php if(!(empty($node->field_photo_of_project))) : ?>with-photo<?php endif; ?>">
	  	<?php hide($content['links']);
	  		  hide($content['field_project_id']);
	  		  hide($content['field_agency']);
	  		  hide($content['field_municipality']);
	  		  hide($content['field_general_project_type']);
	  		  hide($content['field_gaa_year']);
	  		  hide($content['field_budget']);
	  		  hide($content['field_project_status']);
	  		  hide($content['field_photo_of_project']); 
	  	?>
	  	<div class="gray-bar">
		  	<p>Mapped Project in Participatory Budgeting</p>
	  	</div>
	  	<?php if(!(empty($node->field_photo_of_project))) : ?>
		  	<div class="photo-of-project">
		  		<?php print render($content['field_photo_of_project']); ?>
		  	</div>
		  <?php endif; ?>
	  	<div class="left">
	  		<h2><?php print $node->field_project_id['und'][0]['value']; echo ": "; print $title; ?></h2>
	  		<h3><?php print render($content['field_agency']); echo ", "; print render($content['field_municipality']); ?></h3>
	  		<h5>Project Type</h5>
	  		<div class="icon"><img src="<?php global $base_path; print $base_path; print $directory; ?>/images/legend-icons/<?php print strtolower($content['field_general_project_type'][0]['#markup']); ?>.jpg" alt="image icon" /></div>
	  		<?php if (!empty($node->field_general_project_type['und'][0]['tid'])) {
	  			$tid = $node->field_general_project_type['und'][0]['tid'];
	  			$term_object = taxonomy_term_load($tid);
	  			print $term_object->field_project_type['und'][0]['value']; 
	  		} ?>
	  	</div>
	  	<div class="right">
		  	<h4><?php print render($content['field_gaa_year']); ?></h4>
		  	<p>Project Year</p>
		  	<h4><?php print render($content['field_budget']); ?></h4>
		  	<p>Allocated Budget</p>
		  	<h4><?php print render($content['field_project_status']); ?></h4>
		  	<p>Project Status</p>
	  	</div>
	  	<div class="bottom">
	  		<?php print render($content); ?>
	  		<a class="link-to-project" href="node/<?php print $nid; ?>">View Project Page</a>
	  	</div>
  	</div>
  <?php else: ?>

			<div style="clear:both"></div>
            <div class="resp-tabs-container">
                
                
                <div>
					<h4><?php print $title; ?></h4>
					<?php 
						$municipality_info = taxonomy_term_load($node->field_municipality_by_psgc['und'][0]['tid']); 
						$region_info = taxonomy_term_load($municipality_info->field_region['und'][0]['tid']);
						$province_info = taxonomy_term_load($municipality_info->field_province['und'][0]['tid']); 
					?>
					<p style="margin-bottom: 15px;"> Project Location &middot; <?php print $municipality_info->field_municipality_name['und'][0]['value']; ?> &middot; <?php print $province_info->name; ?> &middot; <?php print $region_info->name; ?></p>
                     <table class="respons">
  				<tbody>
  				  <tr>
      				<th>Project Year</th>
      				<th>Project ID</th>
      				<th>Implementing Agency</th>
<!--       				<th>Project Type</th> -->
      				<th>Allocated Budget</th>
					 <th>Project Status</th>
    				</tr>
    				<tr>
      					<td class="highlight"><?php print render($content['field_gaa_year']);?></td>
      					<td class="highlight"><?php print render($content['field_project_id']); ?></td>
      					<td><?php print render($content['field_agency']); ?></td>
<!--       					<td><?php print render($content['field_general_project_type']); ?></td> -->
      					<td><?php print render($content['field_budget']); ?></td>
						<td class="status"><?php print $node->field_project_status['und'][0]['value']; ?></td>
    				</tr>
					
					</tbody>
						 </table>
						 
					<?php print views_embed_view('leaflet_map_for_embedding','block',$node->nid); ?>
					<p style="margin-top: 15px;"><strong>Disclaimer:</strong> This map is for data illustration purposes only. The geographical coordinates of GPB projects are an approximation based on the centroid of a municipality. The boundaries, names shown and designations used on this map do not imply official endorsement or acceptance by the Govt. of the Philippines.</p>
					  <?php print render($content['comments']); ?>
											
					</div>
                </div>
				
            </div>
<?php endif; ?>