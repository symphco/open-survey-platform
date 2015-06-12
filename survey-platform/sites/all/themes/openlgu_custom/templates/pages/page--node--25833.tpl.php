    <div class="main_content">
     <div class="container">
         <div class="row-fluid content page-hdr">
            <div class="span12">
                  <div class="social">
                    <a><img src="http://localhost/wb-opengov-armmdata/sites/all/themes/openlgu_custom/images/service-links/facebook.png"></a>
                    <a><img src="http://localhost/wb-opengov-armmdata/sites/all/themes/openlgu_custom/images/service-links/twitter.png"></a>
                    <a><img src="http://localhost/wb-opengov-armmdata/sites/all/themes/openlgu_custom/images/service-links/forward.png"></a>

                  </div>


             <h1>Lorem ipsum dolor sit amet</h1>
             <?php print render($tabs); ?>
             <select style="float:right" id="surveyList" name="list_of_survey">
             </select>
             </div>
        </div>
         <div class="row-fluid data-pg content">
             <div class="span12">
        
            <!--Horizontal Tab-->
                <?php print $messages; ?>
                <?php print render($page['help']); ?>
                <?php
                    $survey_id = "34057";
                    if(isset($_GET["survey"])){
                        $survey_id = $_GET["survey"];
                    }
                ?>

