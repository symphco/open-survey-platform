<?php
/** @file Webform Component information for a geofield type */
/**
 * Specify the default properties of a component.
 * @return
 *   An array defining the default structure of a component.
 */
function _webform_defaults_geofield() {
	$extra = _webform_defaults_extra_geofield();
  return array(
    'name' => '',
    'form_key' => NULL,
    'required' => 0,
    'mandatory' => 0,
    'pid' => 0,
    'weight' => 0,
    'extra' => array(
      'title_display' => 0,
      'private' => FALSE,
      'attributes' => array(),
      'description' => '',
			'geocode' => '',
    )+$extra['defaults'],
  );
}

function _webform_defaults_extra_geofield(){
	return array(
		'defaults' => array(
			'thoroughfare' => '',
			'premise' => '',
			'locality' => '',
			'administrative_area' => '',
			'postal_code' => '',
			'country' => 'us',
		),
		'labels' => array(
			'thoroughfare' => 'Street address',
			'premise' => 'Apartment, Suite, Box number, etc',
			'locality' => 'City / Town',
			'administrative_area' => 'State / Province / Region',
			'postal_code' => 'Postal code / ZIP Code',
			'country' => 'Country',
		),
	);
}

function _webform_geofield_get_components($node){
	$components = $node->webform['components'];
	foreach ($components as $cid => $component) {
  	if($component['type'] == 'geofield'){
			$geofields[$cid] = $component;
		}
	}
	return $geofields;
}

/**
 * Implements _webform_theme_component().
 */
function _webform_theme_geofield() {
  return array( 'webform_display_geofield' => array( 'render element' => 'element', ), );
}

/**
 * Generate the form for editing a component.
 * Create a set of form elements to be displayed on the form for editing this
 * component. Use care naming the form items, as this correlates directly to the
 * database schema. The component "Name" and "Description" fields are added to
 * every component type and are not necessary to specify here (although they
 * may be overridden if desired).
 *
 * @param $component
 *   A Webform component array.
 *
 * @return
 *   An array of form items to be displayed on the edit component page
 */
function _webform_edit_geofield($component) {
  $form = array();
  // General Options
	$node = node_load($component['nid']);
	
	$fields = array(
		0 => '<none>',
	)+webform_component_list($node, NULL, TRUE, TRUE);
	
	$extras = _webform_defaults_extra_geofield();
	
	foreach($extras['defaults'] as $extra => $default){	
		$form['extra'][$extra] = array(
			'#type'          => 'select',
			'#title'         => t($extras['labels'][$extra]),
			'#options'       => $fields,
			'#default_value' => $component['extra'][$extra],
			'#description'   => t('Which field to use for '.$extras['labels'][$extra].'.  If using addressfield select that field.'),
			'#required'      => TRUE,
		);
	}
  return $form;
}

/**
 * Render a Webform component to be part of a form.
 *
 * @param $component
 *   A Webform component array.
 * @param $value
 *   If editing an existing submission or resuming a draft, this will contain
 *   an array of values to be shown instead of the default in the component
 *   configuration. This value will always be an array, keyed numerically for
 *   each value saved in this field.
 * @param $filter
 *   Whether or not to filter the contents of descriptions and values when
 *   rendering the component. Values need to be unfiltered to be editable by
 *   Form Builder.
 *
 * @see _webform_client_form_add_component()
 */
function _webform_render_geofield($component, $value = NULL, $filter = TRUE) {
  $form_item = array(
    '#type'             => 'hidden',
    '#default_value'    => $filter ? _webform_filter_values($component['value']) : $component['value'],
    '#attributes'       => $component['extra']['attributes'],
    '#theme_wrappers'   => array( 'webform_element' ),
    '#description'      => $filter ? _webform_filter_descriptions($component['extra']['description']) : $component['extra']['description'],
    '#element_validate' => array( 'webform_validate_geofield' ),
    '#required'         => $component['required'] || $component['mandatory'], //Either one being true will could as required...because webform changed in 4.x-alpha8
    '#size'             => 17,
    '#title'            => $filter ? _webform_filter_xss($component['name']) : $component['name'],
    '#title_display'    => $component['extra']['title_display'] ? $component['extra']['title_display'] : 'before',
    '#weight'           => $component['weight'],
    '#translatable'     => array(
      'title',
      'description'
    ),
  );
  if ( isset( $value ) ) {
    $form_item['#default_value'] = $value[0];
  }
  return $form_item;
}

