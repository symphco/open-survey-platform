<?php

/**
 * @file
 * Provides validation functionality and hooks
 */

/**
 * Implements hook_webform_validation_validators().
 *
 * This function returns an array of validators, in the validator key => options array form.
 * Possible options:
 * - name (required): name of the validator
 * - component types (required): defines which component types can be validated by this validator. Specify 'all' to allow all types
 * - negatable (optional): define whether the rule can be negated, meaning it will validate the inverse of the rule.
 * - custom_error (optional): define whether a user can specify a custom error message upon creating the validation rule.
 * - custom_data (optional): define whether custom data can be added to the validation rule
 * - min_components (optional): define the minimum number of components to be selected for creating a validation rule
 * - max_components (optional): define the maximum number of components to be selected for creating a validation rule
 * - description (optional): provide a descriptive explanation about the validator
 */
function webform_validation_webform_validation_validators() {
  $validators = array(
    'numeric' => array(
      'name' => t('Numeric values'),
      'component_types' => array(
        'number',
        'textfield',
        'hidden',
      ),
      'custom_data' => array(
        'label' => t('Specify numeric validation range'),
        'description' => t('Optionally specify the minimum-maximum range to validate the user-entered numeric value against.') . ' ' . t('Usage') . ':'
        . theme('item_list', array('items' => array(t('empty: no value validation'), t('"100": greater than or equal to 100'), t('"|100": less than or equal to 100 (including negative numbers)'), t('"0|100": greater than or equal to 0 &amp; less than or equal to 100'), t('"10|100": greater than or equal to 10 &amp; less than or equal to 100'), t('"-100|-10": greater than or equal to -100 &amp; less than or equal to -10')))),
        'required' => FALSE,
      ),
      'description' => t('Verifies that user-entered values are numeric, with the option to specify min and / or max values.'),
    ),
    'min_length' => array(
      'name' => t('Minimum length'),
      'component_types' => array(
        'number',
        'textfield',
        'textarea',
        'email',
        'hidden',
      ),
      'custom_data' => array(
        'label' => t('Minimum number of characters'),
        'description' => t('Specify the minimum number of characters that have to be entered to pass validation.'),
      ),
      'description' => t('Verifies that a user-entered value contains at least the specified number of characters'),
    ),
    'max_length' => array(
      'name' => t('Maximum length'),
      'component_types' => array(
        'number',
        'textfield',
        'textarea',
        'email',
        'hidden',
      ),
      'custom_data' => array(
        'label' => t('Maximum number of characters'),
        'description' => t('Specify the maximum number of characters that can be entered to pass validation.'),
      ),
      'description' => t('Verifies that a user-entered value contains at most the specified number of characters'),
    ),
    'min_words' => array(
      'name' => t('Minimum number of words'),
      'component_types' => array(
        'textfield',
        'textarea',
        'hidden',
        'html_textarea',
      ),
      'custom_data' => array(
        'label' => t('Minimum number of words'),
        'description' => t('Specify the minimum number of words that have to be entered to pass validation. Words are defined as strings of letters separated by spaces.')
      ),
      'description' => t('Verifies that a user-entered value contains at least the specified number of words.'),
    ),
    'max_words' => array(
      'name' => t('Maximum number of words'),
      'component_types' => array(
        'textfield',
        'textarea',
        'hidden',
        'html_textarea',
      ),
      'custom_data' => array(
        'label' => t('Maximum number of words'),
        'description' => t('Specify the maximum number of words that have to be entered to pass validation. Words are defined as strings of letters separated by spaces.')
      ),
      'description' => t('Verifies that a user-entered value contains at most the specified number of words.'),
    ),
    'equal' => array(
      'name' => t('Equal values'),
      'component_types' => array(
        'number',
        'textfield',
        'email',
        'select',
        'hidden',
      ),
      'min_components' => 2,
      'description' => t('Verifies that all specified components contain equal values.'),
    ),
    'comparison' => array(
      'name' => t('Compare two values'),
      'component_types' => array(
        'date',
        'email',
        'hidden',
        'number',
        'textfield',
        'select',
        'time',
      ),
      'custom_error' => TRUE,
      'custom_data' => array(
        'label' => t('Comparison operator'),
        'description' => t('Specify the comparison operator you want to use. Must be one of: >, >=, <, <=. The validator will compare the first component with the second using this operator.'),
      ),
      'min_components' => 2,
      'max_components' => 2,
      'description' => t('Compare two values for greater than or less than, or equal to.'),
    ),
    'unique' => array(
      'name' => t('Unique values'),
      'component_types' => array(
        'number',
        'textfield',
        'email',
        'select',
        'hidden',
      ),
      'min_components' => 2,
      'description' => t('Verifies that all specified components contain unique values.'),
    ),
    'specific_value' => array(
      'name' => t('Specific value(s)'),
      'negatable' => TRUE,
      'component_types' => array(
        'number',
        'select',
        'textfield',
        'textarea',
        'email',
        'hidden',
      ),
      'custom_error' => TRUE,
      'custom_data' => array(
        'label' => t('(Key) value'),
        'description' => t('Specify the specific value(s) you want the component to contain. Separate multiple options by a comma. For components that have keys, use the key value instead.'),
      ),
      'max_components' => 1,
      'description' => t('Verifies that the value of the specified component is from a list of allowed values.'),
    ),
    'default_value' => array(
      'name' => t('Default value'),
      'negatable' => TRUE,
      'component_types' => array(
        'select',
        'number',
        'textfield',
        'textarea',
        'email',
        'hidden',
      ),
      'custom_error' => TRUE,
      'description' => t('Verifies that the user-entered value is the default value for that component. Negate if you want not the default value.'),
    ),
    'oneoftwo' => array(
      'name' => t('Require at least one of two fields'),
      'component_types' => array(
        'number',
        'textfield',
        'textarea',
        'email',
        'select',
      ),
      'min_components' => 2,
      'max_components' => 2,
      'description' => t('Forces the user to specify / select at least one of two selected webform components'),
    ),
    'oneofseveral' => array(
      'name' => t('Require at least one of several fields'),
      'component_types' => array(
        'number',
        'textfield',
        'textarea',
        'email',
        'select',
      ),
      'min_components' => 2,
      'description' => t('Forces the user to specify / select at least one of several selected webform components.'),
    ),
    'select_min' => array(
      'name' => t('Minimum number of selections required'),
      'component_types' => array(
        'select',
      ),
      'custom_data' => array(
        'label' => t('Minimum number of selections'),
        'description' => t('Specify the minimum number of options a user should select.'),
      ),
      'description' => t('Forces the user to select at least a defined number of options from the specified webform components.'),
    ),
    'select_max' => array(
      'name' => t('Maximum number of selections allowed'),
      'component_types' => array(
        'select',
      ),
      'custom_data' => array(
        'label' => t('Maximum number of selections'),
        'description' => t('Specify the maximum number of options a user can select.'),
      ),
      'description' => t('Forces the user to select at most a defined number of options from the specified webform components.'),
    ),
    'select_exact' => array(
      'name' => t('Exact number of selections required'),
      'negatable' => TRUE,
      'component_types' => array(
        'select',
      ),
      'custom_data' => array(
        'label' => t('Number of selections'),
        'description' => t('Specify how many options a user can select.'),
      ),
      'description' => t('Forces the user to select exactly the defined number of options from the specified webform components.'),
    ),
    'plain_text' => array(
      'name' => t('Plain text (disallow tags)'),
      'negatable' => TRUE,
      'component_types' => array(
        'textfield',
        'textarea',
        'email',
        'hidden',
      ),
      'description' => t('Verifies that user-entered data doesn\'t contain HTML tags.'),
    ),
    'starts_with' => array(
      'name' => t('Starts with'),
      'negatable' => TRUE,
      'component_types' => array(
        'number',
        'textfield',
        'textarea',
        'email',
        'hidden',
      ),
      'custom_data' => array(
        'label' => t('Starts with'),
        'description' => t('Enter the text that this field must start with.'),
      ),
      'description' => t('Verifies that user-entered data starts with a given string.'),
    ),
    'ends_with' => array(
      'name' => t('Ends with'),
      'negatable' => TRUE,
      'component_types' => array(
        'number',
        'textfield',
        'textarea',
        'email',
        'hidden',
      ),
      'custom_data' => array(
        'label' => t('Ends with'),
        'description' => t('Enter the text that this field must end with.'),
      ),
      'description' => t('Verifies that user-entered data ends with a given string.'),
    ),
    'pattern' => array(
      'name' => 'Pattern',
      'component_types' => array(
        'textfield',
        'hidden',
      ),
      'custom_error' => TRUE,
      'custom_data' => array(
        'label' => t('Pattern'),
        'description' => t('Specify a pattern where:')
        . theme('item_list', array('items' => array(t('@ = any letter A-Z'), t('# = any numeral 0-9'), t('| = separates two or more acceptable patterns'), t('Any other character must appear in its exact position'))))
        . t('Examples')
        . theme('item_list', array('items' => array(t('North American phone number: (###) ###-####'), t('D-2500 series model numbers: D-25##'), t('UK Postal Code: @# #@@|@## #@@|@@# #@@|@@## #@@|@#@ #@@|@@#@ #@@|GIR0AA')))),
      ),
      'description' => t('Verifies that a user-entered value follows to a specified pattern.'),
    ),
    'regex' => array(
      'name' => t('Regular expression, case-sensitive'),
      'negatable' => TRUE,
      'component_types' => array(
        'number',
        'textfield',
        'textarea',
        'email',
        'hidden',
      ),
      'custom_error' => TRUE,
      'custom_data' => array(
        'label' => t('Regex code'),
        'description' => t('Specify regex code to validate the user input against.'),
      ),
      'description' => t('Validates user-entered text against a specified case-sensitive regular expression. Note: don\'t include delimiters such as /.'),
    ),
    'regexi' => array(
      'name' => t('Regular expression, case-insensitive'),
      'negatable' => TRUE,
      'component_types' => array(
        'number',
        'textfield',
        'textarea',
        'email',
        'hidden',
      ),
      'custom_error' => TRUE,
      'custom_data' => array(
        'label' => t('Regex code'),
        'description' => t('Specify regex code to validate the user input against.'),
      ),
      'description' => t('Validates user-entered text against a specified case-insensitive regular expression. Note: don\'t include delimiters such as /.'),
    ),
    'must_be_empty' => array(
      'name' => t('Must be empty'),
      'component_types' => array(
        'number',
        'textfield',
        'hidden',
      ),
      'description' => t('Verifies that a specified textfield remains empty. Recommended use case: used as an anti-spam measure by hiding the element with CSS.'),
    ),
    'blacklist' => array(
      'name' => t('Words blacklist'),
      'negatable' => TRUE,
      'component_types' => array(
        'textfield',
        'textarea',
        'email',
        'hidden',
      ),
      'custom_error' => TRUE,
      'custom_data' => array(
        'label' => t('Blacklisted words'),
        'description' => t('Specify illegal words, seperated by commas.'),
      ),
      'description' => t('Validates that user-entered data doesn\'t contain any of the specified illegal words.'),
    ),
   'username' => array(
      'name' => t('Must match a username'),
      'negatable' => TRUE,
      'component_types' => array(
        'textfield',
        'hidden',
      ),
      'description' => t('Validates that user-entered data matches a username.'),
    ),
    'valid_url' => array(
      'name' => 'Valid URL',
      'negatable' => TRUE,
      'component_types' => array(
        'textfield',
        'hidden',
      ),
      'description' => t('Validates that the user-entered data is a valid URL.'),
    ),
  );

  if (module_exists('email_verify')) {
    $validators['email_verify'] = array(
      'name' => 'Email Verify',
      'component_types' => array(
        'email',
      ),
      'description' => t('Verifies that an email address actually exists using the <a href="https://drupal.org/project/email_verify">Email Verification module</a>.'),
    );
  }

  return $validators;
}

