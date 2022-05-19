% LIBCHRYSALID:C_STABLE(3) libchrysalid 0.0.1
%
% 2022


# NAME

`C_STABLE` - marks a function as stable


# SYNOPSIS

```
#include "libchrysalid/api.h"

#define C_STABLE
```


# DESCRIPTION

The `C_STABLE` macro is used to mark a function as being stable. In
*libchrysalid*, we consider a function to be stable if it has the following
properties:

  1. It has no side effects, i.e. it does not modify any static variables,
     non-local variables, reference arguments or input streams
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


# FILES

*/usr/local/src/libchrysalid/ext.h*
: Definition of `C_STABLE` macro.

*/usr/local/include/libchrysalid/ext.h*
: Symbolic link to */usr/local/src/libchrysalid/include/ext.h*; required by
client code to correctly resolve `#include <libchrysalid/api.h>`.

*/usr/local/src/libchrysalid/doc/man/C_STABLE.3.md*
: Markdown documentation in man layout.

*/usr/local/man/man3/libchrysalid:C_STABLE.3.gz*
: Man page documentation.


# EXAMPLES


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


# CONFORMING TO

GCC, Clang.


# NOTES

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


# COPYRIGHT

Copyright &copy; 2022 Abhishek Chakravarti `<abhishek@taranjali.org>`

`libchrysalid` along with its documentation are released under the BSD 2-Clause
License. See **libchrysalid:license(7)** for the full license text.


# SEE ALSO

**libchrysalid:extensions(7)** **libchrysalid:immutable(3)**


# COLOPHON

This page is part of release 0.0.1 of the `libchrysalid` project. The latest
version of this project can be found at
[GitHub](https://github.com/achakravarti/libchrysalid).