<!--                <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?> -->
                    <div class="row-fluid"><p class="intro-sentence">Duis autem vel eum iriure dolor in hendrerit in vulputate velit esse molestie consequat, vel illum dolore eu feugiat nulla facilisis at vero eros et accumsan et iusto odio dignissim qui blandit praesent luptatum zzril delenit augue duis dolore te feugait nulla facilisi</p></div>
                    <div class="row-fluid overview-content">
                    <div class="span12"> 
                        <h2>Duis Autem Vel</h2>
                        <div id="container1" class="graphWrap" style="margin-bottom: 30px;"></div>
                        <script type="text/javascript">
                            jQuery(function () {
                                
                                
                                jQuery.getJSON('/api/v1/schools', function(data){
                                    window.school_count = 0;
                                    water_yes = null;
                                    water_no = null;
                                    water_unknown = null;
                                    water_yes_percentage = null;
                                    water_no_percentage = null
                                    water_unknown_percentage = null
                                    window.school_count = data.length;
                                    jQuery.getJSON('/api/v1/results?survey=<?php print $survey_id; ?>&field=Does%20the%20school%20have%20access%20to%20clean/drinking%20water?', function(data){
                                        for(var i=0; i<data.length; i++){
                                            if(data[i]["data"] == "yes"){
                                                water_yes += 1;    
                                            } else if(data[i]["data"] == "no"){
                                                water_no += 1;
                                            }
                                        }
                                        water_unknown = window.school_count - water_yes - water_no;
                                        water_yes_percentage = water_yes / window.school_count * 100;
                                        water_no_percentage = water_no / window.school_count * 100;
                                        water_unknown_percentage = water_unknown / window.school_count * 100;

                                        print_graph1()
                                    });



                                    electricity_yes = null;
                                    electricity_no = null;
                                    electricity_unknown = null;
                                    electricity_yes_percentage = null;
                                    electricity_no_percentage = null
                                    electricity_unknown_percentage = null
                                    jQuery.getJSON('/api/v1/results?survey=<?php print $survey_id; ?>&field=Does%20this%20school%20have%20access%20to%20electricity', function(data){
                                        for(var i=0; i<data.length; i++){
                                            if(data[i]["data"] == "yes"){
                                                electricity_yes += 1;
                                            } else if(data[i]["data"] == "no"){
                                                electricity_no += 1;
                                            }
                                        }
                                        electricity_unknown = window.school_count - electricity_yes - electricity_no;
                                        electricity_yes_percentage = electricity_yes / window.school_count * 100;
                                        electricity_no_percentage = electricity_no / window.school_count * 100;
                                        electricity_unknown_percentage = electricity_unknown / window.school_count * 100;
                                        print_graph2()
                                    });


                                    walls_dirt = null;
                                    walls_non_dirt = null;
                                    walls_unknown = null;
                                    walls_dirt_percentage = null;
                                    walls_non_dirt_percentage = null
                                    walls_unknown_percentage = null
                                    jQuery.getJSON('/api/v1/results?survey=<?php print $survey_id; ?>&field=Wall%20condition', function(data){
                                        for(var i=0; i<data.length; i++){
                                            if(data[i]["data"] == "Non-Dirt"){
                                                walls_dirt += 1;
                                            } else if(data[i]["data"] == "Dirt"){
                                                walls_non_dirt += 1;
                                            }
                                        }
                                        walls_unknown = window.school_count - walls_non_dirt - walls_dirt;
                                        walls_non_dirt_percentage = walls_non_dirt / window.school_count * 100;
                                        walls_dirt_percentage = walls_dirt / window.school_count * 100;
                                        walls_unknown_percentage = walls_unknown / window.school_count * 100;
                                        print_graph3()
                                    });


                                    windows_good = null;
                                    windows_poor = null;
                                    windows_absent = null;
                                    windows_unknown = null;
                                    windows_good_percentage = null;
                                    windows_poor_percentage = null;
                                    windows_absent_percentage = null;
                                    windows_unknown_percentage = null;
                                    jQuery.getJSON('/api/v1/results?survey=<?php print $survey_id; ?>&field=Window%20condition', function(data){
                                        for(var i=0; i<data.length; i++){
                                            if(data[i]["data"] == "Good"){
                                                windows_good += 1;
                                            } else if(data[i]["data"] == "Poor"){
                                                windows_poor += 1;
                                            } else if(data[i]["data"] == "Absent"){
                                                windows_absent += 1;
                                            }
                                        }
                                        windows_unknown = window.school_count - windows_good - windows_poor - windows_absent;
                                        windows_good_percentage = windows_good / window.school_count * 100;
                                        windows_poor_percentage = windows_poor / window.school_count * 100;
                                        windows_absent_percentage = windows_absent / window.school_count * 100;
                                        windows_unknown_percentage = windows_unknown / window.school_count * 100;

                                        print_graph4()
                                    });
                                    

                                    library_yes = null;
                                    library_no = null;
                                    library_unknown = null;
                                    library_yes_percentage = null;
                                    library_no_percentage = null
                                    library_unknown_percentage = null
                                    jQuery.getJSON('/api/v1/results?survey=<?php print $survey_id; ?>&field=Access%20to%20library', function(data){
                                        for(var i=0; i<data.length; i++){
                                            if(data[i]["data"] == "yes"){
                                                library_yes += 1;
                                            } else if(data[i]["data"] == "no"){
                                                library_no += 1;
                                            }
                                        }
                                        library_unknown = window.school_count - library_yes - library_no;
                                        library_yes_percentage = library_yes / window.school_count * 100;
                                        library_no_percentage = library_no / window.school_count * 100;
                                        library_unknown_percentage = library_unknown / window.school_count * 100;
                                        print_graph5()
                                    });

                                    laboratory_yes = null;
                                    laboratory_no = null;
                                    laboratory_unknown = null;
                                    laboratory_yes_percentage = null;
                                    laboratory_no_percentage = null
                                    laboratory_unknown_percentage = null
                                    jQuery.getJSON('/api/v1/results?survey=<?php print $survey_id; ?>&field=Access%20to%20laboratory', function(data){
                                        for(var i=0; i<data.length; i++){
                                            if(data[i]["data"] == "yes"){
                                                laboratory_yes += 1;
                                            } else if(data[i]["data"] == "no"){
                                                laboratory_no += 1;
                                            }
                                        }
                                        laboratory_unknown = window.school_count - laboratory_yes - laboratory_no;
                                        laboratory_yes_percentage = laboratory_yes / window.school_count * 100;
                                        laboratory_no_percentage = laboratory_no / window.school_count * 100;
                                        laboratory_unknown_percentage = laboratory_unknown / window.school_count * 100;
                                        print_graph6()
                                    });
                                });

                                
                                function print_graph1(){
                                    if(water_yes_percentage == null || water_no_percentage == null){
                                        return;
                                    }
                                    jQuery('.graphWater').highcharts({
                                        chart: { type: 'column' },
                                        title: { text: '' },
                                        subtitle: { text: '' },
                                        xAxis: {
                                            categories: [
                                                'Water',
                                            ]
                                        },
                                        yAxis: {
                                            min: 0,
                                            max: 100,
                                            title: { text: '' }
                                        },
                                        tooltip: {
                                            headerFormat: '<span style="font-size:10px">{point.key}</span><table>',
                                            pointFormat: '<tr><td style="color:{series.color};padding:0">{series.name}: </td>' +
                                                '<td style="padding:0"><b>{point.y:.1f}%</b></td></tr>',
                                            footerFormat: '</table>',
                                            shared: true,
                                            useHTML: true
                                        },
                                        plotOptions: {
                                            column: {
                                                pointPadding: 0.2,
                                                borderWidth: 0
                                            }
                                        },
                                        legend: {
                                            layout: 'horizontal',
                                            align: 'left',
                                            verticalAlign: 'top',
                                            floating: false,
                                            enabled: false,
                                        },
                                        series: [{
                                            name: 'Yes',
                                            data: [water_yes_percentage]
                                        },
                                        {
                                            name: 'No',
                                            data: [water_no_percentage]
                                        },
                                        {
                                            name: 'Data Unavailable',
                                            data: [water_unknown_percentage]
                                        }]
                                    });
                                    
                                }

                                function print_graph2(){
                                    if(electricity_yes_percentage == null || electricity_no_percentage == null){
                                        return;
                                    }
                                    jQuery('.graphElectricity').highcharts({
                                        chart: { type: 'column' },
                                        title: { text: '' },
                                        subtitle: { text: '' },
                                        xAxis: {
                                            categories: [
                                                'Electricity',
                                            ]
                                        },
                                        yAxis: {
                                            min: 0,
                                            max: 100,
                                            title: { text: '' }
                                        },
                                        tooltip: {
                                            headerFormat: '<span style="font-size:10px">{point.key}</span><table>',
                                            pointFormat: '<tr><td style="color:{series.color};padding:0">{series.name}: </td>' +
                                                '<td style="padding:0"><b>{point.y:.1f}%</b></td></tr>',
                                            footerFormat: '</table>',
                                            shared: true,
                                            useHTML: true
                                        },
                                        plotOptions: {
                                            column: {
                                                pointPadding: 0.2,
                                                borderWidth: 0
                                            }
                                        },
                                        legend: {
                                            layout: 'horizontal',
                                            align: 'left',
                                            verticalAlign: 'top',
                                            floating: false,
                                            enabled: false,
                                        },
                                        series: [{
                                            name: 'Yes',
                                            data: [electricity_yes_percentage]
                                        },
                                        {
                                            name: 'No',
                                            data: [electricity_no_percentage]
                                        },
                                        {
                                            name: "Data Unavailable",
                                            data: [electricity_unknown_percentage]
                                        }]
                                    });
                                }

                                function print_graph3(){
                                    if(walls_non_dirt_percentage == null || walls_dirt_percentage == null){
                                        return;
                                    }
                                    jQuery('.graphWalls').highcharts({
                                        chart: { type: 'column' },
                                        title: { text: '' },
                                        subtitle: { text: '' },
                                        xAxis: {
                                            categories: [
                                                'Walls',
                                            ]
                                        },
                                        yAxis: {
                                            min: 0,
                                            max: 100,
                                            title: { text: '' }
                                        },
                                        tooltip: {
                                            headerFormat: '<span style="font-size:10px">{point.key}</span><table>',
                                            pointFormat: '<tr><td style="color:{series.color};padding:0">{series.name}: </td>' +
                                                '<td style="padding:0"><b>{point.y:.1f}%</b></td></tr>',
                                            footerFormat: '</table>',
                                            shared: true,
                                            useHTML: true
                                        },
                                        plotOptions: {
                                            column: {
                                                pointPadding: 0.2,
                                                borderWidth: 0
                                            }
                                        },
                                        legend: {
                                            layout: 'horizontal',
                                            align: 'left',
                                            verticalAlign: 'top',
                                            floating: false,
                                            enabled: false,
                                        },
                                        series: [{
                                            name: 'Non-Dirt',
                                            data: [walls_non_dirt_percentage]
                                        },
                                        {
                                            name: 'Dirt',
                                            data: [walls_dirt_percentage]
                                        },
                                        {
                                            name: 'Data Unavailable',
                                            data: [walls_unknown_percentage]
                                        }]
                                    });
                                }

                                function print_graph4(){

                                    if(windows_good_percentage == null || windows_poor_percentage == null || windows_absent_percentage == null || windows_unknown_percentage == null){
                                        return;
                                    }
                                    jQuery('.graphWindows').highcharts({
                                        chart: { type: 'column' },
                                        title: { text: '' },
                                        subtitle: { text: '' },
                                        xAxis: {
                                            categories: [
                                                'Windows',
                                            ]
                                        },
                                        yAxis: {
                                            min: 0,
                                            max: 100,
                                            title: { text: '' }
                                        },
                                        tooltip: {
                                            headerFormat: '<span style="font-size:10px">{point.key}</span><table>',
                                            pointFormat: '<tr><td style="color:{series.color};padding:0">{series.name}: </td>' +
                                                '<td style="padding:0"><b>{point.y:.1f}%</b></td></tr>',
                                            footerFormat: '</table>',
                                            shared: true,
                                            useHTML: true
                                        },
                                        plotOptions: {
                                            column: {
                                                pointPadding: 0.2,
                                                borderWidth: 0
                                            }
                                        },
                                        legend: {
                                            layout: 'horizontal',
                                            align: 'left',
                                            verticalAlign: 'top',
                                            floating: false,
                                            enabled: false,
                                        },
                                        series: [{
                                            name: 'Good',
                                            data: [windows_good_percentage]
                                        },
                                        {
                                            name: 'Poor',
                                            data: [windows_poor_percentage]
                                        },
                                        {
                                            name: 'Absent',
                                            data: [windows_absent_percentage]
                                        },
                                        {
                                            name: 'Unknown',
                                            data: [windows_unknown_percentage]
                                        }]
                                    });
                                }

                                function print_graph5(){
                                    if(library_yes_percentage == null || library_no_percentage == null){
                                        return;
                                    }
                                    jQuery('.graphLibrary').highcharts({
                                        chart: { type: 'column' },
                                        title: { text: '' },
                                        subtitle: { text: '' },
                                        xAxis: {
                                            categories: [
                                                'Library',
                                            ]
                                        },
                                        yAxis: {
                                            min: 0,
                                            max: 100,
                                            title: { text: '' }
                                        },
                                        tooltip: {
                                            headerFormat: '<span style="font-size:10px">{point.key}</span><table>',
                                            pointFormat: '<tr><td style="color:{series.color};padding:0">{series.name}: </td>' +
                                                '<td style="padding:0"><b>{point.y:.1f}%</b></td></tr>',
                                            footerFormat: '</table>',
                                            shared: true,
                                            useHTML: true
                                        },
                                        plotOptions: {
                                            column: {
                                                pointPadding: 0.2,
                                                borderWidth: 0
                                            }
                                        },
                                        legend: {
                                            layout: 'horizontal',
                                            align: 'left',
                                            verticalAlign: 'top',
                                            floating: false,
                                            enabled: false,
                                        },
                                        series: [{
                                            name: 'Yes',
                                            data: [library_yes_percentage]
                                        },
                                        {
                                            name: 'No',
                                            data: [library_no_percentage]
                                        },
                                        {
                                            name: 'Data Unavailable',
                                            data: [library_unknown_percentage]
                                        }]
                                    });
                                }

                                function print_graph6(){
                                    jQuery('.graphLaboratory').highcharts({
                                        chart: { type: 'column' },
                                        title: { text: '' },
                                        subtitle: { text: '' },
                                        xAxis: {
                                            categories: [
                                                'Laboratory',
                                            ]
                                        },
                                        yAxis: {
                                            min: 0,
                                            max: 100,
                                            title: { text: '' }
                                        },
                                        tooltip: {
                                            headerFormat: '<span style="font-size:10px">{point.key}</span><table>',
                                            pointFormat: '<tr><td style="color:{series.color};padding:0">{series.name}: </td>' +
                                                '<td style="padding:0"><b>{point.y:.1f}%</b></td></tr>',
                                            footerFormat: '</table>',
                                            shared: true,
                                            useHTML: true
                                        },
                                        plotOptions: {
                                            column: {
                                                pointPadding: 0.2,
                                                borderWidth: 0
                                            }
                                        },
                                        legend: {
                                            layout: 'horizontal',
                                            align: 'left',
                                            verticalAlign: 'top',
                                            floating: false,
                                            enabled: false,
                                        },
                                        series: [{
                                            name: 'Yes',
                                            data: [laboratory_yes_percentage]
                                        },
                                        {
                                            name: 'No',
                                            data: [laboratory_no_percentage]
                                        },
                                        {
                                            name: 'Data Unavailable',
                                            data: [laboratory_unknown_percentage]
                                        }]
                                    });
                                }
                                
                            });
                        </script>

                        <div class="graph_wrapper" style="padding-bottom:30px">
                            <div class="colWrap">
                                <div class="graphWater"></div><!-- graphWater -->
                            </div>
                            <div class="colWrap">
                                <div class="graphElectricity"></div><!-- graphElectricity -->
                            </div>
                            <div class="colWrap">
                                <div class="graphWalls"></div><!-- graphWalls -->
                            </div>
                            <div class="clear"></div>
                            <div class="colWrap">
                                <div class="graphWindows"></div><!-- graphWindows -->
                            </div>
                            <div class="colWrap">
                                <div class="graphLibrary"></div><!-- graphLibrary -->
                            </div>
                            <div class="colWrap clrBorder">
                                <div class="graphLaboratory"></div><!-- graphLaboratory -->
                            </div>
                            <div class="clear"></div>
                        </div>

                        <h2>Eum Iriure Dolor</h2>
                        <div id="container2" class="graphWrap" style="margin-bottom: 60px;"></div>
                        <script>
                            jQuery(function () {

                                var a_a = 0; 
                                var a_b = 0; 
                                var a_c = 0; 
                                var a_d = 0; 

                                var b_a = 0; 
                                var b_b = 0; 
                                var b_c = 0; 
                                var b_d = 0; 
                                
                                var c_a = 0; 
                                var c_b = 0; 
                                var c_c = 0; 
                                var c_d = 0; 

                                var d_a = 0; 
                                var d_b = 0; 
                                var d_c = 0; 
                                var d_d = 0; 

                                var e_a = 0; 
                                var e_b = 0; 
                                var e_c = 0; 
                                var e_d = 0; 

                            

                                // teachin materials
                                jQuery.getJSON('/api/v1/results?survey=<?php print $survey_id; ?>&field=6.%20Need%20other%20teaching%20materials', function(data){
                                    for(var i=0; i < data.length; i++){

                                        if(data[i]["data"] == "One of biggest challenges"){
                                            a_a += 1;
                                        }
                                        if(data[i]["data"] == "Significant challenge"){
                                            a_b += 1;
                                        }
                                        if(data[i]["data"] == "Minor challenge"){
                                            a_c += 1;
                                        }
                                        if(data[i]["data"] == "Not a challenge"){
                                            a_d += 1;
                                        }
                                    }
                                    print_challenges_graph();
                                });

                                // qualified teachers
                                jQuery.getJSON('/api/v1/results?survey=<?php print $survey_id; ?>&field=2.%20Need%20better%20qualified%20teachers', function(data){
                                    for(var i=0; i < data.length; i++){

                                        if(data[i]["data"] == "One of biggest challenges"){
                                            b_a += 1;
                                        }
                                        if(data[i]["data"] == "Significant challenge"){
                                            b_b += 1;
                                        }
                                        if(data[i]["data"] == "Minor challenge"){
                                            b_c += 1;
                                        }
                                        if(data[i]["data"] == "Not a challenge"){
                                            b_d += 1;
                                        }
                                    }
                                    print_challenges_graph();
                                });

                                // support personnel
                                jQuery.getJSON('/api/v1/results?survey=<?php print $survey_id; ?>&field=3.%20Need%20support%20personnel', function(data){
                                    for(var i=0; i < data.length; i++){

                                        if(data[i]["data"] == "One of biggest challenges"){
                                            c_a += 1;
                                        }
                                        if(data[i]["data"] == "Significant challenge"){
                                            c_b += 1;
                                        }
                                        if(data[i]["data"] == "Minor challenge"){
                                            c_c += 1;
                                        }
                                        if(data[i]["data"] == "Not a challenge"){
                                            c_d += 1;
                                        }
                                    }
                                    print_challenges_graph();
                                });

                                // more classrooms
                                jQuery.getJSON('/api/v1/results?survey=<?php print $survey_id; ?>&field=7.%20Need%20more%20classrooms%20(large%20PTR)', function(data){
                                    for(var i=0; i < data.length; i++){

                                        if(data[i]["data"] == "One of biggest challenges"){
                                            d_a += 1;
                                        }
                                        if(data[i]["data"] == "Significant challenge"){
                                            d_b += 1;
                                        }
                                        if(data[i]["data"] == "Minor challenge"){
                                            d_c += 1;
                                        }
                                        if(data[i]["data"] == "Not a challenge"){
                                            d_d += 1;
                                        }
                                    }
                                    print_challenges_graph();
                                });

                                // more textbooks
                                jQuery.getJSON('/api/v1/results?survey=<?php print $survey_id; ?>&field=4.%20Need%20more%20textbooks', function(data){
                                    for(var i=0; i < data.length; i++){

                                        if(data[i]["data"] == "One of biggest challenges"){
                                            e_a += 1;
                                        }
                                        if(data[i]["data"] == "Significant challenge"){
                                            e_b += 1;
                                        }
                                        if(data[i]["data"] == "Minor challenge"){
                                            e_c += 1;
                                        }
                                        if(data[i]["data"] == "Not a challenge"){
                                            e_d += 1;
                                        }
                                    }
                                    print_challenges_graph();
                                });

                                function print_challenges_graph(){
                                    if(a_a == 0 || a_b == 0 || a_c == 0 || a_d == 0 || b_a == 0 || b_b == 0 || b_c == 0 || b_d == 0 || c_a == 0 || c_b == 0 || c_c == 0 || c_d == 0 || d_a == 0 || d_b == 0 || d_c == 0 || d_d == 0 || e_a == 0 || e_b == 0 || e_c == 0 || e_d == 0){
                                        return;
                                    };

                                    jQuery('#container2').highcharts({
                                        chart: {
                                            type: 'column'
                                        },
                                        title: {
                                            text: ''
                                        },
                                        subtitle: {
                                            text: ''
                                        },
                                        xAxis: {
                                            categories: [
                                                'Need other teaching materials',
                                                'Need better qualified teachers',
                                                'Need support personnel',
                                                'Need more classrooms',
                                                'Need more textbooks'
                                            ]
                                        },
                                        yAxis: {
                                            min: 0,
                                            max: 100,
                                            title: {
                                                text: ''
                                            }
                                        },
                                        tooltip: {
                                            headerFormat: '<span style="font-size:10px">{point.key}</span><table>',
                                            pointFormat: '<tr><td style="color:{series.color};padding:0">{series.name}: </td>' +
                                                '<td style="padding:0"><b>{point.y:.1f}%</b></td></tr>',
                                            footerFormat: '</table>',
                                            shared: true,
                                            useHTML: true
                                        },
                                        plotOptions: {
                                            column: {
                                                pointPadding: 0.2,
                                                borderWidth: 0
                                            }
                                        },
                                        series: [ {
                                            name: 'One of the Biggest Challenge',
                                            data: [a_a, b_a, c_a, d_a, e_a]

                                        }, {
                                            name: 'Significant Challenge',
                                            data: [a_b, b_b, c_b, d_b, e_b]

                                        }, {
                                            name: 'Minor Challenge',
                                            data: [a_c, b_c, c_c, d_c, e_c]

                                        }, {
                                            name: 'Not a Challenge',
                                            data: [a_d, b_d, c_d, d_d, e_d]

                                        }]
                                    });
                                }
                            });
                        </script>

                        <div class="pieGraphContainer">
                            <div class="colLeft">
                                <h2>Sanctus Sea Sed Takimata</h2>
                                <div id="container3" class="graphWrap"></div>
                                <script>
                                    jQuery(function () {
                                        var count = 0;
                                        var present_ave = 0;
                                        var absent_ave = 0
                                        var schools_with_data_count = 0;


                                        jQuery.getJSON('/api/v1/results?survey=<?php print $survey_id; ?>&field=Percentage%20of%20teachers%20present', function(data){
                                            for(var i=0; i < data.length; i++){
                                                try {
                                                    count += parseInt(data[i]["data"]);
                                                    schools_with_data_count += 1;
                                                }
                                                catch(err) {
                                                    console.log("not integer");
                                                }
                                            }
                                            present_ave = count / schools_with_data_count * 100;
                                            absent_ave = 100 - present_ave;
                                            print_attendance_graph();
                                        });   
                                        

                                        function print_attendance_graph(){
                                            if(present_ave == 0 || absent_ave == 0){ return; }

                                            jQuery('#container3').highcharts({
                                                chart: {
                                                    plotBackgroundColor: null,
                                                    plotBorderWidth: null,
                                                    plotShadow: false
                                                },
                                                title: {
                                                    text: ''
                                                },
                                                tooltip: {
                                                    pointFormat: '<b style="font-size: 30px;">{point.percentage:.1f}%</b>'
                                                },
                                                plotOptions: {
                                                    pie: {
                                                        allowPointSelect: true,
                                                        cursor: 'pointer',
                                                        dataLabels: {
                                                            enabled: true,
                                                            format: '<b>{point.name}</b>: {point.percentage:.1f} %',
                                                            style: {
                                                                color: (Highcharts.theme && Highcharts.theme.contrastTextColor) || 'black'
                                                            }
                                                        }
                                                    }
                                                },
                                                series: [{
                                                    type: 'pie',
                                                    data: [
                                                        ['Present', parseFloat(present_ave.toFixed(2))],
                                                        ['Absent', parseFloat(absent_ave.toFixed(2))],
                                                    ]
                                                }]
                                            });
                                        }
                                    });
                                </script>
                            </div>
                            <div class="colRight">
                                <h2>In Hendrerit In Vulputate</h2>
                                <div id="container4" class="graphWrap"></div>
                                <script>
                                    jQuery(function () {
                                        var count = 0;
                                        var present_ave = 0;
                                        var absent_ave = 0
                                        var total_count = 0;

                                        jQuery.getJSON('/api/v1/results?survey=<?php print $survey_id; ?>&field=Student%20attendance', function(data){
                                            for(var i=0; i < data.length; i++){
                                                try {
                                                    count += parseInt(data[i]["data"]);
                                                    total_count += 1;
                                                }
                                                catch(err) {
                                                    console.log("not integer");
                                                }
                                            }

                                            present_ave = count / total_count * 100;
                                            absent_ave = 100 - present_ave;
                                            print_student_attendance_graph();
                                        });  

                                        function print_student_attendance_graph(){
                                            jQuery('#container4').highcharts({
                                                chart: {
                                                    plotBackgroundColor: null,
                                                    plotBorderWidth: null,
                                                    plotShadow: false
                                                },
                                                title: {
                                                    text: ''
                                                },
                                                tooltip: {
                                                    pointFormat: '<b style="font-size: 30px;">{point.percentage:.1f}%</b>'
                                                },
                                                plotOptions: {
                                                    pie: {
                                                        allowPointSelect: true,
                                                        cursor: 'pointer',
                                                        dataLabels: {
                                                            enabled: true,
                                                            format: '<b>{point.name}</b>: {point.percentage:.1f} %',
                                                            style: {
                                                                color: (Highcharts.theme && Highcharts.theme.contrastTextColor) || 'black'
                                                            }
                                                        }
                                                    }
                                                },
                                                series: [{
                                                    type: 'pie',
                                                    data: [
                                                        ['Present', present_ave],
                                                        ['Absent', absent_ave],
                                                    ]
                                                }]
                                            });
                                        }
                                    });
                                </script>
                            </div>
                            <div class="clear"></div><!-- clear -->
                        </div><!-- pieGraphContainer -->

                        <h2>Velit Esse Molestie Consequat</h2>
                        <div id="container5" class="graphWrap"></div>
                        <script>
                            jQuery(function () {
                                var num_students = 0;
                                var num_teachers = 0

                                jQuery.getJSON('/api/v1/results?survey=<?php print $survey_id; ?>&field=Number%20of%20enrolled%20students', function(data){
                                    for(var i=0; i < data.length; i++){
                                        try {
                                            num_students += parseInt(data[i]["data"]);
                                        }
                                        catch(err) {
                                            console.log("not integer");
                                        }
                                    }
                                    print_total_number_of_students_and_teacher();
                                });

                                jQuery.getJSON('/api/v1/results?survey=<?php print $survey_id; ?>&field=Total%20Number%20of%20Teachers', function(data){
                                    for(var i=0; i < data.length; i++){
                                        try {
                                            num_teachers += parseInt(data[i]["data"]);
                                        }
                                        catch(err) {
                                            console.log("not integer");
                                        }
                                    }
                                    print_total_number_of_students_and_teacher();
                                });

                                function print_total_number_of_students_and_teacher(){
                                    if(num_students == 0 || num_teachers == 0){
                                        return;
                                    }
                                    jQuery('#container5').highcharts({
                                        chart: {
                                            type: 'column'
                                        },
                                        title: {
                                            text: ''
                                        },
                                        subtitle: {
                                            text: ''
                                        },
                                        xAxis: {
                                            categories: [
                                                'Total Number of Students',
                                                'Total Number of Teachers',
                                            ]
                                        },
                                        yAxis: {
                                            min: 0,
                                            title: {
                                                text: ''
                                            }
                                        },
                                        tooltip: {
                                            headerFormat: '<span style="font-size:10px">{point.key}</span><table>',
                                            pointFormat: '<tr>' +
                                            '<td style="padding:0"><b>{point.y}</b></td></tr>',
                                            footerFormat: '</table>',
                                            shared: true,
                                            useHTML: true
                                        },
                                        plotOptions: {
                                            column: {
                                                pointPadding: 0.2,
                                                borderWidth: 0
                                            }
                                        },
                                        series: [{
                                            name: 'Total Number of Students and Teachers',
                                            data: [876, 676]
                                        }]
                                    });
                                }
                            });
                        </script>
            
      </div>
    </div>
