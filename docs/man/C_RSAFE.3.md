% LIBCHRYSALIS:C_RSAFE(3) libchrysalis 0.0.1
%
% 2022


# NAME

`C_RSAFE` - hints a function never returns a null pointer


# SYNOPSIS

```
#include "libchrysalis/api.h"

#define C_RSAFE
```
 

# DESCRIPTION

The `C_RSAFE` macro hints that a function will never return a null pointer. When
a function is marked with this macro, the compiler can make suitable
optimisations for that function. The `C_RSAFE` macro may only be applied to
functions that return a pointer type; a compiler warning will be issued if
applied to functions returning other types.

This macro uses the non-standard `__attribute__((returns_nonnull))` decorator
[@gcc:function-attributes], and is available for both GCC and Clang. On other
compilers, the default behaviour of this macro is to degrade safely to a no-op
with a suitable warning message. If you don't want this warning message to be
displayed, then define the macro `C_SUPPRESS_EXTENSION_WARNINGS` at compile
time.


# FILES

*/usr/local/src/libchrysalis/include/ext.h*
: Definition of `C_RSAFE` macro.

*/usr/local/include/libchrysalis/ext.h*
: Symbolic link to */usr/local/src/libchrysalis/include/ext.h*; required by
client code to correctly resolve `#include <libchrysalis/api.h>`.

*/usr/local/src/libchrysalis/doc/man/C_RSAFE.3.md*
: Markdown documentation in man layout.

*/usr/local/man/man3/libchrysalis:C_RSAFE.3.gz*
: Man page documentation.


# EXAMPLES

```
C_RSAFE int *foo(char *, int *);    /* standard declaration */
void *bar(float *) C_RSAFE;         /* alternate declaration */

/* can also be applied on definitions */
C_RSAFE static int *foobar(char *foo, char c)
{
	*foo = c;
	return (int) c;
}
```


# CONFORMING TO

C99, C11, GCC, Clang.


# COPYRIGHT

Copyright &copy; 2022 Abhishek Chakravarti `<abhishek@taranjali.org>`

`libchrysalis` along with its documentation are released under the BSD 2-Clause
License. See **libchrysalis:license(7)** for the full license text.


# SEE ALSO

**libchrysalis:extensions(7)**, **libchrysalis:C_PSAFE(3)**


# COLOPHON

This page is part of release 0.0.1 of the `libchrysalis` project. The latest
version of this project can be found at
[GitHub](https://github.com/achakravarti/libchrysalis).

