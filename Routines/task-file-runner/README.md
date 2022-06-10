# task-file-runner

This function is a wrapper around cms:__embed__ and helps run tasks from snippets. It sets up many useful variables a task can fill out.<br>
```html
<cms:call 'task-file-runner' path_func='' />
```
The result of the function call is a page with `Content-Type: application/json`, that has only the JSON **response** from a task (embedded snippet file) with info on how the task performed.

## Parameters

* path_func

Parameter **path_func** accepts a name of function that will serve as a callback to configure **path** to embeddable snippet. Normally, a job should not pass a name/path of the snippet file name via URL. Jobs pass only their name e.g. `sitemap` in `index.php?job=sitemap` &mdash; and **path_func** function should convert that job name into the snippet file for convenience.

```html
<cms:func 'set-snippet-path' job_name=''>
    make-sitemaps/<cms:show job_name />.inc
</cms:func>

<cms:call 'task-file-runner' path_func='set-snippet-path' />
```
The callback **set-snippet-path** is an example func that manipulates *job_name* and outputs full path ready to use in cms:**embed**. The only mandatory parameter will receive the job's name.

If the **path_func** is empty or not even added to the call, then default snippet filename as *{job-name}.inc* will be used instead.

## Variables

Func creates a host of __task.\*__ variables that will be available within the embedded snippet. Namely, &mdash;
* task.success
* task.continue
* task.current_task
* task.sequent_task
* task.error
* task.msg
* task.task_time_start
* task.task_time_close
* task.pg
* task.pg_limit
* task.notes

### success,
### continue,
### error,
### sequent_task

As you know from reading README of **execute-jobs** and **add-job** functions, these are 4 mandatory variables every task must maintain in good order.<br>

In case the snippet file is not found (as reported by cms:__exists__) then **error** will contain the message. This can happen if the **path_func** callback function (if user chose to have it defined) is not working correctly e.g.
```
File [ make-sitemaps.inc ] not found
```
### current_task
This is a placeholder that the parent caller - **execute-jobs** - will fill out. Here it is kept to maintain JSON structure.
```html
<!--cms:func 'execute-jobs' sets current_task var:-->
<cms:set response.current_task = job.current_task ... />
```
### msg,
### notes[],
### task_time_start,
### task_time_close

Additional variables to keep details of the task.


### pg,
### pg_limit

Var **pg** receives its value from URL - it is a pagination suffix `pg`. Var **pg_limit** also receives its value from URL - in case it is present as `limit` in the exta params of **task-file-runner** func or **qs** in the params of the job during configuration stage with **add-job** func. If the `limit` is not present in URL query string (as in `index.php?job=myjob&limit=100&pg=2`), then its value is *`25`* by default.

---

It is often necessary to debug the code. Direct call of the function **task-file-runner** is possible with following params &mdash;
* job
* pg
* limit

```html
<cms:call 'task-file-runner' path_func=set-snippet-path pg='1' limit='5' job='sitemap'/>
```
The call above will set up stage for testing the callback function and the task snippet as well. Params passed directly via the call take precedence over those pased in query string. However it is worth to recall that Couch tags, like cms:**pages**, rely only on the query string value in case of **pg** variable.

## Usage

The meat of this function is the following part &mdash;
```html
<cms:abort>
    <cms:content_type 'application/json' />
    <cms:show task as_json='1' />
</cms:abort>
```
It creates **response** for the parent caller and encapsulates everything your snipept task has to say to the above standing "supervisors".

With almost zero-config, this function can be used as is and become indispensable "manager" for all snippets.

### direct call

Very important feature is that this func can be called directly. It incapsulates the embeddable snippet, provides variables to it and returns result as JSON. Func does not receive any reference of the job object, the only info is the job's name. The only hard-coded part is the snippet's extension - it is expected to be *.inc* by default and can be customized via a **path_func** callback.


## Requirements

- none

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



