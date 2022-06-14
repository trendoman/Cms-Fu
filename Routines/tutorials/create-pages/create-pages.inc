<cms:set target_template_name = "<cms:get 'k_named_args.target' default="<cms:gpc 'target' method='get' />" />" scope='global'/>
<cms:set desired_max = "<cms:get 'k_named_args.max-count' default="<cms:gpc 'max-count' method='get' />" />" scope='global'/>
<cms:set total_pages = "<cms:pages masterpage=target_template_name show_future_entries='1' count_only='1' />" scope='global' />


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
        _masterpage = target_template_name
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
