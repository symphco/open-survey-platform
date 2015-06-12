<?php
  define("DRUPAL_ROOT", getcwd());
  require_once DRUPAL_ROOT . "/includes/bootstrap.inc";
  drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
  require_once "includes/password.inc";
  echo user_hash_password("123456");
  die();
  menu_execute_active_handler();
?>