/**
 * Display the result of a submission for a component.
 * The output of this function will be displayed under the "Results" tab then
 * "Submissions". This should output the saved data in some reasonable manner.
 *
 * @param $component
 *   A Webform component array.
 * @param $value
 *   An array of information containing the submission result, directly
 *   correlating to the webform_submitted_data database table schema.
 * @param $format
 *   Either 'html' or 'text'. Defines the format that the content should be
 *   returned as. Make sure that returned content is run through check_plain()
 *   or other filtering functions when returning HTML.
 *
 * @return
 *   A renderable element containing at the very least these properties:
 *    - #title
 *    - #weight
 *    - #component
 *    - #format
 *    - #value
 *   Webform also uses #theme_wrappers to output the end result to the user,
 *   which will properly format the label and content for use within an e-mail
 *   (such as wrapping the text) or as HTML (ensuring consistent output).
 */
function _webform_display_geofield($component, $value, $format = 'html') {
  return array(
    '#title'          => $component['name'],
    '#weight'         => $component['weight'],
    '#theme'          => 'webform_display_geofield',
    '#theme_wrappers' => $format == 'html' ? array( 'webform_element' ) : array( 'webform_element_text' ),
    '#post_render'    => array( 'webform_element_wrapper' ),
    '#component'      => $component,
    '#format'         => $format,
    '#value'          => isset( $value[0] ) ? $value[0] : '',
  );
}

/**
 * Format the output of data for this component.
 */
function theme_webform_display_geofield($variables) {
  $markup = array();
  $element = $variables['element'];
  $plain_value = check_plain($element['#value']);
  $markup['#markup'] = $plain_value;
  return drupal_render($markup);
}

/**
 * A hook for changing the input values before saving to the database.
 * Webform expects a component to consist of a single field, or a single array
 * of fields. If you have a component that requires a deeper form tree
 * you must flatten the data into a single array using this callback
 * or by setting #parents on each field to avoid data loss and/or unexpected
 * behavior.
 * Note that Webform will save the result of this function directly into the
 * database.
 *
 * @param $component
 *   A Webform component array.
 * @param $value
 *   The POST data associated with the user input.
 *
 * @return
 *   An array of values to be saved into the database. Note that this should be
 *   a numerically keyed array.
 */
function _webform_submit_geofield($component, $value) {
	if (isset($value) && !empty($value)) {
		$save_value = $value;
	} 	else {
		$save_value = NULL;
  }
  return $save_value;
}

/**
 * Modify a Webform submission, prior to saving it in the database.
 * This is where a lot of the magic happens however I am not confident about the execution.  **Needs Work**
 * @param $node
 *   The Webform node on which this submission was made.
 * @param $submission
 *   The Webform submission that is about to be saved to the database.
 */
