When formatting an email message, Drupal determines the active template
directory by looking for `htmlmail.tpl.php` file in the following locations:

*    [path\_to\_theme()](http://api.drupal.org/api/drupal/includes--theme.inc/function/path\_to\_theme/7)
*    [drupal\_get\_path(](http://api.drupal.org/api/drupal/includes--common.inc/function/drupal\_get\_path/7)"module", [$installed\_profile](http://api.drupal.org/api/drupal/developer--globals.php/global/installed\_profile/7))
*    [drupal\_get\_path(](http://api.drupal.org/api/drupal/includes--common.inc/function/drupal\_get\_path/7)"module", ["htmlmail"](http://drupal.org/project/htmlmail))

Once the active template directory is found, Drupal looks in that directory
for template files in order from most specific to most general.

For example, if `example\_module` sends mail with:

`
    drupal\_mail("example\_module", "outgoing\_message" ...)
`

the possible template file names would be:

*    `htmlmail-example\_module\_outgoing\_message.tpl.php`
*    `htmlmail-example\_module\_outgoing.tpl.php`
*    `htmlmail-example\_module.tpl.php`
*    `htmlmail.tpl.php`

The `$theme\_hook\_suggestions` variable contains an array of suggested
[theme](http://api.drupal.org/api/drupal/includes--theme.inc/function/theme/7)
[hooks](http://api.drupal.org/api/drupal/modules--system--system.api.php/function/hook\_theme/7),
in reverse priority order.  For the above example, it would contain:

*    `htmlmail`
*    `htmlmail-example\_module`
*    `htmlmail-example\_module\_outgoing`
*    `htmlmail-example\_module\_outgoing\_message`

For another example, to customize the
[password reset](http://api.drupal.org/api/drupal/modules--user--user.pages.inc/function/user\_pass\_submit/7)
emails sent by the
[user module](http://api.drupal.org/api/drupal/modules--user--user.module/7),
copy `htmlmail.tpl.php` to your theme directory, and also
copy it to `htmlmail-user\_password\_reset.tpl.php`, then modify the
latter file. Remember that you will need to put *both* files in your theme
directory for this to work.

Template files are cached, so remember to clear the cache by visiting
_admin/settings/performance_ after creating, copying, or editing any
`.tpl.php` files.

The following variables are also available in this template:

`$body`
:    The message body text.

`$module`
:    The sending module name, usually the first parameter to drupal\_mail().

`$key`
:    The message key, usually the second parameter to drupal\_mail().

`\$message\_id`
:    The email message id, usually "{\$module}\_{\$key}".

`$debug`
:    TRUE if debugging info should be printed.

`$directory`
:    The relative path to the theme template directory.

`$theme\_url`
:    The absolute URL to the theme directory.

The module calling
[drupal\_mail()](http://api.drupal.org/api/drupal/includes--mail.inc/function/drupal\_mail/7)
may set other variables.  For instance, the
[Webform module](http://drupal.org/project/webform)
sets a `$node` variable which may be very useful.

Other modules may also add or modify theme variables by implementing a
`MODULENAME\_preprocess\_htmlmail()`
[hook function](http://api.drupal.org/api/drupal/modules--system--theme.api.php/function/hook_preprocess_HOOK/7).
