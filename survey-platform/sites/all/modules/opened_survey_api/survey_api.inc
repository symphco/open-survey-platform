<?php

/**
    * Execute Web Service Call
*/

function opened_survey_api_execute() {
     global $user;

     if(!$user->uid){
         header('HTTP/1.1 401 Unauthorized');  
         $response = array("status_code" => 401);
         return;
     }

     $node_type = "survey";
     header('Content-Type: application/json');
      if(isset($_GET['since'])){
          $result = db_query("SELECT created, changed, nid, title, type, status FROM node WHERE type = :node_type AND changed >= :since", array(':node_type' => $node_type, ':since' => $_GET['since']));    
      }else{
          $result = db_query("SELECT created, changed, nid, title, type, status FROM node WHERE type = :node_type AND status = 1", array(':node_type' => $node_type));    
      }
      $data = $result->fetchAll(PDO::FETCH_ASSOC);
      watchdog('since value', var_export($_GET['since'], true));

      $new_data = array();
      foreach ($data as $d) {
      watchdog('data', var_export($d, true));
      $temp = array(
        "created" => $d["created"],
              "changed" => $d["changed"],
        "nid" => $d["nid"],
              "title" => $d["title"],
              "type" => $d["type"],
              "status" => $d["status"],
              "uri" => $GLOBALS['base_url'] . '/api/v1/surveys/' . $d["nid"]
            );
            array_push($new_data, $temp);
        }

        watchdog('data query', var_export($data, true));
        echo drupal_json_encode($new_data);
}

function survey_images(){
  $school_id = $_GET["school_id"];
  // $result = db_query("SELECT webform_submitted_data.data FROM webform_submitted_data INNER JOIN webform_component ON webform_submitted_data.cid = webform_component.cid WHERE webform_component.type = 'file' AND webform_component.nid = :nid AND webform_submitted_data.nid = :nid AND webform_submitted_data.cid = 4", array(':nid' => $nid));
  // $data = $result->fetchAll(PDO::FETCH_ASSOC);

  // $data_json = array();
  // for($i=0; $i<count($data); $i++){
  //   $file = file_load($data[$i]["data"]);
  //   watchdog('file content', var_export($file, true));
  //   $json_temp = array(
  //     "url" => $file->filename,
  //     "school_id" => ""
  //   );
  //   array_push($data_json, $json_temp);
  // }

  $result_school_id = db_query("SELECT cid FROM webform_component WHERE name = 'School ID'");  
  $data_school_id = $result_school_id->fetchAll(PDO::FETCH_ASSOC);

  for($i=0; $i<count($data_school_id); $i++){
    foreach ($data_school_id[$i] as $key => $value) {
      if($key == "cid"){
        $item = db_query("SELECT * FROM webform_submitted_data WHERE cid = :cid AND data = :school_id", array(":cid"=>$value, ":school_id"=>$school_id));
        $school_id_items = $item->fetchAll(PDO::FETCH_ASSOC);
      }
    }
  }

  $result_file = db_query("SELECT * FROM webform_component WHERE name = 'Photograph School Exterior'");
  $data_file = $result_file->fetchAll(PDO::FETCH_ASSOC);

  for($i=0; $i<count($data_file); $i++){
    foreach ($data_file[$i] as $key => $value) {
      if($key == "cid"){
        $item = db_query("SELECT * FROM webform_submitted_data WHERE cid = :cid AND nid = :nid", array(":cid"=>$value, ":nid"=> $data_file[$i]["nid"]));
        $data_file_items = $item->fetchAll(PDO::FETCH_ASSOC);
      }
    }  
  }

  watchdog('school id items', var_export($school_id_items, true));
  watchdog('file id items', var_export($data_file_items, true));

  $all_data = array();
  for($i=0; $i<count($school_id_items); $i++){
    for($o=0; $o<count($data_file_items); $o++){

      watchdog('sid school id', var_export($school_id_items[$i]["sid"], true));
      watchdog('sid file id', var_export($data_file_items[$o]["sid"], true));

      if($school_id_items[$i]["sid"] == $data_file_items[$o]["sid"]){

        watchdog('were in...', var_export($school_id_items[$i]["sid"], true));

        $file = file_load($data_file_items[$o]["data"]);
        $json_temp = array(
          "filename" => $file->filename,
          "school_id" => $school_id_items[$i]["data"]
        );
        array_push($all_data, $json_temp);


      }
    }
  }

  watchdog('all data', var_export($all_data, true));
  echo drupal_json_encode($all_data); 
}

