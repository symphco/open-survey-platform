/**
 * Get a list of all webforms.
 */
var getWebforms = function(endpoint, query, callback) {
  var url = endpoint + '/webform.json';
  url += query ? jQuery.param(query) : '';
  jQuery.ajax({
    url: url,
    success: function(data) {
      if (callback) {
        callback(data);
      }
    }
  });
};

/**
 * Create a new webform.
 */
var createWebform = function(endpoint, node, callback) {
  jQuery.ajax({
    url: endpoint + '/webform.json',
    type: 'POST',
    data: node,
    success: function(data) {
      if (callback) {
        callback(data);
      }
    }
  });
};

/**
 * Retrieve a webform.
 */
var getWebform = function(endpoint, webform, callback) {
  jQuery.ajax({
    url: endpoint + '/webform/' + webform.uuid + '.json',
    success: function (data) {
      if (callback) {
        callback(data);
      }
    }
  });
};

/**
 * Update a webform.
 */
var updateWebform = function(endpoint, webform, callback) {
  jQuery.ajax({
    url: endpoint + '/webform/' + webform.uuid + '.json',
    type: 'PUT',
    data: webform,
    success: function(data) {
      if (callback) {
        callback(data);
      }
    }
  });
};

/**
 * Delete a webform.
 */
var deleteWebform = function(endpoint, webform, callback) {
  jQuery.ajax({
    url: endpoint + '/webform/' + webform.uuid + '.json',
    type: 'DELETE',
    success: function(data) {
      if (callback) {
        callback(data);
      }
    }
  });
};

/**
 * Create a new submission.
 */
var addSubmission = function(endpoint, webform, submission, callback) {
  jQuery.ajax({
    url: endpoint + '/submission.json',
    type: 'POST',
    data: {
      webform: webform.uuid,
      submission: submission
    },
    success: function(data) {
      if (callback) {
        callback(data);
      }
    }
  });
};

/**
 * Get a submission.
 */
var getSubmission = function(endpoint, submission, callback) {
  jQuery.ajax({
    url: endpoint + '/submission/' + submission.uuid + '.json',
    success: function(data) {
      if (callback) {
        callback(data);
      }
    }
  });
};

/**
 * Update a submission.
 */
var updateSubmission = function(endpoint, submission, callback) {
  jQuery.ajax({
    url: endpoint + '/submission/' + submission.uuid + '.json',
    type: 'PUT',
    data: submission,
    success: function(data) {
      if (callback) {
        callback(data);
      }
    }
  });
};

/**
 * Delete a submission.
 */
var deleteSubmission = function(endpoint, submission, callback) {
  jQuery.ajax({
    url: endpoint + '/submission/' + submission.uuid + '.json',
    type: 'DELETE',
    success: function(data) {
      if (callback) {
        callback(data);
      }
    }
  });
};