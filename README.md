# [Cms-Fu](https://github.com/trendoman/Cms-Fu)

 The indomitable set of **'cms:func'** functions for CouchCMS

> First time? Visit [**CouchCMS &raquo; website**](http://couchcms.com/) to explore this TIME-TESTED and SECURE CMS. It's perfect for designers and is open source! See the [**CouchCMS &raquo; GitHub**](https://github.com/CouchCMS/CouchCMS) repository.

## Contents

Please visit [**CHANGELOG**](/CHANGELOG.md) and explore directories in repository.

## Installation

1. Clone the repo to your defined in config.php **`snippets`** folder (or default one, `couch/snippets`) and name repo locally as **`func`** &mdash;
   ```shell
   cd /var/www/html/example.com/mysnippets
   ```
   ```shell
   git clone http://github.com/trendoman/Cms-Fu funcs
   ```
   - or download zip &ndash; [master.zip](https://github.com/trendoman/Cms-Fu/archive/refs/heads/master.zip)

2. Register the desired function via **cms:embed**
   ```xml
   <cms:embed 'funcs/DateTime/clock/clock.func' />
   ```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
