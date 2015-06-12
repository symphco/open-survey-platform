(function ($) {
  $(document).ready(function () {
    var amount = 0;
    var alltabs = [];
    //generate the tabs
    jQuery.each(Drupal.settings.WebFormAjaxPage.forms, function () {

      var wrapper = this.wrapper;
      var id = this.id;
      alltabs[id] = $("#" + wrapper).tabs({idPrefix: 'ui-tabs-' + amount});

      //get the amount of tabs
      var totalSize = $("#" + wrapper + " .webform-component-ajax-page").size() - 1;
      //hide submit button until last ajax page is reached
      hideOrShow(alltabs[id], id, totalSize);
      amount += 1;

      //add the next and previous links
      $("#" + wrapper + " .webform-component-ajax-page").each(function (i) {
        var html = '<div class="webform-ajax-page-nav">';

        if (i != totalSize) {
          next = i + 1;

          html += "<a href='#' class='next-tab mover' rel='" + next + "'>" + Drupal.settings.WebFormAjaxPage.labels.next + "</a>";
        }

        if (i != 0) {
          prev = i - 1;
          html += "<a href='#' class='prev-tab mover' rel='" + prev + "'>" + Drupal.settings.WebFormAjaxPage.labels.previous + "</a>";
        }
        html += '</div>';
        $(this).append(html);
      });

      //next and previous links handlers
      $("#" + wrapper + ' .next-tab, #' + wrapper + ' .prev-tab').click(function (e) {
        if ($(this).hasClass('next-tab') && typeof (Drupal.settings.clientsideValidation) != 'undefined') {
          if ($('#' + $(this).parents().find('form').attr('id')).valid()) {
            alltabs[$(this).parents().find('form').attr('id')].tabs('select', parseInt($(this).attr("rel")));
          }
        }
        else{
          alltabs[$(this).parents().find('form').attr('id')].tabs('select', parseInt($(this).attr("rel")));
        }
        hideOrShow(alltabs[$(this).parents().find('form').attr('id')], $(this).parents().find('form').attr('id'), totalSize);
        if ($(this).hasClass('prev-tab') && typeof (Drupal.settings.clientsideValidation) != 'undefined') {
          var formid = $(this).parents().find('form').attr('id');
          $('#' + formid).find('.error').removeClass('error');
          $('#' + $(this).parents().find('form').attr('id')).valid();
        }
        var x = $('#' + wrapper).offset().top - 100;
        $('html, body').animate({scrollTop: x}, 1000);
        e.preventDefault();
      });
      $('#' + id + ' #edit-actions').appendTo($('#' + id + ' .webform-component-ajax-page .webform-ajax-page-nav'));
    });


    function hideOrShow($tabs, wrapperid, size) {
      if ($tabs.tabs('option', 'selected') != size) {

        $('#' + wrapperid + ' .form-actions input').each(function () {
          if (!$(this).hasClass('cancel') && !$(this).is('#edit-draft')) {
            $(this).hide();
          }
        });
      }
      else{
        $('#' + wrapperid + ' .form-actions input').each(function(){
          if (!$(this).hasClass('cancel') && !$(this).is('#edit-draft')) {
            $(this).show();
          }
        });
      }
    }
  });
})(jQuery);