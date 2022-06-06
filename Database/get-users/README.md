# get-users

Fetch users with a certain access level.

```html
<cms:call 'get-users' '10' />
```
Result &mdash;

```txt
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

As a reminder, Couch sets following levels &mdash;

| `access_level` |    name   	|      title |
|:-------:| :--------- | :---------- |
|    1    | superadmin | Super Admin |
|    2    | admin      | Administrator |
|    3    | authenticated_user_special | Authenticated User (Special) |
|    4    | authenitcated_user         | Authenticated User |
|    5    | unauthenticated_user       | Everybody |

More details in documentation on [Users and Access Control](https://docs.couchcms.com/concepts/users.html).

## Usage

Enumerate with 'cms:each' &mdash;
```html
<cms:set myusers = "<cms:call 'get-users' access_level='10' />" is_json='1' />

<cms:each myusers as='user' is_json='1'>
    <cms:show user.k_page_title /><br>
    <cms:show user.extended_user_email /><br>
</cms:each>
```
Pretty print with my **show_json** tag &mdash;
```html
<cms:show_json "<cms:call 'get-users' access_level='10' />" no_validate='1' />
```
(Details about **show_json** can be found in the [README](https://github.com/trendoman/Tweakus-Dilectus/blob/main/anton.cms%40ya.ru__tags-new/__readme__show_json.md))