function webform_geofield_webform_submission_presave($node, &$submission) {
	//grabs the defaults
	$extras = _webform_defaults_extra_geofield();
	
	//runs through the available components to geocode
	foreach(_webform_geofield_get_components($node) as $geocid => $geocomponent){
		//runs through each address part of the geofield
		foreach($node->webform['components'][$geocid]['extra'] as $address_part => $field){
			if(array_key_exists($address_part, $extras['defaults'])){
				// runs through each component of the webform to grab those values
				foreach($node->webform['components'] as $cid => $component){
					//makes sure we are grabbing a field that was chosen in the geofield
					if($field != 0 && $field == $cid){
						//if we are an address this is the value;
						if($component['type'] == 'addressfield'){
							$address_field = unserialize($submission->data[$field][0]);
							$value[$address_part] = $address_field[$address_part];
							 //if we are a select this is the value.
						} elseif($component['type'] == 'select'){
							// split text into chunks after each line-break;
							// if not visible here, use "backslash n" as explode parameter
							$pairs = explode("\n", $component['extra']['items']);			
							// split each line into pairs of key and value
							foreach($pairs as $pair) {
								$temp_array = explode('|', $pair);
								if($temp_array[0] && $temp_array[1]){
									$options[trim($temp_array[0])] = $temp_array[1];
								}
							}
							if(isset($options[$submission->data[$field][0]])){
								$value[$address_part] = $options[$submission->data[$field][0]];
							}
						} else { 
						  $value[$address_part] = $submission->data[$field][0];
						}
					}
				}
			}
		}
		// create an address string to pass to the geocoder.
		$address = implode(', ', $value);
		// grab the geocoded geometry ( we could use something besides point here I believe)
		$geometry = geocoder('google',$address,array('geometry_type' => 'point'));
		if(!empty($geometry)){
			// store the value as WKT
			$wkt = $geometry->out('wkt');
			$submission->data[$geocid][0] = $wkt;
		}
	}
}

/**
 * Return the result of a component value for display in a table.
 * The output of this function will be displayed under the "Results" tab then
 * "Table".
 *
 * @param $component
 *   A Webform component array.
 * @param $value
 *   An array of information containing the submission result, directly
 *   correlating to the webform_submitted_data database schema.
 *
 * @return
 *   Textual output formatted for human reading.
 */
function _webform_table_geofield($component, $value) {
  return check_plain(empty( $value[0] ) ? '' : $value[0]);
}

/**
 * Return the header for this component to be displayed in a CSV file.
 * The output of this function will be displayed under the "Results" tab then
 * "Download".
 *
 * @param $component
 *   A Webform component array.
 * @param $export_options
 *   An array of options that may configure export of this field.
 *
 * @return
 *   An array of data to be displayed in the first three rows of a CSV file, not
 *   including either prefixed or trailing commas.
 */
function _webform_csv_headers_geofield($component, $export_options) {
  $header = array();
  $header[0] = '';
  $header[1] = '';
  $header[2] = $component['name'];
  return $header;
}

/**
 * Format the submitted data of a component for CSV downloading.
 * The output of this function will be displayed under the "Results" tab then
 * "Download".
 *
 * @param $component
 *   A Webform component array.
 * @param $export_options
 *   An array of options that may configure export of this field.
 * @param $value
 *   An array of information containing the submission result, directly
 *   correlating to the webform_submitted_data database schema.
 *
 * @return
 *   An array of items to be added to the CSV file. Each value within the array
 *   will be another column within the file. This function is called once for
 *   every row of data.
 */
function _webform_csv_data_geofield($component, $export_options, $value) {
  return !isset( $value[0] ) ? '' : $value[0];
}

/**
 * Implements _form_builder_webform_form_builder_types_component().
 */
function _form_builder_webform_form_builder_types_geofield() {
  $fields = array();
  $fields['geofield'] = array(
    'title'      => t('Geofield'),
    'properties' => array(),
    'weight'     => -17,
    //Doesn't make sense that modules get to weight themselves, why wouldn't everyone want to be first?
  );
	
	$extras = _webform_defaults_extra_geofield();
	
  $fields['geofield']['default'] = _form_builder_webform_default('geofield');
  $fields['geofield']['default']['#title'] = t('New Geofield');
	
	foreach($extras['defaults'] as $extra => $default){
		$fields['geofield']['default']['#'.$extra] = $default;
	}
	
  return $fields;
}

/**
 * Implements _form_builder_webform_form_builder_map_component().
 */
function _form_builder_webform_form_builder_map_geofield() {
	$properties = array();
	$extras = _webform_defaults_extra_geofield();

	foreach($extras['defaults'] as $extra => $default){
		$properties[$extra] = array(
			'form_parents' => array(
          'extra',
          $extra,
       ),
       'storage_parents' => array(
          'extra',
          $extra,
       ),
		);
	}
  return array(
    'form_builder_type' => 'geofield',
    'properties' => $properties,
  );
}