</div>
</div>
</div>
</div>
    
    
    <div class="footer">
     <div class="container">
       <div class="row-fluid">
       
        
        <div class="footer_right">
            <div class="images-container">
                <img src="/wb-opengov-armmdata/sites/all/themes/openlgu_custom/images/logo-default.png" alt="">
                <p>All content is in the public domain unless otherwise stated.</p>
            </div>
        </div>
         
        <div class="footer_left">
         
         <div class="footer_link social-media" style="float: left; top: 0px;">
          <h4>Social Media</h4>
          <ul>
            <li id="menu-item-3278" class="menu-item">Facebook Page</li>
            <li id="menu-item-251" class="menu-item">Facebook News</li>
            <li id="menu-item-36581" class="menu-item">YouTube Channel</li>
            <li id="menu-item-18123" class="menu-item">Official Blog</li>
         </ul>
         </div>


         <div class="footer_link resources" style="float: left; top: 0px;">
          <h4>Official Link</h4>
          <ul>
            <li id="menu-item-4168" class="menu-item">Official Website Link</li>
         </ul>
         </div>
        </div>
       </div>
     </div>
    </div>

    <script type="text/javascript">
        jQuery.getJSON('/api/v1/surveys', function(data){
            option = "";
            survey_item = getUrlParameter("survey");
            for(var i=0; i < data.length; i++){
                if(survey_item == data[i]["nid"]){
                    option += "<option value='"+ data[i]["nid"] +"' selected='selected'>" + data[i]["title"] + "</option>";    
                }else{
                    option += "<option value='"+ data[i]["nid"] +"'>" + data[i]["title"] + "</option>";
                }
                
            }
            jQuery("#surveyList").append(option);

            jQuery("select[name=list_of_survey]").change(function(){
                window.location = '/dashboard?survey=' + jQuery(this).val();
            });
        });


        function getUrlParameter(sParam)
        {
            var sPageURL = window.location.search.substring(1);
            var sURLVariables = sPageURL.split('&');
            for (var i = 0; i < sURLVariables.length; i++) 
            {
                var sParameterName = sURLVariables[i].split('=');
                if (sParameterName[0] == sParam) 
                {
                    return sParameterName[1];
                }
            }
        }
    </script>

    <!--/.fluid-container-->

    <!-- Le javascript
    ================================================== -->
    <!-- Placed at the end of the document so the pages load faster -->
    <script src="<?php print $base_path; ?><?php print $directory; ?>/js/bootstrap-dropdown.js"></script>
    <script src="<?php print $base_path; ?><?php print $directory; ?>/js/bootstrap-collapse.js"></script>
    <script src="<?php print $base_path; ?><?php print $directory; ?>/js/bootstrap-typeahead.js"></script>




