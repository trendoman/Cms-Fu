# embed-once

Place some content on page only once even if the code is reused many times.

```xml
<cms:call 'embed-once' 'signature.html' />
```

Another example. If a repetitively embedded snippet contains some mandatory assets e.g. fonts, CSS, scripts, etc.. then save on bloat – put the assets to a separate file and embed that file only once:

```xml
<cms:call 'embed-once' 'common-assets.inc' />
```

This function received a special ability to embed a snippet without specifying its path which will be determined automatically from the other snippet path provided via param:

```xml
<cms:call 'embed-once' 'child.inc' relative_to='path/to/parent.inc'/>
```

## Usage

Real-life usage of this func can be observed in **[Soup » toastr](https://github.com/trendoman/Hot-Potato-Soup/tree/master/toastr)** directory where a popup toastr can be embedded a few times but its styles and scripts are embedded only once.

## Parameters

* **snippet**
* **relative_to**

### snippet

As usual, a path to your snippet file relative to the configured snippets directory, e.g. ***snippet='css/styles.css'***.

### relative_to

Parameter takes full relative path to another snippet file and is meant for use in parent snippets to embed dependent child snippets. This arrangement tries to nullify a hefty task to control paths in all dependent files if the folder containing them is renamed or moved. If both parent and dependent snippets are to be placed together in the folder ***embeds/alert/*** then the following would be the code to use inside the parent snippet:

```xml
<cms:call 'embed-once' 'assets.inc' relative_to='embeds/alert/alert-success.html' />
```

Detailed explanation:

Suppose you have a snippet A (***alert-success.html***) that embeds other snippet B (***assets.inc***). Naturally, to embed snippet A you use the path relative to the snippets directory e.g.

```xml
<cms:call 'embed' 'embeds/alert/alert-success.html' />
```

The code inside snippet A also needs the path to the snippet B, because it can not know its directory automatically. So in A you can correctly write something like –

```xml
<cms:call 'embed-once' 'embeds/alert/assets.inc' />
```

Some day you rename a folder ***alert*** to ***alerts*** and may forget to change the path in the code that embeds snippet B inside snippet A. By using relative path this problem becomes non-existent. Practically, this is suitable for snippets downloadable by other users – I would never know where they will place the snippets.

---

**The real deal** is, however, to pass a *variable* holding path to parent snippet. Function **embed** always sets up a variable **k_named_args.snippet** that holds path to snippet A and can be passed to parameter **relative_to** in order to provide a tip where to look for the dependent embedded snippet –

```xml
<cms:call 'embed-once' 'assets.inc' relative_to=k_named_args.snippet />
```

## Related pages

* **[Midware Core Concepts &raquo; Reusable Functions](https://github.com/trendoman/Midware/tree/main/concepts/Reusable-Functions#func-vs-embed)** — **A must-read concept!** There we compare ***cms:embed*** Vs. ***cms:func*** Vs. ***cms:tag***.

## Related Funcs

* **[Sapling &raquo; embed](https://github.com/trendoman/Cms-Fu/tree/master/Sapling/embed)** — mandatory func that actually performs *embedding*

## Installation

**Use amazing [Autoloading](https://github.com/trendoman/Cms-Fu/tree/master/ADDON-FUNCS-ON-DEMAND.md)** instead of manual copypasting.

## Support

[![Mail](https://img.shields.io/badge/gmail-%23539CFF.svg?&style=for-the-badge&logo=gmail&logoColor=white)](mailto:"Anton"<tony.smirnov@gmail.com>?subject=[GitHub])

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
