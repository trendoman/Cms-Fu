# inr-format

Function applies **Indian Rupee** formatting to the number.

```xml
<cms:call 'inr-format' '1123456789' />
```

Output of the call above –

`₹ 1,12,34,56,789.00`

Currency symbol is added before the number.

---

**NOTE:** Function **inr-format** piggybacks on [**cms:number_format**](#related-tags) tag. If you have it modded (i.e. tweaked rounding of decimals), it will be respected.

## Parameters

* **val**

Must *not* contain currency symbol. Please use only a number.

## Example

Automatically fix spaced or comma-separated numbers e.g.

```xml
<cms:call 'inr-format' '1 123 456 789' />

<cms:call 'inr-format' '456,789.00' />
```

– outputs

`₹ 1,12,34,56,789.00`

and

`₹ 4,56,789.00`

## Related tags

* [**Documentation &raquo; number_format**](https://docs.couchcms.com/tags-reference/number_format.html)

## Related pages

* [**Tips&Tricks » number_format**](https://www.couchcms.com/forum/viewtopic.php?f=8&t=11423#p34927) — a modded version of **cms:number_format** on CouchCMS forum.
* [**Feature Requests » Place Value Systems**](https://www.couchcms.com/forum/viewtopic.php?f=3&t=13250) — a forum request about money formatting by **@genxcoders**.

## Installation

```xml
<cms:embed 'funcs/Money/inr-format/inr-format.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
