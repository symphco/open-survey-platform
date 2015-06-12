			<!-- preview block -->
			<section class="preview-block">
				<div class="row">
					<div class="large-12 columns">
						<div class="img">
							<img data-interchange="[<?php print $directory; ?>/img/img01.png, (default)], [<?php print $directory; ?>/img/img01-2x.png, (only screen and ( -webkit-min-device-pixel-ratio : 1.5 ), (min-resolution: 144dpi))]">
							<noscript><img src="<?php print $directory; ?>/img/img01.png" width="234" height="234" alt="image descritpion" /></noscript>
						</div>
						<div class="txt">
							<?php print render($page['content']); ?>
						</div>
					</div>
				</div>
			</section>
			<!-- contain main informative part of the site -->
			<section id="main">
				<div class="row">
					<div class="large-12 columns">
						<form method="post" accept-charset="UTF-8" action="#" style="display:none;">
							<div>
								<div class="form-item">
									<label for="edit-name">Username: <span title="This field is required." class="form-required">*</span></label>
									<input id="edit-name" type="text" class="form-text required" value="" size="15" name="name" maxlength="60"/>
								</div>
								<div class="form-item">
									<label for="edit-pass">Password: <span title="This field is required." class="form-required">*</span></label>
									<input id="edit-pass" type="password" class="form-text required" size="15" maxlength="60" name="pass"/>
								</div>
								<input type="submit" class="form-submit" value="Log in" name="op"/>
								<div class="item-list">
									<ul>
										<li><a title="Create a new user account." href="#">Create new account</a></li>
										<li><a title="Request new password via e-mail." href="#">Request new password</a></li>
									</ul>
								</div>
							</div>
						</form>
						<form method="post" accept-charset="UTF-8" action="#" style="display:none;">
							<div>
								<div class="container-inline" >
									<div class="form-item">
										<label for="edit-search-theme-form-1">Search this site: </label>
										<input id="edit-search-theme-form-1" type="text" class="form-text" title="Enter the terms you wish to search for." value="" size="15" name="search_theme_form" maxlength="128"/>
									</div>
									<input type="submit" class="form-submit" value="Search" />
								</div>
							</div>
						</form>
					</div>
				</div>
				<?php print render($page['below_content']); ?>
			</section>
