# single-thread

Allows the script to finish before the new one can be started.

```xml
<cms:call 'single-thread' />
```

If the call above is placed on page, before some important code, it will lock future attempts to execute the code below the call. When the important code completes, the lock is lifted and any other visitor loading the same page, will trigger the code execution and the lock will be set again till the code completes. A *lock* is a simple variable flag, maintained by a database server i.e. MySQL and is very reliable.

This function works with existing Couch functions that wrap following queries to database –

```sql
SELECT IS_FREE_LOCK()
SELECT RELEASE_LOCK()
SELECT GET_LOCK()
```

Related function is [**limit-decline**](#related-funcs) which does a similar job for multiple locks.

## Parameters

* **uid** — set a string identifying the lock, default is based on current date in 15 min intervals.
* **msg** – set a message to aborted page, default is `<h2>Please wait..</h2>`

## Usage

Limit a block of code to the single instance —

```xml
<cms:call 'single-thread' msg='Script is running..' />
<cms:repeat '100'>
   <cms:call 'sleep' '0.5' />
</cms:repeat>
```

Visit the same page in 2 different browsers simultaneously. You will see a message in one of the windows.

```txt
Script is running..
```

Meanwhile each page request can be visible in the query log when lock is checked for availability —

```sql
SELECT IS_FREE_LOCK('lock_single_thread_20220706001500') AS lck
```

## Installation

Use [**Autoloading**](ADDON-FUNCS-ON-DEMAND.md) or copy the func code to the page before the call or embed the snippet —

```xml
<cms:embed 'funcs/Server/single-thread/single-thread.func' />
```

## Related funcs

* [**limit-decline**](https://github.com/trendoman/Cms-Fu/tree/master/Server/limit-decline/)

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
