<?php

function armmsurveycustom_preprocess_page(&$variables) {
  // Allows us to render $content in page.tpl.php pages instead of just node.tpl.php
  $nid = arg(1);
  if (arg(0) == 'node' && is_numeric($nid)) {
    if (isset($variables['page']['content']['system_main']['nodes'][$nid])) {
      $variables['node_content'] = & $variables['page']['content']['system_main']['nodes'][$nid];
    }
  }
}

?>
  
