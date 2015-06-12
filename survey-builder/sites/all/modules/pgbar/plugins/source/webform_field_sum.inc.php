<?php

$plugin = array(
  'label' => t('Webform - Sum of a field'),
  'handler' => array('class' => 'PgbarSourceWebformSum'),
);

class PgbarSourceWebformSum {
  public function __construct($entity, $instance) {
    $this->entity = $entity;
    $this->instance = $instance;
  }
  public function getValue($item) {
    $entity = $this->entity;
    $q = db_select('node', 'n');
    $q->addExpression('SUM(wsd.data)');
    if (module_exists('variations')) {
      $q->leftJoin('variations', 'v', "n.nid=v.entity_id AND v.entity_type='node'");
      $q->leftJoin('variations', 'vn', "v.vid=vn.vid AND v.entity_type='node'");
      $q->innerJoin('webform_component', 'wc', 'wc.nid = vn.entity_id OR (vn.entity_id IS NULL AND wc.nid=n.nid)');
    } else {
      $q->innerJoin('webform_component', 'wc', 'n.nid=wc.nid');
    }
    $q->innerJoin('webform_submitted_data', 'wsd', 'wsd.nid=wc.nid AND wc.cid=wsd.cid')
      ->where(
        '(n.nid=:nid OR ((n.nid=:tnid OR n.tnid=:tnid) AND :tnid>0)) AND wc.form_key=:fkey',
         array(':nid' => $entity->nid, ':tnid' => $entity->tnid, ':fkey' => $item['options']['source']['form_key'])
      );
    return $q->execute()->fetchField();
  }
  public function widgetForm($item) {
    $source_options = isset($item['options']['source']) ? $item['options']['source'] : array();
    $source_options += array('form_key' => '');
    $form['form_key'] = array(
      '#type' => 'textfield',
      '#title' => t('Form key'),
      '#desription' => t('All values with this form key are summed up to get the current value for the progress bar.'),
      '#default_value' => $source_options['form_key'],
    );
    return $form;
  }
}
