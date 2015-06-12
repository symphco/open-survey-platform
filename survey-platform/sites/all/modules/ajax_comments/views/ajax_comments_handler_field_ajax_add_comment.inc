<?php
/*
 ** @file
 *  views handler class
 *  mostyly just  renders the field for views display  and adds  js and css
 */
class ajax_comments_handler_field_ajax_add_comment extends views_handler_field_comment_node_link {
  var $output;

  function option_definition() {
    $options = parent::option_definition();
    $options['text'] = array('default' => '', 'translatable' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
    );
    parent::options_form($form, $form_state);
    
    // The path is set by render_link function so don't allow to set it.
    $form['alter']['path'] = array('#access' => FALSE);
    $form['alter']['external'] = array('#access' => FALSE);
  }

  function pre_render(&$values) {
    parent::pre_render($values);

    // Load necessary AJAX libraries.
    drupal_add_js(drupal_get_path('module', 'ajax_comments') . '/ajax_comments.js');
    drupal_add_library('system', 'drupal.ajax');
  }

  function render($values) {
    if (user_access('post comments') && $node = $this->get_value($values)) {
      // Generate a unique token to prevent illegitimate requests.
      $options = array(
        'attributes' => array(
          'class' => array(
            'use-ajax',
            'ajax-comments-add-comment',
            'ajax-comments-add-comment-nid-' . $node->nid,
          ),
        ),
        'query' => array('tok' => drupal_get_token('ajax-comments-add-comment-' . $node->nid)),
        );
      $path = 'ajax_comments/comment_form/ajax/' . $node->nid;
      $text = !empty($this->options['text']) ? $this->options['text'] : t('Add new comment');
      //$this->options['element_wrapper_class'] = 'ajax-comments-add-comment-wrapper';
      return l($text, $path, $options);
    }
  }
}
