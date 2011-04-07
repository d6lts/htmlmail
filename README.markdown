## HTML Mail

[HTML Mail](http://drupal.org/project/htmlmail) lets you theme your outgoing
messages the same way you theme the rest of your website.

## Requirements

*   [Mail System](http://drupal.org/project/mailsystem)

## Installation

[Install as usual.](http://drupal.org/documentation/install/modules-themes/modules-5-6)

The following additional modules, while not required, are highly recommended:

*   [Emogrifier](http://drupal.org/project/emogrifier)

*   [Mail MIME](http://drupal.org/project/mailmime)

*   [Pathologic](http://drupal.org/project/pathologic)

*   [Transliteration](http://drupal.org/project/filter_transliteration)

    *Also available as a [patch](http://drupal.org/node/1095278#comment-4219530).*

## Configuration

Visit the [Mail System](http://drupal.org/project/mailsystem) settings page at
<u>admin/settings/mailsystem</u> to select which parts of Drupal will use
[HTML Mail](http://drupal.org/project/htmlmail) instead of the
[default](http://api.drupal.org/api/drupal/modules--system--system.mail.inc/class/DefaultMailSystem/7)
[mail system](http://api.drupal.org/api/drupal/includes--mail.inc/function/drupal_mail_system/7).

Visit the [HTML Mail](http://drupal.org/project/htmlmail) settings page at
<u>admin/settings/htmlmail</u> to select a theme, pre-filter,
and post-filter for your messages.

## Theming

The email message text goes through three transformations before sending:

1.  <h3>Template File</h3>
    A template file is applied to your message header, subject, and body text.
    The default template is the included `htmlmail.tpl.php` file.  You may copy
    this file to your default theme directory and use it to customize the
    contents and formatting of your messages.  The comments within that file
    contain complete documentation on its usage.

2.  <h3>Theming</h3>
    *(Optional: requires [Echo](http://drupal.org/project/echo) module.)*
    The templated text may be wrapped in a website theme.  This lets you
    use any one of [over 800](http://drupal.org/project/themes) themes to
    style your messages.  Creating an email-specific sub-theme lets you use
    the full power of the
    [drupal theme system](http://drupal.org/documentation/theme)
    to format your messages.

3.  <h3>Post-filtering</h3>
    You may choose a <cite>text format</cite> to be used for filtering email
    messages *after* theming. This allows you to use any combination of
    [over 200 filter modules](http://drupal.org/project/modules/?filters=type%3Aproject_project%20tid%3A63%20hash%3A1hbejm%20-bs_project_sandbox%3A1%20bs_project_has_releases%3A1)
    to make final changes to your message before sending.

    Here is a recommended configuration:

    *   [Emogrifier](http://drupal.org/project/emogrifier)
        Converts stylesheets to inline style rules for consistent display on
        mobile devices and webmail.

    *   [Transliteration](http://drupal.org/project/filter_transliteration)
        Converts non-ASCII text to US-ASCII equivalents.  This helps prevent
        Microsoft "smart-quotes" from appearing as question-marks in
        Mozilla Thunderbird.

    *   [Pathologic](http://drupal.org/project/pathologic)
        Converts relative URLS to absolute URLS so that clickable links in
        your message will work as intended.

## Troubleshooting

Visit the [issue queue](http://drupal.org/project/issues/htmlmail) for support
and feature requests.

## Related Modules

**Emogrifier**
:   http://drupal.org/project/emogrifier

**HTML Purifier**
:   http://drupal.org/project/htmlpurifier

**htmLawed**
:   http://drupal.org/project/htmlawed

**Mail MIME**
:   http://drupal.org/project/mailmime

**Mail System**
:   http://drupal.org/project/mailsystem

**Pathologic**
:   http://drupal.org/project/pathologic

**Transliteration**
:   http://drupal.org/project/transliteration

## Documentation

**filter.module**
:   D6: http://api.drupal.org/api/drupal/modules--filter--filter.module/6
:   D7: http://api.drupal.org/api/drupal/modules--filter--filter.module/7

**Installing contributed modules**
:   D6: http://drupal.org/documentation/install/modules-themes/modules-5-6
:   D7: http://drupal.org/documentation/install/modules-themes/modules-7

**Theming guide**
:   http://drupal.org/documentation/theme

## Original Author

*   [Chris Herberte](http://drupal.org/user/1171)

## Current Maintainer

*   [Bob Vincent](http://drupal.org/user/36148)
