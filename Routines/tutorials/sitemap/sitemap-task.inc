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
