# Create pages &bull; Tutorial

Welcome to the Tutorial that shows how to use **Routines** funcs to clone a number of pages.<br>
"Paginated approach" will be used to perform the task gracefully.

## Intro

Again, we'll rely on the core 3 functions:
* __add-job__ &ndash; helps to describe what we need to do, set up parameters and variables to track progress in JSON format.
* __execute-jobs__ – makes URL requests repeatedly while there is the next link to request. Kinda "Supervisor" func.
* __task-file-runner__ – sets up variables for the task-snippet and embeds it. Returns the task's result in JSON back to the previous, supervisor func.


Let's start today by creating a snippet that will be our *task* — actual code that creates a page.

## Create a task snippet

### synopsis

Task's algorythm looks like this:

**Count** existing pages and **compare** the number with the goal. If the goal is not met yet, **loop** main 'creating-pages' code only XX times (_limit_). **Report** result of current request, giving back the **link** for the next request, if there are more pages to create. Report if the task has finished in fullest and no more **requests** are needed.


### tags for the task

Only 3 core tags are needed for the main operation.

1. Tag that creates pages is **db_persist** with mode *create* e.g.
   ```html
   <cms:db_persist
        _masterpage = 'target-template.php'
        _mode = 'create'
        _auto_title = '1'
        _fields = '' >

        <cms:if k_success>

        <cms:else />

        </cms:if>
   </cms:db_persist>
   ```

2. We'll need to know how many pages already exist in a *target-template.php*, so we'll use **pages** tag with *count_only* param e.g.
   ```html
   <cms:pages masterpage='target-template.php' show_future_entries='1' count_only='1' />
   ```
   Tag **pages** is configured with 3 parameters.
   - **masterpage** – our template
   - **show_future_entries** – this is necessary, because Couch will create many pages quickly, within one second, and must count them all. By default, **pages** return only *published* and where *publish_date* is less than current second i.e. with the *1-second* resolution. By using this parameter, we instruct tag to count all pages, except *non-published*.
   - **count_only** – this param will make the tag return only number i.e. how many pages are there (for instance, *40*)

3. And, finally, tag **while** loops the 'creating' code up to the desired limit.
   ```html
   <cms:while condition>
      ...
   </cms:while>
   ```

### vars for the task

Thanks to the __task-file-runner__ func that will embed our task-snippet and already created many helpful variables, we can use a small sub-set from all prepared variables, namely &mdash;
* task.success
* task.continue
* task.sequent_task
* task.error
* task.msg
* task.pg_limit
* task.notes

Again, these variables are created inside the func __task-file-runner__ when it is called. We'll use them to our purpose.

### condition for the 'while' loop

Let's throw in a few variables that help build the condition for the loop.

#### total_pages

As discussed previously:
```html
<cms:set total_pages = "<cms:pages masterpage=k_template_name show_future_entries='1' count_only='1' />" scope='global' />
```

#### desired_max
```html
<cms:set desired_max = "<cms:get 'k_named_args.max-count' default="<cms:gpc 'max-count' method='get' />" />" scope='global'/>
```
Our task code should know how many total pages we want to have. This total number will be passed along each separate request via query string. Let's name it **max-count**. The query string would be like *?max-count=1000*.

In the code above we set a new variable **desired_max** that by _default_ will be using the value from the query string. However, before actually running the task paginated, we would like to test it separately and we need to be able to pass the **max-count** directly. Thanks again, to our **task-file-runner**, we have a variable ***k_named_args***, which is a system-assigned variable by the 'cms:func' tag, that contains all passed named parameters.

I'm going to test our task-snippet later by passing its name to the **task-file-runner** func via a parameter *job* and func will embed the snippet for me. In func's params, I will also use the 'max-count' param value directly, for debug. That is why I am setting **desired_max** variable in the code above from both sources &mdash; from **k_named.args** and, by default, from **gpc** tag (from query string). It allows me to pass params in 2 different ways &ndash; one is directly, by calling **task-file-runner** with params; and another way is indirect, via query string. You will see below how it is done.

#### difference

