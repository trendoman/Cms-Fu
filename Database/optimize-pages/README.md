# optimize-pages

Function returns a random token to the 'cms:pages'. This random token is tracked by the func's code to tweak a few default parameters of 'cms:pages' to make it work faster.

```xml
<cms:pages masterpage='' token="<cms:call 'optimize-pages' />" />
```

Such simple code turns on the 'performance' profile for 'cms:pages' by default. In some cases it is quicker than write the full list of params e.g.


```xml
<cms:pages masterpage='' show_future_entries='1' skip_custom_fields='1' show_unpublished='1' stop_before='' limit='1000000' />
```

Also function exposes 'drafts' as an absolutely new parameter for optimization. See the complete reference of tweaks —

### a. optimized existing parameters —

* **show_future_entries**

   Optimized default is *1* to avoid extra filter by *publish_date*.

* **stop_before**

   Optimized default is the very next 15-minute interval i.e. *HH:15:00, HH:30:00, HH:45:00, HH:00:00*. If there is some query cache in the chain, query result won't expire *the next second* for the same or another visitor.

* **skip_custom_fields**

   Optimized value is *1*. Fields like 'k_page_date', 'k_page_link', 'k_page_title', 'k_page_name' are available without custom fields. And if a field or two is needed, then it is faster to query them separately with 'cms:get_field'.

* **show_unpublished**

   Optimized value is *1* to avoid extra filter by '0000-00-00' date.

* **limit**

   Optimized value is set to *1,000,000* (one million) if **paginate** parameter is not set with 'cms:pages'. Standard default is *1000*.

### b. optimized new component —

* **drafts**

   Optimized setting is to include drafts into listing. By default 'cms:pages' adds extra check to exclude drafts. Rarely used feature adds a filter to every query even if not necessary. This component can be turned on and off by adding **skip_drafts** parameter to 'cms:pages'.


---

**NOTE: Override the optimized values by adding parameters to 'cms:pages'. Function will respect values set manually.**

## Examples

### SQL Inspector

As a rule of thumb, every tweak of 'cms:pages' must be verified by examining generated SQL request.

Write all necessary parameters to the original un-optimized tag and add **return_sql** to it e.g.

```xml
<h2>Original 'pages'</h2>
<cms:pages masterpage= ...  return_sql='1'/>
```

Then add another tag with identical parameters but this time add **token** and call our function —

```xml
<h2>Optimized 'pages'</h2>
<cms:pages masterpage= ... token="<cms:call 'optimize-pages' />" return_sql='1'/>
```

Tweak parameters and examine the changes.

### Override optimized values

State explicitly the parameter that needs a default value in tag's params. If custom fields are required then do this –

```xml
<cms:pages masterpage= ... token="<cms:call 'optimize-pages' />" skip_custom_fields='0' />
```

If any other parameter from the list of existing parameters is added to the tag, function will respect the manually added value e.g.

```xml
<cms:pages masterpage= ... token="<cms:call 'optimize-pages' />" limit='4' stop_before="<cms:date 'yesterday' format='Y-m-d H:i:s' />" />
```

### Drafts included

Instruct 'cms:pages' to use default behavior for drafts i.e. to exclude them by adding new parameter **skip_drafts** –

```xml
<cms:pages masterpage= ... token="<cms:call 'optimize-pages' />" skip_drafts='0' />
```

Without that parameter or with explicitly stated `skip_drafts='1'`, tag 'cms:pages' will be optimized.

### Token

A few words about 'tokens'. These are used to 'track' tags and connect some code to the exact 'cms:pages' and not some other 'cms:pages'. Function **optimize-pages** will create a unique token and supply it to the particular 'cms:pages', so that no other 'cms:pages' would be changed.

## Parameters

Function itself does not take any parameters.

## Related tags

* **pages**
* **get_field**

## Installation

```xml
<cms:embed 'funcs/Database/optimize-pages/optimize-pages.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
