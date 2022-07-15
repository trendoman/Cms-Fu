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


## Related funcs

* **[Cms-Fu &raquo; log-php](https://github.com/trendoman/Cms-Fu/tree/master/Logs/log-php)**

## Related tags

* **[Documentation &raquo; log](https://docs.couchcms.com/tags-reference/log.html)**
* **[Midware Tags Reference &raquo; trim](https://github.com/trendoman/Midware/tree/main/tags-reference/trim.md)**
* **[Tweakus-Dilectus Tags » delete_file](https://github.com/trendoman/Tweakus-Dilectus/tree/main/anton.cms%40ya.ru__tags-new/delete_file)**

## Installation

```xml
<cms:embed 'funcs/Logs/log-html/log-html.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