Calculating the **difference** beween **desired_max** and **total_pages** gives information about how many more pages we need to create. The difference may be *0* i.e. all pages are already created; a small value, that is less than our limit per request; a big value, that is bigger than our limit per request.
```html
<cms:set difference = "<cms:sub desired_max total_pages />" />
```
So if the desired maximum is 100 and total existing pages is 5, then the **difference** will be 95 (pages to create).

We want to let the difference govern the limit for the loop i.e. loop's limit will be shaped by the difference. I am going to reuse existing variable **task.pg_limit** to make it a _variable_ limit for the loop e.g.

```html
<cms:if difference gt task.pg_limit>
   <!--OK, there are still many pages to create. Will use oringinal task.pg_limit-->
   <cms:else_if difference gt '0' />
   <!--There are a few pages left to create, but less than task.pg_limit. Will use new value.-->
   <cms:set task.pg_limit = difference scope='parent' />
   <cms:else />
   <!--Nothing to do-->
   <cms:set task.pg_limit = '0' scope='parent' />
</cms:if>
```
#### counted,
#### allowed

```html
<cms:set counted = '0' scope='global'/>
<cms:set allowed = '1' scope='global'/>
```

Var **counted** will track how many pages were created within the loop. Ideally, that number should match the **task.pg_limit** number, but because of possible errors it can be less than expected. It will gradually increase from *0*, before it reaches the set limit and then it will halt the 'while' loop.

Var **allowed** is a signalling flag that will halt the loop in case something goes wrong. Any error will set this to *0* and loop will stop.

### set up the loop

The following chunk of code should make clear how the loop is set up and how variables go. Imagine the **task.pg_limit** is *3* and go step-by-step with what's happening inside the 'while'. Notes added to the **task.notes** array definitely help follow the idea.
```html
<cms:set counted = '0' scope='global'/>
<cms:set allowed = '1' scope='global'/>
<cms:while (counted lt task.pg_limit) && allowed eq '1'>
   <cms:db_persist
        _masterpage = k_template_name
        _mode = 'create'
        _auto_title = '1'
        _fields = '' >

        <cms:if k_success>
            <cms:set task.notes. = "Created pagename '<cms:show k_last_insert_page_name />' with id '<cms:show k_last_insert_id />'." scope='parent' />
            <cms:incr counted />
        <cms:else />
            <cms:set task.success = '0' scope='parent' />
            <cms:set task.error = k_error scope='parent' />
            <cms:set allowed = '0' scope='parent'/>
            <cms:set task.notes. = "There was a problem creating a page after <cms:show counted /> pages." scope='parent' />
        </cms:if>
   </cms:db_persist>

</cms:while>
```
Hopefully, **counted** number of created pages matches our limit and is less or equal the **desired_max** number. Time to wrap up the request, commit the changes to database (is always done automatically when the response is sent from server) and pass the information about whether we need another request (that is if the **desired_max** is not reached yet).

### condition for success

The result of our small task is defined by the state of two variables &mdash; **task.error** and **counted**. If there was an error and one or more pages were not created, then we should see if at least a single page was created successfully. Error will be reported, but the job will continue. If there were no pages created before the error occured, then we should cancel the job and report back. There is no point in continuation at all, because something is deadly wrong. If there was no error, and the **counted** is zero &ndash; this means that the loop did not even start because of the condition and it means the **desired_max** number is already reached therefore the whole job is fully complete. See the notes &ndash;
```html
<cms:if counted >
   OK, pages were created
   <cms:if task.error >
      Maybe some page was not created, we'll continue and try again later
   </cms:if>
<cms:else_if task.error />
   Wow, this is a dead end, nothing was created and error popped up.
<cms:else />
   Ok, the job is done, no errors, no pages left.
</cms:if>
```

One crucial point is to send back a link for the next request. If you recall, when we used to create a sitemap and that task was based on tag **pages**, the sequent link was handled by the tag, giving us the **k_paginate_link_next** URL. Present task does not need an always-changing URL, we only need to keep track of **max-count**, that is all. So, we'll send back the same URL that we are having. We'll craft the link with **add_querystring** tag, where the base link is our masterpage's link, since the masterpage is where the task goes on.