function opened_survey_api_details($node){
    global $user;
  
    watchdog('METHOD', var_export($_SERVER['REQUEST_METHOD'], true));watchdog('METHOD', var_export($_SERVER['REQUEST_METHOD'], true));

    if ($_SERVER['REQUEST_METHOD'] === 'GET') {
        watchdog('node id', var_export($node, true));
        $node = $node->vid;
        $query = db_query("SELECT nid, type, title FROM node WHERE nid = :node_id", array(':node_id' => $node));
        $query = $query->fetch();

        $components = db_query("SELECT * FROM webform_component WHERE nid = :node_id", array(':node_id' => $node));
        $components = $components->fetchAll(PDO::FETCH_ASSOC);

        foreach ($components as &$component) {
          if($component["name"] == "PSGC"){
            $component["type"] = "psgc";
          }
          if($component["extra"]){
            $component["extra"] = unserialize( $component["extra"] );
          }
        }

        $body = db_query("SELECT entity_id, body_value, body_summary, body_format FROM field_data_body WHERE entity_id = :node_id", array(':node_id' => $node));
        $body = $body->fetch();


        watchdog('webform query', var_export($query, true));
        watchdog('webform components', var_export($components, true));

        $data = array('node' => $query, 'body' => $body, 'components' => $components);
        header('Content-Type: application/json');
        echo drupal_json_encode($data);

    }else  if($_SERVER['REQUEST_METHOD'] === 'POST'){
        watchdog('user ID', var_export($user->uid, true));

        if(!$user->uid){
          header('Content-Type: application/json');
          header('HTTP/1.1 401 Unauthorized');  
          $response = array("status_code" => 401);
          echo drupal_json_encode($response);
          return;
        }

        module_load_include('inc', 'webform', 'includes/webform.submissions');
        module_load_include('inc', 'webform', 'includes/webform.submissions');

        $nid = $node->nid;
        
        if($_SERVER["CONTENT_TYPE"] == "application/json"){
          $data = array();
          $input_data = file_get_contents("php://input");
          $json_data = json_decode(stripslashes($input_data), TRUE);

          foreach ($json_data as $key => $value){
            $n = str_replace("cid_", "", $key);
            $data[intval($n)] = array(0 => $value);
          }
          
        }else{
          $data = array();
          foreach ($_POST as $key => $value){
            watchdog('post keys', var_export($value, true));

            $n = str_replace("cid_", "", $key);
            $data[intval($n)] = array(0 => $value);
          }
        }


        foreach ($_FILES as $key => $value){
            watchdog('file keys', var_export($key, true));

            // 1. file save
            // $file = $value;
            // $file = file_load($value);
            // $file = file_save_upload($file->uri,$validators, 'public://webform/' .  $file->filename, FILE_EXISTS_REPLACE);
            // global $user;

            $validators = array();
            $saved_file = file_save_upload_custom($key, $validators, 'public://webform/', FILE_EXISTS_RENAME);

            // $filename = $_FILES[$key]['name'];

            // $file = new stdClass;
            // $file->uid = $user->uid;
            // $file->uri = 'public://webform/'.$filename;
            // $file->filename = $filename;
            // $file->filemime = $_FILES[$key]['tmp_name'];
            // $file->filesize = $_FILES[$key]['size'];
            // $file->status = 1;
            // $saved_file = file_save($file);

            // $upload_result = move_uploaded_file($filename, 'public://webform/');
            // $upload_result = file_destination('public://webform/' . $filename, FILE_EXISTS_RENAME);
            

            // watchdog('upload result', var_export($upload_result, true));
            watchdog('savefile content', var_export($saved_file, true));
            // 2. save file id to webform cid
            $n = str_replace("cid_", "", $key);
            $data[intval($n)] = array(0 => $saved_file->fid);

            // 3. call file_usage_add
            // file_usage_add($saved_file, "webform", 'node', $nid);
        }


        $time = REQUEST_TIME;
        if(isset($_POST["submission_timestamp"])){
            $time = $_POST["submission_timestamp"];
        }

        watchdog('submitted data', var_export($data, true));            

        $submission = (object) array(
            'nid' => $nid,
            'uid' => $user->uid,
            'submitted' => REQUEST_TIME,
            'is_draft' => FALSE,
            'data' => $data,
            'serial' => _webform_submission_serial_next_value($nid)
        );

        watchdog('webform submission', var_export($submission, true));
        $sid = webform_submission_insert($node, $submission);

        watchdog('webform submission id', var_export($sid, true));
        watchdog('webform submission node', var_export($node, true));

        $response = webform_get_submission($node->nid, $sid);
        header('Content-Type: application/json');
        header('HTTP/1.1 201 Created');  
        echo drupal_json_encode($response);

   }
}

