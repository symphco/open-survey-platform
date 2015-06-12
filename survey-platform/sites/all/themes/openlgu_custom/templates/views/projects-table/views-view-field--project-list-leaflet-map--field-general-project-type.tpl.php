<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
?>
<?php 
if($output == "UD") {
	print "Undefined";
} else if ($output == "BC") {
	print "Bridge Concreting"; 
} else if ($output == "Boat") {
	print "Boat"; 
} else if ($output == "CB") {
	print "Capacity Building"; 
} else if ($output == "CIS") {
	print "Community/Small Impounding or Irrigation System"; 
} else if ($output == "CL") {
	print "Community Library"; 
} else if ($output == "DCC") {
	print "Day Care Center"; 
} else if ($output == "DRG") {
	print "Drainage"; 
} else if ($output == "EL") {
	print "Electrification"; 
} else if ($output == "FC") {
	print "Flood Control"; 
} else if ($output == "FS") {
	print "Feasibility Study"; 
} else if ($output == "HS") {
	print "Health Station"; 
} else if ($output == "LH") {
	print "Lighthouse"; 
} else if ($output == "LV") {
	print "Livelihood Center"; 
} else if ($output == "MPC") {
	print "Multi-Purpose Center"; 
} else if ($output == "MPV") {
	print "Multi-Purpose Vehicle"; 
} else if ($output == "NRM") {
	print "Natural Resource Management"; 
} else if ($output == "PHF") {
	print "Post-Harvest Facility"; 
} else if ($output == "PM") {
	print "Public Marker"; 
} else if ($output == "RC") {
	print "Road Concreting"; 
} else if ($output == "RFP") {
	print "Foot/Tire Path"; 
} else if ($output == "RR") {
	print "Road Rehabilitation"; 
} else if ($output == "RRC") {
	print "Road Rehabilitation and Concreting"; 
} else if ($output == "RW") {
	print "Road with Retaining Wall"; 
} else if ($output == "SB") {
	print "Schoolbuilding"; 
} else if ($output == "SP") {
	print "Spillways"; 
} else if ($output == "ST") {
	print "Sanitary Toilet"; 
} else if ($output == "SW") {
	print "Seawall"; 
} else if ($output == "SWMF") {
	print "Solid Waste Management Facility"; 
} else if ($output == "TC") {
	print "Training Center"; 
} else if ($output == "TH") {
	print "Tribal House/Shelter Upgrading"; 
} else if ($output == "WRF") {
	print "Wharf"; 
} else if ($output == "WS") {
	print "Water System";
} else {
	print $output; 
}
?>