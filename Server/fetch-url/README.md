# fetch-url

 *GET* content of any URL.

```xml
<cms:call 'fetch_url' 'https://www.couchcms.com/' />
```

Func **fetch-url** expects a **cURL** PHP extension, but has an alternative backup 'stream' engine if extension is not available.

## User-defined parameters

Additionally to default parameters listed in the next section, func will read global array **curl** set by you in code with optional keys:

* curl.useragent
* curl.cookies
* curl.referer

For example –

```xml
<cms:set curl = '[]' is_json='1' scope='global' />
<cms:capture into='curl.cookies' trim='1' scope='parent'>
param1=value1;
param2=value2;
PHPSESSID=df0u920id85m0f7efvl2t5fdd;
</cms:capture>
<cms:capture into='curl.useragent' trim='1' scope='parent'>
Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:91.0) Gecko/20100101 Firefox/91.0
</cms:capture>
```

Array **curl** will be looked upon automatically, no need to pass it as a parameter in the call.

Once a request is complete, a key **curl.status** will be added to the variable with output of ***curl_getinfo()*** call (it is an array with information about last request). Print it as usual:

```xml
<cms:call 'fetch-url' mylink />
<cms:show_json curl.status />
```

## Parameters

* url
* as_ajax
* send_cookie
* accept_cookie

### url

Param **url** can be a string or a variable &mdash;

```xml
<cms:call 'fetch_url' k_page_link />
```

### as_ajax

Default value is ***1***. Parameter **as_ajax** allows to imitate Ajax `XMLHttpRequest` requests. Disable that default setting by explicitly setting it to ***0*** –

```xml
<cms:call 'fetch_url' url=other_website as_ajax='0' />
```

### send_cookie

Default value is ***1***. 'Home' requests i.e. same-domain will have additional cookies copied from global **$_COOKIE** variable. That will relay status of the logged-in user, as if the user himself made the request. Outside-the-domain requests will have cookies only copied from user-supplied variable **curl.cookies**. Disable sending 'home' cookies by explicitly stating ***0***:

```xml
<cms:call 'fetch_url' url="<cms:link masterpage='api.php' />" send_cookie='0' />
```

### accept_cookie

Parameter **accept_cookie** helps retain the successful login to a page upon redirect. Default value is ***1***. Cookies are saved in a PHP's temporary directory in a file `mycookies.txt`.

To illustrate, let's assume you want to execute a cron job with Superadmin privileges.<br>
You have activated an Extended Users addon. There is a tag '&lt;cms:process_login /&gt;' and suppose you aim to employ it to login as Superadmin. The tag placed on a non-public template will process your login info. And 'fetch-url' upon connecting will save that cookie on a redirect and will run elevated.

```xml
<cms:process_login username='admin' password='admin' remember='1' redirect='1' />
```

Caller template &mdash;

```xml
<cms:call 'fetch_url' url='cron-elevated.php' />
```

## Usage

**Important notes:** a. It is safe to request the page the func is placed on – there is a built-in protection against recursion. b. Session is closed during 'home' requests, so there should be no unnecessary delays. Also a *COMMIT* completes pending DB transactions.

### Fetch GitHub commits

Let's fetch 5 latest commits from a GitHub repository and place it into a Couch JSON array &mdash;

```xml
<cms:capture into='commits' is_json='1' >
    <cms:call 'fetch-url' url='https://api.github.com/repos/CouchCMS/CouchCMS/commits?per_page=5' as_ajax='0' />
</cms:capture>
```

Now show selected lines &mdash;

```xml
<cms:each commits as='entry' startcount='1' is_json='1'>
    <cms:nl2br>
        <cms:html_encode>

            <cms:date date=entry.commit.committer.date format='M j' /> -- <cms:show entry.commit.message />
        </cms:html_encode>
    </cms:nl2br>
</cms:each>
```

Output as of **June 2022**:

```txt
Jun 2 -- Fix execution of <cms:no_results> in listing folders/nested_pages
Mar 14 -- Fix installation error in PHP 8
Jan 13 -- Update version to 2.3
Jan 2 -- Add PageBuilder
Oct 27 -- Misc. changes
```

## Installation

**Use [Autoloading](https://github.com/trendoman/Cms-Fu/tree/master/ADDON-FUNCS-ON-DEMAND.md),**

or embed func as a snippet —

```xml
<cms:embed 'funcs/Server/fetch-url/fetch-url.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
