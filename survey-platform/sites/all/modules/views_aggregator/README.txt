
VIEWS AGGREGATOR PLUS
=====================
Because the Views and ViewsCalc modules rely on the database to perform
aggregation, you only have limited options at your disposal. That is where this
module comes in. Unlike Views and ViewsCalc, this module:
o enumerates group members (see https://drupal.org/node/1300900)
o produces tallies (textual histograms, see http://drupal.org/node/1256716)
o can aggregate on ViewsPHP code-snippets
o can filter out rows on regular expressions (regexp)
o can aggregate across entire columns (e.g show column data range at the top)
o lets you add your own custom aggregation functions to the existing set
o aggregation functions can take parameters, as currently employed by "Filter
  rows", "Count" and "Label"
o supports "Webform submission data: Value" fields (Webform 7.x-4.x)

Basics Recap: what is aggregation again?
----------------------------------------
In the context of Views and this module, aggregation is the process of grouping
and collapsing result rows on the identical values of ONE column, while at the
same time applying "summary" functions on other columns. For example you can
group the result set on a taxonomy term, so that all rows sharing the same
value of the taxonomy column are represented as single rows, with aggregation
functions, like TALLY, SUM, or ENUMERATE applied to the remaining columns.

Example
-------
Say the original View based on raw database results looks like below.

Industry|Company Name |     Turnover |
--------|-------------|--------------|
IT      |       AquiB |  $25,000,000 |
Clothing|    Cenneton |  $99,000,000 |
Food    |       Heiny |  $66,000,000 |
IT      |PreviousBest |  $ 5,000,000 |
Food    |   McRonalds | $500,000,000 |

Then with the grouping taking place on, say Industry, and aggregation functions
COUNT and SUM applied on Company Name and Turnover respectively, the final
result will display like below. A descending sort was applied to
Turnover and the display name of "Company Name" was changed to "Comp. Count".

Industry| Comp. Count |     Turnover |
--------|-------------|--------------|
Food    |           2 | $566,000,000 |
Clothing|           1 |  $99,000,000 |
IT      |           2 |  $30,000,000 |

That's the basics and you can do the above with Views. But with Views
Aggregator Plus (VAgg+) you can also aggregate like below, using its TALLY and
ENUMERATE group aggregation functions, as well as LABEL, COUNT and SUM for the
added bottom row.

Industry    |Companies           |     Turnover |
------------|--------------------|--------------|
Food (2)    |Heiny, McRonalds    | $566,000,000 |
Clothing (1)|Cenneton            |  $99,000,000 |
IT (2)      |AcquiB, PreviousBest|  $30,000,000 |
------------|--------------------|--------------|
Totals      |                  5 | $695,000,000 |
------------------------------------------------

But that's just the beginning. Remember, you can aggregate on ViewsPHP
expressions, so the possibilities are endless! Say you have a content type
"event" that has a date range field on it with both start and end components
active. Let's say its machine name is "field_duration". The code snippet below
entered in the "Output code" area of a Views PHP field will output in Views for
each event whether it is in progress, closed or not started yet.

<?php
  $start_date = strtotime($data->field_field_duration[0]['raw']['value']);
  $end_date   = strtotime($data->field_field_duration[0]['raw']['value2']);
  echo time() < $start_date ? 'not started' : (time() < $end_date ? 'in progress' : 'closed');
?>

Next you can use VAgg+ to group on the expression and count or enumerate the
event titles in each of these categories.

HOW TO USE
----------
On the main Views UI page, admin/structure/views/view/YOUR-VIEW/edit/page,
under Format, click and select "Table with aggregation options". Having arrived
at the Settings page, follow the hints under the header "Style Options".
All group aggregation functions, except "Filter rows" require exactly one field
to be assigned the "Group and compress" function.
Column aggregation functions may be used independently of group aggregation
functions. If a column aggregation function requires an argument, it may take
it from the corresponding group aggregation function, if also enabled.

There are no permissions or global module configurations.

Views Aggregator Plus does not combine well with Views' native aggregation.
So in the Advanced section (upper right) set "Use aggregation: No".

REGEXPS
-------
Some aggregation functions, like "Filter rows" and "Count" take a regular
expression as a parameter. In its simplest form a regular expression is a word
or part of a word you want to filter on. If you use regexps in this way, you may
omit the special delimiters around the parameter, most commonly a pair of
forward slashes. So "red" and "/red/" are equivalent.
Here are some more regexps:

/RED/i         targets rows that contain the word "red" in the field specified,
               case-insensitive
/red|blue/     rows with either the word "red" or "blue" in the field
/^(Red|Blue)/  rows where the specified field begins with "Red" or "Blue"
/Z[0-9]+/      the letter Z followed by one or more digits

Ref: http://work.lauralemay.com/samples/perl.html (for PERL, but quite good)

LIMITATIONS
-----------
o Views-style table grouping, whereby the original table is split into smaller
  ones, interferes with this plugin, so is not available.
o When you have an aggregated View AND a normal View attachment on the same
  page AND you click-sort on Global:Math Expression the normal View attachment
  will temporarily disappear. This is because the sort is passed to BOTH
  displays and normal Views do not support sorting on Math Expressions.
o When you apply two aggregation functions on the same field, the 2nd function
  gets applied on the results of the first -- not always what you want.
o Grouping, tallying and other functions may not work correctly when you have
  the "Theme Developer" module enabled.

TIPS FOR USING VIEWS PHP MODULE
-------------------------------
Use "Output code", not "Value code", as in the "Value code" area few Views
results are available. Here are some examples of the syntax to use for various
field types for access in the Output code text area. Note that to display
these values you need to put "echo" in front of the expression and place the
<?php and ?> "brackets" around everything.

// General fields, say a field named "Total", machine name: "field_total"
Raw value: $data->field_field_total[0]['raw']['value'] // 1000
Rendered value (i.e. marked-up for display):
$data->field_field_total[0]['rendered']['#markup'] // $ 1,000.00

// Dates, machine name "field_duration" (start & end dates),
Raw start: $data->field_field_duration[0]['raw']['value']// 2013-06-02 00:00:00
Raw end: $data->field_field_duration[0]['raw']['value2'] // 2013-06-04 00:00:00
Rendered: $data->field_field_duration[0]['rendered']['#markup'];  //"Sun
 02-Jun-2013 to Wed 04-Jun-2013"

// Taxonomy terms, machine name: "field_industry"
Raw: $data->field_field_industry[0]['raw']['tid']
Rendered: $data->field_field_industry[0]['rendered']['#title']

ACKNOWLEDGEMENT
---------------
The UI of this module borrows heavily from Views Calc and the work by the
authors and contributors done on that module is gratefully acknowledged.

REFs
----
https://drupal.org/node/1219356#comment-4782582
https://drupal.org/node/1219356#comment-6909160
https://drupal.org/node/1300900
https://drupal.org/node/1791796
https://drupal.org/node/1140896#comment-7657061
