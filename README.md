# [Cms-Fu](https://github.com/trendoman/Cms-Fu)

 The indomitable set of **'cms:func'** functions for CouchCMS

> First time? Visit [**CouchCMS &raquo; website**](http://couchcms.com/) to explore this TIME-TESTED and SECURE CMS. It's perfect for designers and is open source! See the [**CouchCMS &raquo; GitHub**](https://github.com/CouchCMS/CouchCMS) repository.

## Contents

Please visit [**CHANGELOG**](/CHANGELOG.md) and explore directories in repository.

## Installation

1. Clone the repo (or download [**master.zip**](https://github.com/trendoman/Cms-Fu/archive/refs/heads/master.zip)) to the 'snippets' directory (default is `couch/snippets`). Rename repo locally as **funcs** —

   ```shell
   cd /var/www/html/example.com/mysnippets
   ```
   ```shell
   git clone http://github.com/trendoman/Cms-Fu funcs
   ```

2. Use [**Autoloading**](ADDON-FUNCS-ON-DEMAND.md) or either copy the func's code in the page or **&lt;cms:embed&gt;** the func's file, e.g.

   ```xml
   <cms:embed 'funcs/DateTime/clock/clock.func' />
   ```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
