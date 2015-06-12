<?php
# include parseCSV class.
require_once('parsecsv.lib.php');


# create new parseCSV object.
$csv = new parseCSV();
 
$csv->auto('_photos.csv');


$servername = "localhost";
$username = "root";
$password = "xxxxx";
$dbname = "openeddb";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
      die("Connection failed: " . $conn->connect_error);
} 

$services_url = 'http://opened.opengov.ph/appendpoint';

// REST Server URL for auth
$request_url = $services_url . '/user/login';

// User data
$user_data = array(
    'username' => 'xxxx',
    'password' => 'xxxx',
);

$user_data = http_build_query($user_data);

$curl = curl_init($request_url);
curl_setopt($curl, CURLOPT_HTTPHEADER, array('Accept: application/json')); // Accept JSON response
curl_setopt($curl, CURLOPT_POST, 1); // Do a regular HTTP POST
curl_setopt($curl, CURLOPT_POSTFIELDS, $user_data); // Set POST data
curl_setopt($curl, CURLOPT_HEADER, FALSE); // Ask to not return Header
curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE);
curl_setopt($curl, CURLOPT_FAILONERROR, TRUE);

$response = curl_exec($curl);
$http_code = curl_getinfo($curl, CURLINFO_HTTP_CODE);

// Check if login was successful
if ($http_code == 200) {
  $logged_user = json_decode($response);
}
else {
  // Get error msg
  $http_message = curl_error($curl);
  die('Auth error ' . $http_message);
}

// Define cookie session
// this is the key ingredient taken during login
// this will be added when a user create or submits a form

$cookie_session = $logged_user->session_name . '=' . $logged_user->sessid;

foreach($csv->data as $item) {
  $sql = "SELECT entity_id FROM field_data_field_school_id where field_school_id_value=". $item['school_id'];
  $result = $conn->query($sql);

  if ($result->num_rows > 0) {
      // output data of each row
          while($row = $result->fetch_assoc()) {
            exec('curl POST -H "Content-Type: multipart/form-data" -H "Accept: application/json" -b cookies.txt --form "field_name=field_images" --form "files[files]=@/var/www/webroot/open-ed/scripts/opened_images/' . $item['structure']. '_' . $item['school_id'] . '_' . $item['filename'] . '" --form "attach=1" "http://opened.opengov.ph/appendpoint/node/' . $row["entity_id"] . '/attach_file"');

          }
  } else {
             echo "0 results";
  }
  //print $sql;
}




$conn->close();





?>

