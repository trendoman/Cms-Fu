# log-html

Wraps message with `<br>` and sends it to `<cms:log>`.

Default filename is *my_log.html* instead of *my_log.txt*.

## Parameters
* msg
* file

## Usage
```html
<cms:call 'log-html' 'Hello' />
```
```html
<cms:call 'log-html' msg="<cms:dump />" file='dump.html'/>
```
