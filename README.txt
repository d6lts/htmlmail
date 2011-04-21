[1]HTML Mail

   Lets you theme your messages the same way you theme the rest of your
   website.

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

   The [12]6.x-2.x branch shares 97% of its code with the [13]7.x-2.x
   branch, but only 8% of its code with the [14]6.x-1.x branch.

   Let your compatibility expectations be adjusted accordingly.
     * Check the module dependencies, as they have changed. The latest
       version of [15]HTML Mail depends on the [16]Mail System module and
       will not work without it.
     * The user-interface for adding email header and footer text has been
       removed. Headers and footers may be added by template files and/or
       by enabling the [17]Echo module.
     * Any customized filters should be carefully tested, as some of the
       template variables have changed. Full documentation is provided
       both on the module configuration page (Click on the Instructions
       link) and as comments within the htmlmail.tpl.php file itself.
     * The following options have been removed from the module settings
       page. In their place, any combination of [18]over 200 filter
       modules may be used to create an email-specific [19]text format for
       post-template filtering.
          + [20]Line break converter
          + [21]URL Filter
          + [22]Relative Path to Absolute URLs
          + [23]Emogrifier
          + [24]Token support
     * Full MIME handling, including automatic generation of a plaintext
       alternative part and conversion of image references to inline image
       attachments, is available simply by enabling the [25]Mail MIME
       module.

[26]Configuration

   Visit the [27]Mail System settings page at admin/settings/mailsystem to
   select which parts of Drupal will use [28]HTML Mail instead of the
   [29]default [30]mail system.

   Visit the [31]HTML Mail settings page at admin/settings/htmlmail to
   select a theme and post-filter for your messages.

[32]Theming

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
       above. If the [33]Echo module is installed, this theme will also be
       used to wrap your templated text in a webpage. You use any one of
       [34]over 800 themes to style your messages, or [35]create your own
       for even more power and flexibility.
    3. Post-filtering
       You may choose a [36]text format to be used for filtering email
       messages after theming. This allows you to use any combination of
       [37]over 200 filter modules to make final changes to your message
       before sending.
       Here is a recommended configuration:
          + [38]Emogrifier Converts stylesheets to inline style rules for
            consistent display on mobile devices and webmail.
          + [39]Transliteration Converts non-ASCII text to US-ASCII
            equivalents. This helps prevent Microsoft "smart-quotes" from
            appearing as question-marks in Mozilla Thunderbird.
          + [40]Pathologic Converts relative URLS to absolute URLS so that
            clickable links in your message will work as intended.

Troubleshooting

     * Double-check the [41]Mail System module settings and and make sure
       you selected HTMLMailSystem for your Site-wide default mail system.
     * Try selecting the [ ] (Optional) Debug checkbox at the [42]HTML
       Mail module settings page and re-sending your message.
     * Clear your cache after changing any .tpl.php files.
     * Visit the [43]issue queue for support and feature requests.

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

[44]Documentation

   [45]filter.module
          [46]api.drupal.org/api/drupal/modules--filter--filter.module

   [47]Installing contributed modules
          [48]drupal.org/documentation/install/modules-themes/modules-5-6

   [49]Theming guide
          [50]drupal.org/documentation/theme

Original Author

     * [51]Chris Herberte

Current Maintainer

     * [52]Bob Vincent

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
  12. http://drupal.org/node/1119548
  13. http://drupal.org/node/1106064
  14. http://drupal.org/node/329828
  15. http://drupal.org/project/htmlmail
  16. http://drupal.org/project/mailsystem
  17. http://drupal.org/project/echo
  18. http://drupal.org/project/modules/?filters=type%3Aproject_project%20tid%3A63%20hash%3A1hbejm%20-bs_project_sandbox%3A1%20bs_project_has_releases%3A1
  19. http://drupal.org/node/779050
  20. http://api.drupal.org/api/drupal/modules--filter--filter.module/function/_filter_autop/6
  21. http://api.drupal.org/api/drupal/modules--filter--filter.module/function/_filter_url/6
  22. http://drupal.org/project/rel_to_abs
  23. http://www.pelagodesign.com/sidecar/emogrifier/
  24. http://drupal.org/project/token
  25. http://drupal.org/project/mailmime
  26. http://drupal.org/files/images/htmlmail_settings_2.thumbnail.png
  27. http://drupal.org/project/mailsystem
  28. http://drupal.org/project/htmlmail
  29. http://api.drupal.org/api/drupal/modules--system--system.mail.inc/class/DefaultMailSystem/7
  30. http://api.drupal.org/api/drupal/includes--mail.inc/function/drupal_mail_system/7
  31. http://drupal.org/project/htmlmail
  32. http://drupal.org/documentation/theme
  33. http://drupal.org/project/echo
  34. http://drupal.org/project/themes
  35. http://drupal.org/documentation/theme
  36. http://drupal.org/node/779050
  37. http://drupal.org/project/modules/?filters=type%3Aproject_project%20tid%3A63%20hash%3A1hbejm%20-bs_project_sandbox%3A1%20bs_project_has_releases%3A1
  38. http://drupal.org/project/emogrifier
  39. http://drupal.org/project/filter_transliteration
  40. http://drupal.org/project/pathologic
  41. http://drupal.org/project/mailsystem
  42. http://drupal.org/project/htmlmail
  43. http://drupal.org/project/issues/htmlmail
  44. http://drupal.org/project/documentation
  45. http://api.drupal.org/api/drupal/modules--filter--filter.module/6
  46. http://api.drupal.org/api/drupal/modules--filter--filter.module/6
  47. http://drupal.org/documentation/install/modules-themes/modules-5-6
  48. http://drupal.org/documentation/install/modules-themes/modules-5-6
  49. http://drupal.org/documentation/theme
  50. http://drupal.org/documentation/theme
  51. http://drupal.org/user/1171
  52. http://drupal.org/user/36148
