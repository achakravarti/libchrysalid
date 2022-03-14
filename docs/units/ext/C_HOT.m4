include(`macros.m4')


ifdef(<<<MAN>>>,
<<<% LIBCHRYSALIS:C_HOT(3) libchrysalis 0.0.1
%
% 2022>>>)


__NAME__(<<<C_HOT>>>)

`C_COLD` - hints a function as cold


__SYNOPSIS__(<<<C_HOT>>>)

```
#include "libchrysalis/api.h"

#define C_HOT
```


__DESCRIPTION__(<<<C_HOT>>>)

The `C_HOT` macro is used to hint that a function is hot, i.e. it is called
often. When `C_HOT` is applied to a function, the compiler _may_ optimise it
more aggressively, reordering the function so that it appears in a special
section with other hot functions so as to improve locality.

This macro uses the non-standard `__attribute__((hot))` decorator
[@gcc:function-attributes], and is available for both GCC and Clang. On other
compilers, the default behaviour of this macro is to degrade safely to a no-op
with a suitable warning message. If you don't want this warning message to be
displayed, then define the macro `C_SUPPRESS_EXTENSION_WARNINGS` at compile
time.


__FILES__(<<<C_HOT>>>)

*/usr/local/src/libchrysalis/include/ext.h*
: Definition of `C_HOT` macro.

*/usr/local/include/libchrysalis/ext.h*
: Symbolic link to */usr/local/src/libchrysalis/include/ext.h*; required by
client code to correctly resolve `#include <libchrysalis/api.h>`.

*/usr/local/src/libchrysalis/doc/units/ext/C_HOT.m4*
: *m4* template for documentation.

*/usr/local/man/man3/libchrysalis:C_HOT.3.gz*
__SWITCHMX__(
<<<: Man page documentation (this page).>>>,
<<<: Man page documentation.>>>)


__EXAMPLES__(<<<C_HOT>>>)

```
C_HOT int foo(char *, int *);   /* standard declaration */
void bar(float *) C_HOT;        /* alternate declaration */

/* can also be applied on definitions */
C_HOT static int foobar(char *foo, char c)
{
	*foo = c;
	return (int) c;
}
```


__CONFORMINGTO__(<<<C_HOT>>>)

C99, C11, GCC, Clang.


__NOTES__(<<<C_HOT>>>)

- `C_HOT` is ignored by GCC if the `-fprofile-use` flag is used during
  compilation [@gcc:function-attributes].
- Although Clang recognises the `__attribute__((hot))` decorator, it drops it
  silently; however, there is a proposal to implement this
  [@llvm-dev:hot-cold-attributes].


__COPYRIGHT__


__SEEALSO__(<<<C_HOT>>>)

__SWITCHMX__(
<<<**libchrysalis:extensions(7)**, **libchrysalis:C_HOT(3)**>>>,
<<<TODO>>>)


__COLOPHON__


__CITATIONS__

