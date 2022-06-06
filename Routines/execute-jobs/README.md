# execute-jobs

Function walks through every job from itinerary and performs a user-defined task. Tasks may be anything &mdash; listing pages, calling another func, visiting URL, embedding a code snippet, writing a file. A result of each task is made available to the original caller.

```html
<cms:call 'execute-jobs' itinerary='mytodo' />
```

## Parameters

* itinerary &mdash; a list of jobs. A *job* is a JSON object, a *list* is an array of such objects. Read detailed introduction to *jobs* in **add-job** function.
```json
[ {..}, {..} ]
```

## Usage

### intro

The function **execute-jobs** positions itself as a wrapper around an infinite loop based on *while*. So, basically, while there are jobs in the itinerary the loop will go through all of them, one by one. Each job subsequently calls upon its tasks and executes them untill there are no more tasks to do. When this happens, the job is considered complete.

Let's see how it can be exploited.

### pagination

Default "engine" of the **execute-jobs** is the cms:__func__ **'fetch-url'**. It will initially request the link configured in the job, for example
```
http://my.couch/index.php?job=sitemap
```
That page should be expecting the request and will respond at the very least with the following JSON &mdash;

<details><summary>Required response</summary>

```json
{
   "success":"1",
   "continue":"1",
   "sequent_task":"http://my.couch/index.php?job=sitemap&pg=2",
   "error":""
}
```
</details>

So these 4 items are governing the runflow of the function. If the small task finished with **success**, signals that it can **continue** and provides the URL in **sequent_task** - then the discussed function will take that link from `sequent_task` and make a new request to it. It will also pass on the complete job object configured in the beginning. It allows to have a lot of data at hand for the tasks and maintain ultimate control over the process.

The job will stop if there is an **error**, that's understandable. Job will also stop when task reported only **success* e.g. without **continue** AND **sequent_task**. This means that the task can not find anything to do further. In practice, tag cms:**pages** gives empty variable **k_paginated_link_next** when the visitor is on the last paginated page, - that's the perfect candidate for the **sequent_task**.


### callbacks

An important feature of the function is that during the execution, in two crucial moments, there happen **callback** calls.

#### call_func

One crucial moment is the outcome of job. Upon job completion, whether with error or success, func **execute-jobs** will look for user-supplied name of the function that must be called. Job object can have the variable **report_func** set with a user-defined func's name as value.
```html
<cms:call 'add-job' ... report_func='show-report' />
```
&mdash; user callback func **show-report** must be defined before the **execute-jobs** or **add-job** is called. It should have at least one parameter, that will accept incoming job object with full report.

```html
<cms:func 'show-report' report=''>
    <h2><cms:show report.msg /></h2>
    <cms:show_json report />
</cms:func>
```
Tasks can spam a lot of useful information into the report, that is up to the code of the task, 100% controlled by the user. So a very detailed report with info about each step will be passed to the **show-report**. This auxiliary func could be designed to print that report or do something else, like send email or write a file, update a field.

#### engine_func

Jobs are often based on visiting some URL. Pagination, for example, depends on the paginated prefix parameter in URL e.g. **pg** in *blog-list.php?pg=3*.<br>
Initial research on the **execute-jobs** function was meant to imitate a pagination without frontend clicking, so the func was created with that approach in mind.

Default engine for the **execute-jobs** is the function **fetch-url**. It does nothing but requests a given URL with *XMLHttpRequest* header aka Ajax. Read more on **fetch-url** to understand how it works.

Custom engine can be defined in the job object via the **engine_func** parameter e.g.
```html
<cms:call 'add-job' ... report_func='show-report' engine_func='query-database' />
```
Above specification instructs **execute-jobs** to abandon default engine and instead look for and call the function **query-database**.

Again, there are unlimited options for users to define their engines, whether complex or simple, such as *embed a snippet, calculate values, etc.* Use it and design engines very carefully, because it is easy to get an unlimited loop or some undesired outcome. Most tasks are perfectly handled by URL requests via default engine, anyway.

Look for job's notes to see a hint about which engine is configured.

## Variables

Func does not create new variables. It merely fills out those prepared by the **add-job** func. Those are &mdash;
* is_complete &mdash; *1* when the job is done
* status &mdash; with values *`JOB_ERROR`*, *`JOB_COMPLETE`*
* error
* notes
* report
* time_start &mdash; time when job started in format `Y-m-d H:i:s v`
* time_close &mdash; time when job ended in the same format
* msg

## Requirements

Following funcs are used:
* **fetch-url** &mdash; engine for URL request
* **is-callable** &mdash; validates user-defined callbacks
* **show-ms** &mdash; is *optional* and will add milliseconds to the `time_start` / `time_close` timers if the func is available.

Everything can be connected as follows:
```html
<cms:embed 'funcs/DateTime/show-ms/show-ms.func' />
<cms:embed 'funcs/Server/fetch-url/fetch-url.func' />
<cms:embed 'funcs/Validate/is-callable/is-callable.func' />
```

All mentioned funcs don't have further requirements.


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
