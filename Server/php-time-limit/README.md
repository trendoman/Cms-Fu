# php-time-limit

Override maximum time for executing a PHP script.

```html
<cms:call 'php-time-limit' '600' />
<cms:call 'php-time-limit' '0' />
```

Function has aliases –

```xml
<cms:call 'php' />
<cms:call 'php-timeout' />
```

## Parameters

* **timeout**

   Set in seconds. Default is ***120*** seconds and ***0*** is unlimited.

## Installation

**Use [Autoloading](https://github.com/trendoman/Cms-Fu/tree/master/ADDON-FUNCS-ON-DEMAND.md),**

or, alternatively, manually copy the func code to the page before the calling or embed func as a snippet —

```xml
<cms:embed 'funcs/Server/php-time-limit/php-time-limit.func' />
<cms:embed 'funcs/Server/php-time-limit/php-timeout.func' />
<cms:embed 'funcs/Server/php-time-limit/php.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
