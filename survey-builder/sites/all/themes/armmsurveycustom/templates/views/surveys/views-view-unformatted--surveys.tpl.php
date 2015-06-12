				<div class="surveys">
					<header class="title">
						<div class="row">
							<div class="large-12 columns">
								<h1>Surveys</h1>
							</div>
						</div>
					</header>
					<div class="row">
						<div class="grid-row">
							<?php foreach ($rows as $id => $row) : ?>
								<?php print $row; ?>
							<?php endforeach; ?>
						</div>
					</div>
					<div class="row">
						<div class="large-12 columns">
							<a href="<?php global $base_url; print $base_url; ?>/surveys" class="btn-more">View All SURVEYS</a>
						</div>
					</div>
				</div>
