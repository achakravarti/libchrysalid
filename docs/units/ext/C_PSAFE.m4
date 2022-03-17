include(`macros.m4')


ifdef(<<<MAN>>>,
<<<% LIBCHRYSALIS:C_IMMUTABLE(3) libchrysalis 0.0.1
%
% 2022>>>)


__NAME__(<<<C_PSAFE>>>)

`C_PSAFE` - hints a function has no null parameters


__SYNOPSIS__(<<<C_PSAFE>>>)

```
#include "libchrysalis/api.h"

#define C_PSAFE
```


__DESCRIPTION__(<<<C_PSAFE>>>)

The `C_PSAFE` macro indicates that *all* pointer parameters of a function are
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


__FILES__(<<<C_PSAFE>>>)

*/usr/local/src/libchrysalis/include/ext.h*
: Definition of `C_PSAFE` macro.

*/usr/local/include/libchrysalis/ext.h*
: Symbolic link to */usr/local/src/libchrysalis/include/ext.h*; required by
client code to correctly resolve `#include <libchrysalis/api.h>`.

*/usr/local/src/libchrysalis/doc/units/ext/C_PSAFE.m4*
: *m4* template for documentation.

*/usr/local/man/man3/libchrysalis:C_PSAFE.3.gz*
__SWITCHMX__(
<<<: Man page documentation (this page).>>>,
<<<: Man page documentation.>>>)


__EXAMPLES__(<<<C_PSAFE>>>)

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


__CONFORMINGTO__(<<<C_PSAFE>>>)

GCC, Clang.


__NOTES__(<<<C_PSAFE>>>)

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


__COPYRIGHT__


__SEEALSO__(<<<C_IMMUTABLE>>>)

__SWITCHMX__(
<<<**libchrysalis:extensions(7)**, **libchrysalis:C_RSAFE(3)**>>>,
<<<TODO>>>)


__COLOPHON__


__CITATIONS__

