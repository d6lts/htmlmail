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

[11]Updating from previous versions

     * Check the module dependencies, as they have changed. The latest
       version of [12]HTML Mail depends on the [13]Mail System module and
       will not work without it.
     * The user-interface for adding email header and footer text has been
       removed. Headers and footers may be added by template files and/or
       by enabling the [14]Echo module.
     * Any customized filters should be carefully tested, as some of the
       template variables have changed. Full documentation is provided
       both on the module configuration page (Click on the Instructions
       link) and as comments in the htmlmail.tpl.php file itself.
     * The following options have been removed from the module settings
       page. In their place, any combination of [15]over 200 filter
       modules may be used to create an email-specific [16]text format for
       post-template filtering.
          + [17]Line break converter,
          + [18]URL Filter,
          + [19]Emogrifier,
          + [20]Token support
     * Full MIME handling, including automatic generation of a plaintext
       alternative part and conversion of images references to inline
       image attachments, is available simply by enabling the [21]Mail
       MIME module.

[22]Configuration

   Visit the [23]Mail System settings page at admin/settings/mailsystem to
   select which parts of Drupal will use [24]HTML Mail instead of the
   [25]default [26]mail system.

   Visit the [27]HTML Mail settings page at admin/settings/htmlmail to
   select a theme and post-filter for your messages.

[28]Theming

   The email message text goes through three transformations before
   sending:
    1. Template File
       A template file is applied to your message header, subject, and
       body text. The default template is the included htmlmail.tpl.php
       file. You may copy this file to your email theme directory
       (selected below), and use it to customize the contents and
       formatting of your messages. The comments within that file contain
       complete documentation on its usage.
    2. Theming
       You may choose a theme that will hold your templates from Step 1
       above. If the [29]Echo module is installed, this theme will also be
       used to wrap your templated text in a webpage. You use any one of
       [30]over 800 themes to style your messages, or [31]create your own
       for even more power and flexibility.
    3. Post-filtering
       You may choose a text format to be used for filtering email
       messages after theming. This allows you to use any combination of
       [32]over 200 filter modules to make final changes to your message
       before sending.
       Here is a recommended configuration:
          + [33]Emogrifier Converts stylesheets to inline style rules for
            consistent display on mobile devices and webmail.
          + [34]Transliteration Converts non-ASCII text to US-ASCII
            equivalents. This helps prevent Microsoft "smart-quotes" from
            appearing as question-marks in Mozilla Thunderbird.
          + [35]Pathologic Converts relative URLS to absolute URLS so that
            clickable links in your message will work as intended.

Troubleshooting

   Visit the [36]issue queue for support and feature requests.

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

     * [37]Chris Herberte

Current Maintainer

     * [38]Bob Vincent

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
  11. http://drupal.org/node/250790
  12. http://drupal.org/project/htmlmail
  13. http://drupal.org/project/mailsystem
  14. http://drupal.org/project/echo
  15. http://drupal.org/project/modules/?filters=type%3Aproject_project%20tid%3A63%20hash%3A1hbejm%20-bs_project_sandbox%3A1%20bs_project_has_releases%3A1
  16. http://drupal.org/node/779050
  17. http://api.drupal.org/api/drupal/modules--filter--filter.module/function/_filter_autop/6
  18. http://api.drupal.org/api/drupal/modules--filter--filter.module/function/_filter_url/6
  19. http://drupal.org/project/emogrifier
  20. http://drupal.org/project/token
  21. http://drupal.org/project/mailmime
  22. http://drupal.org/files/images/htmlmail_settings_2.thumbnail.png
  23. http://drupal.org/project/mailsystem
  24. http://drupal.org/project/htmlmail
  25. http://api.drupal.org/api/drupal/modules--system--system.mail.inc/class/DefaultMailSystem/7
  26. http://api.drupal.org/api/drupal/includes--mail.inc/function/drupal_mail_system/7
  27. http://drupal.org/project/htmlmail
  28. http://drupal.org/documentation/theme
  29. http://drupal.org/project/echo
  30. http://drupal.org/project/themes
  31. http://drupal.org/documentation/theme
  32. http://drupal.org/project/modules/?filters=type%3Aproject_project%20tid%3A63%20hash%3A1hbejm%20-bs_project_sandbox%3A1%20bs_project_has_releases%3A1
  33. http://drupal.org/project/emogrifier
  34. http://drupal.org/project/filter_transliteration
  35. http://drupal.org/project/pathologic
  36. http://drupal.org/project/issues/htmlmail
  37. http://drupal.org/user/1171
  38. http://drupal.org/user/36148
