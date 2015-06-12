<?php

/**
 * @file
 * Template to display a view as a table.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $header: An array of header labels keyed by field id.
 * - $caption: The caption for this table. May be empty.
 * - $header_classes: An array of header classes keyed by field id.
 * - $fields: An array of CSS IDs to use for each field id.
 * - $classes: A class or classes to apply to the table, based on settings.
 * - $row_classes: An array of classes to apply to each row, indexed by row
 *   number. This matches the index in $rows.
 * - $rows: An array of row items. Each row is an array of content.
 *   $rows are keyed by row number, fields within rows are keyed by field ID.
 * - $field_classes: An array of classes to apply to each field, indexed by
 *   field id, then row number. This matches the index in $rows.
 * @ingroup views_templates
 */
?>
<?php // $i=0; ?>

<?php // foreach ($rows as $row_count => $row): ?>


<table class="table_row">
  <thead>
    <tr>
      <th>YEAR</th>
      <th>SCHOOL ID</th>
      <th>SCHOOL TYPE</th>
      <th># STUDENTS</th>
      <th># TEACHERS</th>
      <th>TEACHERS ATTENDANCE</th>
      <th>STUDENTS ATTENDANCE</th>
    </tr>  
  </thead>
  <tbody>
    <tr>
        <td>2014</td>
        <td>01238</td>
        <td>Lorem ipsum</td>
        <td>270</td>
        <td>10</td>
        <td>72.93%</td>
        <td>90%</td>
    </tr>
    <tr>
        <td>2014</td>
        <td>23543</td>
        <td>Aenean commodo</td>
        <td>100</td>
        <td>18</td>
        <td>75.8%</td>
        <td>67.0%</td>
    </tr>
    <tr>
        <td>2014</td>
        <td>01238</td>
        <td>Aenean massa</td>
        <td>129</td>
        <td>5</td>
        <td>60.73%</td>
        <td>100%</td>
    </tr>
    <tr>
        <td>2014</td>
        <td>01238</td>
        <td>Ligula eget</td>
        <td>60</td>
        <td>9</td>
        <td>89.22%</td>
        <td>69.9%</td>
    </tr>
    
    <!-- <tr>
        <td><?php print $rows[$i]["value_13"] ?></td>
        <td><?php print $rows[$i]["value_14"] ?></td>
        <td><?php print $rows[$i]["value_12"] ?></td>
        <td><?php print $rows[$i]["value_4"] ?></td>
        <td><?php print $rows[$i]["value_6"] ?></td>
        <td>

          <?php 
            $results = $rows[$i]["value_15"] * 100;
            print round($results, 2); 
            ?>%
        </td>
        <td id="student_present_<?php print $rows[$i]['value_14'] ?>">
          <script type="text/javascript">
            function student_present(school_id){
              jQuery.getJSON('/api/v1/schooldetails?school_id='+school_id, function(data){
                  var has_data = false;
                  for(var i=0; i<data.length; i++){

                    if(data[i]["name"] == "Student attendance"){
                      has_data = true;
                      var result = data[i]["data"] * 100;
                      jQuery("#student_present_" + school_id).html(result.toFixed(2) + "%");  
                    
                    }
                  }

                  if(!has_data){
                    jQuery("#student_present_" + school_id).html("-");  
                  }
              });
            }
            student_present(<?php print $rows[$i]['value_14'] ?>);
          </script>
        </td>
    </tr>
 -->
    <!-- <tr>
      <td colspan="7" class="table_content">
          <?php foreach ($row as $field => $content): ?>
            <?php if(!in_array($field, array("value_13", "value_14", "value", "value_12", "value_4", "value_6", "value_15", "value_5", "nid"))): ?>
              <?php print $content; ?>
            <?php endif; ?>
          <?php endforeach; ?>
      </td>
    </tr> -->
  </tbody>
</table>

  <?php $i++; ?>
<?php // endforeach; ?>

<script type="text/javascript">
  jQuery(".windowvalue").each(function(e){
    value = jQuery(this).html().replace("1:", "");
    jQuery(this).html(value);
  });
  

</script>


