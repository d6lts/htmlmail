[1]HTML Mail

   Lets you theme your outgoing messages the same way you theme the rest
   of your website.

[2]Requirement

     * [3]Mail System

[4]Installation

   The following additional modules, while not required, are highly
   recommended:
     *

        [5]Echo
                Wraps your messages in a drupal theme. Now you can "brand"
                your messages with the same logo, header, fonts, and
                styles as your website.

     *

        [6]Emogrifier
                Converts stylesheets to inline style rules, for consistent
                display on mobile devices and webmail.

     *

        [7]Mail MIME
                Provides a text/plain alternative to text/html emails, and
                automatically converts image references to inline image
                attachments.

     *

        [8]Pathologic
                Converts urls from relative to absolute, so clickable
                links in your email messages work as intended.

     *

        [9]Transliteration
                Converts non-ASCII characters to their US-ASCII
                equivalents, such as from Microsoft "smart-quotes" to
                regular quotes.

                Also available as a [10]patch.

[11]Configuration

   Visit the [12]Mail System settings page at admin/settings/mailsystem to
   select which parts of Drupal will use [13]HTML Mail instead of the
   [14]default [15]mail system.

   Visit the [16]HTML Mail settings page at admin/settings/htmlmail to
   select a theme and post-filter for your messages.

[17]Theming

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
       (Optional: requires [18]Echo module.) The templated text may be
       wrapped in a website theme. This lets you use any one of [19]over
       800 themes to style your messages. Creating an email-specific
       sub-theme lets you use the full power of the [20]drupal theme
       system to format your messages.
    3. Post-filtering
       You may choose a text format to be used for filtering email
       messages after theming. This allows you to use any combination of
       [21]over 200 filter modules to make final changes to your message
       before sending.
       Here is a recommended configuration:
          + [22]Emogrifier Converts stylesheets to inline style rules for
            consistent display on mobile devices and webmail.
          + [23]Transliteration Converts non-ASCII text to US-ASCII
            equivalents. This helps prevent Microsoft "smart-quotes" from
            appearing as question-marks in Mozilla Thunderbird.
          + [24]Pathologic Converts relative URLS to absolute URLS so that
            clickable links in your message will work as intended.

Troubleshooting

   Visit the [25]issue queue for support and feature requests.

Related Modules

   Echo
          http://drupal.org/project/echo

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

     * [26]Chris Herberte

Current Maintainer

     * [27]Bob Vincent

References

   1. http://drupal.org/project/htmlmail
   2. http://www.dict.org/bin/Dict?Form=Dict2&Database=*&Query=requirement
   3. http://drupal.org/project/mailsystem
   4. http://drupal.org/documentation/install/modules-themes/modules-5-6
   5. http://drupal.org/project/echo
   6. http://drupal.org/project/emogrifier
   7. http://drupal.org/project/mailmime
   8. http://drupal.org/project/pathologic
   9. http://drupal.org/project/filter_transliteration
  10. http://drupal.org/node/1095278#comment-4219530
  11. http://drupal.org/files/images/htmlmail_settings_2.thumbnail.png
  12. http://drupal.org/project/mailsystem
  13. http://drupal.org/project/htmlmail
  14. http://api.drupal.org/api/drupal/modules--system--system.mail.inc/class/DefaultMailSystem/7
  15. http://api.drupal.org/api/drupal/includes--mail.inc/function/drupal_mail_system/7
  16. http://drupal.org/project/htmlmail
  17. http://drupal.org/documentation/theme
  18. http://drupal.org/project/echo
  19. http://drupal.org/project/themes
  20. http://drupal.org/documentation/theme
  21. http://drupal.org/project/modules/?filters=type%3Aproject_project%20tid%3A63%20hash%3A1hbejm%20-bs_project_sandbox%3A1%20bs_project_has_releases%3A1
  22. http://drupal.org/project/emogrifier
  23. http://drupal.org/project/filter_transliteration
  24. http://drupal.org/project/pathologic
  25. http://drupal.org/project/issues/htmlmail
  26. http://drupal.org/user/1171
  27. http://drupal.org/user/36148
