(function($) {

  Drupal.behaviors.form_placeholder = {
    attach: function(context, settings) {
      var include = Drupal.settings.form_placeholder.include;
      include += ', .form-placeholder-include-children *';
      include += ', .form-placeholder-include';

      var exclude = Drupal.settings.form_placeholder.exclude;
      exclude += ', .form-placeholder-exclude-children *';
      exclude += ', .form-placeholder-exclude';

      var required_indicator = Drupal.settings.form_placeholder.required_indicator;

      $(include, context).not(exclude).each(function() {
        $textfield = $(this);

        // Check if element is a textfield
        if (!$textfield.is('input[type=text], input[type=email], input[type=password], textarea')) {
          return;
        }

        $form = $textfield.closest('form');
        $label = $form.find('label[for=' + this.id + ']');

        if (required_indicator === 'append') {
          $label.find('.form-required').insertAfter($textfield).prepend('&nbsp;');
        }
        else if (required_indicator === 'remove') {
          $label.find('.form-required').remove();
        }
        else if (required_indicator === 'text') {
          $label.find('.form-required').text('(' + Drupal.t('required') + ')');
        }

        $label.hide();
        $textfield.attr('placeholder', $label.text());

        // If the jQuery Placeholder plugin is loaded correctly.
        if (Drupal.settings.form_placeholder.fallback_support) {
          $textfield.placeholder();
        }
      });
    }
  }

})(jQuery);
