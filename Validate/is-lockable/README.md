# is-lockable

Tries to obtain a lock and returns either ***1*** upon success or ***0*** if the lock is in use or can not be set.

```xml
<cms:call 'is-lockable' />
```

If the call above is placed on page, before some important code, it will lock future attempts to execute the code below the call. When the important code completes, the lock is lifted and any other visitor loading the same page, will trigger the code execution and the lock will be set again till the code completes. A *lock* is a simple variable flag, maintained by a database server i.e. MySQL and is very reliable.

This function works with existing Couch functions that wrap following queries to database –

```sql
SELECT IS_FREE_LOCK()
SELECT RELEASE_LOCK()
SELECT GET_LOCK()
```

Related function is [**limit-decline**](#related-funcs) which does a similar job for multiple locks or [**single-thread**](#related-funcs), however both these funcs do not have return values.

## Parameters

* **uid** — set a string identifying the lock, default is based on current date at 15-minutes intervals.

## Usage

Limit a block of code to the single instance —

```xml
<cms:if "<cms:call 'is-lockable' />">
   <cms:repeat '10'>
      <cms:call 'sleep' '0.5' />
   </cms:repeat>
Done.
<cms:else />
Wait..
</cms:if>
```

Visit the same page in 2 different browsers simultaneously. You will see a message in one of the windows.

```txt
Wait..
```

Meanwhile each page request can be visible in the query log when lock is checked for availability —

```sql
SELECT IS_FREE_LOCK('lock_is_lockable_20220706031500') AS lck
```

Lock is automatically lifted after the page completes execution by running another query e.g.

```sql
SELECT RELEASE_LOCK('lock_is_lockable_20220706031500') AS lck
```

## Installation

Use [**Autoloading**](ADDON-FUNCS-ON-DEMAND.md) or copy the func code to the page before the call or embed the snippet —

```xml
<cms:embed 'funcs/Validate/is-lockable/is-lockable.func' />
```

## Related funcs

* [**limit-decline**](https://github.com/trendoman/Cms-Fu/tree/master/Server/limit-decline/)
* [**single-thread**](https://github.com/trendoman/Cms-Fu/tree/master/Server/single-thread/)

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
