# add-job

This function is part of the Routines

Func **add-job** quickly sets up variables relevant to jobs and arranges them into JSON object.

1. Creates a JSON object only with named parameters, including user-supplied extra params;
    ```json
    {"name":"sitemaps", "list": "mytodo", ..}
    ```
2. Validate user-supplied functions
2. Adds the object to the array e.g. a job with name _sitemaps_ to an array _mytodo_.
    ```html
    <cms:call 'add-job' name='sitemaps' list='mytodo' />
    ```

<details open><summary>Table of Contents</summary>

  * [Parameters](#parameters)
  * [Example](#example)
  * [Variables](#variables)
  * [Result](#result)
  * [Requirements](#requirements)
  * [Support](#support)
    + [email](#email)
    + [donation](#donation)

</details>



## Parameters

|Required | Optional |
|-------- | -------- |
| <ul><li>name</li><li>list</li></ul> | <ul><li>masterpage</li><li>qs</li><li>report_func</li><li>engine_func</li></ul> |


Add further as many optional parameters as you wish. See examples below.

### name

A name for the job. It will be seen in report and tasks that use default engine for execution (URL requests) will expect *job=__name__* in URL e.g.
```
http://my.couch/index.php?job=sitemaps&pg=999
```

### list

An itinerary for the jobs. It is an array with job objects, e.g.
```json
[ {..}, {..} ]
```

### masterpage

An optional parameter that is mainly used with jobs that rely on URL requests. Function **add-job** will take the *masterpage* and convert it to URL with a query string.
```html
<cms:call 'add-job' name='sitemaps' list='mytodo' masterpage='index.php' />
```
Job object will have a variable set to something like
```json
{ "initial_task" : "http://my.couch/index.php?job=sitemaps" }
```

Note that tag cms:__link__ is used, so with pretty-urls [enabled](https://docs.couchcms.com/concepts/pretty-urls.html)  in Couch config the links will be automatically pretty.


### qs

If the previous parameter *masterpage* is present, a query string value from **qs** will be added to the URL.
```html
<cms:call 'add-job' name='sitemaps' list='mytodo' masterpage='index.php' qs='limit=50'/>
```
```json
{ "initial_task" : "http://my.couch/index.php?job=sitemaps&limit=50" }
```

### report_func,

### engine_func

The 2 parameters, **report_func** and **engine_func** are destined to accept names of custom user-defined functions. A running job will _call them back_ in certain moments. That's our **callback** functions. The former will be called upon when the completed job report becomes available. The latter allows to select a different "engine" for the job, whilst the default one is already known to this **add-job** func.


## Example

Connect the required functions and add a simple job to see how it is being set up.
```html
<cms:embed 'funcs/Routines/add-job/add-job.func' />
<cms:embed 'funcs/JSON/add-value-to-array/add-value-to-array.func' />
<cms:embed 'funcs/Validate/is-callable/is-callable.func' />

<cms:call 'add-job' name='my-first-job' list='my-todo' />
```
Print out itinerary *my-todo* &mdash;
```html
<cms:show_json my-todo />
```
If you don't have my tag cms:__show_json__ from repository [Tweakus Dilectus](https://github.com/trendoman/Tweakus-Dilectus) then you can use browser's ability to display JSON in a pretty way e.g.
```html
<cms:abort>
    <cms:content_type 'application/json' />
    <cms:show my-todo as_json='1' />
</cms:abort>
```

You should see this JSON array, which contains one object &mdash;
<details open><summary>JSON</summary>

```json
[
   {
      "name":"my-first-job",
      "is_complete":"",
      "status":"",
      "error":"",
      "initial_task":"",
      "current_task":"",
      "sequent_task":"",
      "report":[],
      "msg":"",
      "time_start":"",
      "time_close":"",
      "notes":[
         "Using default ~fetch-url~ engine.",
         "Opted not to display report via "report_func"."
      ],
      "list":"my-todo",
      "user":{
         "name":"my-fisrt-job",
         "list":"my-todo",
         "engine_func":"",
         "report_func":""
      }
   }
]
```
</details>

Throw in 3 optional parameters and another extra parameter and see how links appear, and `user` section prints all optional parameters &mdash;
```html
<cms:call 'add-job' name='my-first-job' list='my-todo' masterpage='index.php' qs='limit=50' sometestparam="Hello!" report_func="show-report"/>
```
<details open><summary>JSON with params</summary>

```json
[
   {
      "name":"my-first-job",
      "is_complete":"",
      "status":"",
      "error":"",
      "initial_task":"http://my.couch/index.php?job=my-first-job&limit=50",
      "current_task":"http://my.couch/index.php?job=my-first-job&limit=50",
      "sequent_task":"http://my.couch/index.php?job=my-first-job&limit=50",
      "report":[],
      "msg":"",
      "time_start":"",
      "time_close":"",
      "notes":[
         "Using default ~fetch-url~ engine.",
         "Using custom ~show-report~ report.",
         "ERROR: specified custom report function is not callable."
      ],
      "list":"my-todo",
      "user":{
         "name":"my-first-job",
         "list":"my-todo",
         "masterpage":"index.php",
         "qs":"limit=50",
         "sometestparam":"Hello!",
         "report_func":"ERROR",
         "engine_func":""
      }
   }
]
```
</details>

The ERROR message signalizes that the specified function _show-report_ must be added. We can thank **add-job** for this nice little check that helps write correct code.

Add the required simple function that will actually show our job object passed to it later  e.g.
```html
<cms:func 'show-report' report=''>
    <h2><cms:show report.msg /></h2>
    <cms:show_json report />
</cms:func>
<cms:call 'add-job' name='my-first-job' list='my-todo' report_func='show-report' />
```
Now the job object is set up.

<details open><summary>JSON</summary>

```json
[
   {
      "name":"my-first-job",
      "is_complete":"",
      "status":"",
      "error":"",
      "initial_task":"",
      "current_task":"",
      "sequent_task":"",
      "report":[],
      "msg":"",
      "time_start":"",
      "time_close":"",
      "notes":[
         "Using default ~fetch-url~ engine.",
         "Using custom ~show-report~ report."
      ],
      "list":"my-todo",
      "user":{
         "name":"my-first-job",
         "list":"my-todo",
         "report_func":"show-report",
         "engine_func":""
      }
   }
]
```

</details>

Of course, you may opt to use an anonymous function, which is also very cool to play with. Don't forget to remove the quotes to pass the function by reference, not name &mdash;
```html
<cms:func _into='show-report' _scope='global' report=''>
    <h2><cms:show report.msg /></h2>
    <cms:show_json report />
</cms:func>

<cms:call 'add-job' name='my-first-job' list='my-todo' report_func=show-report />
```

<details open><summary>JSON with anonymous func</summary>

```json
[
   {
      "name":"my-first-job",
      "is_complete":"",
      "status":"",
      "error":"",
      "initial_task":"",
      "current_task":"",
      "sequent_task":"",
      "report":[],
      "msg":"",
      "time_start":"",
      "time_close":"",
      "notes":[
         "Using default ~fetch-url~ engine.",
         "Using custom ~anonymous func~ report."
      ],
      "list":"my-todo",
      "user":{
         "name":"my-first-job",
         "list":"my-todo",
         "report_func":{
            "code":[
               {
                  "type":2,
                  "name":"",
                  "attributes":[],
                  "text":"    <h2>",
                  "ID":"_15_588_116_4639",
                  "line_num":116,
                  "char_num":4639,
                  "children":[]
               },
               {
                  "type":1,
                  "name":"show",
                  "attributes":[
                     {
                        "value":"report.msg",
                        "value_type":2,
                        "op":"="
                     }
                  ],
                  "text":"",
                  "ID":"_15_588_116_4661",
                  "line_num":116,
                  "char_num":4661,
                  "children":[]
               },
               {
                  "type":2,
                  "name":"",
                  "attributes":[],
                  "text":"</h2>rn    ",
                  "ID":"_15_588_117_4673",
                  "line_num":117,
                  "char_num":4673,
                  "children":[]
               },
               {
                  "type":1,
                  "name":"show_json",
                  "attributes":[
                     {
                        "value":"report",
                        "value_type":2,
                        "op":"="
                     }
                  ],
                  "text":"",
                  "ID":"_15_588_117_4696",
                  "line_num":117,
                  "char_num":4696,
                  "children":[]
               },
               {
                  "type":2,
                  "name":"",
                  "attributes":[],
                  "text":"",
                  "ID":"_15_588_117_4699",
                  "line_num":117,
                  "char_num":4699,
                  "children":[]
               }
            ],
            "params":{
               "report":""
            }
         },
         "engine_func":""
      }
   }
]
```
</details>

Generated JSON above also contains Couch representation of the anonymous function as inevitable spell. Don't think too much and switch to regular funcs if this bothers you and advantages are not worth inflating the JSON.


## Variables

Let's dive into variables that **add-job** sets up in JSON.

| <!-- -->    | <!-- -->    |
|-------------:|-------------|
 **`name`** | name of the job
 is_complete | it is the flag that will become *1* when the job is done (has no tasks left).
 status | either `JOB_ERROR` or `JOB_COMPLETE` that is set when job is done
 error | error placeholder for errors generated in execution
 **`initial_task`** | when *masterpage* is given, the link holds initial URL of the job. Custom engine can use this to set some initial value e.g. batch number
 **`current_task`** | when *masterpage* is given, it is initially a copy of previous URL.<br>Then it keeps URL of current request with changing _pg_ e.g. `index.php?pg=5&limit=10` or, for alternative engine, can have some values like current number of records
 **`sequent_task`** | when *masterpage* is given, it is initially a copy of previous URL.<br>Then it provides a crucial URL for the next request. Custom engine may use this to indicate the next task number or next database query to process, etc.
 report[] | this array will hold all reports from each small task
 msg | meant to display a final message from job, e.g. `Job [ my-lazy-job ] FAILED`
 time_start | marks time when job is started. Will display date in format `Y-m-d H:i:s` and add milliseconds if you connect a function **show-ms**.
 time_close | marks time when job is complete, format same as above
 notes[] | notes from your job, such as helping messages about engine and report etc.
**`list`** | itinerary of jobs this job belongs to
user[] | sub-node holding all user-defined parameters and their values

Variables set in **bold** can be configured via params of **add-job** i.e.
```html
<cms:call 'add-job' name='my-first-job' list='my-todo' initial_task='10' max-limit='10'/>
```
Configurables can be accessed as direct descendants i.e. `job.current_task`<br>
Other user-supplied parameters will appear in **user** section, so look there &mdash; `job.user.max-limit`<br>

**Note:** Function **add-job** will not create links in \*\_task variables, if any of the those variables is set explicitly i.e.
```html
<cms:call 'add-job' name='my-first-job' list='my-todo' masterpage='index.php' current_task='0' />
```
This gives much-needed space for custom engines and tasks. Not every job will be using URL requests, but every job must have some kind of pagination control.
```json
{ ..
  "initial_task":"",
  "current_task":"0",
  "sequent_task":"",
 .. }
```

## Result

Finish configuring the job and get next to the **execute-jobs** function.

As a little spoiler, let's see how the **executed** job with several tasks may have amended the job object with all variables  &mdash;

<details open><summary>Sample executed job</summary>

```json
{
    "name": "sitemap",
    "is_complete": "1",
    "status": "JOB_COMPLETE",
    "error": "",
    "initial_task": "http://my.couch/index.php?job=sitemap&limit=300",
    "current_task": "http://my.couch/index.php?job=sitemap&limit=300&pg=4",
    "sequent_task": "http://my.couch/index.php?job=sitemap&limit=300&pg=4",
    "report": [{
        "success": "1",
        "continue": "1",
        "current_task": "http://my.couch/index.php?job=sitemap&limit=300",
        "sequent_task": "http://my.couch/index.php?job=sitemap&limit=300&pg=2",
        "error": "",
        "msg": "Added more data to file [ sitemap-common.xml ].",
        "task_time_start": "16:22:03 971",
        "task_time_close": "16:22:04 244",
        "pg": "",
        "pg_limit": "300",
        "notes": ["Job started. Written initial tags to [ sitemap-common.xml ] file", "1st tag listed [300 / 1040] records", "2nd tag listing done [8] records", "3rd tag :no_results", "Added more data to file [ sitemap-common.xml ]."],
        "task_file": "_sitemaps/sitemap.inc",
        "path_func": "set-snippet-path"
    }, {
        "success": "1",
        "continue": "1",
        "current_task": "http://my.couch/index.php?job=sitemap&limit=300&pg=2",
        "sequent_task": "http://my.couch/index.php?job=sitemap&limit=300&pg=3",
        "error": "",
        "msg": "Added more data to file [ sitemap-common.xml ].",
        "task_time_start": "16:22:04 332",
        "task_time_close": "16:22:04 588",
        "pg": "2",
        "pg_limit": "300",
        "notes": ["1st tag listed [600 / 1040] records", "2nd tag :no_results", "3rd tag :no_results", "Added more data to file [ sitemap-common.xml ]."],
        "task_file": "_sitemaps/sitemap.inc",
        "path_func": "set-snippet-path"
    }, {
        "success": "1",
        "continue": "1",
        "current_task": "http://my.couch/index.php?job=sitemap&limit=300&pg=3",
        "sequent_task": "http://my.couch/index.php?job=sitemap&limit=300&pg=4",
        "error": "",
        "msg": "Added more data to file [ sitemap-common.xml ].",
        "task_time_start": "16:22:04 680",
        "task_time_close": "16:22:04 929",
        "pg": "3",
        "pg_limit": "300",
        "notes": ["1st tag listed [900 / 1040] records", "2nd tag :no_results", "3rd tag :no_results", "Added more data to file [ sitemap-common.xml ]."],
        "task_file": "_sitemaps/sitemap.inc",
        "path_func": "set-snippet-path"
    }, {
        "success": "1",
        "continue": "0",
        "current_task": "http://my.couch/index.php?job=sitemap&limit=300&pg=4",
        "sequent_task": "",
        "error": "",
        "msg": "File [ sitemap-common.xml ] is written to disk.",
        "task_time_start": "16:22:05 001",
        "task_time_close": "16:22:05 121",
        "pg": "4",
        "pg_limit": "300",
        "notes": ["1st tag listing done [1040] records", "2nd tag :no_results", "3rd tag :no_results", "Job finished. Written final tag-urlset to [ sitemap-common.xml ] file"],
        "task_file": "_sitemaps/sitemap.inc",
        "path_func": "set-snippet-path"
    }],
    "msg": "Job [ sitemap ] is COMPLETE",
    "time_start": "16:22:03 870",
    "time_close": "16:22:05 123",
    "notes": ["Using default ~fetch-url~ engine.", "Using custom ~show-report~ report."],
    "list": "my_todo",
    "user": {
        "masterpage": "index.php",
        "name": "sitemap",
        "list": "my_todo",
        "qs": "limit=300",
        "report_func": "show-report",
        "engine_func": ""
    }
}
```

</details>

## Requirements

This func employs a required func __add-value-to-array__ to wrap an object (job) into array (list of jobs) as in &mdash;
```html
<cms:call 'add-value-to-array' value=job array=list />
```

Throw in the **is-callable** function that takes care of validating **report_func** and **engine_func** params.

Add an optional **show-ms** func to view times with milliseconds (for those _very quick_ tasks).

Everything can be connected as follows:
```html
<cms:embed 'funcs/Routines/add-job/add-job.func' />

<cms:embed 'funcs/DateTime/show-ms/show-ms.func' />
<cms:embed 'funcs/JSON/add-value-to-array/add-value-to-array.func' />
<cms:embed 'funcs/Validate/is-callable/is-callable.func' />
```



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
- continue receiving your [thank you's](https://github.com/trendoman/Dignotas)
- improve existing functions
- write new code

### forum

Browse helpful Tips&Tricks sub forum: https://www.couchcms.com/forum/viewforum.php?f=8

**Telegram**: https://t.me/couchcms
