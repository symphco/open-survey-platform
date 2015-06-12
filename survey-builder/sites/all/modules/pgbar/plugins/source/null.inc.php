
<?php

$plugin = array(
  'label' => t('Manual count'),
  'handler' => array('class' => 'PgbarSourceNull'),
);

class PgbarSourceNull {
  public function __construct($entity, $field, $instance) {
  }
  public function getValue($item) {
    return 0;
  }
  public function widgetForm($item) {
    return NULL;
  }
}
