include(`macros.m4')


ifdef(<<<MAN>>>,
<<<% LIBCHRYSALID:C_IMMUTABLE(3) libchrysalid 0.0.1
%
% 2022>>>)


__NAME__(<<<C_IMMUTABLE>>>)

`C_IMMUTABLE` - marks a function as immutable


__SYNOPSIS__(<<<C_IMMUTABLE>>>)

```
#include "libchrysalid/api.h"

#define C_IMMUTABLE
```


__DESCRIPTION__(<<<C_IMMUTABLE>>>)

The `C_IMMUTABLE` macro is used to mark a function as being immutable. In
*libchrysalid*, we consider a function to be immutable if it has the following
properties:

  1. It has no side effects, i.e. it does not modify any static variables,
     non-local variables, reference arguments or input streams.
  2. It returns the same value when repeatedly called with the same arguments.

Immutable functions can therefore be considered to be strictly pure functions,
unlike the case of weakly pure functions (which *libchrysalid* refers to as
*stable* and are marked with the `C_STABLE` macro) [@wiki:pure-function]. A good
example of an immutable function is `abs` since it always returns the same value
for the same argument.

In contrast, `strlen` is a stable function but not an immutable one since it
returns the same value as long as its argument points to the same memory
location between subsequent calls [@gcc:function-attributes].

By marking a function as stable with the `C_IMMUTABLE` macro, we allow the
compiler to perform optimisations such as common subexpression elimination,
especially when there are repeated calls to the function with the same arguments
[@gcc:function-attributes]. Note that by definition functions which return
`void` cannot be considered as stable; marking such functions with `C_IMMUTABLE`
will lead to a compiler diagnostic to be emitted [@gcc:function-attributes].


__FILES__(<<<C_IMMUTABLE>>>)

*/usr/local/src/libchrysalid/include/ext.h*
: Definition of `C_IMMUTABLE` macro.

*/usr/local/include/libchrysalid/ext.h*
: Symbolic link to */usr/local/src/libchrysalid/include/ext.h*; required by
client code to correctly resolve `#include <libchrysalid/api.h>`.

*/usr/local/share/doc/libchrysalid/units/ext/C_IMMUTABLE.m4*
: *m4* template for documentation.

*/usr/local/share/man/man3/libchrysalid:C_IMMUTABLE.3.gz*
__SWITCHMX__(
<<<: Man page documentation (this page).>>>,
<<<: Man page documentation.>>>)


__EXAMPLES__(<<<C_IMMUTABLE>>>)

```

/* Declare function check_empty to be stable */
static C_IMMUTABLE bool check_positive(int);


/* Define check_empty function; note that we don't mark it stable again */
bool check_positive(int x)
{
	return x > 0;
}


/* Declare function check_not_empty as stable directly within its definition */
static C_IMMUTABLE bool check_negative(int x)
{
	return <= 0;
}
```


__CONFORMINGTO__(<<<C_IMMUTABLE>>>)

GCC 11.2, Clang 13.0.1.


__NOTES__(<<<C_IMMUTABLE>>>)

- The `C_IMMUTABLE` macro is defined in terms of the non-standard
  `__attribute__((const))` attribute available on GCC and Clang
  [@gcc:function-attributes]. If any other compiler is used which does not
  support this attribute then the `C_IMMUTABLE` macro expands to a safe no-op
  with a compiler warning. Although not recommended, if you want to suppress
  this warning, then define the `C_SUPPRESS_EXTENSION_WARNINGS` symbolic
  constant at compilation time.

- The term immutable is borrowed from the `IMMUTABLE` volatility class of
  PostgreSQL functions, which has a similar connotation as the `C_IMMUTABLE`
  macro [@pgsql:volatility].


__COPYRIGHT__


__SEEALSO__(<<<C_IMMUTABLE>>>)

__SWITCHMX__(
<<<**libchrysalid:extensions(7)**, **libchrysalid:C_STABLE(3)**>>>,
<<<TODO>>>)


__COLOPHON__


__CITATIONS__

