<?php

/**
 * @file
 * API documentation for Google Charts module.
 */

/**
 * Create a new chart.
 */
// Create a control wrapper.
$control_wrapper = new GoogleChartsControlWrapper(array(
  'control_type' => GoogleChartsControlWrapper::STRING_FILTER,
  'control_name' => 'my_custom_control',
  'container_id' => 'my-custom-control',
));

$control_options = new GoogleChartsOptionWrapper();
$control_options->set('filter_column_label', t('Label'));

$control_wrapper->setOptions($control_options);

// Create a chart to which the control will be bound.
$chart_wrapper = new GoogleChartsWrapper(array(
  'chartType' => GoogleChartsWrapper::LINE_CHART,
  'chartName' => 'my_custom_chart',
  'containerId' => 'my-custom-chart',
));

$chart_options = new GoogleChartsOptionWrapper();
$chart_options->set('title', t('My custom chart'));
$chart_options->set('chart_area', array('width' => 600, 'height' => 600));

$chart_wrapper->setOptions($chart_options);

// Create the dashboard and bind the control and chart.
$dashboard = new GoogleChartsDashboard('my-dashboard');
$dashboard->bind($control_wrapper, $chart_wrapper);

// Create a data table for the dashboard.
$data_table = new GoogleChartsDataTable();
$data_table->addColumn('label',GoogleChartsDataColumn::STRING, t('Label'));
$data_table->addColumn('number_1', GoogleChartsDataColumn::NUMBER, t('Number 1'));
$data_table->addColumn('number_1', GoogleChartsDataColumn::NUMBER, t('Number 2'));

// Add rows to the data table.
$data_table->addRow(array('first', 1, 2));
$data_table->addRow(array('second', 3, 4));
$data_table->addRow(array('first', 5, 6));
$data_table->addRow(array('second', 7, 8));
$data_table->addRow(array('third', 9, 10));
$data_table->addRow(array('second', 11, 12));
$data_table->addRow(array('fourth', 13, 14));
$data_table->addRow(array('third', 15, 16));
$data_table->addRow(array('fourth', 17, 18));
$data_table->addRow(array('fourth', 19, 20));

// Finally, draw the dashboard.
$dashboard->draw($data_table);
