# is-image

Validate images to be real – ***gif, png, bmp, jpeg, webp***

```xml
<cms:call 'is-image' file='test.webp' />
```

Check if the version of PHP and GD supports certain formats by running ***phpinfo();*** e.g.

```xml
<cms:php>phpinfo();</cms:php>
```

Navigate to *GD* section and see 'enabled' for each format, esp. **webp**.

If some format is not supported, func will always return ***0*** even if the image is valid, because that particular PHP build has no means to validate it.

## Parameters

* **file**

   Relative or absolute path or link must be below website root directory.

* **strict**

   Default value is ***1***, i.e. always enabled. Strict validation skips identification solely by mime content type and, instead, tries to verify the content.

## Usage

```xml
<cms:if "<cms:call 'is-image' file='fakes/not-an-image.png' />"><cms:else /><!-- Content mismatch -->Not an image!</cms:if>
```

Extension and filename does not matter in default **strict** mode — the result will depend on the content.

Sometimes the *trusted* sources needn't a deep verification and mime check is enough to filter out unwanted types of files. Call the func without strict validation:

```xml
<cms:call 'is-image' file='pic-from-mom.jpg' strict='0'/>

→ 1
```

## Installation

**Use [Autoloading](https://github.com/trendoman/Cms-Fu/tree/master/ADDON-FUNCS-ON-DEMAND.md),**

or, alternatively, manually copy the func code to the page before the calling or embed func as a snippet —

```xml
<cms:embed 'funcs/Validate/is-image/is-image.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
