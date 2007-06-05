HTML Mail

HTML Mail empowers Drupal with the ability to send emails in HTML. I know that this is widely frowned upon but the flexibility should be there.

This module presently is very simple in operation. It changes email headers to force the mail as 
be Raw HTML, as apposed to HTML as attachment or embedded. An entire HTML document should be inserted into the body, remember that many email clients will not be happy with certain code, your CSS may conflict with a web-mail providers CSS and HTML in email may expose security hazards. Beyond this, if your still really, really must have HTML in your email, you may find this module useful.

Future upgrades to this module may include:
* Multiple formats, ie. user can select HTML or filtered as text.
* 