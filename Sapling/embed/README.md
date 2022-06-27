# embed

Function **embed** *embeds* a snippet with parameters and a user-defined *callback* function.

```xml
<cms:call 'embed' 'snippet.inc' />
```

There is an extra check for the presence of the file.

This function is inspired by the [**Sapling**](#related-pages) project.

## Parameters

* **snippet**

   File to embed, searched within `couch/snippets` directory or the one set via `couch/config.php`.

* **udf**

   Abbreviation stands for __*U*ser-*D*efined&nbsp;*F*unction__. Parameter's value is the name of an udf.

## Example

### Simple embed

Ordinary embed works almost like **cms:embed** tag, with **additional check for snippet's presence**. Basically, function employs available Couch tag **cms:exists** so you don't need to write that extra condition i.e. a snippet will be loaded only if it exists. There is nothing to be added to the call besides the name e.g.

```xml
<cms:call 'embed' 'snippet.inc' />
```

Next, if you are familiar with how [**cms:func**](#related-tags) tag works internally (if not, click the link and read my docs), you'd remember that it sets a few useful variables, namely ***k_args*** and ***k_named_args***. This is where it gets interesting:

### Passing parameters

Suppose, you have placed a bootstrap component 'Progress bar' in a snippet called 'bs/progress-bar.html' with following content —

```html
<div class="progress">
   <div class="bar" style="width: 60%;"></div>
</div>
```

We'd like to be able to embed that snippet too, but set width dynamically using a simple one-liner as in –

```xml
<cms:call 'embed' snippet='bs/progress-bar.html' width='60%' />
```

With the call above it is possible, with only one change in our snippet HTML —

```html
<div class="progress">
   <div class="bar" style="width: <cms:show k_named_args.width />;"></div>
</div>
```

Notice, how the HTML has been amended to use a variable instead of some percentage (as in '60%'). Variable's name consists of 2 parts: ***k_named_args*** and ***width***. If you are not familiar with [**Couch Arrays**](#related-pages), the explanation is that *width* is a key in JSON object named *k_named_args*. If we print that object (*which is set automatically for all calls, by [**cms:func**](#related-tags) tag*), the object will show all named parameters passed to a func via 'cms:call' e.g.

```js
{
   "snippet":"bs/progress-bar.html",
   "width":"50%"
}
```

– *Beautiful!*\
We can add as many parameters as we want, right into the call, for instance —

```xml
<cms:call 'embed' snippet='some-other-snippet.html' name='Anton' content='<h1>Hello!</h1>' />
```

– and placing code `<cms:show k_named_args as_json='1' />` to the `some-other-snippet.html` file we can see the complete JSON object e.g.

```js
{
   "snippet":"some-other-snippet.html",
   "name":"Anton",
   "content":"<h1>Hello!</h1>"
}
```

It is possible to pass anything – text, HTML, variables, arrays or Couch code (as string). Values can be used as follows –

```html
Dear <cms:show k_named_args.name />! We have a message for you:

<cms:show k_named_args.content />
```

In a real-world scenario, the code of the snippet may be more complex, e.g. contain some 'listing' code that must be tweaked depending on the current logged-in user. Dynamically changed dropdown with cities where a lot of `<option>` stays not selected but one option is selected requires a string-replacement code. But it will be inefficient to re-generate such list each page load. A snippet containing all cities can be generated once, saved to disk and embedded with a single parameter - current user's city! Code will set one option as *selected* in that static list and be done. It becomes a real deal, to be able to load snippet with parameters.

---

I have to admit, snippets with parameters behave *almost* like a function 'cms:func'. But a few key differences are nevertheless striking: functions must be embedded first, then called; while a snippet is only embedded. Next, functions are a bit more generic; snippets can be very, *very* granular – down to a single bootstrap component or even smaller. Also, functions are often designed to be called with strictly defined parameters, while snippets may define parameters 'on-the-fly' and use them loosely. Last, but not the least, snippets do not have any 'wrapping' code - their content is HTML, JS, JSON, CSS and whatever else you design them to hold, even **without any Couch tags** whatsoever.

---

With that more or less de-fogged, let's take the example with cities from the preceding paragraph and see an alternative way to process a snippet. Pass a parameter **udf** and see what happens next:

### UDF *callback*

```xml
<cms:call 'embed' snippet='cities.inc' udf='process-result'/>
```

A *callback* is simply another function that will be called by our **embed** func. It's purpose is solely defined by you, the writer. As we see, parameter **udf** is set with value *process-result* – let's create this function and place it before the call to 'embed' e.g.

```xml
<cms:func 'process-result' result=''>
   <cms:trim result />
</cms:func>
<cms:call 'embed' snippet='cities.inc' udf='process-result'/>
```

---

**NOTE:** You must become informed, that with **udf** bearing a name of an existing function, **the snippet will be embedded into a variable first**. There will be **no echo-ing at all**, because this option means that you've taken the sail in your hands and became responsible for it.

---

With such "código débil" as a simplistic 'show trimmed result', the outcome is a printed snippet, as if embedded directly. If a snippet is not found, **this is the only way to see the error generated by Couch** – by using a custom function printing the passed variable holding the result of 'embed'.

Let's amend the code to illustrate a basic principle of working with the callback function. We'll be adding a condition and some 'processing' in a pseudo-code –

```xml
<cms:func 'replace-city' result='' city=city_of_current_user>
   <cms:set myoption = "<option value='<cms:show city />'><cms:show city /></option>" />
   <cms:set myoption_active = "<option  selected  value='<cms:show city />'><cms:show city /></option>" />
   <cms:if "<cms:tag_exists 'replace' />">
      <cms:replace what=myoption with=myoption_active where=result />
   <cms:else />
      <cms:php>echo str_replace(
         '<cms:show myoption />',
         '<cms:show myoption_active />',
         '<cms:show result />');
      </cms:php>
   </cms:if>
</cms:func>

<cms:call 'embed' snippet='cities.inc' udf='replace-city'/>
```

I hope you'll agree that by taking out the generic 'processing' code and keeping it separately from the embedded data we acquired a function that can be **a)** applied to any similar data in the future, and **b)** it became replaceable in our 'embed' call. The latter is **very important**, because from now on, you can apply any kind of activity to the embedded code by changing the single parameter — the **udf** callback ☺.

```xml
<cms:call 'embed' snippet='cities.inc' udf='highlight-searched-keyword'/>
```

Do not hesitate to [**contact**](#support) me to discuss any further applications.

## Variables

Same variables that are being set by 'cms:func' are *available within the snippet* i.e.

* **k_named_args**
* **k_args**

Print them with 'cms:show' or custom 'cms:show_json' tags.

```xml
<cms:show k_named_args as_json='1'/>
<cms:show_json k_named_args />
```

Plus an unnamed variable holding content of the snippet is passed to the callback and can be received under any name, for instance:

* **result**

## Related Tags

* [**Documentation &raquo; embed**](https://docs.couchcms.com/tags-reference/embed.html)
* [**Midware Tags Reference &raquo; func**](https://github.com/trendoman/Midware/tree/main/tags-reference/func.md)
* [**Midware Tags Reference &raquo; call**](https://github.com/trendoman/Midware/tree/main/tags-reference/call.md)
* [**Tweakus-Dilectus Modded Tags &raquo; call**](https://github.com/trendoman/Tweakus-Dilectus/tree/main/anton.cms%40ya.ru__tags-modded/call)

## Related pages

* [**GroveOS » Sapling**](https://github.com/GroveOS/Sapling) — A CouchCMS starter codebase that implements MVC patterns and shell script automation.
* [**Midware Core Concepts &raquo; Couch Arrays**](https://github.com/trendoman/Midware/tree/main/concepts/Arrays)

## Installation

```xml
<cms:embed 'funcs/Sapling/embed/embed.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