/**
 * Implements hook_webform_validation_validate().
 */
function webform_validation_webform_validation_validate($validator_name, $items, $components, $rule) {
  if ($items) {
    $errors = array();
    switch ($validator_name) {
      case 'numeric':
        $num_range = _webform_numeric_check_data($rule['data']);
        foreach ($items as $key => $val) {
          if ($val != '') {
            // first check if the value is numeric
            if (is_numeric($val)) {
              $val = (float) $val;
            }
            else {
              $errors[$key] = t('%item is not numeric.', array('%item' => $components[$key]['name']));
              continue;
            }

            // now validate the entered numeric value against the validator range settings, if appropriate
            // a. validate min & max
            if (isset($num_range['min']) && isset($num_range['max'])) {
              // validate the min - max range
              if ($val < $num_range['min'] || $val > $num_range['max']) {
                $errors[$key] = t('%item is not within the allowed range %range.', array('%item' => $components[$key]['name'], '%range' => str_replace('|' , ' - ', $rule['data'])));
              }
            }
            else {
              // b. validate min
              if (isset($num_range['min'])) {
                if ($val < $num_range['min']) {
                  $errors[$key] = t('%item should be greater than or equal to %val.', array('%item' => $components[$key]['name'], '%val' => $num_range['min']));
                }
              }
              // c. validate max
              if (isset($num_range['max'])) {
                if ($val > $num_range['max']) {
                  $errors[$key] = t('%item should be less than or equal to %val.', array('%item' => $components[$key]['name'], '%val' => $num_range['max']));
                }
              }
            }
          }
        }
        return $errors;
      case 'min_length':
        $min_length = $rule['data'];
        foreach ($items as $key => $val) {
          if ($val != '' && (drupal_strlen($val) < $min_length)) {
            $errors[$key] = t('%item should be at least %num characters long.', array('%item' => $components[$key]['name'], '%num' => $min_length));
          }
        }
        return $errors;
      case 'max_length':
        $max_length = $rule['data'];
        foreach ($items as $key => $val) {
          if ($val != '' && (drupal_strlen($val) > $max_length)) {
            $errors[$key] = t('%item should be at most %num characters long.', array('%item' => $components[$key]['name'], '%num' => $max_length));
          }
        }
        return $errors;
      case 'min_words':
        $min_words = $rule['data'];
        foreach ($items as $key => $val) {
          if ($val != '' && (_webform_validation_count_words($val) < $min_words)) {
            $error = format_plural($min_words, '%item should be at least 1 word long.', '%item should be at least @count words long.', array('%item' => $components[$key]['name']));
            $errors[$key] = $error;
          }
        }
        return $errors;
      case 'max_words':
        $max_words = $rule['data'];
        foreach ($items as $key => $val) {
          if ($val != '' && (_webform_validation_count_words($val) > $max_words)) {
            $error = format_plural($max_words, '%item should be at most 1 word long.', '%item should be at most @count words long.', array('%item' => $components[$key]['name']));
            $errors[$key] = $error;
          }
        }
        return $errors;
      case 'equal':
        $first_entry_key = key($items);
        $first_entry = array_shift($items);
        $first_entry = _webform_validation_flatten_array($first_entry); // flatten in case of array
        // now check if following components equal the first one
        foreach ($items as $key => $val) {
          $val = _webform_validation_flatten_array($val); // flatten in case of array
          if ($val !== $first_entry) {
            $errors[$key] = t('%item_checked does not match %item_first.', array('%item_checked' => $components[$key]['name'], '%item_first' => $components[$first_entry_key]['name']));
          }
        }
        return $errors;
      case 'comparison':
        foreach (array(1, 2) as $count) {
          $entry[$count]['key'] = key($items);
          $value = array_shift($items);
          if ($components[$entry[$count]['key']]['type'] === 'date') {
            if (checkdate((int) $value['month'], (int) $value['day'], (int) $value['year'])) {
              $entry[$count]['value'] = date('Y-m-d', mktime(0, 0, 0, (int) $value['month'], (int) $value['day'], (int) $value['year']));
            }
            else {
              $entry[$count]['value'] = NULL;
            }
          }
          elseif ($components[$entry[$count]['key']]['type'] === 'time') {
            $time = $value['hour'] . ':' . $value['minute'];
            if (!empty($value['ampm'])) {
              $time .= ' ' . $value['ampm'];
            }
            $time = strtotime($time);
            if ($time) {
              $entry[$count]['value'] = date('H:i', $time);
            }
            else {
              $entry[$count]['value'] = NULL;
            }
          }
          else {
            $entry[$count]['value'] = _webform_validation_flatten_array($value);
          }
        }

        // Don't validate if either are empty.
        if (empty($entry[1]['value']) || empty($entry[2]['value'])) {
          return;
        }

        $error = FALSE;
        switch ($rule['data']) {
          case '>':
            if (!($entry[1]['value'] > $entry[2]['value'])) {
              $error = TRUE;
            }
            break;
          case '>=':
            if (!($entry[1]['value'] >= $entry[2]['value'])) {
              $error = TRUE;
            }
            break;
          case '<':
            if (!($entry[1]['value'] < $entry[2]['value'])) {
              $error = TRUE;
            }
            break;
          case '<=':
            if (!($entry[1]['value'] <= $entry[2]['value'])) {
              $error = TRUE;
            }
            break;
        }

        if ($error) {
          $errors[$entry[2]['key']] = _webform_validation_i18n_error_message($rule);
        }
        return $errors;
      case 'unique':
        foreach ($items as $key => $val) {
          if (is_array($val)) {
            // make sure to flatten arrays first
            $items[$key] = _webform_validation_flatten_array($val);
          }
          if (empty($items[$key])) {
            // items without a value selected shouldn't be validated
            unset($items[$key]);
          }
        }
        // now we count how many times each value appears, and find out which values appear more than once
        $items_count = array_count_values(array_map('drupal_strtolower', array_map('trim', $items)));
        $doubles = array_filter($items_count, create_function('$x', 'return $x > 1;'));
        foreach ($items as $key => $val) {
          if (in_array(drupal_strtolower($val), array_keys($doubles))) {
            $errors[$key] = t('The value of %item is not unique.', array('%item' => $components[$key]['name']));
          }
        }
        return $errors;
      case 'specific_value':
        $specific_values = explode(',', $rule['data']);
        $specific_values = array_map('trim', $specific_values);
        foreach ($items as $key => $val) {
          if (is_array($val)) {
            // Selects: Fail if at least one checked and at least one not in the allowed values.
            $val = array_filter($val);
            $test = count($val) && count(array_diff($val, $specific_values));
          }
          else {
            // Fail if not empty and not in the allowed values.
            $test = $val && !in_array($val, $specific_values);
          }
          _webform_validation_test($errors, $key, $rule, $test);
        }
        return $errors;
      case 'default_value':
        foreach ($items as $key => $val) {
          if (is_array($val)) {
            $val = _webform_validation_flatten_array($val);
          }
          $test = $val != $components[$key]['value'];
          _webform_validation_test($errors, $key, $rule, $test);
        }
        return $errors;
      case 'oneoftwo':
        // $components should have 2 items
        $keys = array_keys($items);
        $item1 = array_shift($keys);
        $item2 = array_shift($keys);
        $entry1 = _webform_validation_flatten_array($items[$item1]);
        $entry2 = _webform_validation_flatten_array($items[$item2]);
        if (empty($entry1) && empty($entry2)) {
          return array($item1 => t('You have to specify %item1 or %item2 (or both).', array('%item1' => $components[$item1]['name'], '%item2' => $components[$item2]['name'])));
        }
        return;
      case 'oneofseveral':
        foreach ($items as $key => $val) {
          if (is_array($val)) {
            // make sure to flatten arrays first
            $items[$key] = _webform_validation_flatten_array($val);
          }
        }
        // $components should have at least one of several items
        if (count(array_filter($items)) < 1) {
          $keys = array_keys($items);
          $names = array();
          foreach ($keys as $value) {
            $names[] = $components[$value]['name'];
          }
          return array($keys[0] => t('You have to specify at least one of these items:') . theme('item_list', array('items' => $names)));
        }
        return;
      case 'select_min':
        $min_selections = $rule['data'];
        foreach ($items as $key => $val) {
          if (is_array($val) && (count(array_filter($val, '_webform_validation_check_false')) < $min_selections)) {
            $errors[$key] = t('Please select at least %num options for %item.', array('%num' => $min_selections, '%item' => $components[$key]['name']));
          }
        }
        return $errors;
      case 'select_max':
        $max_selections = $rule['data'];
        foreach ($items as $key => $val) {
          if (is_array($val) && (count(array_filter($val, '_webform_validation_check_false')) > $max_selections)) {
            $errors[$key] = t('Please select maximum %num options for %item.', array('%num' => $max_selections, '%item' => $components[$key]['name']));
          }
        }
        return $errors;
      case 'select_exact':
        $allowed_selections = $rule['data'];
        foreach ($items as $key => $val) {
          $error_strings = array(
            'regular' => 'Please select %num options for %item.',
            'negated' => 'Please do not select %num options for %item.',
          );
          $error_vars = array('%num' => $allowed_selections, '%item' => $components[$key]['name']);
          $test = is_array($val) && (count(array_filter($val, '_webform_validation_check_false')) != $allowed_selections);
          _webform_validation_test($errors, $key, $rule, $test, $error_strings, $error_vars);
        }
        return $errors;
      case 'plain_text':
        foreach ($items as $key => $val) {
          $error_strings = array(
            'regular' => '%item only allows the use of plain text.',
            'negated' => '%item must contain HTML tags.',
          );
          $error_vars = array('%item' => $components[$key]['name']);
          $test = $val != '' && (strcmp($val, strip_tags($val)));
          _webform_validation_test($errors, $key, $rule, $test, $error_strings, $error_vars);
        }
        return $errors;
      case 'starts_with':
      case 'ends_with':
        $pattern = _webform_validation_preg_quote($rule['data'], '/');
        if ($validator_name === 'starts_with') {
          $pattern = '^' . $pattern;
          $verb = t('start');
        }
        else {
          $pattern .= '$';
          $verb = t('end');
        }
        $pattern = '/' . $pattern . '/';

        foreach ($items as $key => $val) {
          $val = (string) $val;
          $error_strings = array(
            'regular' => '%item must %verb with "%string".',
            'negated' => '%item must not %verb with "%string".',
          );
          $error_vars = array('%item' => $components[$key]['name'], '%verb' => $verb, '%string' => $rule['data']);
          $test = $val && !preg_match($pattern, $val);
          _webform_validation_test($errors, $key, $rule, $test, $error_strings, $error_vars);
        }
        return $errors;
      case 'pattern':
        $pattern = _webform_validation_preg_quote($rule['data'], '/');
        $pattern = str_replace('@', '[a-zA-Z]', $pattern);
        $pattern = str_replace('#', '[0-9]', $pattern);
        $pattern = '(' . $pattern . ')';
        // Un-escape "|" operator.
        $pattern = preg_replace('/(\\s*)(\\\\)(\\|)(\\s*)/', ')|(', $pattern);
        foreach ($items as $key => $val) {
          $val = (string) $val;
          $test = $val !== '' && !preg_match('/^(' . $pattern . ')$/', $val);
          _webform_validation_test($errors, $key, $rule, $test);
        }
        return $errors;
      case 'regex':
      case 'regexi':
        mb_regex_encoding('UTF-8');
        $regex = $rule['data'];
        foreach ($items as $key => $val) {
          $val = (string) $val;
          if ($val) {
            if ($validator_name === 'regexi') {
              $match = (bool) mb_eregi($regex, $val);
            }
            else {
              $match = (bool) mb_ereg($regex, $val);
            }
            $test = !$match;
            _webform_validation_test($errors, $key, $rule, $test);
          }
        }
        return $errors;
      case 'must_be_empty':
        foreach ($items as $key => $val) {
          if ($val) {
            $errors[$key] = t('%item does not contain the correct data.', array('%item' => $components[$key]['name']));
          }
        }
        return $errors;
      case 'blacklist':
        $blacklist = _webform_validation_preg_quote($rule['data'], '/');
        $blacklist = explode(',', $blacklist);
        $blacklist = array_map('trim', $blacklist);
        $blacklist = '/\b(' . implode('|', $blacklist) . ')\b/i';
        foreach ($items as $key => $val) {
          $test = $val != '' && preg_match($blacklist, $val);
          _webform_validation_test($errors, $key, $rule, $test);
        }
        return $errors;
      case 'username':
        foreach ($items as $key => $val) {
          $error_strings = array(
            'regular' => 'The %item field does not match an active username.',
            'negated' => 'The %item field matches an active username.',
          );
          $error_vars = array('%item' => $components[$key]['name']);
          $test = $val != '' && !db_query_range('SELECT 1 FROM {users} WHERE name = :username AND status = 1', 0, 1, array(':username' => $val))->fetchField();
          _webform_validation_test($errors, $key, $rule, $test, $error_strings, $error_vars);
        }
        return $errors;
      case 'valid_url':
        foreach ($items as $key => $val) {
          $error_strings = array(
            'regular' => '%item does not appear to be a valid URL.',
            'negated' => '%item must not be a valid URL.',
          );
          $error_vars = array('%item' => $components[$key]['name']);
          $test = $val && !valid_url($val, TRUE);
          _webform_validation_test($errors, $key, $rule, $test, $error_strings, $error_vars);
        }
        return $errors;
      case 'email_verify':
        if (module_exists('email_verify')) {
          foreach ($items as $key => $val) {
            $error = email_verify_check($val);
            if ($error) {
              $errors[$key] = $error;
            }
          }
        }
        return $errors;
    }
  }
}

