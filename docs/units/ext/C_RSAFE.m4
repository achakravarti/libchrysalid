include(`macros.m4')


ifdef(<<<MAN>>>,
<<<% LIBCHRYSALID:C_RSAFE(3) libchrysalid 0.0.1
%
% 2022>>>)


__NAME__(<<<C_RSAFE>>>)

`C_RSAFE` - hints a function never returns a null pointer


__SYNOPSIS__(<<<C_RSAFE>>>)

```
#include "libchrysalid/api.h"

#define C_RSAFE
```


__DESCRIPTION__(<<<C_RSAFE>>>)

The `C_RSAFE` macro hints that a function will never return a null pointer. When
a function is marked with this macro, the compiler can make suitable
optimisations for that function. The `C_RSAFE` macro may only be applied to
functions that return a pointer type; a compiler warning will be issued if
applied to functions returning other types.


__FILES__(<<<C_RSAFE>>>)

*/usr/local/src/libchrysalid/include/ext.h*
: Definition of `C_RSAFE` macro.

*/usr/local/include/libchrysalid/ext.h*
: Symbolic link to */usr/local/src/libchrysalid/include/ext.h*; required by
client code to correctly resolve `#include <libchrysalid/api.h>`.

*/usr/local/share/doc/libchrysalid/units/ext/C_RSAFE.m4*
: *m4* template for documentation.

*/usr/local/share/man/man3/libchrysalid:C_RSAFE.3.gz*
__SWITCHMX__(
<<<: Man page documentation (this page).>>>,
<<<: Man page documentation.>>>)


__EXAMPLES__(<<<C_RSAFE>>>)

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


__CONFORMINGTO__(<<<C_RSAFE>>>)

GCC 11.2, Clang 13.0.1.


__NOTES__(<<<C_RSAFE>>>)

- This macro uses the non-standard `__attribute__((returns_nonnull))` decorator
  [@gcc:function-attributes], and is available for both GCC and Clang. On other
  compilers, the default behaviour of this macro is to degrade safely to a no-op
  with a suitable warning message. If you don't want this warning message to be
  displayed, then define the macro `C_SUPPRESS_EXTENSION_WARNINGS` at compile
  time.


__COPYRIGHT__


__SEEALSO__(<<<C_RSAFE>>>)

__SWITCHMX__(
<<<**libchrysalid:extensions(7)**, **libchrysalid:C_PSAFE(3)**>>>,
<<<TODO>>>)


__COLOPHON__


__CITATIONS__

