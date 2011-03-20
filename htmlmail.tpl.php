<?php

/**
 * @file
 * Default template for HTML Mail
 *
 * DO NOT EDIT THIS FILE. Copy it to your theme directory, and edit the copy.
 *
 **************************************************** Begin instructions.
 *
 * When formatting an email message, Drupal determines the active template
 * directory by looking for htmlmail.tpl.php file in the following
 * locations:
 *   * [1]path_to_theme()
 *   * [2]drupal_get_path("module", [3]$installed_profile)
 *   * [4]drupal_get_path("module", [5]"htmlmail")
 * 
 * Once the active template directory is found, Drupal looks in that
 * directory for template files in order from most specific to most
 * general.
 * 
 * For example, if foo_module sends mail with:
 * 
 * drupal_mail("foo_module", "outgoing_message" ...)
 * 
 * the possible template file names would be:
 *   * htmlmail-foo_module_outgoing_message.tpl.php
 *   * htmlmail-foo_module_outgoing.tpl.php
 *   * htmlmail-foo_module.tpl.php
 *   * htmlmail.tpl.php
 * 
 * The $theme_hook_suggestions variable contains an array of suggested
 * [6]theme [7]hooks, in reverse priority order. For the above example, it
 * would contain:
 *   * htmlmail
 *   * htmlmail-foo_module
 *   * htmlmail-foo_module_outgoing
 *   * htmlmail-foo_module_outgoing_message
 * 
 * For another example, to customize the [8]password reset emails sent by
 * the [9]user module, copy htmlmail.tpl.php to your theme directory, and
 * also copy it to htmlmail-user_password_reset.tpl.php, then modify the
 * latter file. Remember that you will need to put both files in your
 * theme directory for this to work.
 * 
 * Template files are cached, so remember to clear the cache by visiting
 * admin/settings/performance after creating, copying, or editing any
 * .tpl.php files.
 * 
 * The following variables are also available in this template:
 * 
 * $body
 *        The message body text.
 * 
 * $module
 *        The sending module name, usually the first parameter to
 *        drupal_mail().
 * 
 * $key
 *        The message key, usually the second parameter to drupal_mail().
 * 
 * $message_id
 *        The email message id, usually "{$module}_{$key}".
 * 
 * $theme
 *        The name of the email-specific theme used to embed the message
 *        body into a fully-themed webpage.
 * 
 *        Note: This may be different from the default website theme.
 *        Theme suggestion templates such as html.tpl.php should be copied
 *        to the website theme directory, not the email theme directory.
 * 
 * $directory
 *        The relative path to the website theme template directory
 *        (Again, this is different from the email theme directory, which
 *        is not used for templates).
 * 
 * $theme_url
 *        The absolute URL to the website theme directory.
 * 
 * $debug
 *        TRUE if debugging info should be printed.
 * 
 * The module calling [10]drupal_mail() may set other variables. For
 * instance, the [11]Webform module sets a $node variable which may be
 * very useful.
 * 
 * Other modules may also add or modify theme variables by implementing a
 * MODULENAME_preprocess_htmlmail() [12]hook function.
 * 
 * References
 * 
 * 1. http://api.drupal.org/api/drupal/includes--theme.inc/function/path_to_theme/7
 * 2. http://api.drupal.org/api/drupal/includes--common.inc/function/drupal_get_path/7
 * 3. http://api.drupal.org/api/drupal/developer--globals.php/global/installed_profile/7
 * 4. http://api.drupal.org/api/drupal/includes--common.inc/function/drupal_get_path/7
 * 5. http://drupal.org/project/htmlmail
 * 6. http://api.drupal.org/api/drupal/includes--theme.inc/function/theme/7
 * 7. http://api.drupal.org/api/drupal/modules--system--system.api.php/function/hook_theme/7
 * 8. http://api.drupal.org/api/drupal/modules--user--user.pages.inc/function/user_pass_submit/7
 * 9. http://api.drupal.org/api/drupal/modules--user--user.module/7
 * 10. http://api.drupal.org/api/drupal/includes--mail.inc/function/drupal_mail/7
 * 11. http://drupal.org/project/webform
 * 12. http://api.drupal.org/api/drupal/modules--system--theme.api.php/function/hook_preprocess_HOOK/7
 *
 ****************************************************** End instructions.
 */
?>
<div class="htmlmail-body">
<?php print $body; ?>
</div>
<?php if ($debug): ?>
<pre class="htmlmail-debug">
Theme hook suggestions: <?php print_r($theme_hook_suggestions); ?>
</pre>
<?php endif; ?>
