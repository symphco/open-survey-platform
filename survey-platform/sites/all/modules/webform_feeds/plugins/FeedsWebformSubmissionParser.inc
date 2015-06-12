<?php

/**
 * Parses a given webform submission.
 */
class FeedsWebformSubmissionParser extends FeedsParser {

  /**
   * Implements FeedsParser::parse().
   */
  public function parse(FeedsSource $source, FeedsFetcherResult $fetcher_result) {
    $source_config = $source->getConfigFor($this);
    $result = new FeedsParserResult();

    // Get component info.
    $importer = feeds_importer($this->id);
    $node = node_load($importer->config['fetcher']['config']['webform']);
    $components = _webform_feeds_webform_components($node);

    // Iterate through the fetcher results.
    foreach ($fetcher_result->getRaw() as $index => $submission) {
      $row = array();
      foreach ($submission->data as $cid => $field) {
        $component_key = $components[$cid]['form_key'];
        // TODO: Change this to accommodate multiple values.
        $row[$component_key] = $field['value'][0];
      }

      // Add meta fields.
      $meta_fields = _webform_feeds_meta_fields();
      foreach ($meta_fields as $meta_index => $meta_field) {
         $row['meta_' . $meta_index] = $submission->$meta_index;
      }

      $result->items[$index] = $row;
    }

    return $result;
  }

  /**
   * Override parent::getMappingSources().
   */
  public function getMappingSources() {
    $config = $this->getConfig();
    $importer = feeds_importer($this->id);
    $fetcher_config = $importer->config['fetcher'];
    $sources = array();

    if ($fetcher_config['plugin_key'] == 'FeedsWebformFetcher' && isset($fetcher_config['config']['webform'])) {
      $node = node_load($fetcher_config['config']['webform']);
      $components = _webform_feeds_webform_components($node);

      if ($components) {  
        // Create mapping sources.
        foreach ($components as $component) {
          $sources[$component['form_key']] = array(
            'name' => $component['form_key'],
            'description' => $component['name'],
          );
        }
  
        // Add meta fields.
        $meta_fields = _webform_feeds_meta_fields();
        foreach ($meta_fields as $meta_index => $meta_field) {
          $sources['meta_' . $meta_index] = array(
            'name' => 'meta_' . $meta_index,
            'description' => 'meta_' . $meta_index,
          );
        }
      }
    }

    if (!empty($sources)) {
      return $sources;
    }
    else {
      return parent::getMappingSources();
    }
  }

  /**
   * Define defaults.
   */
  public function sourceDefaults() {
    return array();
  }

  /**
   * Source form.
   */
  public function sourceForm($source_config) {
    $form = array();
    return $form;
  }

  /**
   * Define default configuration.
   */
  public function configDefaults() {
    return array();
  }

  /**
   * Build configuration form.
   */
  public function configForm(&$form_state) {
    $form = array();
    return $form;
  }

}
