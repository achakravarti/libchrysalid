include(`macros.m4')


ifdef(<<<MAN>>>,
<<<% LIBCHRYSALIS:C_STABLE(3) libchrysalis 0.0.1
%
% 2022>>>)


__NAME__(<<<C_STABLE>>>)

`C_STABLE` - marks a function as stable


__SYNOPSIS__(<<<C_STABLE>>>)

```
#include "libchrysalis/api.h"

#define C_STABLE
```


__DESCRIPTION__(<<<C_STABLE>>>)

The `C_STABLE` macro is used to mark a function as being stable. In
*libchrysalis*, we consider a function to be stable if it has the following
properties:

  1. It has no side effects, i.e. it does not modify any static variables,
     non-local variables, reference arguments or input streams.
  2. It returns the same value when repeatedly called with the same arguments,
     provided the arguments point to the same memory locations.

Stable functions can therefore be considered to be weak pure functions, since
their return value may change if their arguments point to different memory
locations between successive calls, unlike the case of strictly pure functions
[@wiki:pure-function]. A good example of a stable function is `strlen` since it
returns the same value as long as its argument points to the same memory
location between subsequent calls [@gcc:function-attributes].

By marking a function as stable with the `C_STABLE` macro, we allow the compiler
to perform optimisations such as common subexpression elimination, especially
when there are repeated calls to the function with the same arguments
[@gcc:function-attributes]. Note that by definition functions which return
`void` cannot be considered as stable; marking such functions with `C_STABLE`
will lead to a compiler diagnostic to be emitted [@gcc:function-attributes].


__FILES__(<<<C_STABLE>>>)

*/usr/local/src/libchrysalis/include/ext.h*
: Definition of `C_STABLE` macro.

*/usr/local/include/libchrysalis/ext.h*
: Symbolic link to */usr/local/src/libchrysalis/include/ext.h*; required by
client code to correctly resolve `#include <libchrysalis/api.h>`.

*/usr/local/src/libchrysalis/doc/units/ext/C_STABLE.m4*
: *m4* template for documentation.

*/usr/local/man/man3/libchrysalis:C_STABLE.3.gz*
__SWITCHMX__(
<<<: Man page documentation (this page).>>>,
<<<: Man page documentation.>>>)


__EXAMPLES__(<<<C_STABLE>>>)

```

/* Declare function check_empty to be stable */
static C_STABLE bool check_empty(char *);


/* Define check_empty function; note that we don't mark it stable again */
bool check_empty(char *str)
{
	return str && *str;
}


/* Declare function check_not_empty as stable directly within its definition */
static C_STABLE bool check_not_empty(char *str)
{
	return !(str && *str);
}
```


__CONFORMINGTO__(<<<C_STABLE>>>)

GCC 11.2, Clang 13.0.1.


__NOTES__(<<<C_STABLE>>>)

- The `C_STABLE` macro is defined in terms of the non-standard
  `__attribute__((pure))` attribute available on GCC and Clang
  [@gcc:function-attributes]. If any other compiler is used which does not
  support this attribute then the `C_STABLE` macro expands to a safe no-op with
  a compiler warning. Althogh not recommended, if you want to suppress this
  warning, then define the `C_SUPPRESS_EXTENSION_WARNINGS` symbolic constant at
  compilation time.

- The term stable is borrowed from the `STABLE` volatility class of PostgreSQL
  functions, which has a similar connotation as the `C_STABLE` macro
  [@pgsql:volatility].


__COPYRIGHT__


__SEEALSO__(<<<C_STABLE>>>)

__SWITCHMX__(
<<<**libchrysalis:extensions(7)**, **libchrysalis:C_IMMUTABLE(3)**>>>,
<<<TODO>>>)


__COLOPHON__


__CITATIONS__

