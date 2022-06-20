# invalidate-cache

Function invalidates Couch cache.

```xml
<cms:call 'invalidate-cache' />
```

Visit [**Midware concepts &raquo; Caching Pages**](#related-pages) to read about how Couch cache works. In essence, to invalidate cache, Couch creates a fresh file –

`couch/cache/cache_invalidate.dat`

Using the parameter **_invalidate_cache** in 'cms:db_persist', 'cms:db_persist_form' tags in page-view or in a form would have the same effect.

Function **invalidate-cache** is not bound by constraints of views or forms and is fully detached from mentioned tags therefore gives flexibility to build various caching strategies.

## Parameters

Function does not take any parameter.

## Usage

Unpublishing pages in batch (i.e. old blog posts dated before the beginning of this year) might need cache invalidated after the operation is complete e.g.

```xml
<cms:pages masterpage='old-blog.php' stop_before="<cms:date 'last day of last year' />" skip_custom_fields='1'>
   <cms:call 'unpublish-by-id' id=k_page_id />
   <cms:if k_paginated_bottom>
      <cms:call 'invalidate-cache' />
   </cms:if>
</cms:pages>
```

Code above is optimized for performance plus minimizes file operations. If only a handful of pages were to be processed tag 'cms:db_persist' would suffice e.g.

```xml
<cms:pages masterpage='old-blog.php' stop_before="<cms:date 'last day of last year' />" skip_custom_fields='1'>
   <cms:db_persist _mode='edit' _masterpage=k_template_name _page_id=k_page_id _invalidate_cache='1' />
</cms:pages>
```

## Related tags

* **db_persist**
* [**Midware Tags Reference &raquo; call**](https://github.com/trendoman/Midware/tree/main/tags-reference/call.md)
* [**Midware Tags Reference &raquo; date**](https://github.com/trendoman/Midware/tree/main/tags-reference/date.md)
<!--* [**Documentation &raquo; pages**](https://docs.couchcms.com/tags-reference/pages.html)-->

## Related funcs

* [**Cache &raquo; uncache-by-pagelink**](https://github.com/trendoman/Cms-Fu/tree/master/Cache/uncache-by-pagelink)
* [**Database &raquo; unpublish-by-id**](https://github.com/trendoman/Cms-Fu/tree/master/Database/unpublish-by-id)

## Related pages

* [**Midware Core Concepts &raquo; Caching Pages**](https://github.com/trendoman/Midware/tree/main/concepts/Caching-Pages/)

## Installation

```xml
<cms:embed 'funcs/Server/invalidate-cache/invalidate-cache.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
