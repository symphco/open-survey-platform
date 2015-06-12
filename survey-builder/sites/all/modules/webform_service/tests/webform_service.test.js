
// Test creating a new webform.
var testCreateWebform = function(endpoint, callback) {
  asyncTest('Create Webform', function() {
    expect(5);

    // Create the webform...
    createWebform(endpoint, {
      title: 'Test',
      body: 'Testing body',
      name: 'admin',
      webform: {
        components: [
          {form_key: 'first_name', type: 'textfield', name: 'First Name'},
          {form_key: 'last_name', type: 'textfield', name: 'Last Name'},
          {form_key: 'email', type: 'email', name: 'Email'}
        ]
      }
    }, function(webform) {
      ok(webform.title == 'Test');
      ok(!!webform.webform);
      ok(webform.webform.components['1']['form_key'] == 'first_name');
      ok(webform.webform.components['2']['form_key'] == 'last_name');
      ok(webform.webform.components['3']['form_key'] == 'email');
      start();
      callback(webform);
    });
  });
};

// Test getting a new webform.
var testGetWebform = function(endpoint, webform, callback) {
  asyncTest('Get Webform', function() {
    expect(3);
    getWebform(endpoint, webform, function(retrieved) {
      ok(webform.title == retrieved.title);
      ok(webform.body == retrieved.body);
      ok(!!retrieved.webform);
      start();
      callback(retrieved);
    });
  });
};

// Test updating a webform.
var testUpdateWebform = function(endpoint, webform, callback) {
  asyncTest('Update Webform', function() {
    expect(3);

    // Convert the components to an array and add a middle name.
    webform.webform.components = Array.prototype.slice.call(webform.webform.components);
    webform.webform.components.push({
      form_key: 'middle_name',
      type: 'textfield',
      name: 'Middle Name'
    });

    updateWebform(endpoint, webform, function(webform) {
      ok(webform.webform.components['4'].form_key == 'middle_name');
      ok(webform.webform.components['4'].type == 'textfield');
      ok(webform.webform.components['4'].name == 'Middle Name');
      start();
      callback(webform);
    });
  });
};

// Test deleting a webform.
var testDeleteWebform = function(endpoint, webform, callback) {
  asyncTest('Delete Webform', function() {
    expect(1);
    deleteWebform(endpoint, webform, function(status) {
      ok(!!status);
      start();
      callback(status);
    });
  });
};

// Create a new submission.
var testCreateSubmission = function(endpoint, webform, callback) {
  asyncTest('Create Submission', function() {
    expect(5);
    addSubmission(endpoint, webform, {
      data: {
        '1': {values: ['Travis']},
        '2': {values: ['Tidwell']},
        '3': {values: ['travis@allplayers.com']},
        '4': {values: ['Michael']}
      }
    }, function(submission) {
      ok(!!submission);
      ok(submission.data['1'].values[0] == 'Travis');
      ok(submission.data['2'].values[0] == 'Tidwell');
      ok(submission.data['3'].values[0] == 'travis@allplayers.com');
      ok(submission.data['4'].values[0] == 'Michael');
      start();
      callback(submission);
    });
  });
};

// Retrieve a submission.
var testGetSubmission = function(endpoint, submission, callback) {
  asyncTest('Get Submission', function() {
    expect(1);
    getSubmission(endpoint, submission, function(submission) {
      ok(!!submission);
      start();
      callback(submission);
    });
  });
};

// Update a submission.
var testUpdateSubmission = function(endpoint, submission, callback) {
  asyncTest('Update Submission', function() {
    expect(5);
    submission.data['1'] = {values: ['Travis Update']};
    submission.data['2'] = {values: ['Tidwell Update']};
    submission.data['3'] = {values: ['travis_update@allplayers.com']};
    submission.data['4'] = {values: ['Michael Update']};
    updateSubmission(endpoint, submission, function(submission) {
      ok(!!submission);
      ok(submission.data['1'].values[0] == 'Travis Update');
      ok(submission.data['2'].values[0] == 'Tidwell Update');
      ok(submission.data['3'].values[0] == 'travis_update@allplayers.com');
      ok(submission.data['4'].values[0] == 'Michael Update');
      start();
      callback(submission);
    });
  });
};

// Delete a submission.
var testDeleteSubmission = function(endpoint, submission, callback) {
  asyncTest('Delete Submission', function() {
    expect(1);
    deleteSubmission(endpoint, submission, function(status) {
      ok(!!status);
      start();
      callback(status);
    });
  });
};