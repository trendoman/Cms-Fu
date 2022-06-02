# sleep

Make server wait. Count in seconds.
Example -
```html
<cms:call 'sleep' for='0.500' />
```
```html
<cms:call 'sleep' '1' />
```

## Parameters

* for &mdash; time in seconds

## Usage

Add 'sleeping' code that imitates a heavy page loading for a while (*5* seconds)
```html
<cms:call 'sleep' '5' />
```
It equals to &ndash;
```html
<cms:php>usleep(1000000 * 5);</cms:php>
```
