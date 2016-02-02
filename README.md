# mod_writable

Assuming you have the dependencies you can build and enable via:

    $ sudo make

This will install the module on a Debian GNU/Linux system.

Once installed reload:

    $ sudo service apache2 restart

## Dependencies

    apt-get install build-essential apache2-dev

## Testing

Create the file `/var/www/html/index.php` with the contents:

    <?php phpinfo(); ?>

If you restart Apache after running `make` to install the module, as root, you should find you see the PHP info page as normal.

Now make the file writeable:

    chmod 777 /var/www/html/index.php

Visiting your site should now show a HTTP 403 error, and the following logged:

    [Tue Feb 02 19:17:04.222904 2016] [:crit] [pid 8366]
    Refusing to serve the writeable file /var/www/html/index.php

