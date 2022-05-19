% LIBCHRYSALID:C_PSAFE(3) libchrysalid 0.0.1
%
% 2022


# NAME

`C_PSAFE` - hints a function has no null parameters


# SYNOPSIS

```
#include "libchrysalid/api.h"

#define C_PSAFE
```

 
# DESCRIPTION

The `C_PSAFE` macro indicates that _all_ pointer parameters of a function are
required to be non-null. A warning is issued if a null pointer is passed to any
of the parameters of such a function. This macro has no effect on non-pointer
parameters, and so must be used to decorate functions with at least one pointer
parameter. A warning is issued if this macro is used to decorate a function
without any pointer parameters.

This macro uses the non-standard `__attribute__((nonnull))` decorator
[@gcc:function-attributes], and is available for both GCC and Clang. On other
compilers, the default behaviour of this macro is to degrade safely to a no-op
with a suitable warning message. If you don't want this warning message to be
displayed, then define the macro `C_SUPPRESS_EXTENSION_WARNINGS` at compile
time.


# FILES

*/usr/local/src/libchrysalid/include/ext.h*
: Definition of `C_PSAFE` macro.

*/usr/local/include/libchrysalid/ext.h*
: Symbolic link to */usr/local/src/libchrysalid/include/ext.h*; required by
client code to correctly resolve `#include <libchrysalid/api.h>`.

*/usr/local/src/libchrysalid/doc/man/C_PSAFE.3.md*
: Markdown documentation in man layout.

*/usr/local/man/man3/libchrysalid:C_PSAFE.3.gz*
: Man page documentation.


# EXAMPLES

```
C_PSAFE int foo(char *, int *);     /* standard declaration */
void bar(float *) C_PSAFE;          /* alternate declaration */

/* can also be applied on definitions */
C_PSAFE static int foobar(char *foo, char c)
{
	*foo = c;
      	return (int) c;
}
```

# CONFORMING TO

C99, C11, GCC, Clang.


# NOTES

- The `__attribute__((nonnull))` decorator optionally allows you to
  specify the 1-based index of the function parameters that are to be
  considered non-null; `C_PSAFE` doesn't do this both for the sake of
  brevity and also because we consider null pointer parameters to be a
  code smell [@gcc:function-attributes].

- Clang allows the `__attribute__((nonnull))` decorator to be applied
  directly to a function parameter, but GCC does not. Therefore,
  `C_PSAFE` may be used to mark specific function parameters when
  compiled with Clang; however, it is better not to do so in the
  interest of portability [@clang:attributes].

- Clang also provides the non-standard attribute `_Nonnull`, which is
  semantically identical to `__attribute__((nonnull))`; however, GCC
  does not support this [@clang:attributes].


# COPYRIGHT

Copyright &copy; 2022 Abhishek Chakravarti `<abhishek@taranjali.org>`

`libchrysalid` along with its documentation are released under the BSD 2-Clause
License. See **libchrysalid:license(7)** for the full license text.


# SEE ALSO

**libchrysalid:extensions(7)**, **libchrysalid:C_RSAFE(3)**


# COLOPHON

This page is part of release 0.0.1 of the `libchrysalid` project. The latest
version of this project can be found at
[GitHub](https://github.com/achakravarti/libchrysalid).

