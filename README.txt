HTML Mail empowers Drupal with the ability to send emails in HTML. I know that this is widely frowned upon but we should not be inflexible to it.

This module presently is very simple in operation. It changes email headers to tell the recipient the email is in Raw HTML or "HTML email", as opposed to HTML as a multipart MIME attachment or embedded.

By default, template tags are inserted and all you have to worry about is what goes between the body tags. There is an option to override this and an entire HTML document could then be inserted into the email body.

Remember that many email clients will not be happy with certain code, your CSS may conflict with a web-mail providers CSS and HTML in email may expose security hazards. Beyond this, if your still really, really must have HTML in your email, ie. my current employer d:-{), you may find this module useful.