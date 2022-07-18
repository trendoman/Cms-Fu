# login

Function allows to bypass forms and login a user programmatically.

```xml
<cms:call 'login' 'admin' 'passw0rd' />
```

This func should not be used online, because of obvious consequences of auto-login with provided credentials. ☺

## Parameters

* username
* password
* email
* id
* redirect

### username
### email
### id

Parameter **username** declared as first parameter and can be provided without explicit parameter name. If, instead, **email** or user **id** is used, then names must be present e.g.

```xml
<cms:call 'login' email='admin@admin.com' password='passw0rd' />
```

### redirect

Default value is ***2***. Meaning of all values follows:

* ***0***

   do not redirect

* ***1***, ***@current***

   redirect to current page (full request path including the querystring)

* ***2***, ***@qs***, ___""___ *(empty)*

   link supplied as querystring parameter (this is default behaviour) i.e. ***?redirect=/***

* *link*

   Any link directly supplied to the parameter will be used. Some examples –

   * redirect=&quot;&lt;cms:link masterpage='welcome.php' /&gt;&quot;
   * redirect=&quot;&lt;cms:admin_link /&gt;&quot;
   * redirect=k_site_link
   * redirect=k_user_edit_link

## Usage

Drop the call in a snippet that is loaded for all templates. Helpful during development stage, as Couch will never ask for your password again. Assuming your name is *admin* and password is also *admin* the following is what needs to be copied –

```xml
<cms:call 'login' 'admin' 'admin' />
```

---

Function employs standard-issue Couch addon **[extended-users](#related-pages)** and its tag **[process_login](#related-tags)**. Refer to documentation with provided links on the tag and addon. Func auto-loads required addon file, so you don't need to configure anything.

---

Upon successful login, a flash message ***logged_in*** will be set and can be captured via code –

```xml
<cms:get_flash 'logged_in' />
```

Unsuccessful login will only log a message to `log.txt` in website's root directory with a message:

> Error: login via tag "process_login" in func "login" failed for user: "admin" password: "password"

## Related tags

* **[Midware Tags Reference » process_login](https://github.com/trendoman/Midware/tree/main/tags-reference/Extended-Users/process_login.md#process_login--extended-users)**

## Related pages

* **[Midware Core Concepts » Extended Users](https://github.com/trendoman/Midware/tree/main/concepts/Extended-Users)**

## Installation

**Use [Autoloading](https://github.com/trendoman/Cms-Fu/tree/master/ADDON-FUNCS-ON-DEMAND.md),**

or, alternatively, manually copy the func code to the page before the calling or embed func as a snippet —

```xml
<cms:embed 'funcs/Server/login/login.func' />
```

## Support

[![Mail](https://img.shields.io/badge/gmail-%23539CFF.svg?&style=for-the-badge&logo=gmail&logoColor=white)](mailto:"Anton"<tony.smirnov@gmail.com>?subject=[GitHub])

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