function file_save_upload_custom($form_field_name, $validators = array(), $destination = FALSE, $replace = FILE_EXISTS_RENAME) {
  global $user;
  
  // Begin building file object.
  $file = new stdClass();
  $file->uid = $user->uid;
  $file->status = 0;
  $file->filename = trim(drupal_basename($_FILES[$form_field_name]['name']), '.');
  $file->uri = $_FILES[$form_field_name]['tmp_name'];
  $file->filemime = file_get_mimetype($file->filename);
  $file->filesize = $_FILES[$form_field_name]['size'];

  $extensions = '';
  if (isset($validators ['file_validate_extensions'])) {
    if (isset($validators ['file_validate_extensions'][0])) {
      // Build the list of non-munged extensions if the caller provided them.
      $extensions = $validators ['file_validate_extensions'][0];
    }
    else {
      // If 'file_validate_extensions' is set and the list is empty then the
      // caller wants to allow any extension. In this case we have to remove the
      // validator or else it will reject all extensions.
      unset($validators ['file_validate_extensions']);
    }
  }
  else {
    // No validator was provided, so add one using the default list.
    // Build a default non-munged safe list for file_munge_filename().
    $extensions = 'jpg jpeg gif png txt doc xls pdf ppt pps odt ods odp';
    $validators ['file_validate_extensions'] = array();
    $validators ['file_validate_extensions'][0] = $extensions;
  }

  if (!empty($extensions)) {
    // Munge the filename to protect against possible malicious extension hiding
    // within an unknown file type (ie: filename.html.foo).
    $file->filename = file_munge_filename($file->filename, $extensions);
  }

  // Rename potentially executable files, to help prevent exploits (i.e. will
  // rename filename.php.foo and filename.php to filename.php.foo.txt and
  // filename.php.txt, respectively). Don't rename if 'allow_insecure_uploads'
  // evaluates to TRUE.
  if (!variable_get('allow_insecure_uploads', 0) && preg_match('/\.(php|pl|py|cgi|asp|js)(\.|$)/i', $file->filename) && (substr($file->filename, -4) != '.txt')) {
    $file->filemime = 'text/plain';
    $file->uri .= '.txt';
    $file->filename .= '.txt';
    // The .txt extension may not be in the allowed list of extensions. We have
    // to add it here or else the file upload will fail.
    if (!empty($extensions)) {
      $validators ['file_validate_extensions'][0] .= ' txt';
      watchdog('savefile content', 'For security reasons, your upload has been renamed to');
      /*drupal_set_message(t('For security reasons, your upload has been renamed to %filename.', array('%filename' => $file->filename)));*/
    }
  }

  // If the destination is not provided, use the temporary directory.
  if (empty($destination)) {
    $destination = 'temporary://';
  }

  // Assert that the destination contains a valid stream.
  $destination_scheme = file_uri_scheme($destination);
  if (!$destination_scheme || !file_stream_wrapper_valid_scheme($destination_scheme)) {
    watchdog('savefile content', 'The file could not be uploaded, because the destination');
    /*drupal_set_message(t('The file could not be uploaded, because the destination %destination is invalid.', array('%destination' => $destination)), 'error');*/
    return FALSE;
  }

  /*$file->source = $form_field_name;*/
  // A URI may already have a trailing slash or look like "public://".
  if (substr($destination, -1) != '/') {
    $destination .= '/';
  }
  $file->destination = file_destination($destination . $file->filename, $replace);
  // If file_destination() returns FALSE then $replace == FILE_EXISTS_ERROR and
  // there's an existing file so we need to bail.
  if ($file->destination === FALSE) {
    /*drupal_set_message(t('The file %source could not be uploaded because a file by that name already exists in the destination %directory.', array('%source' => $form_field_name, '%directory' => $destination)), 'error');*/
    watchdog('savefile content', 'The file');
    return FALSE;
  }

  // Add in our check of the file name length.
  /*$validators ['file_validate_name_length'] = array();*/

  // Call the validation functions specified by this function's caller.
  $errors = file_validate($file, $validators);

  // Check for errors.
  /*if (!empty($errors)) {
    $message = t('The specified file %name could not be uploaded.', array('%name' => $file->filename));
    if (count($errors) > 1) {
      $message .= theme('item_list', array('items' => $errors));
    }
    else {
      $message .= ' ' . array_pop($errors);
    }
    form_set_error($form_field_name, $message);
    watchdog('savefile content', $message);
    return FALSE;
  }*/

  // Move uploaded files from PHP's upload_tmp_dir to Drupal's temporary
  // directory. This overcomes open_basedir restrictions for future file
  // operations.
  $file->uri = $file->destination;
  if (!drupal_move_uploaded_file($_FILES [$form_field_name]['tmp_name'], $file->uri)) {
    /*form_set_error($form_field_name, t('File upload error. Could not move uploaded file.'));*/
    watchdog('file', 'Upload error. Could not move uploaded file %file to destination %destination.', array('%file' => $file->filename, '%destination' => $file->uri));
    return FALSE;
  }

  // Set the permissions on the new file.
  drupal_chmod($file->uri);

  // If we are replacing an existing file re-use its database record.
  if ($replace == FILE_EXISTS_REPLACE) {
    $existing_files = file_load_multiple(array(), array('uri' => $file->uri));
    if (count($existing_files)) {
      $existing = reset($existing_files);
      $file->fid = $existing->fid;
    }
  }

  // If we made it this far it's safe to record this file in the database.
  if ($file = file_save($file)) {
    // Add file to the cache.
    /*$upload_cache [$form_field_name] = $file;*/
    return $file;
  }
  return FALSE;
}

