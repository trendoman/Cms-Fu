# unpublish-by-name

Unpublish a page if supplied with name of page and masterpage.

```xml
<cms:call 'unpublish-by-name' 'blog.php' 'my-old-post'/>
```

Function will return *1* upon success or *0* if page was not found.

Input value is validated then sanitized by Couch before processing.

## Parameters

* masterpage
* name

## Example

```xml
<cms:hide><cms:call 'unpublish-by-name' 'blog.php' 'my-old-post'/></cms:hide>
```

Code above will not output result.

Can pass a variable –

```xml
<cms:call 'unpublish-by-name' k_template_name k_page_name />
```

In a condition –

```xml
<cms:if "<cms:call 'unpublish-by-name' k_template_name k_page_name />"><cms:else />Page not found!</cms:if>
```

Function will not invalidate complete cache by itself (tag 'cms:db_persist' does that). Use additional funcs, e.g.

```xml
<cms:if "<cms:call 'unpublish-by-name' k_template_name k_page_name />"><cms:call 'uncache-by-pagelink' k_page_link /><cms:else />Page not found!</cms:if>
```

– or bust full cache with

```xml
<cms:call 'invalidate-cache' />
```

## Code intel

Func is not optimized to the teeth, uses 3 Couch tags that produces queries to db – 'page_exists', 'pages' and 'db_persist'. The latter fetches complete page with all fields. Employment of native tags leads to sending quite a few queries (min 4, max ~) to database. Func [**unpublish-by-id**](#related-funcs) is much faster (1 query) for batch ops.

## Related funcs

* [**Database &raquo; unpublish-by-id**](/Database/unpublish-by-id)

## Related tags

* **db_persist**

## Installation

```xml
<cms:embed 'funcs/Database/unpublish-by-name/unpublish-by-name.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
