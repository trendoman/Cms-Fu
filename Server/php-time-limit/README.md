# php-time-limit

Override maximum time for executing a PHP script.

```html
<cms:call 'php-time-limit' '600' />
<cms:call 'php-time-limit' '0' />
```
Timeout in seconds.

## Parameters

* timeout &mdash; `0` is unlimited timeout, otherwise counted in seconds. Default is `120`.

## Installation

```xml
<cms:embed 'funcs/Server/php-time-limit/php-time-limit.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
