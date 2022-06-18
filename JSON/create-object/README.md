# create-object

Given unlimited number of named params, returns valid JSON.

```xml
<cms:call 'create-object' name='Vagabond' type='Yacht' is_cat='1' has_sail='YES' />
```
Results in –

```json
{"name":"Vagabond","type":"Yacht","is_cat":"1","has_sail":"YES"}
```

## Parameters

Any number of named parameters.

## Installation

```xml
<cms:embed 'funcs/JSON/create-object/create-object.func' />
```

## Related tags

* [**Tweakus-Dilectus &raquo; show_json**](https://github.com/trendoman/Tweakus-Dilectus/tree/main/anton.cms%40ya.ru__tags-new/show_json/)

## Related pages

* [**Midware tutorials &raquo; Couch Arrays**](https://github.com/trendoman/Midware/tree/main/tutorials/Arrays)

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