/*function psgc_api_details(){
    $result = array();
    $new_data = array();

    if (($handle = fopen("sites/all/modules/opened_survey_api/psgc.csv", "r")) !== FALSE) {

  while (($data = fgetcsv($handle)) !== FALSE) {
            if(!isset( $new_data[$data[5]]))
            {
                $new_data[$data[5]] = array();
            }
    $new_data[$data[5]][$data[8]][$data[11]] = $data[10];
        }


        fclose($handle);
    }
    $json = drupal_json_encode($new_data);
    echo $json;
}*/


function psgc_api_details(){
    $new_data = array();
    $final_data = array();

    $final_data["ARMM"] = array();
    $final_data["ARMM"]["psgc"] = "150000000";
    $first = TRUE;

    if(isset($_GET['since'])){
      if (filemtime ( "sites/all/modules/opened_survey_api/psgc.csv" ) < intval($_GET['since'])){
        $json = drupal_json_encode(array());
        echo $json;
        return;
      }
    }

    if (($handle = fopen("sites/all/modules/opened_survey_api/psgc.csv", "r")) !== FALSE) {
        while (($data = fgetcsv($handle)) !== FALSE) {
            if ($first){
                $first = FALSE;
                continue;
            }
            
            if(!isset( $new_data[$data[5]]))
            {
                $new_data[$data[5]]["psgc"] = $data[4];
            }

            if(!isset( $new_data[$data[5]]["municipalities"][$data[8]]))
            {
                $new_data[$data[5]]["municipalities"][$data[8]]["psgc"] = $data[7];
            }
            
            $new_data[$data[5]]["municipalities"][$data[8]]["barangays"][$data[11]]["psgc"] = $data[10];
        }


        fclose($handle);
    }

    $final_data["ARMM"]["provinces"] = $new_data;

    $super_final_data = array();


    $super_final_data["name"] = "ARMM";
    $super_final_data["psgc"] = "150000000";
    $super_final_data["provinces"] = array();
    
    foreach ($new_data as $province_name => $province_object){
        $new_province_object = array();
        $new_province_object["name"] = $province_name;
        $new_province_object["psgc"] = $province_object["psgc"];
        $new_province_object["municipalities"] = array();

        foreach ($province_object["municipalities"] as $municipality_name => $municipality_object){
            $new_municipality_object = array();
            $new_municipality_object["name"] = $municipality_name;
            $new_municipality_object["psgc"] = $municipality_object["psgc"];
            $new_municipality_object["barangays"] = array();

            foreach ($municipality_object["barangays"] as $barangay_name => $barangay_object){
                $new_barangay_object = array();
                $new_barangay_object["name"] = $barangay_name;
                $new_barangay_object["psgc"] = $barangay_object["psgc"];
                array_push($new_municipality_object["barangays"], $new_barangay_object);    
            }
            array_push($new_province_object["municipalities"], $new_municipality_object);    
        }
        array_push($super_final_data["provinces"], $new_province_object);
    }

    $output_data = array();

    array_push($output_data, $super_final_data);

    $json = drupal_json_encode($output_data);
    echo $json;

     /*[{"name":"ARMM", "psgc": "150000000",
      "provinces":[
        {"name":"BASILAN (excluding Isabela City)", "psgc":"150700000",
         "municipalities":[
            {"name":"CITY OF LAMITAN", "psgc": "150702000",
             "barangays":[
                {"name":"Arco", "psgc": "150702001"},
                {"name":"Ba-as", "psgc": "150702002"}
             ]}
         ]}     
     ]}
    }]*/
}

