# Routines (a tutorial)

> **Everything** that needs to be done from time to time _is done best in a paginated way_ &mdash; @everybody

## Intro

Paginated approach works fine in browsers via JS-powered clicking on the buttons. [CSV importer](https://www.couchcms.com/forum/viewtopic.php?f=5&t=8803) / [CSV exporter](https://www.couchcms.com/forum/viewtopic.php?f=8&t=11378) are based on that _frontend solution_. Larger websites need to have many tasks automated. Let us deal with it by **paginating without browser**.

Take a brief look at the functions presented in this area, namely &mdash;
* add-job
* execute-jobs
* task-file-runner

View the READMEs and let's begin with a first task for this Tutorial.

## Create a sitemap

### Prepare

All functions will be connected or placed via the example snippet &mdash;
```html
<cms:embed 'myfuncs.inc' />
```
Main thread will be running indefinitely untill all the jobs are done, so let's also limit the visitors for the page  &mdash;
```html
<cms:call 'php-time-limit' '0' />
<cms:call 'limit-decline' '1' 'Wait..' />
```

### Create the job

This part is one of the 2 most important things to do - configure a *job*. Refresh the **add-job** README, because it has many important details.
```html
<cms:func 'show-report' report=''>
    <h2><cms:show report.msg /></h2>
    <cms:show_json report />
</cms:func>

<cms:call 'add-job' name='sitemap' list='mylist' report_func='show-report' masterpage='index.php' qs='limit=10' />

<h1>mylist:</h1><cms:show_json mylist /><hr>
```
Above code defines a helper callback **show-report** as a named (not anonymous) function that will print out job report.<br>
Temporarily display **mylist** with my cms:__show_json__ tag to review the configuration and the generated JSON object with description of our job &mdash;

<details><summary>Job configured</summary>

```json
[
   {
      "name":"sitemap",
      "is_complete":"",
      "status":"",
      "error":"",
      "initial_task":"http://my.couch/index.php?job=sitemap&limit=10",
      "current_task":"http://my.couch/index.php?job=sitemap&limit=10",
      "sequent_task":"http://my.couch/index.php?job=sitemap&limit=10",
      "time_start":"",
      "time_close":"",
      "report":[],
      "msg":"",
      "notes":[
         "Using default ~fetch-url~ engine.",
         "Using custom ~show-report~ report."
      ],
      "list":"mylist",
      "user":{
         "name":"sitemap",
         "list":"mylist",
         "report_func":"show-report",
         "masterpage":"index.php",
         "qs":"limit=10",
         "engine_func":""
      }
   }
]
```
</details>

### Add the "engine"

Now, everything looks good. Let's place our engine-wrapper "supervisor" function call and keep it under tight control with cms:__test__. Refresh the page in browser to see the output and then *ignore* the function for a moment.

```html
<cms:test ignore='0'>
    <cms:call 'execute-jobs' my_todo />
</cms:test>
```
Output should contain an ERROR; actually that's good and helpful &mdash;

<details><summary>Errors are hints</summary>

```json
{
   "name":"sitemap",
   "is_complete":"",
   "status":"JOB_ERROR",
   "error":"ERROR: Task code is wrong!",
   "initial_task":"http://my.couch/index.php?job=sitemap&limit=10",
   "current_task":"http://my.couch/index.php?job=sitemap&limit=10",
   "sequent_task":"http://my.couch/index.php?job=sitemap&limit=10",
   "time_start":"23:02:30 487",
   "time_close":"23:02:30 624",
   "report":[
      "http://my.couch/index.php?job=sitemap&limit=10",
      "REQUEST_FAIL",
      ""
   ],
   "msg":"Job [
       sitemap
   ] FAILED",
   "notes":[
      "Using default ~fetch-url~ engine.",
      "Using custom ~show-report~ report.",
      "ABORT! Request *unexpectedly* reported no status.",
      "Requested task must return valid JSON with "success" or "error".",
      "Requested task may also have "continue" and "sequent_task"."
   ],
   "list":"mylist",
   "user":{
      "name":"sitemap",
      "list":"mylist",
      "report_func":"show-report",
      "masterpage":"index.php",
      "qs":"limit=10",
      "engine_func":""
   }
}
```
</details>

Review the hints and realize that our task must respond with special keywords in JSON. Let's take care of that.

### Set up task-runner

Since the template we chose is actually the one that has all our code - `index.php` - and the links already point to it, there must be some code that handles the JSON response. That code is our **task-file-runner** function. Couch's tag cms:__is_ajax__ will allow to control what is visible to the Ajaxed-visitor. I'll remind that our engine - function **fetch-url** is already configured within **execute-jobs** func to send ajax headers.

Somewhere at the top of the page, but after the `myfuncs.inc` place the controlling tags with the *task-runner* &mdash;
```html
=>index.php
<cms:embed 'myfuncs.inc' />

<cms:call 'php-time-limit' '0' />
<cms:call 'limit-decline' '1' 'Wait..' />

<cms:if "<cms:is_ajax />">

    <cms:func 'set-snippet-path' name=''>
        _sitemaps/<cms:show name />.inc
    </cms:func>

    <cms:call 'task-file-runner' path_func='set-snippet-path' />

</cms:if>
```
I have already pasted the callback function **set-snippet-path** from the README example. It will help me hide the path of the embedded snippet and not pass it via URL.

At this moment, preparations are complete and we can begin crafting the actual task.

### Task testing

Our task is meant to generate a sitemap. Shouldn't be complicated for the only clonable template that I have. But there are over *7000 cloned pages!* Let's paginate.

As good coders, we first test and verify our code works. So, make sure to embed the snippet directly first and see how those links appear just fine. Tag cms:__ignore__ around all out previous code will help temporarily disable everything besides the cms:**embed** (for debug!) &mdash;
```html
<cms:ignore>
  ..
</cms:ignore>
<cms:embed '_sitemaps/sitemap.inc' />
```
The content of the `sitemap.inc` snippet will be split into 3 parts
- header, that is supposed to be written only at the first visit &ndash; it is when the pagination sufix is either not present or is *1*
- main content, that is being written on every visit
- closure, &ndash; the last line that closes the xml.

<details><summary>Verify the code works</summary>

```html
<cms:ignore>=> _sitemaps/sitemap.inc</cms:ignore>
<cms:set pg = "<cms:gpc 'pg' />" />

<cms:ignore><!-- first call. writing the beginning of the xml file --></cms:ignore>
<cms:if pg = '' || pg = '1'>
    <cms:capture into='xmlcontent' >
        <cms:concat
            '<'
            '?xml version="1.0" encoding="' k_site_charset '"?'
            '>'
            '<urlset xmlns="https://www.sitemaps.org/schemas/sitemap/0.9">'
        />
        <cms:ignore><!-- Общи --></cms:ignore>
        <url><loc><cms:show k_site_link/></loc></url>
    </cms:capture>

    <cms:write 'sitemap.xml' truncate='1'><cms:trim><cms:show xmlcontent /></cms:trim></cms:write>
</cms:if>

<cms:ignore><!-- Body --></cms:ignore>
<cms:capture into='xmlcontent' >

    <cms:pages masterpage='index.php'
        skip_custom_fields='1'
        order='asc'
        limit='10'
        paginate='1'>
        <url><loc><cms:show k_page_link/></loc></url>
    </cms:pages>

</cms:capture>

<cms:write 'sitemap.xml' truncate='0'><cms:trim><cms:show xmlcontent /></cms:trim></cms:write>

<cms:ignore><!--Closure--></cms:ignore>
<cms:write 'sitemap.xml' truncate='0'><cms:show '</urlset>' /></cms:write>
```
</details>

Visit the page with a sample URL `index.php?pg=25` and verify the file `sitemap.xml` in written to the website's root.

### Response

Now everything is ready for the task to start responding to the outside requests with JSON. By sending to the engine the **k_paginate_link_next** variable supplied by the cms:__pages__ tag we expect it to follow and re-request the task-runner again. There are only *4* required variables in the JSON response, but we'll add some flavor by keeping notes on the task's performance. Check the docs for the functions to refresh on the variables.

<details><summary>Complete listing</summary>

```html
<cms:if task.pg = '' || task.pg = '1'>
    <cms:ignore><!-- first call. writing the beginning of the xml file --></cms:ignore>
    <cms:capture into='xmlcontent' >
        <cms:concat
            '<'
            '?xml version="1.0" encoding="' k_site_charset '"?'
            '>'
            '<urlset xmlns="https://www.sitemaps.org/schemas/sitemap/0.9">'
        />
        <url><loc><cms:show k_site_link/></loc></url>
    </cms:capture>

    <cms:write 'sitemap.xml' truncate='1'><cms:trim><cms:show xmlcontent /></cms:trim></cms:write>
    <cms:set task.notes. = "Job started. Written initial tags to \"sitemap.xml\"  file" scope='parent' />
</cms:if>

<cms:capture into='xmlcontent' >
    <cms:pages masterpage='index.php'
        skip_custom_fields='1'
        order='asc'
        limit=task.pg_limit
        paginate='1'>
        <url><loc><cms:show k_page_link/></loc></url>
        <cms:if k_paginated_bottom && k_paginate_link_next>
            <cms:set task.sequent_task = k_paginate_link_next scope='parent' />
            <cms:set task.notes. = "Tag :pages listed <cms:concat '[' k_current_record ' / ' k_total_records '] records' />" scope='parent' />
        <cms:else_if k_paginated_bottom />
            <cms:set task.notes. = "Tag :pages is done with <cms:concat '[' k_total_records '] records' />" scope='parent' />
        </cms:if>
        <cms:no_results>
            <cms:set task.notes. = "Tag :pages :no_results" scope='parent' />
        </cms:no_results>
    </cms:pages>
</cms:capture>

<cms:write 'sitemap.xml' truncate='0'><cms:trim><cms:show xmlcontent /></cms:trim></cms:write>

<cms:if task.sequent_task = '' >
    <cms:write 'sitemap.xml' truncate='0'><cms:show '</urlset>' /></cms:write>

    <cms:set task.success = "1" scope='parent'/>
    <cms:set task.notes. = "Job finished. Written final tag-urlset to \"sitemap.xml\" file" scope='parent' />
    <cms:set task.msg = "File \"sitemap.xml\" is written to disk." scope='parent'/>

<cms:else />
    <cms:set task.msg = "Added more data to file \"sitemap.xml\"." scope='parent'/>
    <cms:set task.notes. = task.msg scope='parent'/>
    <cms:set task.success = "1" scope='parent'/>
    <cms:set task.continue= "1" scope='parent'/>
</cms:if>
```
</details>

All the `task.*` variables were already provided to us by the **task-file-runner** func. We can be free to use them as we go and add notes, for instance. The only difficulty is to remember setting `scope='parent'`, because the vars were defined outside the current scope, in the parent func.

What's most important is that we put **k_paginate_link_next** to the _very important variable_ &ndash; ***task.sequent_task*** &ndash; it will give the engine either "stop" or "go" order, depending on whether there is a value or no.<br>
> Just a quick reference: for the "go" i.e. request, the engine must see **success** AND **continue** AND **sequent_task** having a good standing. Then the request will be performed with the newly supplied link.


## Result

When it is time to run the bells, change *1* to *0* in cms:__test__ tag and refresh the page.

Actually I received an error, telling me &mdash; `Request *unexpectedly* reported no status.`. When there are errors, I use my **log-html** function that prints output of variables or code directly in HTML file e.g.
```html
<cms:call 'log-html' "<cms:dump_all />" />
<cms:call 'log-html' task />
```
However, the little problem was very clear - there was no success because we request the same template `index.php` and our own func **limit-decline** doesn't allow the page to load.<br>
Fixed by setting it to *2* &mdash;
```html
<cms:call 'limit-decline' '2' 'Wait..' />
```
Refresh the page and it works!

Since I had over 7k pages, I changed the limit to *3000* to keep report short and paste it to this tutorial.<br>
Here we go! &mdash;

<details><summary>Job report</summary>

`Job [ sitemap ] is COMPLETE`
```json
{
   "name":"sitemap",
   "is_complete":"1",
   "status":"JOB_COMPLETE",
   "error":"",
   "initial_task":"http://my.couch/index.php?job=sitemap&limit=3000",
   "current_task":"http://my.couch/index.php?job=sitemap&limit=3000&pg=3",
   "sequent_task":"http://my.couch/index.php?job=sitemap&limit=3000&pg=3",
   "time_start":"00:13:47 134",
   "time_close":"00:13:52 595",
   "report":[
      {
         "success":"1",
         "continue":"1",
         "current_task":"http://my.couch/index.php?job=sitemap&limit=3000",
         "sequent_task":"http://my.couch/index.php?job=sitemap&limit=3000&pg=2",
         "error":"",
         "msg":"Added more data to file "sitemap.xml".",
         "task_time_start":"00:13:47 259",
         "task_time_close":"00:13:49 540",
         "pg":"",
         "pg_limit":"3000",
         "notes":[
            "Job started. Written initial tags to "sitemap.xml"  file",
            "Tag :pages listed [
               3000 / 7097
            ] records",
            "Added more data to file "sitemap.xml"."
         ],
         "task_file":"_sitemaps/sitemap.inc",
         "path_func":"set-snippet-path"
      },
      {
         "success":"1",
         "continue":"1",
         "current_task":"http://my.couch/index.php?job=sitemap&limit=3000&pg=2",
         "sequent_task":"http://my.couch/index.php?job=sitemap&limit=3000&pg=3",
         "error":"",
         "msg":"Added more data to file "sitemap.xml".",
         "task_time_start":"00:13:49 628",
         "task_time_close":"00:13:51 651",
         "pg":"2",
         "pg_limit":"3000",
         "notes":[
            "Tag :pages listed [
               6000 / 7097
            ] records",
            "Added more data to file "sitemap.xml"."
         ],
         "task_file":"_sitemaps/sitemap.inc",
         "path_func":"set-snippet-path"
      },
      {
         "success":"1",
         "continue":"",
         "current_task":"http://my.couch/index.php?job=sitemap&limit=3000&pg=3",
         "sequent_task":"",
         "error":"",
         "msg":"File "sitemap.xml" is written to disk.",
         "task_time_start":"00:13:51 771",
         "task_time_close":"00:13:52 593",
         "pg":"3",
         "pg_limit":"3000",
         "notes":[
            "Tag :pages is done with [
               7097
            ] records",
            "Job finished. Written final tag-urlset to "sitemap.xml" file"
         ],
         "task_file":"_sitemaps/sitemap.inc",
         "path_func":"set-snippet-path"
      }
   ],
   "msg":"Job [
       sitemap
   ] is COMPLETE",
   "notes":[
      "Using default ~fetch-url~ engine.",
      "Using custom ~show-report~ report."
   ],
   "list":"mylist",
   "user":{
      "name":"sitemap",
      "list":"mylist",
      "report_func":"show-report",
      "masterpage":"index.php",
      "qs":"limit=3000",
      "engine_func":""
   }
}
```
</details>

All of that became possible with the help of a few functions and a short listing &mdash;

<details open><summary>Listing of index.php code</summary>

```html
<cms:embed 'myfuncs.inc' />

<cms:call 'php-time-limit' '0' />
<cms:call 'limit-decline' '2' 'Wait..' />

<cms:if "<cms:is_ajax />">

    <cms:func 'set-snippet-path' name=''>
        _sitemaps/<cms:show name />.inc
    </cms:func>

    <cms:call 'task-file-runner' path_func='set-snippet-path' />

</cms:if>

<cms:func 'show-report' report=''>
    <h2><cms:show report.msg /></h2>
    <cms:show_json report />
</cms:func>

<cms:call 'add-job' name='sitemap' list='mylist' report_func='show-report' masterpage='index.php' qs='limit=3000' />

<cms:test ignore='1'>
    <cms:call 'execute-jobs' mylist />
</cms:test>

```

</details>

## Requirements

I have used the following functions quickly connected via `myfuncs.inc` &mdash;

```html
<cms:embed 'funcs/DateTime/show-ms/show-ms.func' />
<cms:embed 'funcs/JSON/add-value-to-array/add-value-to-array.func' />
<cms:embed 'funcs/Logs/log-html/log-html.func' />
<cms:embed 'funcs/Routines/add-job/add-job.func' />
<cms:embed 'funcs/Routines/execute-jobs/execute-jobs.func' />
<cms:embed 'funcs/Routines/task-file-runner/task-file-runner.func' />
<cms:embed 'funcs/Server/php-time-limit/php-time-limit.func' />
<cms:embed 'funcs/Server/limit-decline/limit-decline.func' />
<cms:embed 'funcs/Server/fetch-url/fetch-url.func' />
<cms:embed 'funcs/Validate/is-callable/is-callable.func' />
```

All mentioned funcs don't have further requirements.

### Quick install

Clone the repo to your  **`snippets`** folder and name repo locally as **`func`** &mdash;
```bash
cd /var/www/html/example.com/mysnippets
```
```bash
git clone http://github.com/trendoman/Cms-Fu funcs
```
or download the zip and place accordingly.


## Support

You should have downloaded this function from [Cms-Fu repository](https://github.com/trendoman/Cms-Fu) (Other sources are not trusted)

Donate to keep functions updated!

### email

Support requests: tony.smirnov@gmail.com<br>
You'll get a *well-informed up-to-date* reply.


### donation

**Bitcoin**: bc1qsl2tulmsjcvpkegepeunmumz599yz0lhuktdjt

Desperately waiting for your help that enables
- keep up with support requests;
- continue receiving your [thankyou's](https://github.com/trendoman/Dignotas)
- improve existing functions
- write new code

### forum

Browse helpful Tips&Tricks subforum: https://www.couchcms.com/forum/viewforum.php?f=8

**Telegram**: https://t.me/couchcms

