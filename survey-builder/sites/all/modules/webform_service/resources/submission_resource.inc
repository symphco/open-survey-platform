<?php
/**
 * The submission resource definition.
 *
 * @return array
 */
function _submission_resource_definition() {
  return array(
    'submission' => array(
      'operations' => array(
        'retrieve' => array(
          'callback' => 'webform_service_get_submission_by_uuid',
          'args' => array(
            array(
              'name' => 'uuid',
              'optional' => FALSE,
              'source' => array('path' => 0),
              'type' => 'string',
              'description' => 'The uuid of the submission.',
            ),
          ),
          'access callback' => 'webform_service_submission_access',
          'access arguments' => array('view'),
          'access arguments append' => TRUE,
        ),
        'create' => array(
          'file' => array('type' => 'inc', 'module' => 'webform_service', 'name' => 'resources/submission_resource'),
          'callback' => 'webform_service_submission_create',
          'args' => array(
            array(
              'name' => 'uuid',
              'optional' => FALSE,
              'source' => array('data' => 'webform'),
              'type' => 'string',
              'description' => 'The uuid of the webform.',
            ),
            array(
              'name' => 'submission',
              'optional' => FALSE,
              'source' => array('data' => 'submission'),
              'description' => 'The submission data for this webform.',
              'type' => 'array',
              'default value' => array(),
            ),
           ),// args
          'access callback' => 'webform_service_submission_access',
          'access arguments' => array('create'),
          'access arguments append' => TRUE,
        ),// create
        'update' => array(
          'file' => array('type' => 'inc', 'module' => 'webform_service', 'name' => 'resources/submission_resource'),
          'callback' => 'webform_service_submission_update',
          'args' => array(
            array(
              'name' => 'uuid',
              'optional' => FALSE,
              'source' => array('path' => 0),
              'type' => 'string',
              'description' => 'The uuid of the submission.',
            ),
            array(
              'name' => 'submission',
              'optional' => FALSE,
              'source' => 'data',
              'description' => 'The submission data to update',
              'type' => 'array',
            ),
          ),
          'access callback' => 'webform_service_submission_access',
          'access arguments' => array('edit'),
          'access arguments append' => TRUE,
        ),
        'delete' => array(
          'file' => array('type' => 'inc', 'module' => 'webform_service', 'name' => 'resources/submission_resource'),
          'callback' => 'webform_service_submission_delete',
          'args' => array(
            array(
              'name' => 'uuid',
              'optional' => FALSE,
              'source' => array('path' => 0),
              'type' => 'string',
              'description' => 'The uuid of the submission.',
            ),
          ),
          'access callback' => 'webform_service_submission_access',
          'access arguments' => array('delete'),
          'access arguments append' => TRUE,
        ),
      ),
    ),
  );
}

/**
 * Creates a new submission within a webform.
 *
 * Note that this function uses drupal_execute() to create new nodes,
 * which may require very specific formatting. The full implications of this
 * are beyond the scope of this comment block. The Googles are your friend.
 *
 * @param $media
 *   Array representing the attributes a media edit form would submit.
 * @return
 *   An associative array contained the new node's nid and, if applicable,
 *   the fully qualified URI to this resource.
 *
 * @see drupal_execute()
 */
function webform_service_submission_create($uuid, $submission) {
  // Get the webform entity.
  $webform = webform_service_resource_load($uuid);

  // If the entity exists.
  if ($webform && $submission) {
    module_load_include('inc', 'webform', 'includes/webform.submissions');
    $sid = webform_submission_insert($webform, webform_service_parse_submission($webform, $submission));
    return webform_service_get_submission($webform, webform_get_submission($webform->nid, $sid, TRUE));
  }
  else {
    return FALSE;
  }
}

/**
 * Updates a webform submission based on submitted values.
 *
 * Note that this function uses drupal_execute() to create new nodes,
 * which may require very specific formatting. The full implications of this
 * are beyond the scope of this comment block. The Googles are your friend.
 *
 * @param $uuid
 *   UUID of the webform we're editing.
 * @param $sid
 *   Submission ID of the submission we are editing.
 * @param $submission
 *   Array representing the submission.
 * @return
 *   The submission object.
 *
 * @see drupal_execute()
 */
function webform_service_submission_update($uuid, $submission) {

  // Get the webform entity.
  $webform = webform_submission_uuid_webform($uuid);
  $current_submission = webform_submission_uuid_submission($uuid);

  // If the entity exists.
  if ($webform && $current_submission) {
    foreach ($current_submission as $key => $value) {
      if ($key == 'data') {
        foreach ($value as $cid => $data) {
          if (!isset($submission['data'][$cid])) {
            $submission['data'][$cid] = array('values' => $data);
          }
        }
      }
      else {
        $submission[$key] = $value;
      }
    }

    module_load_include('inc', 'webform', 'includes/webform.submissions');
    $sid = webform_submission_update($webform, webform_service_parse_submission($webform, $submission));
    return webform_service_get_submission($webform, webform_get_submission($webform->nid, $sid, TRUE));
  }
  else {
    return FALSE;
  }
}

/**
 * Delete a submission within a webform.
 *
 * @param $nid
 *   Node ID of the node we're deleting.
 * @return
 *   The node's nid.
 */
function webform_service_submission_delete($uuid) {
  // Get the webform entity.
  $webform = webform_submission_uuid_webform($uuid);
  $submission = webform_submission_uuid_submission($uuid);

  // If the entity exists.
  if ($webform && $submission) {
    module_load_include('inc', 'webform', 'includes/webform.submissions');
    webform_submission_delete($webform, webform_service_parse_submission($webform, $submission));
    return TRUE;
  }
  else {
    return FALSE;
  }
}
