## HTML Mail

HTML Mail lets you theme your outgoing messages the same way you theme the rest
of your website.

For a full description of the module, visit the
[project page](http://drupal.org/project/htmlmail).

To submit bug reports and feature suggestions, visit the
[issue queue](http://drupal.org/project/issues/htmlmail).

## Requirements

HTML Mail requires the [Mail System](http://drupal.org/project/mailsystem)
module.

## Installation

Install as usual; see
[Installing contributed modules (Drupal 5 and 6)](http://drupal.org/node/70151)
for further information.

The following additional modules, while not required, are highly recommended:

*   [Emogrifier](http://drupal.org/project/emogrifier)

*   [Pathologic](http://drupal.org/project/pathologic)

*   [Transliteration](http://drupal.org/project/transliteration)

    *Requires a [patch](http://drupal.org/node/1095278#comment-4219530).*

## Configuration

Visit the Mail System settings page at _admin/config/system/mailsystem_
to select which parts of Drupal will use HTML Mail instead of the
[default](http://api.drupal.org/api/drupal/modules--system--system.mail.inc/class/DefaultMailSystem/7)
[mail system](http://api.drupal.org/api/drupal/includes--mail.inc/function/drupal_mail_system/7).

Visit the HTML Mail settings page at _admin/config/system/htmlmail_ to
select a theme, pre-filter, and post-filter for your emails.

## Theming

The email message text goes through four transformations before sending:

1.  The *Text format pre-filter* from the module settings page is applied.
    This should be the same text format that your website uses for contributed
    content such as comments or blog postings.  For consistency and security,
    it should include the the
    [Correct faulty and chopped off HTML](http://api.drupal.org/api/drupal/modules--filter--filter.module/function/_filter_htmlcorrector/6)
    from [filter.module](http://api.drupal.org/api/drupal/modules--filter--filter.module/6),
    or a better replacement such as
    [HTML Purifier](http://drupal.org/project/htmlpurifier) or
    [htmLawed](http://drupal.org/project/htmlawed).

2.  A theme template is applied. The default template is the included
    `htmlmail.tpl.php` file.  You may copy this file to your theme directory
    and use it to customize the contents and formatting of your emails.  The
    comments within the file contain complete documentation on its usage.

3.  The message may be wrapped in a website theme selected on the module settings
    page.  Creating an email-specific theme lets you use the full power of the
    [drupal theme system](http://drupal.org/documentation/theme) to format your
    emails.

4.  The *Text format post-filter* from the module settings page is applied. For
    best results, this should be an email-specific input format containing the
    following text format filters:

    * [Transliteration](http://drupal.org/node/1095278#comment-4219530)
    * [Emogrifier](http://drupal.org/project/emogrifier)
    * [Pathologic](http://drupal.org/project/pathologic)
    * [Correct faulty and chopped off HTML](http://api.drupal.org/api/drupal/modules--filter--filter.module/function/_filter_htmlcorrector/6)

## Related Modules

Emogrifier
:    http://drupal.org/project/emogrifier

HTML Purifier
:    http://drupal.org/project/htmlpurifier

htmLawed
:    http://drupal.org/project/htmlawed

Mail MIME
:    http://drupal.org/project/mailmime

Mail System
:    http://drupal.org/project/mailsystem

Pathologic
:    http://drupal.org/project/pathologic

Transliteration
:    http://drupal.org/project/transliteration

## Documentation

filter.module
:    http://api.drupal.org/api/drupal/modules--filter--filter.module/6

Installing contributed modules (Drupal 5 and 6)
:    http://drupal.org/node/70151

Theming guide
:    http://drupal.org/documentation/theme

## Original Author

* [Chris Herberte](http://drupal.org/user/1171)

## Current Maintainer

* [Bob Vincent](http://drupal.org/user/36148)
