# trim-tags

Removes unwanted HTML tags from around the richtext content.

```xml
<cms:call 'trim-tags' html=my_richtext tags='p, br' />
```

## Parameters

* **html**
* **tags**

Default value of parameter **tags** is ***p, br***

## Example

Pass a string or multiline richtext content to the tag and define list of unwanted tags e.g.

```xml
<cms:set mystr = '  <p> <span>Welcome!<br><p>Thanks!</p> </p><br /> ' />
<cms:call 'trim-tags' mystr 'p, br, span' />

→ <span>Welcome!<br><p>Thanks!</p>
```

Processing is recursive —

* first, 'br' is removed from the right side of the string in the above snippet.
* Second, opening **and** closing 'p' will trimmed from the start and end of the string respectively, because 'p' is treated as a non self-closed tag.
* Next, 'span' will be left untouched, because it lacks closing 'span'.
* Finally, last 'p' surrounding 'Thanks!' will not be touched, because it encloses only a part of the string, therefore can not be considered for 'trimming'.


Self-closed tags are: *area, base, br, col, embed, hr, img, input, link, meta, param, source, track, wbr*.

## Related tags

* [**Documentation &raquo; excerptHTML**](https://docs.couchcms.com/tags-reference/excerptHTML.html)

## Installation

**Use [Autoloading](https://github.com/trendoman/Cms-Fu/tree/master/ADDON-FUNCS-ON-DEMAND.md),**

or, alternatively, manually copy the func code to the page before the calling or embed func as a snippet —

```xml
<cms:embed 'funcs/Converters/trim-tags/trim-tags.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
