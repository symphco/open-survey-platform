<?php

/**
 * @file
 * Provides result page functions for the webform_chart module
 */


/**
 * Provides graphical analysis of all submissions to a webform. 
 *
 * By adding checks for 'grid' and 'table_element' - type components that 
 * have either insufficent analysis formatting or no analysis callbacks at 
 * all, we can shoe-horn in our own analysis formatting functions by switching
 * the callback from 'analysis' to 'chart_analysis'. Return handling needed to
 * be modified for these elements as well since these functions return arrays 
 * of questions/answers, not single questions/answers.
 *
 * This also differs from the webform core results formatter by sending 
 * forward the component along with the analysis data to the theme function
 * in the main data array. This provides additional functionality down stream
 * in the theme functions.
 *
 * @param String $node
 *   The webform node on which to generate the analysis.
 * @param array $sids
 *   An array of submission IDs to which this analysis may be
 * filtered. May be  used to generate results that are per-user or other 
 * groups of submissions.
 * @param String $analysis_component 
 *   A webform component. If passed in, additional information may be returned
 * relating specifically to that component's analysis, such as a list of
 *  "Other" values within a select list.
 */
function webform_chart_page($node, $sids = array(), $analysis_component = NULL) {

  // Helps to sanityze the $sids when one was given manually in the URL
  // (it should not).
  if (!is_array($sids)) {
    $sids = array();
  }

  // Helps to sanityze the $analysis_component when one was given manually in
  // the URL (it should not).
  // If showing a component's details, we don't want to loose the menu tabs.
  if ($analysis_component) {
    $item = menu_get_item('node/' . $node->nid . '/webform-results/chart');
    menu_set_item(NULL, $item);
  }

  // Retrieve the components list: either the customer component to analyse
  // or the list of all components from the webform.
  $components = isset($analysis_component) ? array($analysis_component['cid'] => $analysis_component) : $node->webform['components'];

  $data = array();
  foreach ($components as $cid => $component) {

    // Get the component type.
    $type = $component['type'];

    // Get the callback to use, depending on the component.
    $callback = _webform_chart_webform_callback($type);

    // Do component specific call.
    if ($type == 'table_element' || $callback == 'analysis_data') {
      $component['components'] = $components;
    }

    // Invoke the component analysis callback:
    // -   _webform_chart_analysis_grid, for grid component,
    // callback defined in this module.
    // -   _webform_chart_analysis_table_element, for table component,
    // callback in this module.
    // (from http://drupal.org/project/webform_table_element)
    // -   _webform_analysis_*type*, for all other components,
    // callback defined in webform.
    $row_data = webform_component_invoke($type, $callback, $component, $sids, isset($analysis_component));
    if ($row_data) {
      // Case of grid: build the result.
      if ($type == 'grid') {
        foreach ($row_data['question_set'] as $key => $qa_set) {
          $data[$key] = array(
            'row_data' => $row_data['answer_set'][$key],
            'component_data' => $qa_set,
          );
        }
      }
      // Case of grid: build the result.
      elseif ($type == 'table_element') {
        foreach ($row_data['question_set'] as $key => $qa_set) {
          $data[$key] = array(
            'row_data' => $row_data['answer_set'][$key],
            'component_data' => $qa_set,
          );
        }
      }
      // Case of all other: build the result.
      else {
        $data[$cid] = array(
          'row_data' => $row_data,
          'component_data' => $component,
        );
      }
    }
  }

  // Return the rendered chart page.
  return theme('webform_chart_page', array(
    'node' => $node,
    'data' => $data,
    'sids' => $sids,
    'component' => $analysis_component,
  ));
}

/*
 * -----------------------------------------------------------------------
 * HELPER FUNCTIONS.
 *------------------------------------------------------------------------
 */

/**
 * Returns the webform_analysis_ callback to use for a given component type.
 *
 *  - _webform_chart_analysis_grid            for grid component, callback 
 *                                            defined in this module.
 *  - _webform_chart_analysis_table_element   for table component, callback
 *                                            defined in this module.
 *      (from http://drupal.org/project/webform_table_element)
 *  - _webform_analysis_*type*                for all other components,
 *                                            callback defined in webform.
 *
 * @param String $type
 *   The type of component, for example grid, select, textarea
 *
 * @return string
 *   The callback function to be called
 */
function _webform_chart_webform_callback($type) {

  if ($type == 'table_element' || $type == 'grid') {
    return 'chart_analysis';
  }
  else {
    return 'analysis';
  }
}

/**
 * Provides escaping for JavaScript.
 *
 * This will not encode entities for 
 * ampersands and greater-thans. First, the string is run through check_plain,
 * then it is unescaped. It also has provisions for new-line characters as 
 * these will break JavaScript.
 *
 * @param String $text
 *   The text to be safely escaped for JavaScript.
 *
 * @return string
 *   The processed string.
 */
function _webform_chart_js_plain($text) {
  $text = str_replace('&amp;', '&', $text);
  $text = str_replace('&gt;', '>', $text);
  $text = str_replace("\n", ' ', $text);
  $text = str_replace("\r", ' ', $text);
  $text = check_plain($text);
  $text = str_replace('&amp;', '&', $text);
  $text = str_replace('&gt;', '>', $text);
  return $text;
}

/*
 * --------------------------------------------------------------------------
 * WEBFORM ANALYSIS COMPONENT FUNCTIONS.
 * --------------------------------------------------------------------------
 */