```html
<cms:set task.sequent_task = "<cms:add_querystring k_template_link querystring />" scope='parent' />
```

The query string part will continue to hold the job's name (that is our snippet name) and maximum count. Query string is then copy-pasted without changes. I'll take query string from the superglobal *$_SERVER* array, because it is already there and no special reason to craft it anew with **gpc** tag.
```html
<cms:set querystring = "<cms:php>echo $_SERVER['QUERY_STRING'];</cms:php>" />
```

Let's see the final part together &mdash;

```html
<cms:if counted >
   <!--OK, pages were created-->
   <cms:set task.notes. = "Task is successful with creating <cms:show counted /> new page(s)." scope='parent' />
   <cms:set task.success = '1' scope='parent' />
   <cms:set task.continue= '1' scope='parent' />
   <cms:set querystring = "<cms:php>echo $_SERVER['QUERY_STRING'];</cms:php>" />
   <cms:set task.sequent_task = "<cms:add_querystring k_template_link querystring />" scope='parent' />
   <cms:if task.error >
      <!--Maybe some page was not created, we'll continue and try again later-->
      <cms:set task.notes. = "There was a problem during the task:" scope='parent' />
      <cms:set task.notes. = task.error scope='parent' />
   </cms:if>
<cms:else_if task.error />
   <!--Wow, this is a dead end, nothing was created and error popped up.-->
   <cms:set task.success = '0' scope='parent' />
   <cms:set task.continue= '0' scope='parent' />
   <cms:set task.sequent_task = '' scope='parent' />
   <cms:set task.msg = "Job failed completely." scope='parent' />
   <cms:set task.notes. = "There is a serious problem:" scope='parent' />
   <cms:set task.notes. = task.error scope='parent' />
<cms:else />
   <!--Ok, the job is done, no errors, no pages left.-->
   <cms:set task.success = '1' scope='parent' />
   <cms:set task.continue= '0' scope='parent' />
   <cms:set task.sequent_task = '' scope='parent' />
   <cms:set task.msg = "Job is done." scope='parent' />
   <cms:set task.notes. = "Request confirmed that no more pages are required." scope='parent' />
</cms:if>
```

### task is written

Piece by piece we managed to craft the task. Here is the task-snippet's code:

<details><summary>complete listing</summary>

```html
<cms:set desired_max = "<cms:get 'k_named_args.max-count' default="<cms:gpc 'max-count' method='get' />" />" scope='global'/>
<cms:set total_pages = "<cms:pages masterpage=k_template_name show_future_entries='1' count_only='1' />" scope='global' />

<cms:set difference = "<cms:sub desired_max total_pages />" />
<cms:if difference gt task.pg_limit>
   <!--OK, there are still many pages to create. Will use oringinal task.pg_limit-->
   <cms:else_if difference gt '0' />
   <!--There are a few pages left to create, but less than task.pg_limit. Will use new value.-->
   <cms:set task.pg_limit = difference scope='parent' />
   <cms:else />
   <!--Nothing to do-->
   <cms:set task.pg_limit = '0' scope='parent' />
</cms:if>

<cms:set counted = '0' scope='global'/>
<cms:set allowed = '1' scope='global'/>
<cms:while (counted lt task.pg_limit) && allowed eq '1'>
   <cms:db_persist
        _masterpage = k_template_name
        _mode = 'create'
        _auto_title = '1'
        _fields = '' >

        <cms:if k_success>
            <cms:set task.notes. = "Created pagename '<cms:show k_last_insert_page_name />' with id '<cms:show k_last_insert_id />'." scope='parent' />
            <cms:incr counted />
        <cms:else />
            <cms:set task.success = '0' scope='parent' />
            <cms:set task.continue= '1' scope='parent' />
            <cms:set task.error = k_error scope='parent' />
            <cms:set allowed = '0' scope='parent'/>
            <cms:set task.notes. = "There was a problem creating a page after <cms:show counted /> pages." scope='parent' />
        </cms:if>
   </cms:db_persist>

</cms:while>

<cms:if counted >
   <!--OK, pages were created-->
   <cms:set task.notes. = "Task is successful with creating <cms:show counted /> new page(s)." scope='parent' />
   <cms:set task.success = '1' scope='parent' />
   <cms:set task.continue= '1' scope='parent' />
   <cms:set querystring = "<cms:php>echo $_SERVER['QUERY_STRING'];</cms:php>" />
   <cms:set task.sequent_task = "<cms:add_querystring k_template_link querystring />" scope='parent' />
   <cms:if task.error >
      <!--Maybe some page was not created, we'll continue and try again later-->
      <cms:set task.notes. = "There was a problem during the task:" scope='parent' />
      <cms:set task.notes. = task.error scope='parent' />
   </cms:if>
<cms:else_if task.error />
   <!--Wow, this is a dead end, nothing was created and error popped up.-->
   <cms:set task.success = '0' scope='parent' />
   <cms:set task.continue= '0' scope='parent' />
   <cms:set task.sequent_task = '' scope='parent' />
   <cms:set task.msg = "Job failed completely." scope='parent' />
   <cms:set task.notes. = "There is a serious problem:" scope='parent' />
   <cms:set task.notes. = task.error scope='parent' />
<cms:else />
   <!--Ok, the job is done, no errors, no pages left.-->
   <cms:set task.success = '1' scope='parent' />
   <cms:set task.continue= '0' scope='parent' />
   <cms:set task.sequent_task = '' scope='parent' />
   <cms:set task.msg = "Job is done." scope='parent' />
   <cms:set task.notes. = "Request confirmed that no more pages are required." scope='parent' />
</cms:if>
```

