HTML Mail

   [1]HTML Mail lets you theme your outgoing messages the same way you
   theme the rest of your website.

Requirements

     * [2]Mail System

Installation

   [3]Install as usual.

   The following additional modules, while not required, are highly
   recommended:
     * [4]Emogrifier
     * [5]Mail MIME
     * [6]Pathologic
     * [7]Transliteration
       Also available as a [8]patch.

Configuration

   Visit the [9]Mail System settings page at admin/settings/mailsystem to
   select which parts of Drupal will use [10]HTML Mail instead of the
   [11]default [12]mail system.

   Visit the [13]HTML Mail settings page at admin/settings/htmlmail to
   select a theme, pre-filter, and post-filter for your messages.

Theming

   The email message text goes through three transformations before
   sending:
    1. Template File
       A template file is applied to your message header, subject, and
       body text. The default template is the included htmlmail.tpl.php
       file. You may copy this file to your default theme directory and
       use it to customize the contents and formatting of your messages.
       The comments within that file contain complete documentation on its
       usage.
    2. Theming
       (Optional: requires [14]Echo module.) The templated text may be
       wrapped in a website theme. This lets you use any one of [15]over
       800 themes to style your messages. Creating an email-specific
       sub-theme lets you use the full power of the [16]drupal theme
       system to format your messages.
    3. Post-filtering
       You may choose a text format to be used for filtering email
       messages after theming. This allows you to use any combination of
       [17]over 200 filter modules to make final changes to your message
       before sending.
       Here is a recommended configuration:
          + [18]Emogrifier Converts stylesheets to inline style rules for
            consistent display on mobile devices and webmail.
          + [19]Transliteration Converts non-ASCII text to US-ASCII
            equivalents. This helps prevent Microsoft "smart-quotes" from
            appearing as question-marks in Mozilla Thunderbird.
          + [20]Pathologic Converts relative URLS to absolute URLS so that
            clickable links in your message will work as intended.

Troubleshooting

   Visit the [21]issue queue for support and feature requests.

Related Modules

   Emogrifier
          http://drupal.org/project/emogrifier

   HTML Purifier
          http://drupal.org/project/htmlpurifier

   htmLawed
          http://drupal.org/project/htmlawed

   Mail MIME
          http://drupal.org/project/mailmime

   Mail System
          http://drupal.org/project/mailsystem

   Pathologic
          http://drupal.org/project/pathologic

   Transliteration
          http://drupal.org/project/transliteration

Documentation

   filter.module
          D6:
          http://api.drupal.org/api/drupal/modules--filter--filter.module/
          6
          D7:
          http://api.drupal.org/api/drupal/modules--filter--filter.module/
          7

   Installing contributed modules
          D6:
          http://drupal.org/documentation/install/modules-themes/modules-5
          -6
          D7:
          http://drupal.org/documentation/install/modules-themes/modules-7

   Theming guide
          http://drupal.org/documentation/theme

Original Author

     * [22]Chris Herberte

Current Maintainer

     * [23]Bob Vincent

References

   1. http://drupal.org/project/htmlmail
   2. http://drupal.org/project/mailsystem
   3. http://drupal.org/documentation/install/modules-themes/modules-5-6
   4. http://drupal.org/project/emogrifier
   5. http://drupal.org/project/mailmime
   6. http://drupal.org/project/pathologic
   7. http://drupal.org/project/filter_transliteration
   8. http://drupal.org/node/1095278#comment-4219530
   9. http://drupal.org/project/mailsystem
  10. http://drupal.org/project/htmlmail
  11. http://api.drupal.org/api/drupal/modules--system--system.mail.inc/class/DefaultMailSystem/7
  12. http://api.drupal.org/api/drupal/includes--mail.inc/function/drupal_mail_system/7
  13. http://drupal.org/project/htmlmail
  14. http://drupal.org/project/echo
  15. http://drupal.org/project/themes
  16. http://drupal.org/documentation/theme
  17. http://drupal.org/project/modules/?filters=type%3Aproject_project%20tid%3A63%20hash%3A1hbejm%20-bs_project_sandbox%3A1%20bs_project_has_releases%3A1
  18. http://drupal.org/project/emogrifier
  19. http://drupal.org/project/filter_transliteration
  20. http://drupal.org/project/pathologic
  21. http://drupal.org/project/issues/htmlmail
  22. http://drupal.org/user/1171
  23. http://drupal.org/user/36148