function webform_submit_data(){
    module_load_include('inc', 'webform', 'includes/webform.submissions');
    $nid = 34047;
    $node = node_load($nid);

    watchdog('user ID', var_export($user->uid, true));  

    $data = array(
      1 => array(0 => "Firstname data"),
      2 => array(0 => "Profession data")
    );

    $submission = (object) array(
        'submitted' => REQUEST_TIME,
        'is_draft' => FALSE,
        'data' => $data,
        'serial' => _webform_submission_serial_next_value($node->nid)
    );

    watchdog('webform submission', var_export($submission, true));    
    webform_submission_insert($node, $submission);
}

function school_details(){
    $query = db_query("SELECT title, nid, field_coordinate_type_value, field_latlong_wkt, field_sch_province_value FROM node LEFT JOIN field_data_field_latlong ON node.nid = field_data_field_latlong.entity_id LEFT JOIN field_data_field_coordinate_type ON node.nid = field_data_field_coordinate_type.entity_id LEFT JOIN field_data_field_sch_province ON node.nid = field_data_field_sch_province.entity_id WHERE node.type = :school_type", array(':school_type' => 'school_profile'));
    $data = $query->fetchAll(PDO::FETCH_ASSOC);

    foreach ($data as &$d) {
        $new_data = str_replace("POINT (", "", $d['field_latlong_wkt']);
        $new_data = str_replace(")", "", $new_data);
        $new_data = explode(" ", $new_data);
        $d["lat"] = $new_data[1];
        $d["long"] = $new_data[0];
        $d["uri"] = $GLOBALS['base_url'] . "/node/" . $d["nid"];
    }
  
    $json = drupal_json_encode($data);
    echo $json;    
}