/**
 * Implements _webform_analysis_component(). 
 *
 * This is shoe-horned in below in 
 * webform_chart_page, and is necessary because the core grid analysis 
 * component returns a rendered HTML table, not data, so it is useless for
 * charting. This formats the grid components as separate question/answer sets
 * which are added to the main set of questions below.
 *
 * @param array $component
 *   The grid component to be parsed for analysis.
 * @param array $sids
 *   An array of submission ID's to optionally filter the results by.
 *
 * @return array
 *   An array of questions and answers that are added to the primary $data
 * array in webform_chart_page below.
 */
function _webform_chart_analysis_grid($component, $sids = array()) {

  // Generate the list of options and questions.
  $options = _webform_select_options_from_text($component['extra']['options'], TRUE);
  $questions = _webform_select_options_from_text($component['extra']['questions'], TRUE);
  $cid = $component['cid'];
  $form_key = $component['form_key'];
  // Generate a lookup table of results.
  $query = db_select('webform_submitted_data', 'wsd')
    ->fields('wsd', array('no', 'data'))
    ->condition('nid', $component['nid'])
    ->condition('cid', $component['cid'])
    ->condition('data', '', '<>')
    ->groupBy('no')
    ->groupBy('data');
  $query->addExpression('COUNT(sid)', 'datacount');

  if (count($sids)) {
    $query->condition('sid', $sids, 'IN');
  }

  $result = $query->execute();
  $counts = array();

  foreach ($result as $data) {
    $counts[$data->no][$data->data] = $data->datacount;
  }

  // Create an entire table to be put into the returned row.
  $answer_set = array();
  $question_set = array();
  // Add questions as each row.
  foreach ($questions as $qkey => $question) {
    $answers = array();
    $question_set[$cid . '_' . $qkey] = $component;
    $question_set[$cid . '_' . $qkey]['name'] = $question;
    $question_set[$cid . '_' . $qkey]['type'] = 'grid_component';
    $question_set[$cid . '_' . $qkey]['form_key'] = $form_key . '_' . $qkey;
    foreach ($options as $okey => $option) {
      $answers[] = array(_webform_filter_xss($option), !empty($counts[$qkey][$okey]) ? $counts[$qkey][$okey] : 0);
    }
    $answer_set[$cid . '_' . $qkey] = $answers;
  }

  return array('question_set' => $question_set, 'answer_set' => $answer_set);
}

/**
 * Implements _webform_analysis_component(). 
 *
 * Since the webform_table_element plugin does not currently offer any
 * reporting at all, it is at least 
 * implemented here. This takes the component argument, which is passed in as
 * an array of all current webform components ($component['components']) as 
 * well as the table element ($component['component']), finds all components
 * that have a parent ID of the table element component, and adds them to an 
 * array of questions similar to the grid component above.  This is shoe-horned
 * in below in webform_chart_page.
 *
 * @param array $component
 *   The table element ($component['component']) and all components 
 * ($component['components']) to be parsed for analysis.
 * @param array $sids
 *   An array of submission ID's to optionally filter the results by.
 *
 * @return array
 *   An array of questions and answers that are added to the primary 
 * $data array in webform_chart_page below.
 */
function _webform_chart_analysis_table_element($component, $sids = array()) {
  $components = $component['components'];
  $questions = _webform_select_options_from_text($component['extra']['rows'], TRUE);
  $answers = array();
  $answer_set = array();
  $labels = array();
  $options = array();
  $results = array();
  foreach ($components as $item) {
    if ($item['pid'] == $component['cid']) {
      $answers[] = $item;
      $labels[$item['cid']] = $item['name'];
      $options[$item['cid']] = _webform_select_options_from_text($item['extra']['items'], TRUE);
    }
  }
  foreach ($answers as $answer) {
    // Generate a lookup table of results.
    $query = db_select('webform_submitted_data', 'wsd')
      ->fields('wsd', array('data', 'cid'))
      ->condition('nid', $answer['nid'])
      ->condition('cid', $answer['cid'])
      ->condition('data', '', '<>');

    if (count($sids)) {
      $query->condition('sid', $sids, 'IN');
    }
    $result = $query->execute();
    foreach ($result as $data) {
      $results[$data->cid][] = unserialize($data->data);
    }
  }
  foreach ($results as $cid => $result) {
    foreach ($result as $responses) {
      foreach ($responses as $q_key => $response) {
        $arr_key = $q_key < 10 ? '0' . $q_key : $q_key;
        if (!array_key_exists($cid . $arr_key, $answer_set)) {
          $answer_set[$cid . $arr_key] = array();
          foreach ($options[$cid] as $option) {
            $answer_set[$cid . $arr_key][] = array(
              0 => $option,
              1 => 0,
            );
          }
        }
        foreach ($answer_set[$cid . $arr_key] as $k => $ans_set) {
          if ($ans_set[0] == $response) {
            $answer_set[$cid . $arr_key][$k][1]++;
          }
        }
      }
    }
  }

  foreach ($questions as $q_key => $question) {
    foreach ($labels as $cid => $label) {
      $arr_key = $q_key < 10 ? '0' . $q_key : $q_key;
      $question_set[$cid . $arr_key] = array(
        'name' => t('@question - @label', array(
          '@question' => $question,
          '@label' => $label,
        )),
      );
    }
  }
  ksort($question_set);
  ksort($answer_set);
  return array(
    'question_set' => $question_set,
    'answer_set' => $answer_set,
  );
}
