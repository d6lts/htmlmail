When formatting an email message, Drupal determines the active template
directory by looking for <cite>htmlmail.tpl.php</cite> file in the following locations:

*    [path\_to\_theme()](http://api.drupal.org/api/drupal/includes--theme.inc/function/path\_to\_theme/7)
*    [drupal\_get\_path(](http://api.drupal.org/api/drupal/includes--common.inc/function/drupal\_get\_path/7)"module", [$installed\_profile](http://api.drupal.org/api/drupal/developer--globals.php/global/installed\_profile/7))
*    [drupal\_get\_path(](http://api.drupal.org/api/drupal/includes--common.inc/function/drupal\_get\_path/7)"module", ["htmlmail"](http://drupal.org/project/htmlmail))

Once the active template directory is found, Drupal looks in that directory
for template files in order from most specific to most general.

For example, if <cite>foo\_module</cite> sends mail with:

<code>
    drupal\_mail("foo\_module", "outgoing\_message" ...)
</code>

the possible template file names would be:

*    <code>htmlmail-foo\_module\_outgoing\_message.tpl.php</code>
*    <code>htmlmail-foo\_module\_outgoing.tpl.php</code>
*    <code>htmlmail-foo\_module.tpl.php</code>
*    <code>htmlmail.tpl.php</code>

The <code>$theme\_hook\_suggestions</code> variable contains an array of suggested
[theme](http://api.drupal.org/api/drupal/includes--theme.inc/function/theme/7)
[hooks](http://api.drupal.org/api/drupal/modules--system--system.api.php/function/hook\_theme/7),
in reverse priority order.  For the above example, it would contain:

*    <code>htmlmail</code>
*    <code>htmlmail-foo\_module</code>
*    <code>htmlmail-foo\_module\_outgoing</code>
*    <code>htmlmail-foo\_module\_outgoing\_message</code>

For another example, to customize the
[password reset](http://api.drupal.org/api/drupal/modules--user--user.pages.inc/function/user\_pass\_submit/7)
emails sent by the
[user module](http://api.drupal.org/api/drupal/modules--user--user.module/7),
copy <code>htmlmail.tpl.php</code> to your theme directory, and also
copy it to <code>htmlmail-user\_password\_reset.tpl.php</code>, then modify the
latter file. Remember that you will need to put *both* files in your theme
directory for this to work.

Template files are cached, so remember to clear the cache by visiting
<cite>admin/settings/performance</cite> after creating, copying, or editing any
<code>.tpl.php</code> files.

The following variables are also available in this template:

<code>$body</code>
:    The message body text.

<code>$module</code>
:    The sending module name, usually the first parameter to drupal\_mail().

<code>$key</code>
:    The message key, usually the second parameter to drupal\_mail().

<code>\$message\_id</code>
:    The email message id, usually "{\$module}\_{\$key}".

<code>$debug</code>
:    TRUE if debugging info should be printed.

<code>$directory</code>
:    The relative path to the theme template directory.

<code>$theme\_url</code>
:    The absolute URL to the theme directory.

The module calling
[drupal\_mail()](http://api.drupal.org/api/drupal/includes--mail.inc/function/drupal\_mail/7)
may set other variables.  For instance, the
[Webform module](http://drupal.org/project/webform)
sets a <code>$node</code> variable which may be very useful.

Other modules may also add or modify theme variables by implementing a
<code>MODULENAME\_preprocess\_htmlmail()</code>
[hook function](http://api.drupal.org/api/drupal/modules--system--theme.api.php/function/hook_preprocess_HOOK/7).
