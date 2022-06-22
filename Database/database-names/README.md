# database-names

Function shows databases on server formatted as JSON –

```js
{
   "my1couch":{
      "name":"my1couch",
      "is_couchcms":true
   },
   "test":{
      "name":"test",
      "is_couchcms":false
   }
}
```

Example above shows 2 databases, one of which holds tables for CouchCMS, following the func's call –

```xml
<cms:call 'database-names' />
```

## Parameters

* only_couch – default value is *0*
* skip_system – default value is *1*

### only_couch

List databases that only hold tables for CouchCMS.

### skip_system

Do not list databases with names **information_schema, mysql, performance_schema, sys**. Default setting is to skip them.

## Example

Show only Couch-related databases:

```xml
<cms:call 'database-names' only_couch='1' />
```

or simply –

```xml
<cms:call 'database-names' '1' />
```

Show all databases, including system ones –

```xml
<cms:call 'database-names' skip_system='0' />
```

That prints –

<details><summary>JSON</summary>

```js
{
   "information_schema":{
      "name":"information_schema",
      "is_couchcms":false
   },
   "my1couch":{
      "name":"my1couch",
      "is_couchcms":true
   },
   "mysql":{
      "name":"mysql",
      "is_couchcms":false
   },
   "performance_schema":{
      "name":"performance_schema",
      "is_couchcms":false
   },
   "sys":{
      "name":"sys",
      "is_couchcms":false
   },
   "test":{
      "name":"test",
      "is_couchcms":false
   }
}
```
</details>

An example to iterate the JSON with 'cms:each' —

```xml
<cms:each "<cms:call 'database-names' />" key='name' as='db' is_json='1'>
   <cms:show name /> <cms:if db.is_couchcms >(CouchCMS)<cms:else />(not Couch)</cms:if><br>
</cms:each>
```

outputs

```
my1couch (CouchCMS)
test (not Couch)
```

## Variables

* **_cached_databases**

Function fetches all database names and caches the result into this variable. Subsequent calls do not query database information but filter already cached information. Variable is placed to the **global** scope, visible with 'cms:dump_all' tag.

May be listed with 'cms:show' or '[**cms:show_json**](#related-tags)' –

```xml
<cms:show _cached_databases as_json='1'/>
<cms:show_json _cached_databases />
```

## Related funcs

* [**Database » database-name**](https://github.com/trendoman/Cms-Fu/tree/master/Database/database-name)

## Related tags

* [**Tweakus-Dilectus &raquo; show_json**](https://github.com/trendoman/Tweakus-Dilectus/tree/main/anton.cms%40ya.ru__tags-new/show_json/)

## Installation

```xml
<cms:embed 'funcs/Database/database-names/database-names.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