</details>

Now we can be good coders and try to run this task separately, one or two times, to see that it works without problems.

## Verify the task works

One line one call makes the verification &mdash;
```html
<cms:call 'task-file-runner' job='create-pages' limit='2' max-count='5'/>
```
The call above, placed in our empty clonable template, will embed the snippet ***create-pages***__.inc__ and the snippet will create exactly *2* pages, if the number of pages in this clonable template is less than 5. Visit the page once.

The printed result should look similar to what follows &mdash;
```json
{
   "success":"1",
   "continue":"1",
   "current_task":"",
   "sequent_task":"index.php",
   "error":"",
   "msg":"",
   "task_time_start":"12:59:38 939",
   "task_time_close":"12:59:39 003",
   "pg":"",
   "pg_limit":"2",
   "notes":[
      "Created pagename '0b0f31e2584638ad6d7cfc86af09e9ff' with id '11054'.",
      "Created pagename '0df49232b84cb0cda19c89a197c41d74' with id '11055'.",
      "Task is successful with creating 2 new page(s)."
   ],
   "task_file":"create-pages.inc",
   "path_func":""
}
```

Refresh the page a couple of times and soon there will be no more pages to create. The report will become as follows &mdash;

```json
{
   "success":"1",
   "continue":"0",
   "current_task":"",
   "sequent_task":"",
   "error":"",
   "msg":"Job is done.",
   "task_time_start":"13:00:46 625",
   "task_time_close":"13:00:46 628",
   "pg":"",
   "pg_limit":"0",
   "notes":[
      "Request confirmed that no more pages are required."
   ],
   "task_file":"create-pages.inc",
   "path_func":""
}
```

That concludes the debug and we can now be almost sure the task-snippet runs fune.

Later, we will remove the parameters from the **task-file-runner** call and let the query string be the boss. It is time to set up the job and try it live.

## Set up the job

I will note here that my *target* masterpage is simply **index.php**. The code will be running on the 'index.php' template, I will visit it to start the job. The job will be creating the pages in the same template. That explained, let's make the calls.

```html
<cms:call 'add-job' name='create-pages' list='mytodo' masterpage='index.php' qs='max-count=50' report_func='report'/>
```

### is it what you want?

This part is not necessary, not required. May skip it completely.

