<?php

function openlgu_custom_form_views_exposed_form_alter(&$form, &$form_state, $form_id) {
	
	// Turn Acadmic Year into a checkbox select
	$options = array(
                '2013' => '2013',
		'2014' => '2014',
		'2015' => '2015'
	);
	$form['data_3']['#type'] = "select";
	$form['data_3']['#options'] = $options;
	$form['data_3']['#multiple'] = TRUE;
	$form['data_3']['#theme'] = "select_as_checkboxes";
	
	// Turn School Type into a checkbox select
	$options = array(
		'1' => '1-6',
		'2' => 'Y1-4/5'
	);
	$form['data_2']['#type'] = "select";
	$form['data_2']['#options'] = $options;
	$form['data_2']['#multiple'] = TRUE;
	$form['data_2']['#theme'] = "select_as_checkboxes";

}

function openlgu_custom_preprocess_page(&$vars) { 
	if(!(empty($vars['node']))) {
		if($vars['node']->nid == "258334444444") {
		
		
			// Get all webform submissions for this form 
			include("/var/www/webroot/open-ed/sites/all/modules/webform/includes/webform.submissions.inc");
			$submissions = webform_get_submissions("34057");

			foreach ($submissions as $submission) {
			  if($submission->serial == 11) {
			  }
			}
                      
			// Variable for General Facilities Condition 
			$conditionsGraph = array(
				'water' => '0',
				'electricity' => '0',
				'library' => '0',
				'science_classroom' => '0',
				'computers' => '0',
                                'windows' => '0',
                                'walls' => '0',
                                'total_submissions' => '0',
                                'total_enrolled_students' => '0',
			);
                         
		foreach ($submissions as $submission) {
				if($submission->data[35][0] == 'yes') {
					$conditionsGraph['water']++;
				}
				if($submission->data[33][0] == 'yes') {
					$conditionsGraph['electricity']++;
				}
				if($submission->data[36][0] == 'yes') {
					$conditionsGraph['library']++;
				}
				if($submission->data[37][0] == 'yes') {
					$conditionsGraph['science_classroom']++;
				}
				if($submission->data[38][0] == 'yes') {
					$conditionsGraph['computers']++;
				}
                                if($submission->data[336][0] == '1: Good') {
                                        $conditionsGraph['windows']++;
                                }
                                if($submission->data[175][0] == '1: Dirt') {
                                        $conditionsGraph['walls']++;
                                }
			
                                $conditionsGraph['total_submissions']++;
                                $conditionsGraph['total_enrolled_students']+=$submission->data[26][0];
                                $conditionsGraph['total_number_teachers']+=$submission->data[71][0];
			}
			$vars['conditionsGraph'] = $conditionsGraph;
			
			// Variable for Biggest Challenges Graphs 
			$challengesGraphWorking = array();

			$challengesGraphWorking = array(
				'num_teachers' => array('score' => 0, 1 =>0, 2=>0, 3=>0, 4=>0, 'cid' => 203),
				'qual_teachers' => array('score' => 0, 1 =>0, 2=>0, 3=>0, 4=>0, 'cid' => 204),
				'personnel' => array('score' => 0, 1 =>0, 2=>0, 3=>0, 4=>0, 'cid' => 205),
				'num_textbooks' => array('score' => 0, 1 =>0, 2=>0, 3=>0, 4=>0, 'cid' => 206),
				'furniture' => array('score' => 0, 1 =>0, 2=>0, 3=>0, 4=>0, 'cid' => 207),
				'other_materials' => array('score' => 0, 1 =>0, 2=>0, 3=>0, 4=>0, 'cid'=> 208),
				'num_classrooms' => array('score' => 0, 1 =>0, 2=>0, 3=>0, 4=>0, 'cid' => 209),
				'maintenance' => array('score' => 0, 1 =>0, 2=>0, 3=>0, 4=>0, 'cid' => 210),
				'teacher_absent' => array('score' => 0, 1 =>0, 2=>0, 3=>0, 4=>0, 'cid' => 211),
				'student_absent' => array('score' => 0, 1 =>0, 2=>0, 3=>0, 4=>0, 'cid' => 212),
				'gender_imbalance' => array('score' => 0, 1 =>0, 2=>0, 3=>0, 4=>0, 'cid' =>213),
				'budget' => array('score' => 0, 1 =>0, 2=>0, 3=>0, 4=>0, 'cid' => 214),
				'poverty' => array('score' => 0, 1 =>0, 2=>0, 3=>0, 4=>0, 'cid' => 215),
				'students_food' => array('score' => 0, 1 =>0, 2=>0, 3=>0, 4=>0, 'cid' => 216),
				'parent_support' => array('score' => 0, 1 =>0, 2=>0, 3=>0, 4=>0, 'cid' => 217),
				'electricity' => array('score' => 0, 1 =>0, 2=>0, 3=>0, 4=>0, 'cid' => 218),
				'sanitation' => array('score' => 0, 1 =>0, 2=>0, 3=>0, 4=>0, 'cid' => 219),
				'water' => array('score' => 0, 1 =>0, 2=>0, 3=>0, 4=>0, 'cid' => 220),
				'commute' => array('score' => 0, 1 =>0, 2=>0, 3=>0, 4=>0, 'cid' => 221),
				'conflict' => array('score' => 0, 1 =>0, 2=>0, 3=>0, 4=>0, 'cid' => 222)
			);
			$challengesGraphFullNames = array(
				'num_teachers' => "Need More Teachers (Large PTR)",
				'qual_teachers' => "Need Better Qualified Teachers",
				'personnel' => "Need Support Personnel",
				'num_textbooks' => "Need More Textbooks",
				'furniture' => "Need Furniture",
				'other_materials' => "Need Other Teaching Materials",
				'num_classrooms' => "Need More Classrooms (Large PTR)",
				'maintenance' => "Need Better Building Maintenance",
				'teacher_absent' => "Teachers Absenteeism",
				'student_absent' => "Students Absenteeism",
				'gender_imbalance' => "Gender Imbalance",
				'budget' => "Need More Budget to Cover Operating Expenses",
				'poverty' => "Poverty (Among Parents)",
				'students_food' => "Students Lack Sufficient Food",
				'parent_support' => "Need More Support From Parents",
				'electricity' => "Electricity",
				'sanitation' => "Sanitation",
				'water' => "Drinking Water",
				'commute' => "Long Commuting Time",
				'conflict' => "Conflict / Insecurity / Rido"			
			);
			foreach($submissions as $submission) {
				foreach ($challengesGraphWorking as $key=>$workingItem) {
					// Update num teachers
					$user_val = 0;
					$user_val = $submission->data[$workingItem['cid']][0];
					if($user_val != "") {
						$save_val = 4 - $user_val;
						$challengesGraphWorking[$key]['score'] += $save_val;
						$challengesGraphWorking[$key][$user_val] += 1;
					}
				}
			}
                        
			arsort($challengesGraphWorking);
			$challengesGraphWorking = array_slice($challengesGraphWorking, 0, 3);	

			$challengesGraph = array();
			foreach($challengesGraphWorking as $key => $val) {
				$challengesGraph[$key] = array(
					1 => $val[1],
					2 => $val[2],
					3 => $val[3],
					4 => $val[4],
					'name' => $key,
					'full_name' => $challengesGraphFullNames[$key]
				);
			}
			$vars['challengesGraphs'] = $challengesGraph;
			
			// Variables for Students / Textbook Graphs
			
			$studentsPerTextbooksGraph = array(
				'2013' => array(
					'students' => 0,
					'textbooks' => 0
				),
				'2014' => array(
					'students' => 0,
					'textbooks' => 0
				)
			);
			foreach($submissions as $submission) {
				$textbooks = 0;
				$students = 0;
				foreach($submission->wfm_data[165][328] as $students_submission) {
					$students += $students_submission[165][0];
				}
				foreach($submission->wfm_data[172][328] as $textbooks_submission) {
					$textbooks += $textbooks_submission[172][0];
					
				}
				$academic_year = $submission->wfm_data['190'][0];
				$studentsPerTextbooksGraph[$academic_year]['students'] += $students;
				$studentsPerTextbooksGraph[$academic_year]['textbooks'] += $textbooks;
			}
			$vars['studentsPerTextbookGraph'] = $studentsPerTextbooksGraph;
			
			// Variables for Classroom Conditions
			
			$classroom_conditions = array(
				'roof' => array(
					'good' => 0,
					'poor' => 0,
					'absent' => 0
				),
				'walls' => array(					
					'good' => 0,
					'poor' => 0,
					'absent' => 0
				),
				'floor' => array(
					'good' => 0,
					'poor' => 0,
					'absent' => 0
				),
				'benches' => array(
					'good' => 0,
					'poor' => 0,
					'absent' => 0
				),
				'tables' => array(
					'good' => 0,
					'poor' => 0,
					'absent' => 0				
				),
				'chalkboard' => array(
					'good' => 0,
					'poor' => 0,
					'absent' => 0				
				)
			);
			foreach($submissions as $submission) {
			}
			
		}
		
	}

 $bundle = isset($vars['page']['content']['system_main']['nodes'][arg(1)]['#bundle']) ? $vars['page']['content']['system_main']['nodes'][arg(1)]['#bundle'] : "";
  if (isset($bundle) && $bundle =="school_profile") {
    // If the content type's machine name is "my_machine_name" the file
    drupal_add_js('http://leafletjs.com/dist/leaflet.js', 'external');
    drupal_add_css('http://leafletjs.com/dist/leaflet.css', 'external');
    $vars['theme_hook_suggestions'][] = 'page__school_profile';
  }
}


