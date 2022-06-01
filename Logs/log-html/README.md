# log-html

Wraps message with `<br>` and sends it to `<cms:log>`.
```html
<cms:call 'log-html' 'Hello' />
```

Default filename is *my_log.html* instead of *my_log.txt*.

## Parameters
* msg
* file

## Usage
Common application is to log HTML-based output of tags, such as **dump** or **dump_all**
```html
<cms:call 'log-html' msg="<cms:dump />" file='dump.html'/>
```
