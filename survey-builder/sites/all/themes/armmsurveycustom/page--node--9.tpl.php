			<!-- contain main informative part of the site -->
			<section id="main">
				<!-- title of content -->
				<header class="title title-alt">
					<div class="row">
						<div class="large-12 columns">
							<h1>CONTACT US</h1>
						</div>
					</div>
				</header>
				<div class="row">
					<div class="large-12 medium-12 columns">
							<?php print $messages; ?>
							<?php print render($tabs); ?>
					</div>
				</div>
				<div class="row">
					<div class="large-6 medium-6 columns">
						<!-- contain the main content of the page -->
						<div id="content">
							<?php if(isset($_GET['sid'])) : ?>
								<?php print render($page['content']); ?>
							<?php else: ?>
								<?php print render($node_content['body']); ?>
							<?php endif; ?>
						</div>
					</div>
					<div class="large-6 medium-6 columns">
						<!-- form contact -->
						<?php print render($node_content['webform']); ?>
					</div>
				</div>
				<div class="row">
					<div class="large-12 medium-12 columns">
						<?php print render($page['below_content']); ?>
					</div>
				</div>
			</section>
