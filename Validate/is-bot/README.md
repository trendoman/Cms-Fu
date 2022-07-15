# is-bot

Function returns ***1*** if the visitor is a bot, ***0*** otherwise.

```xml
<cms:call 'is-bot' />
```

Detects over 1400 bots. Based on code from [**CrawlerDetect.io →**](https://crawlerdetect.io/).

Processing takes ~20-30 millisec.

## Parameters

Function does not take any parameter.

## Usage

Example usage in a condition –

```xml
<cms:if "<cms:call 'is-bot' />">
   // do not count as a visitor
<cms:else />
   // code to increment page-view counter
</cms:if>
```

---

**First and foremost**, make sure the func is working well. Place the un-conditioned call on page, refresh the page (func will report ***0***) and check PHP's error log for errors. There should be none if the 'vendor' directory exist and readable.

```xml
<cms:call 'is-bot' />
```

By default, func looks in `/funcs/Validate/is-bot/vendor/` inside the snippets directory. If that's not the case, open file `is-bot.func` and edit the path line i.e.

```php
$vendor_path = K_SITE_DIR.K_SNIPPETS_DIR.'/funcs/Validate/is-bot/vendor/';
```

Set the actual path and save the file. Reload the page and there should be no error in log now.

---

Following snippet can help test your favorite User-Agent string by requesting the page itself (func **[fetch-url](#related-funcs)**):

```xml
<cms:if "<cms:is_ajax />">
   <cms:abort>
      <cms:call 'is-bot' />
   </cms:abort>
</cms:if>

<cms:call 'fetch-url' k_page_link as_ajax='1' />
```

Default User-Agent sent by 'fetch-url' func is ***CouchCMS***.

Change the User-Agent temporarily to a desired testing value in the file `funcs/Server/fetch-url/fetch-url.func` e.g.

from

```php
curl_setopt($ch, CURLOPT_USERAGENT, "CouchCMS ".$CTX->get('k_cms_version') );
```

to

```php
curl_setopt($ch, CURLOPT_USERAGENT, "bot ".$CTX->get('k_cms_version') );
```

Refresh the page with the snippet above and see the returned value is ***1*** i.e. **the bot was detected**. When you are done with tests, don't forget to return original User-Agent i.e. ***CouchCMS***!

If, instead of simple ***1***, you want the returned value to contain **matched name of the bot**, uncomment the line №39 in `is-bot.func` –

```php
//return $CrawlerDetect->getMatches();
```

## Related tags

Documentation on all mentioned Couch tags can be found in **[Midware Tags Reference](https://github.com/trendoman/Midware/tree/main/tags-reference)**.

## Related funcs

* **[Server &raquo; fetch-url](https://github.com/trendoman/Cms-Fu/tree/master/Server/fetch-url#as_ajax)**

## Related pages

* **[Forum » Most viewed articles (page-hits counter)](https://www.couchcms.com/forum/viewtopic.php?f=8&t=8913)**
* **[Forum » File Downloads with counter](https://www.couchcms.com/forum/viewtopic.php?f=2&t=9572)**

## Installation

**Use [Autoloading](https://github.com/trendoman/Cms-Fu/tree/master/ADDON-FUNCS-ON-DEMAND.md),**

or, alternatively, manually copy the func code to the page before the calling or embed func as a snippet —

```xml
<cms:embed 'funcs/Validate/is-bot/is-bot.func' />
```

## Support

[![Mail](https://img.shields.io/badge/gmail-%23539CFF.svg?&style=for-the-badge&logo=gmail&logoColor=white)](mailto:"Anton"<tony.smirnov@gmail.com>?subject=[GitHub])

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
