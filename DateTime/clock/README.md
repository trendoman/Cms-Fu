# clock

Records time and memo.

```html
<cms:call 'clock' memo='Timer started'/>
```

Unlimited number of memos are kept in the global variable **clock**.

Format of time is **Y-m-d H:i:s** with optional milliseconds.

## Parameters

* __memo__ — a message that will be stored alongside current time.

## Usage

Designed to track tag's time, this function will keep memos and times in a list.

### record

```html
<cms:call 'clock' memo='Tag :pages start'/>

.. some probably long-executing code ..
<cms:pages masterpage=k_template_name limit='10000' />

<cms:call 'clock' memo='Tag :pages end'/>
```

### print

Print the result to review where the bottleneck is —
```html
<cms:show_json clock />
```
Or, if you are unsure whether tag **show_json** is available, use tag **show** with parameter **as_json** &mdash;
```html
<cms:if "<cms:tag_exists 'show_json' />">
  <cms:show_json clock />
<cms:else />
  <cms:show clock as_json='1' />
</cms:if>
```

### result

```json
{
   "13:11:03 139":"Tag :pages start",
   "13:11:03 173":"Tag :pages end"
}
```

## Installation


```html
<cms:embed 'funcs/DateTime/clock/clock.func' />
```

## Requirements

### optional

* [__show-ms__](../show-ms/) &mdash; this is a function that displays milliseconds. Add it to your stack of functions to record time with precision.

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
