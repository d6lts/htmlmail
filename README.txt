HTML Mail

   HTML Mail lets you theme your outgoing messages the same way you theme
   the rest of your website.

   For a full description of the module, visit the [1]project page.

   To submit bug reports and feature suggestions, visit the [2]issue
   queue.

Requirements

   HTML Mail requires the [3]Mail System module.

Installation

   Install as usual; see [4]Installing contributed modules (Drupal 7) for
   further information.

   The following additional modules, while not required, are highly
   recommended:
     * [5]Emogrifier
     * [6]Pathologic
     * [7]Transliteration
       Requires a [8]patch.

Configuration

   Visit the Mail System settings page at admin/config/system/mailsystem
   to select which parts of Drupal will use HTML Mail instead of the
   [9]default [10]mail system.

   Visit the HTML Mail settings page at admin/config/system/htmlmail to
   select a theme, pre-filter, and post-filter for your emails.

Theming

   The email message text goes through four transformations before
   sending:
    1. The Text format pre-filter from the module settings page is
       applied. This should be the same text format that your website uses
       for contributed content such as comments or blog postings. For
       consistency and security, it should include the the [11]Correct
       faulty and chopped off HTML from [12]filter.module, or a better
       replacement such as [13]HTML Purifier or [14]htmLawed.
    2. A theme template is applied. The default template is the included
       htmlmail.tpl.php file. You may copy this file to your theme
       directory and use it to customize the contents and formatting of
       your emails. The comments within the file contain complete
       documentation on its usage.
    3. The message may be wrapped in a website theme selected on the
       module settings page. Creating an email-specific theme lets you use
       the full power of the [15]drupal theme system to format your
       emails.
    4. The Text format post-filter from the module settings page is
       applied. For best results, this should be an email-specific input
       format containing the following text format filters:
          + [16]Transliteration
          + [17]Emogrifier
          + [18]Pathologic
          + [19]Correct faulty and chopped off HTML

Related Modules

   Emogrifier : http://drupal.org/project/emogrifier

   HTML Mail : http://drupal.org/project/htmlmail

   HTML Purifier : http://drupal.org/project/htmlpurifier

   htmLawed : http://drupal.org/project/htmlawed

   Mail System : http://drupal.org/project/mailsystem

   Pathologic : http://drupal.org/project/pathologic

   Transliteration : http://drupal.org/project/transliteration

Documentation

   filter.module :
   http://api.drupal.org/api/drupal/modules--filter--filter.module/7

   Installing contributed modules (Drupal 7) :
   http://drupal.org/node/895232

   Theming guide : http://drupal.org/documentation/theme

   Standard filters :
   http://api.drupal.org/api/drupal/modules--filter--filter.module/group/s
   tandard_filters/7

Maintainers

     * [20]Chris Herberte
     * [21]Bob Vincent

References

   1. http://drupal.org/project/htmlmail
   2. http://drupal.org/project/issues/htmlmail
   3. http://drupal.org/project/mailsystem
   4. http://drupal.org/node/895232
   5. http://drupal.org/project/emogrifier
   6. http://drupal.org/project/pathologic
   7. http://drupal.org/project/transliteration
   8. http://drupal.org/node/1095278#comment-4219530
   9. http://api.drupal.org/api/drupal/modules--system--system.mail.inc/class/DefaultMailSystem/7
  10. http://api.drupal.org/api/drupal/includes--mail.inc/function/drupal_mail_system/7
  11. http://api.drupal.org/api/drupal/modules--filter--filter.module/function/_filter_htmlcorrector/7
  12. http://api.drupal.org/api/drupal/modules--filter--filter.module/7
  13. http://drupal.org/project/htmlpurifier
  14. http://drupal.org/project/htmlawed
  15. http://drupal.org/documentation/theme
  16. http://drupal.org/node/1095278#comment-4219530
  17. http://drupal.org/project/emogrifier
  18. http://drupal.org/project/pathologic
  19. http://api.drupal.org/api/drupal/modules--filter--filter.module/function/_filter_htmlcorrector/7
  20. http://drupal.org/user/1171
  21. http://drupal.org/user/36148
