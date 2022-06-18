# sleep

Make server wait. Count in seconds.

```xml
<cms:call 'sleep' for='0.500' />
```

```xml
<cms:call 'sleep' '5' />
```

## Parameters

* for &mdash; time in seconds

## Usage

Add 'sleeping' code that imitates a heavy page loading for a while (*5* seconds)

```xml
<cms:call 'sleep' '5' />
```

Internally func employs PHP function *usleep*.

## Installation

```xml
<cms:embed 'funcs/Server/sleep/sleep.func' />
```

## Support

Check out my dedicated [**SUPPORT**](/SUPPORT.md) page.