function openlgu_custom_textarea($variables) {
  $element = $variables['element'];
  $element['#attributes']['name'] = $element['#name'];
  $element['#attributes']['id'] = $element['#id'];
  $element['#attributes']['cols'] = $element['#cols'];
  $element['#attributes']['rows'] = $element['#rows'];
  _form_set_class($element, array('form-textarea'));

  $wrapper_attributes = array(
    'class' => array('form-textarea-wrapper'),
  );

  // Add resizable behavior.
  if (!empty($element['#resizable'])) {
    // $wrapper_attributes['class'][] = 'resizable';
  }

  $output = '<div' . drupal_attributes($wrapper_attributes) . '>';
  $output .= '<textarea' . drupal_attributes($element['#attributes']) . '>' . check_plain($element['#value']) . '</textarea>';
  $output .= '</div>';
  return $output;
}

function openlgu_custom_status_messages($variables) {
  $display = $variables['display'];
  $output = '';

  
  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
  );
  foreach (drupal_get_messages($display) as $type => $messages) {
  	if(strpos($messages[0], "to view this form.") !== FALSE) { 
  		$path = current_path();
  		$messages[0] = "You must <a href='/user/login?destination=" . $path . "'>log in</a> to submit this form.";
  		$type .= " form";
  	}
  	
    $output .= "<div class=\"messages $type\">\n";
    if (!empty($status_heading[$type])) {
      $output .= '<h2 class="element-invisible">' . $status_heading[$type] . "</h2>\n";
    }
    if (count($messages) > 1) {
      $output .= " <ul>\n";
      foreach ($messages as $message) {
        $output .= '  <li>' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      $output .= $messages[0];
    }
    $output .= "</div>\n";
  }
  return $output;
}

?>
