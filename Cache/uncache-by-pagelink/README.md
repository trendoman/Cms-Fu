# uncache-by-pagelink

Removes cache file from disk given page's URL.

```xml
<cms:call 'uncache-by-pagelink' k_template_link />
```

Function has no output.

## Parameters

* link

[**Couch Cache**](#related-pages) treats same pages with different query strings in URL as separate cached entities. Set link with due attention to query string params and values.

## Usage

Func is most useful in situations where invalidation of complete cache is unwarranted.

Take for example a submitted databound form that changed only a minor thing in fields, without cross-dependencies from other pages or templates. Set parameter **_invalidate_cache** of tag 'cms:db_persist_form' to *0* and bust page's cache selectively e.g.

```xml
<cms:form ..>
   ...
   <cms:if k_success >

      <cms:db_persist_form
        _invalidate_cache='0'
      />

      <cms:call 'uncache-by-pagelink' k_page_link />

      <cms:redirect k_page_link />
   </cms:if>
</cms:form>
```

## Related functions

* [**Cache &raquo; invalidate-cache**](/Cache/invalidate-cache)

## Related tags

* **db_persist**
* **db_persist_form**

## Related pages

* [**Midware Core Concepts &raquo; Caching-Pages**](https://github.com/trendoman/Midware/tree/main/concepts/Caching-Pages)

## Installation

```xml
<cms:embed 'funcs/Cache/uncache-by-pagelink/uncache-by-pagelink.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