/**
 * Helper function to negate validation rules as needed and create the correct error message.
 */
function _webform_validation_test(&$errors, $key, $rule, $test, array $error_strings = NULL, array $error_vars = NULL) {
  $rule['negate'] = !empty($rule['negate']);
  if ($rule['negate']) {
    $test = !$test;
  }
  if ($test) {
    if ($error_strings) {
      $error = t($error_strings[$rule['negate'] ? 'negated' : 'regular'], $error_vars);
    }
    else {
      $error = _webform_validation_i18n_error_message($rule);
    }
    $errors[$key] = $error;
  }
}

/**
 * Count the number of words in a value.
 */
function _webform_validation_count_words($val) {
  // Deal with values from HTML textareas.
  if (is_array($val) && isset($val['value'])) {
    $val = strip_tags($val['value']);
    // Replace entities representing spaces with actual spaces.
    $val = str_replace('&nbsp;', ' ', $val);
    $val = str_replace('&#160;', ' ', $val);
  }
  else {
    $val = _webform_validation_flatten_array($val);
  }
  return str_word_count($val);
}

/**
 * Fixed version of preg_quote() to work around PHP bug #47229. Remove when
 * PHP_VERSION < 5.3 is no longer supported.
 */
function _webform_validation_preg_quote($str, $delimiter = NULL) {
  $str = preg_quote($str, $delimiter);
  if (PHP_VERSION < 5.3) {
    $str = str_replace('-', '\-', $str);
  }
  return $str;
}

