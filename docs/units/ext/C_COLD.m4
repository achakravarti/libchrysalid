include(`macros.m4')


ifdef(<<<MAN>>>,
<<<% LIBCHRYSALID:C_COLD(3) libchrysalid 0.0.1
%
% 2022>>>)


__NAME__(<<<C_COLD>>>)

`C_COLD` - hints a function as cold


__SYNOPSIS__(<<<C_COLD>>>)

```
#include "libchrysalid/api.h"

#define C_COLD
```


__DESCRIPTION__(<<<C_COLD>>>)

The `C_COLD` macro is used to hint that a function is cold, i.e. it is
unlikely to called. Functions that are marked with `C_COLD` are
optimised by the compiler for size rather than speed, and are placed
into a special cold section in order to improve locality of code with
other cold functions. Exception handlers are good candidates for marking
with `C_COLD`.

This macro uses the non-standard `__attribute__((cold))` decorator
[@gcc:function-attributes], and is available for both GCC and Clang. On other
compilers, the default behaviour of this macro is to degrade safely to a no-op
with a suitable warning message. If you don't want this warning message to be
displayed, then define the macro `C_SUPPRESS_EXTENSION_WARNINGS` at compile
time.


__FILES__(<<<C_COLD>>>)

*/usr/local/src/libchrysalid/include/ext.h*
: Definition of `C_COLD` macro.

*/usr/local/include/libchrysalid/ext.h*
: Symbolic link to */usr/local/src/libchrysalid/include/ext.h*; required by
client code to correctly resolve `#include <libchrysalid/api.h>`.

*/usr/local/share/doc/libchrysalid/units/ext/C_COLD.m4*
: *m4* template for documentation.

*/usr/local/share/man/man3/libchrysalid:C_COLD.3.gz*
__SWITCHMX__(
<<<: Man page documentation (this page).>>>,
<<<: Man page documentation.>>>)


__EXAMPLES__(<<<C_COLD>>>)

```
C_COLD int foo(char *, int *);  /* standard declaration */
void bar(float *) C_COLD;       /* alternate declaration */
    
/* can also be applied on definitions */
C_COLD static int foobar(char *foo, char c)
{
	*foo = c;
	return (int) c;
}
```


__CONFORMINGTO__(<<<C_COLD>>>)

GCC 11.2, Clang 13.0.1.


__NOTES__(<<<C_COLD>>>)

- `C_COLD` is ignored by GCC if the `-fprofile-use` flag is used during
  compilation [@gcc:function-attributes].
- Unlike the case of `C_HOT`, Clang does _not_ silently drop this macro
  [@llvm-dev:hot-cold-attributes].


__COPYRIGHT__


__SEEALSO__(<<<C_COLD>>>)

__SWITCHMX__(
<<<**libchrysalid:extensions(7)**, **libchrysalid:C_HOT(3)**>>>,
<<<TODO>>>)


__COLOPHON__


__CITATIONS__

