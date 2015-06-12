#Drupal Documentation

This platform is built on top of the Drupal CMS. Check Drupal Documentation for more information:

http://drupal.org/documentation


----


#Custom API Endpoints

###Base URL: http://armmdata.urls.ph/api/v1/


###GET /api/v1/surveys

List available surveys

Parameters:

- **since** - UNIX timestamp. If provided, will only return surveys created since timestamp. **optional*

Example: http://armmdata.urls.ph/api/v1/surveys

Response body:

```
[
	{
      created: "1420186596",
      changed: "1426503571",
      nid: "34057",
      title: "Final OpenEd School Survey",
      type: "survey",
      status: "1",
      uri: "http://armmdata.urls.ph/api/v1/surveys/34057"
	}
]
```



###GET /api/v1/surveys/[survey id]

Content, questions, and structure of a single survey

Example: http://armmdata.urls.ph/api/v1/surveys/34057

Response body:

```
{
  node: {
    nid: "34057",
    type: "survey",
    title: "Final OpenEd School Survey"
  },
  body: {
    entity_id: "34057",
    body_value: "<p>Welcome to the OpenEd Schools Survey. We are gathering data about schools in the ARMM Region. This survey includes questions about students, teachers, administrators, physical condition, attendance, and many other attribtues of schools.</p><p><img src="/sites/default/files/sample-image.jpg" alt="" width="427" height="282" /></p>",
    body_summary: "Welcome to the OpenEd Schools Survey. We are gathering data about schools in the ARMM Region. ",
    body_format: "full_html"
  },
  components: [
    {
      nid: "34057",
      cid: "1",
      pid: "0",
      form_key: "textfield_1",
      name: "Province",
      type: "textfield",
      value: "",
      extra: {
        width: "",
        maxlength: "",
        field_prefix: "",
        field_suffix: "",
        disabled: 0,
        unique: 0,
        title_display: "inline",
        description: "",
        attributes: [ ],
        private: 0,
        placeholder: "",
        analysis: false
      },
      required: "0",
      weight: "398",
      charting: null
    },
    {
      nid: "34057",
      cid: "2",
      pid: "0",
      form_key: "school_division",
      name: "School Division",
      type: "textfield",
      value: "",
      extra: {
        width: "",
        maxlength: "",
        field_prefix: "",
        field_suffix: "",
        disabled: 0,
        unique: 0,
        title_display: "inline",
        description: "",
        attributes: [ ],
        private: 0,
        placeholder: "",
        analysis: false
      },
      required: "0",
      weight: "399",
      charting: null
    }
  ]
}
```

###POST /api/v1/surveys/[survey id]


*multipart/form-data*


Submit a survey result. Multipart/form-data accept file uploads.

- Parameters
	- **cid_[number]** - answer to survey field.
	- **submission_timestamp** - optional timestamp to indicate actual timestamp of completion of survey. Defaults to current timestamp.



###POST /api/v1/surveys/[survey id]


*application/json*


Submit a survey result. Does **NOT** accept file uploads.

Request body:

```
{
	"cid_1": "text answer goes here",
	"cid_2": 24,
	"cid_3": "multi \n line \n answer",
	"submission_timestamp": 1234567890
}
```



###GET /api/v1/schools

List of Schools with location information

Example: http://armmdata.urls.ph/api/v1/schools

Response body:

```
[
  {
    title: "Bulingan ES",
    nid: "54173",
    field_coordinate_type_value: "Actual GPS",
    field_latlong_wkt: "POINT (122.11840057373 6.5744919776917)",
    field_sch_province_value: "Basilan",
    lat: "6.5744919776917",
    long: "122.11840057373",
    uri: "http://armmdata.urls.ph/node/54173"
  },
  {
    title: "Panansangan ES",
    nid: "54174",
    field_coordinate_type_value: "Actual GPS",
    field_latlong_wkt: "POINT (122.11708068848 6.6690192222595)",
    field_sch_province_value: "Basilan",
    lat: "6.6690192222595",
    long: "122.11708068848",
    uri: "http://armmdata.urls.ph/node/54174"
  }
]
```


