<?php

/**
 * @file
 * Sample template for HTML Mail test messages.
 */
?>
<h1><a href="http://drupal.org/project/htmlmail">HTML Mail</a> test message</h1>
<div class="htmlmail-body">
<?php print $body; ?>
</div>
<?php if ($debug): ?>
<hr />
<div class="htmlmail-debug">
  <dl><dt><p>
    To customize this test message:
  </p></dt><dd><ol><li><p>
    Copy
    <a href="http://drupalcode.org/project/htmlmail.git/blob_plain/refs/heads/6.x-2.x:/htmlmail-htmlmail.tpl.php"><code>htmlmail-htmlmail.tpl.php</code></a>
    to your <q><?php echo ucfirst($theme) ?> theme</q> directory
    <u><code><?php echo $theme_path; ?></code></u>.
  </p></li></ul></p></li><li><p>
    Edit your copy of the <u><code>htmlmail-htmlmail.tpl.php</code></u> file.
  </p></li><ol>
</div>
<?php endif;
