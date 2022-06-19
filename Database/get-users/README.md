# get-users

Fetch users with a certain access level.

```xml
<cms:call 'get-users' '10' />
```

Result &mdash;

```js
[
    {
          "k_page_name" : "admin"
        , "k_page_title" : "Admin"
        , "extended_user_email" : "admin@example.com"
        , "extended_user_id" : "1"
    }
]
```

## Parameters

* access_level

Couch sets following levels &mdash;

| `access_level` |    name   	|      title |
|:-------:| :--------- | :---------- |
|    1    | superadmin | Super Admin |
|    2    | admin      | Administrator |
|    3    | authenticated_user_special | Authenticated User (Special) |
|    4    | authenitcated_user         | Authenticated User |
|    5    | unauthenticated_user       | Everybody |

More details in [**Documentation &raquo; Users and Access Control**](https://docs.couchcms.com/concepts/users.html).

## Usage

Enumerate with 'cms:each' &mdash;

```xml
<cms:set myusers = "<cms:call 'get-users' access_level='10' />" is_json='1' />

<cms:each myusers as='user' is_json='1'>
    <cms:show user.k_page_title /><br>
    <cms:show user.extended_user_email /><br>
</cms:each>
```

Pretty print with my **show_json** tag &mdash;

```xml
<cms:show_json "<cms:call 'get-users' access_level='10' />" no_validate='1' />
```

## Related pages

* [**Documentation &raquo; Users and Access Control**](https://docs.couchcms.com/concepts/users.html)

## Related tags

* [**Tweakus-Dilectus &raquo; show_json**](https://github.com/trendoman/Tweakus-Dilectus/tree/main/anton.cms%40ya.ru__tags-new/show_json/)

## Installation

```xml
<cms:embed 'funcs/Database/get-users/get-users.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
