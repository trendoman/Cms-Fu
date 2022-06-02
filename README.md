# [Cms-Fu](https://github.com/trendoman/Cms-Fu)
 The indomitable set of **cms:func** functions for CouchCMS

> First time? Visit CouchCMS [website](https://www.couchcms.com/) to enjoy this TIME-TESTED AND SECURE CMS. It's perfect for designers and is open source! See its [GitHub Repo](https://github.com/CouchCMS/CouchCMS).

## Contents

Call me maybe..

## Install


## Installation

1. Clone repo to website's root
    - or download zip &ndash; [master.zip](https://github.com/trendoman/Cms-Fu/archive/refs/heads/master.zip)

 ```bash
 git clone https://github.com/trendoman/Cms-Fu _CmsFu
 ```
2. Copy files to a directory with snippets, into a suggested folder 'funcs'
 ```bash
cp -r _CmsFu/* mysnippets/funcs
 ```
3. Register the desired function via **embed**
```html
<cms:embed
    'funcs/JSON/create-object/create-object.func'
    />
```
