# is-file

Returns ***1*** if the filename exists and is a regular file, ***0*** otherwise.

```xml
<cms:call 'is-file' file />
```

## Parameters

* **file**

   Takes either relative to website's folder path or full disk path or site's link to file.

## Usage

Use in conditional as follows:

```xml
<cms:if "<cms:call 'is-file' 'index.php' />">...</cms:if>
```

## Installation

**Use [Autoloading](https://github.com/trendoman/Cms-Fu/tree/master/ADDON-FUNCS-ON-DEMAND.md),**

or, alternatively, manually copy the func code to the page before the calling or embed func as a snippet —

```xml
<cms:embed 'funcs/Validate/is-file/is-file.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
