# is-callable

Is a named or anonymous function available to be called?

```html
<cms:call 'is-callable' func='myfunc' />
```

## Parameters

* func &mdash; regular (named) or anonymous function

## Usage

Perfect for **callback** functions e.g.

```xml
<cms:if "<cms:call 'is-callable' func=callback_func />"><cms:call callback_func myparam /></cms:if>
```

A related tag 'cms:func_exists' works only with named functions, that's why **is-callable** is the better substitution.

## Related tags

* [**Midware Tags Reference &raquo; func_exists**](https://github.com/trendoman/Midware/tree/main/tags-reference/func_exists.md)

## Installation

```xml
<cms:embed 'funcs/Validate/is-callable/is-callable.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
