# unpublish-by-id

Unpublish a page if supplied with id of page.

```xml
<cms:call 'unpublish-by-id' id='' />
```

Function will return *1* upon success or *0* if page was not found.

Input value is validated then sanitized by Couch before processing.

Func does the job with only 1 query to database.

## Parameters

* id – non-negative integer (*1*, *2*, etc...)

## Example

```xml
<cms:hide><cms:call 'unpublish-by-id' '11234' /></cms:hide>
```

Code above will not output result.

Can pass a variable –

```xml
<cms:call 'unpublish-by-id' k_page_id />
```

In a condition –

```xml
<cms:if "<cms:call 'unpublish-by-id' k_page_id />"><cms:else />Page not found!</cms:if>
```

Function will not invalidate complete cache by itself (tag 'cms:db_persist' does that). Use additional funcs, e.g.

```xml
<cms:if "<cms:call 'unpublish-by-id' k_page_id />"><cms:call 'uncache-by-pagelink' k_page_link /><cms:else />Page not found!</cms:if>
```

– or bust full cache with

```xml
<cms:call 'invalidate-cache' />
```

## Related tags

* **db_persist**

## Installation

```xml
<cms:embed 'funcs/Database/unpublish-by-id/unpublish-by-id.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