I am simply printing the job to test the call to **add-job** func. I'll temporarily use tag **ignore** around our previous experiment and throw in a simple **report** func e.g.
```html
<cms:ignore>
   <cms:call 'task-file-runner' job='create-pages' limit='2' max-count='5'/>
</cms:ignore>

<cms:func 'report' rep=''>
   <cms:show_json rep />
</cms:func>

<cms:call 'add-job' name='create-pages' list='mytodo' masterpage='index.php' qs='max-count=50&limit=5' report_func='report'/>

<cms:show_json mytodo />
```
Output should display how our job is created. Again, this part is, of course, not required and not necessary at all.

<details><summary>Job's parameters in JSON</summary>

```json
[
   {
      "name":"create-pages",
      "is_complete":"",
      "status":"",
      "error":"",
      "initial_task":"http://my.couch/index.php?job=create-pages&max-count=50&limit=5",
      "current_task":"http://my.couch/index.php?job=create-pages&max-count=50&limit=5",
      "sequent_task":"http://my.couch/index.php?job=create-pages&max-count=50&limit=5",
      "time_start":"",
      "time_close":"",
      "report":[],
      "msg":"",
      "notes":[
         "Using default ~fetch-url~ engine.",
         "Using custom ~report~ report."
      ],
      "list":"mytodo",
      "user":{
         "name":"create-pages",
         "list":"mytodo",
         "masterpage":"index.php",
         "qs":"max-count=50&limit=5",
         "report_func":"report",
         "engine_func":""
      }
   }
]
```

</details>

If you are happy with the job, it is time to wrap up and run the task.

## Exec

If you recall (parent README), we set up the environment very simply e.g.
```html
<cms:embed 'myfuncs.inc' />
<cms:call 'php-time-limit' '0' />
<cms:call 'limit-decline' '2' 'Wait..' />
```

As discussed previously, I will remove all parameters from **task-file-runner** call. Also I wrap this call inside the **is_ajax** tag, that recognizes that the page was accessed programmatically. Func **task-file-runner** will abort the page with JSON reponse from the task and therefore we don't need to do anything else besides running it only for programmatic requests e.g.

```html
<cms:if "<cms:is_ajax />"><cms:call 'task-file-runner' /></cms:if>
```

The call above will not use any parameters to tweak a path to the task-snippet, because I simply placed the task-snippet in my *snippets* folder and named it *create-pages.inc*. That should do.

Next, place our previous code —
```html
<cms:func 'report' rep=''>
   <cms:show_json rep />
</cms:func>

<cms:call 'add-job' name='create-pages' list='mytodo' masterpage='index.php' qs='max-count=50&limit=5' report_func='report'/>
```

And let the job run &mdash;
```html
<cms:call 'execute-jobs' mytodo />
```

That is all.

<details><summary>full listing</summary>

```html
<cms:embed 'myfuncs.inc' />
<cms:call 'php-time-limit' '0' />
<cms:call 'limit-decline' '2' 'Wait..' />

<cms:if "<cms:is_ajax />"><cms:call 'task-file-runner' /></cms:if>

<cms:func 'report' rep=''>
   <cms:show_json rep />
</cms:func>

<cms:call 'add-job' name='create-pages' list='mytodo' masterpage='index.php' qs='max-count=25&limit=10' report_func='report'/>
<cms:call 'execute-jobs' mytodo />
```

</details>

Visit the page in browser and see the full report.

<details><summary>full report in JSON</summary>

