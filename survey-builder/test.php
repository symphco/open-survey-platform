<?php 
  echo phpinfo();

//  $curl = curl_init();
  //  curl_setopt ($curl, CURLOPT_URL, "http://www.php.net");
   // curl_exec ($curl);
   // curl_close ($curl)
/*

$ch = curl_init();
  $skipper = "luxury assault recreational vehicle";
  $fields = array( 'penguins'=>$skipper, 'bestpony'=>'rainbowdash');
  $postvars = '';
  foreach($fields as $key=>$value) {
    $postvars .= $key . "=" . $value . "&";
  }
  $url = "http://www.google.com";
  curl_setopt($ch,CURLOPT_URL,$url);
  curl_setopt($ch,CURLOPT_POST, 1);                //0 for a get request
  curl_setopt($ch,CURLOPT_POSTFIELDS,$postvars);
  curl_setopt($ch,CURLOPT_RETURNTRANSFER, true);
  curl_setopt($ch,CURLOPT_CONNECTTIMEOUT ,3);
  curl_setopt($ch,CURLOPT_TIMEOUT, 20);
  $response = curl_exec($ch);
  print "curl response is:" . $response;
  curl_close ($ch);

function httpGet($url)
{
    $ch = curl_init();  
 
    curl_setopt($ch,CURLOPT_URL,$url);
    curl_setopt($ch,CURLOPT_RETURNTRANSFER,true);
//  curl_setopt($ch,CURLOPT_HEADER, false); 
 
    $output=curl_exec($ch);
 
    curl_close($ch);
    return $output;
}
 
echo httpGet("http://hayageek.com");

*/

if(is_callable('curl_init')){
   echo "Enabled";
}
else
{
   echo "Not enabled";
}

?>
