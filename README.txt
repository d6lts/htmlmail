HTML Mail

   [1]HTML Mail lets you theme your outgoing messages the same way you
   theme the rest of your website.

Requirements

     * [2]Echo
     * [3]Mail System

Installation

   [4]Install as usual.

   The following additional modules, while not required, are highly
   recommended:
     * [5]Emogrifier
     * [6]Filter transliteration
     * [7]Mail MIME
     * [8]Pathologic
       Also available as a [9]patch.

Configuration

   Visit the [10]Mail System settings page at admin/settings/mailsystem to
   select which parts of Drupal will use [11]HTML Mail instead of the
   [12]default [13]mail system.

   Visit the [14]HTML Mail settings page at admin/settings/htmlmail to
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
       (Optional: requires [15]Echo module.) The templated text may be
       wrapped in a website theme. This lets you use any one of [16]over
       800 themes to style your messages. Creating an email-specific
       sub-theme lets you use the full power of the [17]drupal theme
       system to format your messages.
    3. Post-filtering
       You may choose a text format to be used for filtering email
       messages after theming. This allows you to use any combination of
       [18]over 200 filter modules to make final changes to your message
       before sending.
       Here is a recommended configuration:
          + [19]Emogrifier Converts stylesheets to inline style rules for
            consistent display on mobile devices and webmail.
          + [20]Transliteration Converts non-ASCII text to US-ASCII
            equivalents. This helps prevent Microsoft "smart-quotes" from
            appearing as question-marks in Mozilla Thunderbird.
          + [21]Pathologic Converts relative URLS to absolute URLS so that
            clickable links in your message will work as intended.

Troubleshooting

   Visit the [22]issue queue for support and feature requests.

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

     * [23]Chris Herberte

Current Maintainer

     * [24]Bob Vincent

References

   1. http://drupal.org/project/htmlmail
   2. http://drupal.org/project/echo
   3. http://drupal.org/project/mailsystem
   4. http://drupal.org/documentation/install/modules-themes/modules-5-6
   5. http://drupal.org/project/emogrifier
   6. http://drupal.org/project/filter_transliteration
   7. http://drupal.org/project/mailmime
   8. http://drupal.org/project/pathologic
   9. http://drupal.org/node/1095278#comment-4219530
  10. http://drupal.org/project/mailsystem
  11. http://drupal.org/project/htmlmail
  12. http://api.drupal.org/api/drupal/modules--system--system.mail.inc/class/DefaultMailSystem/7
  13. http://api.drupal.org/api/drupal/includes--mail.inc/function/drupal_mail_system/7
  14. http://drupal.org/project/htmlmail
  15. http://drupal.org/project/echo
  16. http://drupal.org/project/themes
  17. http://drupal.org/documentation/theme
  18. http://drupal.org/project/modules/?filters=type%3Aproject_project%20tid%3A63%20hash%3A1hbejm%20-bs_project_sandbox%3A1%20bs_project_has_releases%3A1
  19. http://drupal.org/project/emogrifier
  20. http://drupal.org/project/filter_transliteration
  21. http://drupal.org/project/pathologic
  22. http://drupal.org/project/issues/htmlmail
  23. http://drupal.org/user/1171
  24. http://drupal.org/user/36148
