# limit-decline

Restricts visitors above the limit.

```html
<cms:call 'limit-decline' '2' 'Please wait..'/>
```
Code above will show a **decline** message to any visitor above the maximum **limit**.

Locks are established for a process, while it lasts. Once the page stops loading (and PHP thread dies) the lock is automatically released, raising the limit.<br>
It means that a visitor may refresh the page and get through, if within the limit.

Locks are maintained by MySQL database and it is quite performant &ndash; 1000 (one thousand) locks can be obtained in less than a second.

## Parameters

* limit &mdash; natural number (above `0`)
* decline &mdash; a text message or code (it will execute *before* trying the lock).


## Usage

1. Limit a page to a single visitor &mdash;
```html
<cms:call 'limit-decline' '1' 'Please wait..'/>
```
2. Add 'sleeping' code that imitates a heavy page loading for a while (*5* seconds)
```html
<cms:php>usleep(1000000 * 5);</cms:php>
```
3. Visit the same page in 2 different browsers simultaneously. You will see a message in one of the windows.
```txt
Please wait..
```
