# add-value-to-array

Adds a given value into the array ***plus*** checks if the array exists.

**Will create a new array in 'global' scope, if one not present.** This saves a few lines of code.

```xml
<cms:call 'add-value-to-array' job 'my_todo' />
```

Expected values are &mdash;
* string `""`
* array `[]`
* object `{}`

## Parameters

* value
* array

## Related tags

* [**Tweakus-Dilectus &raquo; show_json**](https://github.com/trendoman/Tweakus-Dilectus/tree/main/anton.cms%40ya.ru__tags-new/show_json/)

## Related pages

* [**Midware Core Concepts &raquo; Couch Arrays**](https://github.com/trendoman/Midware/tree/main/concepts/Arrays)

## Installation

```xml
<cms:embed 'funcs/JSON/add-value-to-array/add-value-to-array.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
