			<!-- contain main informative part of the site -->
			<section id="main">
				<!-- title of content -->
				<header class="title">
					<div class="row">
						<div class="large-12 columns">
							<h1><?php print $title; ?></h1>
						</div>
					</div>
				</header>
				<div class="row">
					<div class="<?php if(empty($page['sidebar_second'])) { echo "large-12 medium-12"; } else { echo "large-8 medium-8"; } ?> columns">
						<!-- contain the main content of the page -->
						<div id="content">
							<?php print $messages; ?>
							<?php print render($tabs); ?>
							<?php print render($page['content']); ?>
							<?php print render($page['below_content']); ?>
						</div>
					</div>
					<?php if(!(empty($page['sidebar_second']))) : ?>
						<div class="large-3 medium-4 columns">
								<!-- contain sidebar of the page -->
								<?php print render($page['sidebar_second']); ?>
							</div>
					<?php endif; ?>
				</div>
			</section>
