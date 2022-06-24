# date-to-english-words

Convert a date to words in English.

```xml
<cms:call 'date-to-english-words' />
```

## Parameters

* **date**

   Date is expected to be in **Y-m-d** format. If skipped, current date (today) will be used.

* **print_func**

   Name of a custom function that will accept result as JSON and print it as you prefer.

## Example

No date specified –

```xml
<cms:call 'date-to-english-words' />
```

`Twenty-fourth of June, Two Thousand and Twenty Two` — which is today's date

Date formatted as **Y-m-d**:

```xml
<cms:call 'date-to-english-words' date='1945-05-09' />
```

– prints

`Ninth of May, Nineteen Hundred and Fourty Five`

Date formatted as **d-m-Y** –

```xml
<cms:call 'date-to-english-words' date='12-04-1961' />
```

– prints

`Twelfth of April, Nineteen Hundred and Sixty One`

Relative dates, thanks to [**cms:date**](#related-tags) tag –

```xml
<cms:call 'date-to-english-words' date="<cms:date 'first day of January next year' />"/><br>
<cms:call 'date-to-english-words' date="<cms:date '16th September next year' />"/>
```

```
First of January, Two Thousand and Twenty Three
Sixteenth of September, Two Thousand and Twenty Three
```

### Leap year

The leap year rule for the Gregorian Calendar is that excepting century years (ending in 00), every year divisible by 4 is a leap year with a February 29th. Century years are not leap years, unless divisible by 400. Thus 1900 was not a leap year, but 2000 was.

```xml
<cms:call 'date-to-english-words' date='1900-02-29'/>
```

– prints

`First of March, Nineteen Hundred`


And following

```xml
<cms:call 'date-to-english-words' date='2000-02-29'/>
```

– prints

`Twenty-ninth of February, Two Thousand`

## Custom print

Parameter **print_func** must have a value of a function declared before the call to **date-to-english-words** e.g.

```xml
<cms:func 'custom-print' result=''>
   <cms:show result.year_hi_num /><cms:show result.year_lo_num /> / <cms:show result.month /> / <cms:show result.day />
</cms:func>
```

Above code shows a custom function which **must accept one named parameter**. Then place func's name as a value to **print_func** e.g.

```xml
<cms:call 'date-to-english-words' date='2022-12-31' print_func='custom-print'/>
```

And the custom output will be:

`2022 / December / Thirty-first`

Function **date-to-english-words** sends a JSON object that contains word- & numeric- representation of the date e.g.

```js
{
   "day":"Thirty-first",
   "month":"December",
   "year_hi":"Two Thousand",
   "year_lo":"Twenty Two",
   "day_num":"31",
   "month_num":"12",
   "year_hi_num":"20",
   "year_lo_num":"22"
}
```

– so that you can construct any kind of custom output.

If the output needs to be changed to **lowercase, UPPERCASE, Titlecase** – look at [**modded cms:show**](#related-tags) tag.

Also visit docs on [**cms:func**](#related-tags) to see more examples of *callbacks*, such as above.

## Other languages

Create a copy of the function, edit the func's name and its content by writing-in words for your language e.g for spanish –

```xml
<cms:set words_0_to_19 = '[ "Cero",

   "Uno", "Dos", "Tres", "Cuatro", "Cinco",..etc
```

– or simply send me a [**message**](#support).

## Related tags

* [**Midware Tags Reference &raquo; date**](https://github.com/trendoman/Midware/tree/main/tags-reference/date.md)
* [**Midware Tags Reference &raquo; call**](https://github.com/trendoman/Midware/tree/main/tags-reference/call.md)
* [**Midware Tags Reference &raquo; func**](https://github.com/trendoman/Midware/tree/main/tags-reference/func.md)
* [**Tweakus-Dilectus Modded Tags &raquo; show**](https://github.com/trendoman/Tweakus-Dilectus/tree/main/anton.cms%40ya.ru__tags-modded/show)

## Installation

```xml
<cms:embed 'funcs/DateTime/date-to-english-words/date-to-english-words.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
