# [Func-on-demand](https://github.com/trendoman/Tweakus-Dilectus/tree/main/anton.cms@ya.ru__func-on-demand)

Visit [**Func-on-demand**](https://github.com/trendoman/Tweakus-Dilectus/tree/main/anton.cms@ya.ru__func-on-demand) addon's page to download and complete instructions.

## Intro

To use &lt;cms:call&gt; with a func, we first need to embed that func code somewhere. This becomes tedious and error prone when there are tens of funcs. With this addon, you can keep all the funcs in a single folder and only specify the path of that folder to addon. Now whenever Couch encounters a **cms:call**, it will ask addon to locate the code for the func being called and automatically embed it. This is akin to what PHP does with its Autoloading.

**TLDR;** Specify **only location(s) of snippets** to begin with and the **cms:func** gets loaded only when that particular func is called with &lt;cms:call&gt; in code. In other words, we recreate for Couch the **autoload** feature.