/**
 * Helper function to deal with submitted values that are arrays (e.g. multiple select component)
 * We flatten the array as a comma-separated list to do the comparison.
 */
function _webform_validation_flatten_array($val) {
  if (is_array($val)) {
    $arr = array_filter($val, '_webform_validation_check_false');
    return implode(',', $arr);
  }
  return $val;
}

/**
 * Get a list of validator definitions
 */
function webform_validation_get_validators() {
  $validators = module_invoke_all('webform_validation_validators');
  // let modules use hook_webform_validator_alter($validators) to change validator settings
  drupal_alter('webform_validator', $validators);
  return $validators;
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function webform_validation_get_validators_selection() {
  $selection = array();
  $validators = webform_validation_get_validators();
  if ($validators) {
    foreach ($validators as $validator_key => $validator_info) {
      $selection[$validator_key] = $validator_info['name'];
    }
  }
  return $selection;
}

/**
 * Get a list of valid component types per validator, as defined via hook_webform_validation_validators().
 * If 'all' is specified, all available component types will be returned.
 */
function webform_validation_valid_component_types($validator) {
  $validators = webform_validation_get_validators();
  if ($info = $validators[$validator]) {
    $allowed_types = $info['component_types'];
    if (_webform_validation_all_allowed($allowed_types)) {
      return array_keys(webform_components());
    }
    return $info['component_types'];
  }
}

/**
 * Helper function to check whether all components are allowed to be used for a certain validator
 */
function _webform_validation_all_allowed($allowed) {
  if ($allowed) {
    foreach ($allowed as $type) {
      if ($type == 'all') {
        return TRUE;
      }
    }
  }
  return FALSE;
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function webform_validation_get_validator_info($validator_key) {
  $validators = webform_validation_get_validators();
  return $validators[$validator_key];
}

/**
 * Handle translatable error messages, if available
 */
function _webform_validation_i18n_error_message($rule) {
  $rule['error_message'] = filter_xss($rule['error_message']);
  if (module_exists('i18nstrings')) {
    return i18nstrings('webform_validation:error_message:' . $rule['ruleid'] . ':message', $rule['error_message']);
  }
  return $rule['error_message'];
}

/**
 * Helper function used by array_filter to determine if a value was selected or not
 */
function _webform_validation_check_false($var) {
  return $var !== FALSE && $var !== 0;
}

/**
 * Process the numeric value validation range that was provided in the numeric validator options
 */
function _webform_numeric_check_data($data) {
  $range = array('min' => NULL, 'max' => NULL);
  // if no value was specified, don't validate
  if ($data == '') {
    return $range;
  }

  // If only one numeric value was specified, this is the min value
  if (is_numeric($data)) {
    $range['min'] = (float) $data;
  }

  if (strpos($data, '|') !== FALSE) {
    list($min, $max) = explode('|', $data);
    if ($min != '' && is_numeric($min)) {
      $range['min'] = (float) $min;
    }
    if ($max != '' && is_numeric($max)) {
      $range['max'] = (float) $max;
    }
  }
  return $range;
}
