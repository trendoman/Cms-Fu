# inr-format

Function applies **Indian Rupee** formatting to the number.

```xml
<cms:call 'inr-format' '1123456789' />
```

Output of the call above –

`1,12,34,56,789`

## Parameters

* **val**

   Can have a `+` or `-` sign and decimal part, but every other non-digit symbol will be removed, including spaces.

## Example

Automatically fixes following problematic input values —

* spaces or commas are removed
* any other non-digit symbol is also removed (signs are kept only if placed first)

```xml
<pre>
<br><cms:call 'inr-format' '1 123 456 789' />
<br><cms:call 'inr-format' '456,789.00' />
<br><cms:call 'inr-format' '45789.--' />
<br><cms:call 'inr-format' '4579.' />
<br><cms:call 'inr-format' '456' />
<br><cms:call 'inr-format' '46' />
</pre>
```

— prints

```
1,12,34,56,789
4,56,789.00
45,789
4,579
456
46
```

With more complicated cases –

```xml
<pre>
<br><cms:call 'inr-format' '046' />
<br><cms:call 'inr-format' '.46' />
<br><cms:call 'inr-format' '00.46' />
<br><cms:call 'inr-format' '00.468' />
<br><cms:call 'inr-format' '1234.4689' />
<br><cms:call 'inr-format' '+1689' />
<br><cms:call 'inr-format' '--1689.001' />
<br><cms:call 'inr-format' '₹ +1689.00' />
<br><cms:call 'inr-format' '1/68/899.25' />
<br><cms:call 'inr-format' '1.68.899.25' />
</pre>
```

– the result is

```
46
0.46
0.46
0.468
1,234.4689
+1,689
-1,689.001
+1,689.00
1,68,899.25
1.68
```

### number_format

Pre-format numbers with [**cms:number_format**](#related-tags) if decimal part needs some work (including rounding or trimming) e.g.

```xml
<cms:call 'inr-format' val="<cms:number_format '1234567890' decimal_precision='4' />" />
```

result is

`1,23,45,67,890.0000`

## Related tags

* [**Documentation &raquo; number_format**](https://docs.couchcms.com/tags-reference/number_format.html)
* [**Tips&Tricks » number_format**](https://www.couchcms.com/forum/viewtopic.php?f=8&t=11423#p34927) — a modded version of **cms:number_format** on CouchCMS forum with rounding option.

## Related pages

* [**Feature Requests » Place Value Systems**](https://www.couchcms.com/forum/viewtopic.php?f=3&t=13250) — a forum request about money formatting by **@genxcoders**.

## Installation

```xml
<cms:embed 'funcs/Money/inr-format/inr-format.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
