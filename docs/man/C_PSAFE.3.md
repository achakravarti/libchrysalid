% LIBCHRYSALIS:C_PSAFE(3) libchrysalis 0.0.1
%
% 2022


# NAME

`C_PSAFE` - hints a function has no null parameters


# SYNOPSIS

```
#include "libchrysalis/api.h"

#define C_PSAFE
```

 
# DESCRIPTION

The `C_PSAFE` macro indicates that _all_ pointer parameters of a function are
required to be non-null. A warning is issued if a null pointer is passed to any
of the parameters of such a function. This macro has no effect on non-pointer
parameters, and so must be used to decorate functions with at least one pointer
parameter. A warning is issued if this macro is used to decorate a function
without any pointer parameters.

This macro uses the non-standard `__attribute__((nonnull))` decorator, and is
available for both GCC and Clang. On other compilers, the default behaviour of
this macro is to degrade safely to a no-op with a suitable warning message. If
you don't want this warning message to be displayed, then define the macro
`C_SUPPRESS_EXTENSION_WARNINGS` at compile time.


# FILES

*/usr/local/src/libchrysalis/include/base/ext.h*
: Definition of `C_PSAFE` macro.

*/usr/local/include/libchrysalis/base/ext.h*
: Symbolic link to */usr/local/src/libchrysalis/include/base/ext.h*; required by
client code to correctly resolve `#include <libchrysalis/api.h>`.

*/usr/local/src/libchrysalis/doc/base/c_psafe.md*
: Markdown documentation in man layout.

*/usr/local/man/man3/libchrysalis:C_PSAFE.3.gz*
: Man page documentation (this page).


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
  code smell.

- Clang allows the `__attribute__((nonnull))` decorator to be applied
  directly to a function parameter, but GCC does not. Therefore,
  `C_PSAFE` may be used to mark specific function parameters when
  compiled with Clang; however, it is better not to do so in the
  interest of portability.

- Clang also provides the non-standard attribute `_Nonnull`, which is
  semantically identical to `__attribute__((nonnull))`; however, GCC
  does not support this.


# COPYRIGHT

`libchrysalis` along with its documentation are released under the BSD 2-Clause
License.


# SEE ALSO

**libchrysalis:C_RSAFE(3)**, 
*[GCC Online Docs](https://gcc.gnu.org/onlinedocs/gcc-11.2.0/gcc
/Common-Function-Attributes.html#Common-Function-Attributes)*,
*[Clang Documentation](https://clang.llvm.org/docs/AttributeReference.html)*


# COLOPHON

This page is part of release 0.0.1 of the `libchrysalis` project. The latest
version of this project can be found at
[GitHub](https://github.com/achakravarti/libchrysalis).

