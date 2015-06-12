<?php

$plugin = array(
  'label' => t('Webform Submissions'),
  'handler' => array('class' => 'PgbarSourceWebformSubmissions'),
);

class PgbarSourceWebformSubmissions {
  public function __construct($entity, $field, $instance) {
    $this->entity = $entity;
    $this->field = $field;
    $this->instance = $instance;
  }
  public function getValue($item) {
    $entity = $this->entity;
    $q = db_select('node', 'n');
    $q->addExpression('COUNT(ws.nid)');
    if (module_exists('variations')) {
      $q->leftJoin('variations', 'v', "n.nid=v.entity_id AND v.entity_type='node'");
      $q->leftJoin('variations', 'vn', "v.vid=vn.vid AND v.entity_type='node'");
      $q->innerJoin('webform_submissions', 'ws', 'ws.nid = vn.entity_id OR (vn.entity_id IS NULL AND ws.nid=n.nid)');
    } else {
      $q->innerJoin('webform_submissions', 'ws', 'n.nid=ws.nid');
    }
    $q->where('n.nid=:nid OR ((n.nid=:tnid OR n.tnid=:tnid) AND :tnid>0)', array(':nid' => $entity->nid, ':tnid' => $entity->tnid));
    return $q->execute()->fetchField();
  }
  public function widgetForm($item) {
    return NULL;
  }
}
