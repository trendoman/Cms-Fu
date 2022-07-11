# error-log

Print something to PHP's error_log.

```xml
<cms:call 'error-log' myvar />
```

Func has aliases: **log-php, php-log** with the same parameters.

## Parameters

* **msg**
* **delete**

## Usage

Func can delete error_log to clear it, before printing strings or Couch variables (including arrays)

```xml
<cms:call 'error-log' k_user_name '1'/>
```

PHP Variables may be sent as well e.g.

```xml
<cms:call 'error-log' '$myvar' />
```

example with objects properties –

```xml
<cms:call 'error-log' '$FUNCS->funcs' />
```

Strings and arrays are printed with info about length and count respectively. Objects and properties include their names.

```
[12-Jul-2022 00:10:06 Europe/Moscow] .:: Object $FUNCS->funcs ::.
[12-Jul-2022 00:10:06 Europe/Moscow] ______________________
...
[12-Jul-2022 00:12:44 Europe/Moscow] .:: String(2) ::.
[12-Jul-2022 00:12:44 Europe/Moscow] ______________________
[12-Jul-2022 00:12:44 Europe/Moscow]
[12-Jul-2022 00:12:44 Europe/Moscow] -1
...
```

## Related funcs

* [**Cms-Fu &raquo; log-html**](https://github.com/trendoman/Cms-Fu/tree/master/Logs/log-html)

## Related tags

* [**Documentation &raquo; log**](https://docs.couchcms.com/tags-reference/log.html)
* [**Midware Tags Reference &raquo; delete_file**](https://github.com/trendoman/Midware/tree/main/tags-reference/delete_file.md)

## Installation

**Use [Autoloading](https://github.com/trendoman/Cms-Fu/tree/master/ADDON-FUNCS-ON-DEMAND.md),**

or, alternatively, manually copy the func code to the page before the calling or embed func as a snippet —

```xml
<cms:embed 'funcs/Logs/error-log/error-log.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