function download_csv(){
  // surveys
  if(isset($_GET['surveys'])){
    // output headers so that the file is downloaded rather than displayed
    header('Content-Type: text/csv; charset=utf-8');

    // create a file pointer connected to the output stream
    $output = fopen('php://output', 'w');

    fputcsv($output, array('Survey ID', 'Survey Title', 'Series of Questions'));

    watchdog('webform export', "1");    
    header('Content-Disposition: attachment; filename=surveys.csv');
    $query = db_query("SELECT nid, type, title FROM node WHERE type = :node_type", array(':node_type' => 'survey'));
    $query = $query->fetchAll(PDO::FETCH_ASSOC);


    foreach ($query as $survey) {
      watchdog('webform survey', var_export($survey, true));    
      $internal_array = array();

      if(isset($survey['title'])){
        array_push($internal_array, $survey['nid'], $survey['title']);
      }
      else {
        continue;
      }

      watchdog('webform result', "2");    

      $components = db_query("SELECT * FROM webform_component WHERE nid = :node_id", array(':node_id' => $survey['nid']));
      $components = $components->fetchAll(PDO::FETCH_ASSOC);

      foreach ($components as $component){
        array_push($internal_array, $component['name']);
      }

      watchdog('webform result', var_export($internal_array, true));    

      fputcsv($output, $internal_array);
    }

  }

  else if(isset($_GET['schools'])){
    // output headers so that the file is downloaded rather than displayed
    header('Content-Type: text/csv; charset=utf-8');

    // create a file pointer connected to the output stream
    $output = fopen('php://output', 'w');

    $internal_array = array();

    array_push($internal_array, 'School Node ID', 'School ID', 'School Name', 'MUNICODE', 'Municipality', 'Region', 'Province', 'Division', 'District', 'Address', 'School Head', 'Designation', 'Coordinate Type', 'Latitude', 'Longitude', 'Survey 1', 'Survey 2', 'School Type', 'Location Level', 'Location Source', 'Location Validated');

    fputcsv($output, $internal_array);
    
    watchdog('webform export', "1");    
    header('Content-Disposition: attachment; filename=schools.csv');
    $query = db_query("SELECT nid, field_school_id_value, field_muni_code_value, field_municipality_value, title, field_sch_region_value, field_sch_province_value, field_division_value, field_district_value, field_address_value, field_school_head_value, field_designation_value, field_coordinate_type_value, field_latlong_wkt, field_survey1_value, field_survey2_value, field_sch_type_value, field_location_level_value, field_location_source_value, field_location_validated_value FROM node 
      LEFT JOIN field_data_field_school_id ON node.nid = field_data_field_school_id.entity_id 
      LEFT JOIN field_data_field_muni_code ON node.nid = field_data_field_muni_code.entity_id 
      LEFT JOIN field_data_field_municipality ON node.nid = field_data_field_municipality.entity_id
      LEFT JOIN field_data_field_sch_region ON node.nid = field_data_field_sch_region.entity_id
      LEFT JOIN field_data_field_sch_province ON node.nid = field_data_field_sch_province.entity_id
      LEFT JOIN field_data_field_division ON node.nid = field_data_field_division.entity_id
      LEFT JOIN field_data_field_district ON node.nid = field_data_field_district.entity_id
      LEFT JOIN field_data_field_address ON node.nid = field_data_field_address.entity_id
      LEFT JOIN field_data_field_school_head ON node.nid = field_data_field_school_head.entity_id
      LEFT JOIN field_data_field_designation ON node.nid = field_data_field_designation.entity_id
      LEFT JOIN field_data_field_coordinate_type ON node.nid = field_data_field_coordinate_type.entity_id 
      LEFT JOIN field_data_field_latlong ON node.nid = field_data_field_latlong.entity_id 
      LEFT JOIN field_data_field_survey1 ON node.nid = field_data_field_survey1.entity_id 
      LEFT JOIN field_data_field_survey2 ON node.nid = field_data_field_survey2.entity_id 
      LEFT JOIN field_data_field_sch_type ON node.nid = field_data_field_sch_type.entity_id 
      LEFT JOIN field_data_field_location_level ON node.nid = field_data_field_location_level.entity_id 
      LEFT JOIN field_data_field_location_source ON node.nid = field_data_field_location_source.entity_id 
      LEFT JOIN field_data_field_location_validated ON node.nid = field_data_field_location_validated.entity_id 
      
      WHERE node.type = :school_type", array(':school_type' => 'school_profile'));
    $query = $query->fetchAll(PDO::FETCH_ASSOC);

    foreach ($query as $school) {  
      $internal_array = array();

      if(isset($school['title'])){
        $new_data = str_replace("POINT (", "", $school['field_latlong_wkt']);
        $new_data = str_replace(")", "", $new_data);
        $new_data = explode(" ", $new_data);
        $lat = $new_data[1];
        $long = $new_data[0];

        array_push($internal_array, $school['nid'], $school['field_school_id_value'], $school['title'], $school['field_muni_code_value'], $school['field_municipality_value'], $school['field_sch_region_value'], $school['field_sch_province_value'], $school['field_division_value'], $school['field_district_value'], $school['field_address_value'], $school['field_school_head_value'], $school['field_designation_value'], $school['field_coordinate_type_value'], $lat, $long, $school['field_survey1_value'], $school['field_survey2_value'], $school['field_sch_type_value'], $school['field_location_level_value'], $school['field_location_source_value'], $school['field_location_validated_value']);
      }
      else {
        continue;
      }

      fputcsv($output, $internal_array);
    }

  }
}


function results_api(){

  // get survey if id is provided. otherwise, get all surveys

  // loop through each survey and get all
  if(!isset($_GET['field'])){
    return;
  }

  if(isset($_GET['survey'])){
    $query = db_query("SELECT name, node.nid, data FROM node 
      LEFT JOIN webform_component ON node.nid = webform_component.nid 
      LEFT JOIN webform_submitted_data ON (node.nid = webform_submitted_data.nid AND webform_component.cid = webform_submitted_data.cid)
      WHERE webform_component.name = :component_name AND node.nid = :nid", array(':component_name' => $_GET['field'], ':nid' => $_GET['survey']));
    $data = $query->fetchAll(PDO::FETCH_ASSOC);
  }
  else {
    $query = db_query("SELECT name, node.nid, data FROM node 
      LEFT JOIN webform_component ON node.nid = webform_component.nid 
      LEFT JOIN webform_submitted_data ON (node.nid = webform_submitted_data.nid AND webform_component.cid = webform_submitted_data.cid)
      WHERE webform_component.name = :component_name", array(':component_name' => $_GET['field']));
    $data = $query->fetchAll(PDO::FETCH_ASSOC);
  }

  watchdog('webform RESULTS', "1"); 

  echo drupal_json_encode($data);

}



function school_detail_api(){

  // get survey if id is provided. otherwise, get all surveys

  // loop through each survey and get all
  if(!isset($_GET['school_id'])){
    return;
  }


  // get submission ID of the submission that has the value for the component named School ID to the given school_id
  /*$query = db_query("SELECT * FROM webform_submitted_data 
    LEFT JOIN webform_component ON (webform_submitted_data.cid = webform_component.cid AND webform_submitted_data.nid = webform_component.nid AND webform_component.name = :component_name AND webform_submitted_data.data = :school_id)
    LEFT JOIN webform_submissions ON webform_submissions.nid = webform_submitted_data.nid
    ORDER BY webform_submissions.submitted DESC", array(':component_name' => 'School ID', ':school_id' => $_GET['school_id']));
  $data = $query->fetchAll(PDO::FETCH_ASSOC);*/

  if(isset($_GET['survey_id'])){
    $query = db_query("SELECT a.sid FROM webform_submissions a INNER JOIN webform_submitted_data b ON a.sid = b.sid INNER JOIN webform_component c ON (b.cid = c.cid AND b.nid = c.nid) WHERE c.name = :component_name AND a.nid = :survey_id AND b.data = :school_id ORDER BY a.submitted DESC", array(':component_name' => 'School ID', ':school_id' => $_GET['school_id'], ':survey_id' => $_GET['survey_id']));
    $data = $query->fetch(PDO::FETCH_ASSOC);

    $query2 = db_query("SELECT webform_component.name, webform_submitted_data.data FROM webform_submitted_data 
      INNER JOIN webform_component ON webform_submitted_data.cid = webform_component.cid
      WHERE webform_submitted_data.sid = :sid AND webform_submitted_data.nid = :survey_id", array(':sid' => $data['sid'], ':survey_id' => $_GET['survey_id']));

    $data2 = $query2->fetchAll(PDO::FETCH_ASSOC);
    $temp = array(
      "name"=>"survey_id",
      "data"=> $_GET['survey_id']
    );
      
    array_push($data2, $temp);
    echo drupal_json_encode($data2);

  }else{
    $query = db_query("SELECT a.sid FROM webform_submissions a INNER JOIN webform_submitted_data b ON a.sid = b.sid INNER JOIN webform_component c ON (b.cid = c.cid AND b.nid = c.nid) WHERE c.name = :component_name AND b.data = :school_id ORDER BY a.submitted DESC", array(':component_name' => 'School ID', ':school_id' => $_GET['school_id']));
    $data = $query->fetch(PDO::FETCH_ASSOC);


    $query2 = db_query("SELECT name, data FROM webform_submitted_data 
      LEFT JOIN webform_component ON webform_submitted_data.cid = webform_component.cid
      WHERE webform_submitted_data.sid = :sid", array(':sid' => $data['sid']));  

    $data2 = $query2->fetchAll(PDO::FETCH_ASSOC);
    echo drupal_json_encode($data2);
  }

}


function schoolredirect_api(){
  $item = 0;
  if(isset($_GET['school_id'])){
    $item = $_GET['school_id'];
    $query = db_query("SELECT entity_id FROM field_data_field_school_id WHERE field_school_id_value = :school_id", array(':school_id' => $item));
    $data = $query->fetch(PDO::FETCH_ASSOC);
    if($data){
      $item = $data['entity_id'];
    }
  }

  header('Location: /node/'.$item);
  die();
}


?>

