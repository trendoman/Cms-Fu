# show-ms

Show milliseconds of current time.

```html
<cms:call 'show-ms' />
```

## Parameters

## Usage

```html
<cms:repeat '3'>
    <cms:nl2br>

        <cms:date format='Y-m-d H:i:s' /> <cms:call 'show-ms' /><cms:call 'sleep' '0.01' />
    </cms:nl2br>
</cms:repeat>
```
Notice how we had to call the **sleep** func to wait at least *10 milliseconds* before the next 'repeat'. Otherwise the output would be identical.<br>
Result &mdash;
```txt
2022-06-02 18:45:54 753
2022-06-02 18:45:54 773
2022-06-02 18:45:54 788
```