```json
{
   "name":"create-pages",
   "is_complete":"1",
   "status":"JOB_COMPLETE",
   "error":"",
   "initial_task":"http://my.couch/index.php?job=create-pages&max-count=25&limit=10",
   "current_task":"http://my.couch/index.php?job=create-pages&max-count=25&limit=10",
   "sequent_task":"http://my.couch/index.php?job=create-pages&max-count=25&limit=10",
   "time_start":"13:50:24 299",
   "time_close":"13:50:25 429",
   "report":[
      {
         "success":"1",
         "continue":"1",
         "current_task":"http://my.couch/index.php?job=create-pages&max-count=25&limit=10",
         "sequent_task":"http://my.couch/index.php?job=create-pages&max-count=25&limit=10",
         "error":"",
         "msg":"",
         "task_time_start":"13:50:24 412",
         "task_time_close":"13:50:24 710",
         "pg":"",
         "pg_limit":"10",
         "notes":[
            "Created pagename '9d966f3ee99d39a37da8096379f91c0d' with id '11187'.",
            "Created pagename '7461ae383a6c4238fde53b1a9a3b1608' with id '11188'.",
            "Created pagename 'c4e5d1a3e754c2575c2c2ec647d2458e' with id '11189'.",
            "Created pagename '3efc8037a94603253e78f177857f9fef' with id '11190'.",
            "Created pagename 'b8f2733bbae71f3ab728be4312f7d78f' with id '11191'.",
            "Created pagename 'b0fe0dc37acbc3adeb0c24ff1a898bed' with id '11192'.",
            "Created pagename '01ba9e827b8deb82fc7acf53e8629d86' with id '11193'.",
            "Created pagename '6278f52d664729b9f4da44fd18cc6dd5' with id '11194'.",
            "Created pagename '85fbde5ba6546b09e308d54eb9dbcdbb' with id '11195'.",
            "Created pagename '8b4c125136fa745e9ff6c8f8a61b513d' with id '11196'.",
            "Task is successful with creating 10 new page(s)."
         ],
         "task_file":"create-pages.inc",
         "path_func":""
      },
      {
         "success":"1",
         "continue":"1",
         "current_task":"http://my.couch/index.php?job=create-pages&max-count=25&limit=10",
         "sequent_task":"http://my.couch/index.php?job=create-pages&max-count=25&limit=10",
         "error":"",
         "msg":"",
         "task_time_start":"13:50:24 787",
         "task_time_close":"13:50:25 074",
         "pg":"",
         "pg_limit":"10",
         "notes":[
            "Created pagename 'ab3cb9e3cdae9050cbd86a5ccb2354bd' with id '11197'.",
            "Created pagename 'ed896c21b8729603b7cc44ce6d8d1b9a' with id '11198'.",
            "Created pagename '0b07d5d4b472398415cd9ee2e7cb629b' with id '11199'.",
            "Created pagename '3cabf92f0b086adfac9a1e5a30604814' with id '11200'.",
            "Created pagename '7102623794eca5808802478bac7489ed' with id '11201'.",
            "Created pagename '621103e043fa0bafe0962b3b1f4da39e' with id '11202'.",
            "Created pagename 'e67fa3898939c419d6a7022fba0de3df' with id '11203'.",
            "Created pagename '094a89697b3e7ce65f1258ad65d12244' with id '11204'.",
            "Created pagename '0f773797205ee5d0b100d615feb13d66' with id '11205'.",
            "Created pagename 'be250f9f44fa58cad1ff705fc4f3b601' with id '11206'.",
            "Task is successful with creating 10 new page(s)."
         ],
         "task_file":"create-pages.inc",
         "path_func":""
      },
      {
         "success":"1",
         "continue":"1",
         "current_task":"http://my.couch/index.php?job=create-pages&max-count=25&limit=10",
         "sequent_task":"http://my.couch/index.php?job=create-pages&max-count=25&limit=10",
         "error":"",
         "msg":"",
         "task_time_start":"13:50:25 164",
         "task_time_close":"13:50:25 307",
         "pg":"",
         "pg_limit":"5",
         "notes":[
            "Created pagename '07d397850fd729861ad78b15e2a007bb' with id '11207'.",
            "Created pagename 'f0e42a588239380bca97c75dd71d5d0a' with id '11208'.",
            "Created pagename '534034ad86e9048701c93b6d08ad1bd5' with id '11209'.",
            "Created pagename 'a829784d90342f8c1e2d3e9484895bb1' with id '11210'.",
            "Created pagename '71a5a611164cb699f66606f20ad25d1d' with id '11211'.",
            "Task is successful with creating 5 new page(s)."
         ],
         "task_file":"create-pages.inc",
         "path_func":""
      },
      {
         "success":"1",
         "continue":"0",
         "current_task":"http://my.couch/index.php?job=create-pages&max-count=25&limit=10",
         "sequent_task":"",
         "error":"",
         "msg":"Job is done.",
         "task_time_start":"13:50:25 423",
         "task_time_close":"13:50:25 427",
         "pg":"",
         "pg_limit":"0",
         "notes":[
            "Request confirmed that no more pages are required."
         ],
         "task_file":"create-pages.inc",
         "path_func":""
      }
   ],
   "msg":"Job [
       create-pages
   ] is COMPLETE",
   "notes":[
      "Using default ~fetch-url~ engine.",
      "Using custom ~report~ report."
   ],
   "list":"mytodo",
   "user":{
      "name":"create-pages",
      "list":"mytodo",
      "masterpage":"index.php",
      "qs":"max-count=25&limit=10",
      "report_func":"report",
      "engine_func":""
   }
}
```
</details>