###GET /api/v1/psgc

List of Provinces, Municipalities, and Barangays with their corresponding hierarchy and PSGC codes

Example: http://armmdata.urls.ph/api/v1/psgc

Sample Response body:

```
{
  name: "ARMM",
  psgc: "150000000",
  provinces: [
    {
      name: "BASILAN (excluding Isabela City)",
      psgc: "150700000",
      municipalities: [
        {
          name: "CITY OF LAMITAN",
          psgc: "150702000",
          barangays: [
            {
              name: "Arco",
              psgc: "150702001"
            },
            {
              name: "Ba-as",
              psgc: "150702002"
            }
         ]
        }
      ]
    }
  ]
}
```


###GET /api/v1/exports

Generate and download CSV Files of exportable data

Parameters:

- **schools=1** - List of Schools and their information
- **surveys=1** - List of Surveys and their questions

Example: http://armmdata.urls.ph/api/v1/exports?schools=1




###GET /api/v1/results

Retrieve the submitted values for a specific question

Parameters:

- **field** - The question name. **required*
- **survey** - Survey ID of the specific survey. Defaults to all surveys.


Example: http://armmdata.urls.ph/api/v1/results?field=Does%20the%20school%20have%20access%20to%20clean/drinking%20water%3F


```
[
  {
    name: "Does the school have access to clean/drinking water?",
    nid: "34057",
    data: "yes"
  },
  {
    name: "Does the school have access to clean/drinking water?",
    nid: "34057",
    data: "no"
  },
  {
    name: "Does the school have access to clean/drinking water?",
    nid: "34057",
    data: "no"
  }
]
```


###GET /api/v1/schoolredirectapi

Helper API. Given a school ID, redirect to the appropriate School Page.

Parameter:

- **school_id** - The school ID of the School to redirect to.

Example: http://armmdata.urls.ph/api/v1/schoolredirectapi?school_id=134879



###GET /api/v1/schooldetails

Given a school ID, output the survey submission results of that school

Parameters:

- **school_id** - The school ID to filter the survey results to that specific school. *_required_
- **survey_id** - The survey ID to filter by specific survey

Example: http://armmdata.urls.ph/api/v1/schooldetails?school_id=134879


Response body:

```
[
  {
    name: "Municipality/City",
    data: "TANDUBAS"
  },
  {
    name: "Barangay",
    data: "Danglog"
  },
  {
    name: "Name of School",
    data: "Danglog ES"
  },
  {
    name: "School ID",
    data: "134879"
  },
  {
    name: "School is an Annex/Extension?",
    data: "no"
  }
]
```


###GET /api/v1/surveyimages

Helper API. Given a School ID, return a list of images for that school that was submitted through survey results.

Parameters:

- **school_id** - School ID to limit images to that specific school. *_required_



-----


#Important code & files to take note of

##Custom Drupal Module for ARMM API
**URL:** /api/v1

Module Name: "Open-Ed API".

Directory Location:

```
/sites/all/modules/opened_survey_api
```


##Relevant pages and the template files that control them

Various Template Files control specific pages, and can be found in the custom templates directory

###Custom Template Directory

```
/sites/all/themes/openlgu_custom
```


###Front Page Content Template
**URL:** / (homepage)

Main Template File:

```
/sites/all/themes/openlgu_custom/templates/pages/page--front.tpl.php
```


###Survey Results Page

**URL:** /schools

Main Template File: 

```
/sites/all/themes/openlgu_custom/templates/views/views-secondary-row-view-table--schools.tpl.php
```

**Note:**
Custom Search, "Enter School Name or School ID", is implemented by checking if the search text is a number or not. If it's a number, the query is made against the School ID field. If the search text is not a number, the query is made against the School Name field.**


###Dashboard Page Template

**URL:** /dashboard

Main Template File:

```
/sites/all/themes/openlgu_custom/templates/pages/page--node--25833.tpl.php
```


###Map Page Template

**URL:** /map

Main Template File:

```
/sites/all/themes/openlgu_custom/templates/pages/page--node--34040.tpl.php
```

