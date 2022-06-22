# database-name

Print name of the database.

```xml
<cms:call 'database-name' />
```

Function has an alias –

```xml
<cms:call 'db-name' />
```

Basically, it is an eye-candy alternative to PHP code –

```xml
<cms:php>echo K_DB_NAME;</cms:php>
```

or, if you has access to the variable [**k__defined**](#related-pages), then it goes as –

```xml
<cms:show k__defined.K_DB_NAME />
```

## Parameters

None.

## Related funcs

* [**Database » database-names**](https://github.com/trendoman/Cms-Fu/tree/master/Database/database-names)

## Related pages

* [**Tweakus-Dilectus Variables &raquo; k__defined**](https://github.com/trendoman/Tweakus-Dilectus/tree/main/anton.cms%40ya.ru__variables-new/k__defined)

## Installation

```xml
<cms:embed 'funcs/Database/database-name/database-name.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
