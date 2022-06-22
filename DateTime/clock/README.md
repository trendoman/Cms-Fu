# clock

Records time with a memo.

```xml
<cms:call 'clock' memo='Timer started'/>
```

Unlimited number of memos are kept in the global variable **clock**.

Format of time is **H:i:s** with optional milliseconds.

## Parameters

* __memo__ — a message that will be stored alongside current time.
* __show__ — will print **clock** as json

## Usage

Designed to track tag's time, this function will keep memos and times in a list.

### record

```xml
<cms:call 'clock' memo='Tag :pages start'/>

.. some probably long-executing code ..
<cms:pages masterpage=k_template_name limit='10000' />

<cms:call 'clock' memo='Tag :pages end'/>
```

### print

Print the result to review where the bottleneck is —

```xml
<cms:show_json clock />
```

Or, if you are unsure whether tag [**show_json**](#related-tags) is available, use tag **show** with parameter **as_json** &mdash;

```xml
<cms:if "<cms:tag_exists 'show_json' />">
  <cms:show_json clock />
<cms:else />
  <cms:show clock as_json='1' />
</cms:if>
```

If parameter **show** is passed to the function, the code above will be executed automatically —

```xml
<cms:call 'clock' 'Tag :pages end' '1' />
```

### result

```json
{
   "13:11:03 139":"Tag :pages start",
   "13:11:03 173":"Tag :pages end"
}
```

## Variables

* **clock**

Set in global scope, this variable keeps all timers and memos.

## Requirements

### optional

* [__show-ms__](../show-ms/) &mdash; this is a function that displays milliseconds. Add it to your stack of functions to record time with precision.

## Related tags

* [**Tweakus-Dilectus &raquo; show_json**](https://github.com/trendoman/Tweakus-Dilectus/tree/main/anton.cms%40ya.ru__tags-new/show_json/)

## Installation

```xml
<cms:embed 'funcs/DateTime/clock/clock.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
