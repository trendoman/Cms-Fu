# fetch-url

Requests content of any URL.
```html
<cms:call 'fetch_url' 'https://www.couchcms.com/' />
```
There is a built-in protection against nested requests. It means it is safe to request the same page the function is being called from. Such request will complete only once.

Func **fetch-url** expects a **cURL** php-extension, but has an alternative backup engine if extension is not available.

## Parameters

* url
* as_ajax
* send_cookie
* accept_cookie


### url

Param **url** can be a string or a variable &mdash;
```html
<cms:call 'fetch_url' k_page_link />
```

### as_ajax

Parameter **as_ajax** allows to imitate Ajax `XMLHttpRequest` requests  &mdash;
```html
<cms:call 'fetch_url' url="<cms:link 'cart.php' />" as_ajax='1' />
```

### send_cookie

Parameter **send_cookie** will relay status of the logged-in user, as if the user himself made the request.
```html
<cms:call 'fetch_url' url="<cms:link masterpage='login.php' />" send_cookie='1' />
```

### accept_cookie

Parameter **accept_cookie** helps retain the successful login to a page upon redirect.

To illustrate an application let's assume you want to execute a cron job with Superadmin privileges.<br>
You have activated an Extended Users addon. There is a tag 'cms:process_login' and suppose you aim to employ it to login as Superadmin. The tag placed on a non-public template will process your login info. And 'fetch-url' upon connecting will save that cookie on a redirect and will run elevated.
```html
<cms:process_login username='admin' password='admin' remember='1' redirect='1' />
```
Caller template &mdash;
```html
<cms:call 'fetch_url' url=k_site_link send_cookie='1' accept_cookie='1' />
```

## Usage

### Fetch GitHub commits

Let's fetch 5 latest commits from a GitHub repository and place it into a Couch JSON array &mdash;
```html
<cms:capture into='commits' is_json='1' >
    <cms:call 'fetch-url' url='https://api.github.com/repos/CouchCMS/CouchCMS/commits?per_page=5' />
</cms:capture>
```
Now show selected lines &mdash;
```html
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
