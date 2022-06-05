# is-callable

Is a named or anonymous function available to be called?

Example -
```html
<cms:call 'is-callable' func='myfunc' />
```

## Parameters

* func &mdash; regular (named) or anonymous function

## Usage

Perfect for **callback** functions e.g.
```html
<cms:if "<cms:call 'is-callable' func=callback_func />"><cms:call callback_func myparam /></cms:if>
```
