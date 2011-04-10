When formatting an email message with a given `$module` and `$key`,
[HTML Mail](http://drupal.org/project/htmlmail)
will use the first template file it finds from the following list:

1.  `htmlmail-$module-$key.tpl.php`
2.  `htmlmail-$module.tpl.php`
3.  `htmlmail.tpl.php`

For each filename,
[HTML Mail](http://drupal.org/project/htmlmail)
looks first in the chosen *Email theme* directory, then in its own
module directory, before proceeding to the next filename.

For example, if `example_module` sends mail with:

    drupal_mail("example_module", "outgoing_message" ...)

the possible template file names would be:

1.  `htmlmail-example-module-outgoing-message.tpl.php`
2.  `htmlmail-example-module.tpl.php`
3.  `htmlmail.tpl.php`

For another example, to customize the
[password reset](http://api.drupal.org/api/drupal/modules--user--user.pages.inc/function/user_pass_submit/6)
messages sent by the
[user module](http://api.drupal.org/api/drupal/modules--user--user.module/6),
copy
[`htmlmail.tpl.php`](http://drupalcode.org/project/htmlmail.git/blob/refs/heads/6.x-2.x:/htmlmail.tpl.php)
to a file called
`htmlmail-user-password-reset.tpl.php`
in your *Email theme* directory, and edit the copy.

Template files are cached, so remember to clear the cache by visiting
<u>admin/settings/performance</u>
after changing any `.tpl.php` files.

The following variables available in this template:

**`$body`**
:   The message body text.

**`$module`**
:   The first argument to
    [`drupal_mail()`](http://api.drupal.org/api/drupal/includes--mail.inc/function/drupal_mail/6),
    which is, by convention, the machine-readable name of the sending module.

**`$key`**
:   The second argument to
    [`drupal_mail()`](http://api.drupal.org/api/drupal/includes--mail.inc/function/drupal_mail/6),
    which should give some indication of why this email is being sent.

**`$message_id`**
:   The email message id, which should be equal to `"{$module}_{$key}"`.

**`$theme`**
:   The name of the *Email theme* used to hold template files. If the
    [Echo](http://drupal.org/project/echo) module is enabled this theme will
    also be used to transform the message body into a fully-themed webpage.

**`$template_path`**
:   The relative path to the template directory.

**`$template_url`**
:   The absolute URL to the template directory.

**`$debug`**
:   `TRUE` to add some useful debugging info to the bottom of the message.

The module calling
[`drupal_mail()`](http://api.drupal.org/api/drupal/includes--mail.inc/function/drupal_mail/6)
may set other variables.  For instance, the
[Webform module](http://drupal.org/project/webform)
sets a `$node` variable which may be very useful.

Other modules may also add or modify theme variables by implementing a
`MODULENAME_preprocess_htmlmail(&$variables)`
[hook function](http://api.drupal.org/api/drupal/modules--system--theme.api.php/function/hook_preprocess_HOOK/7).
