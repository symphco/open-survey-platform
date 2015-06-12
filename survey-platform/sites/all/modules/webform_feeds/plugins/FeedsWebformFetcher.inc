<?php

/**
 * @file
 * Class definition of FeedsWebformFetcher.
 */

/**
 * Fetches content from a webform.
 */
class FeedsWebformFetcher extends FeedsFetcher {

 /**
   * Fetch content from a source and return it.
   *
   * @param $source
   *   Feed source as entered by user through sourceForm().
   */
  public function fetch(FeedsSource $source) {
    $results = array();
    $source_config = $source->getConfigFor($this);
    $nid = $source_config['webform'];
    $sid = $source_config['submission'];

    if (!empty($nid) && module_load_include('inc', 'webform', 'includes/webform.submissions')) {
      if (empty($sid)) {
        $results = webform_get_submissions(array('nid' => $nid));
      }
      else {
        $results[] = webform_get_submission($nid, $sid);
      }
    }

    return new FeedsFetcherResult($results);
  }

 /**
   * Source form.
   */
  public function sourceForm($source_config) {
    $config = $this->getConfig();
    $node = node_load($config['webform']);

    $form = array();
    $form['webform'] = array(
      '#type' => 'value',
      '#value' => empty($config['webform']) ? '' : $config['webform'],
    );
    if (!empty($node->title)) {
      $form['webform_info'] = array(
        '#type' => 'markup',
        '#prefix' => '<p>',
        '#markup' => t('Webform submissions will be imported from %webform.', array('%webform' => $node->title )),
        '#suffix' => '</p>',
      );
    }
    $form['submission'] = array(
      '#type' => 'textfield',
      '#title' => t('Webform submission'),
      '#description' => t('Enter the ID of the webform submission to import. Leave empty to import all submissions.'),
      '#default_value' => isset($source_config['submission']) ? $source_config['submission'] : '',
      '#required' => FALSE,
    );

    return $form;
  }

 /**
   * Override parent::sourceFormValidate().
   */
  public function sourceFormValidate(&$values) {
  }

 /**
   * Override parent::configDefaults().
   */
  public function configDefaults() {
    return array(
      'webform' => '',
    );
  }

  /**
   * Override parent::configForm().
   */
  public function configForm(&$form_state) {
    $form = array();
    $available_webforms = _webform_feeds_available_webforms();

    if (empty($available_webforms)) {
      $form['no_webforms'] = array(
        '#title' => t('Webform'),
        '#markup' => '<p>' . t('There are no webforms available.') . '</p>',
      );
    } else {
      $form['webform'] = array(
        '#type' => 'select',
        '#title' => t('Webform'),
        '#description' => t('Choose a webform to be used for the import.'),
        '#options' => $available_webforms,
        '#default_value' => isset($this->config['webform']) ? $this->config['webform'] : '',
        '#required' => TRUE,
      );
    }

    return $form;
  }
}
