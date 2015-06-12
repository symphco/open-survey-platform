<?php

/**
 * @file
 * API documentation for Views Aggregator Plus module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Define your own group and column aggregation functions.
 *
 * @return array
 *   aggregation display names indexed by associated function id.
 */
function hook_views_aggregation_functions_info() {
  $functions = array(
    'views_aggregator_variance' => array(
      'group' => t('Variance'),
      'column' => t('Variance'),
    ),
  );
  return $functions;
}

/**
 * Alter existing aggregation functions.
 *
 * @param array $aggregation_functions
 *   the aggregation functions currently defined
 */
function hook_views_aggregation_functions_info_alter($aggregation_functions) {
}

/**
 * @} End of "addtogroup hooks".
 */