WIth everything done, you can totally use this code anywhere by either copy-pasting or embedding via a new snippet. There are enthusiasts, though, who will demand even more *encapsulation* and even less work. If you are one of them, the next chapter is for you.

## Reuse

Hopefully, you appreciated how simple became the listing after the bits were written here and there. Once the task-snippet file is figured out, the wrapping parts are very basic. It even allows us to wrap the whole listing in yet *another* 'cms:func' to achieve complete re-usability.

Our goal would be like having a single call for our needs e.g.

```html
<cms:call 'create-pages' 'fields.php' '5' '10' />
```

Pretty elegant, if you ask me.

### new func

Let's wrap our small code in the func **create-pages** and make a few changes. First, make **masterpage** dynamic and introduce a new **target** parameter to the query string – it will catch the name of template which needs new pages from **masterpage**.

```html
<cms:func 'create-pages' masterpage='' limit='' total=''>
   <cms:set my_qs = "<cms:concat 'max-count=' total '&limit=' limit '&target=' masterpage />" />

   <cms:if "<cms:is_ajax />"><cms:call 'task-file-runner' /></cms:if>

   <cms:func 'report' rep=''>
      <cms:show_json rep />
   </cms:func>

   <cms:call 'add-job' name='create-pages' list='mytodo' masterpage=k_template_name qs=my_qs report_func='report'/>
   <cms:call 'execute-jobs' mytodo />
</cms:func>
```

You see that our query string has got a new element and I decided to set it separately as **my_qs** for readability.

Again, the job will be requesting the template it is called from with ajax-headers, so the previous code with **is_ajax** tag remains the same.

### changes in task

#### new parameter
Change the task-snippet to use newly-supplied query string parameter e.g.
```html
<cms:set target_template_name = "<cms:get 'k_named_args.target' default="<cms:gpc 'target' method='get' />" />" scope='global'/>
```
#### tag pages

Variable **target_template_name** will be used in tags: **pages** and **db_persist** e.g.
```html
<cms:set total_pages = "<cms:pages masterpage=target_template_name show_future_entries='1' count_only='1' />" scope='global' />
```
#### tag db_persist
```html
<cms:db_persist
     _masterpage = target_template_name
```

### debug

Please remember the moment where we debugged our task-snippet and used **task-file-runner** directly. If you wish to re-do the tutorial with the re-usability in mind and new parameter **target**, make the amendment e.g.
```html
<cms:call 'task-file-runner' job='create-pages' target='my-target-template.php' limit='2' max-count='5'/>
```


### YES!

With all preparations we may now stash the task-snippet *create-pages.inc* and the new function **create-pages** somewhere and call it when needed.

```html
<cms:call 'create-pages' 'my-clonable-template.php' limit='25' total='10000' />
```

Paginated approach will work and server will be happy ☻.

---

Thank you for your time!


## Requirements

I have used the following functions quickly connected via `myfuncs.inc` that you may copy-paste &mdash;

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

Clone the repo to your configured **`snippets`** folder and name repo locally as **`func`** &mdash;
```shell
cd /var/www/html/example.com/mysnippets
```
```shell
git clone http://github.com/trendoman/Cms-Fu funcs
```
or download the zip and place content in the same folder.

Create 'myfuncs.inc' snippet and copy-paste the above embeds there.


## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
