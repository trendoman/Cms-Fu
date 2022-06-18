# log-html

Writes message to a HTML file.

```xml
<cms:call 'log-html' '<h1>Hello</h1>' />
```

Default filename is **my_log.html**.

## Parameters

* msg
* file

## Usage

Common application is to log HTML-based output of tags, such as **dump** or **dump_all**

```xml
<cms:call 'log-html' msg="<cms:dump />" file='dump.html'/>
```

Any content may be sent to log –

```xml
<cms:call 'log-html' msg=my_variable />
```

preprocessed with 'trim' –

```xml
<cms:call 'log-html' msg="<cms:trim my_variable />" />
```

Internally, function wraps message with `<br>` and employs 'cms:log' tag to write the file.


## Related tags

* [**Documentation &raquo; log**](https://docs.couchcms.com/tags-reference/log.html)
* [**Midware Tags Reference &raquo; trim**](https://github.com/trendoman/Midware/tree/main/tags-reference/trim.md)

## Installation

```xml
<cms:embed 'funcs/Logs/log-html/log-html.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
