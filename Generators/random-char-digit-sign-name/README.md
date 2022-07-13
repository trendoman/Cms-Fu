# random-name, -char, -digit, -sign

All functions correctly support UTF-8 charset.

## random-name

Get a random string of chars from **set**. Specify any **length** of chars and any kind of **set**.

```xml
<cms:call 'random-name' />
<cms:call 'random-name' lenght='7' set='ol'/>

→  1rux0y0u
→  lolooll
```

Default **set** is `abcdefghijklmnopqrstuvwxyz0123456789` and default **length** is ***8***.

## random-char

Returns a random char from a specified **set**.

```xml
<cms:call 'random-char' />

→  +
```

Default **set** is `abcdefghijklmnopqrstuvwxyz0123456789/*-+()|\#$%^&@[]{};`

## random-digit

Returns a random digit from a specified **set**.

```xml
<cms:call 'random-digit' set='012'/>

→  1
```

Default **set** is complete set of numbers e.g. ***0123456789***

## random-sign

Returns a random sign from a specified **set**.

```xml
<cms:call 'random-sign' set='↑↓→←'/>

→ ↑
```

Default **set** is plus, minus e.g. ***+–***

## Related tags

* **random_name**

   A built-in Couch tag `<cms:random_name />` returns **fixed 32** lowercase alphanumerics e.g. `330a1f8f04696eca7f29d0a5e90e9a35`.

## Installation

**Use [Autoloading](https://github.com/trendoman/Cms-Fu/tree/master/ADDON-FUNCS-ON-DEMAND.md).**

Alternatively, manually copy the func code to the page before the calling or embed func as a snippet —

```xml
<cms:embed 'funcs/Generators/random-char-digit-sign-name/random-name.func' />
<cms:embed 'funcs/Generators/random-char-digit-sign-name/random-char.func' />
<cms:embed 'funcs/Generators/random-char-digit-sign-name/random-digit.func' />
<cms:embed 'funcs/Generators/random-char-digit-sign-name/random-sign.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
