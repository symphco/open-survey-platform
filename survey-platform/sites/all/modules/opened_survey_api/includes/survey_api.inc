<?php

/**
    * Execute Web Service Call
*/

function opened_survey_api_execute() {
    // Start building XML
    $response = "<?xml version="1.0" encoding="UTF-8"?><XmlResponse>"
    if (!isset($_GET["op"])) {
        // Return an error xml
        $response .= "<Error>Missing operation argument</Error>";

    } else {
        // Get "op" parameter from POST or GET requests
        $op = strtoupper($_POST["op"]);
        if (!isset($op)) {
            // Get name from GET request
            $op = strtoupper($_GET["op"]);
            $name = $_GET["name"];
        } else {
            // Get name from POST request
            $name = $_POST["name"];
        }
        if (!isset($name)) {
            // Return error XML
            $response .= "<Error>Name missing</Error>";
        } else {
            // Do something according to "op" argument
            switch ($op) {
                case "TEST":
                // Create TEST XML response
                $response .= "<TEST>Hello leonard!</TEST>";
                break;
            }
        }
    }
    // Finish XML
    $response .= "</XmlResponse>";
    // Make sure the response is understood as XML
    header('Content-Type: text/xml');
    // Send response back
    echo $response;
}

?>
