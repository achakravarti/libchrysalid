include(`macros.m4')


ifdef(<<<MAN>>>,
<<<% LIBCHRYSALIS:C_UNLIKELY(3) libchrysalis 0.0.1
%
% 2022>>>)


__NAME__(<<<C_UNLIKELY>>>)

`C_UNLIKELY` - hints predicate as unlikely to be true


__SYNOPSIS__(<<<C_UNLIKELY>>>)

```
#include "libchrysalis/api.h"

#define C_UNLIKELY
```


__DESCRIPTION__(<<<C_UNLIKELY>>>)

The `C_UNLIKELY()` macro provides a branch prediction hint to the compiler,
indicating that a predicate expression `_P_` is UNlikely to be true. `_P_` is
expected to be an integral predicate expression that evaluates to a Boolean
value.

This macro uses the non-standard `__builtin_expect()` macro
[@gcc:other-builtins], and is available for both GCC and Clang. On other
compilers, the default behaviour of this macro is to degrade safely to a no-op
with a suitable warning message. If you don't want this warning message to be
displayed, then define the macro `C_SUPPRESS_EXTENSION_WARNINGS` at compile
time.


__RETURN__(<<<C_UNLIKELY>>>)

The Boolean value which the predicate `_P_` evaluates to is returned.


__FILES__(<<<C_UNLIKELY>>>)

*/usr/local/src/libchrysalis/include/ext.h*
: Definition of `C_UNLIKELY` macro.

*/usr/local/include/libchrysalis/ext.h*
: Symbolic link to */usr/local/src/libchrysalis/include/ext.h*; required by
client code to correctly resolve `#include <libchrysalis/api.h>`.

*/usr/local/share/doc/libchrysalis/units/ext/C_UNLIKELY.m4*
: *m4* template for documentation.

*/usr/local/share/man/man3/libchrysalis:C_UNLIKELY.3.gz*
__SWITCHMX__(
<<<: Man page documentation (this page).>>>,
<<<: Man page documentation.>>>)


__EXAMPLES__(<<<C_UNLIKELY>>>)

```
int foobar(char *foo, char c)
{
	if (C_UNLIKELY (foo != NULL)) {
		*foo = c;
		return (int) c;
	}
 
	return -1;
}
```

__CONFORMINGTO__(<<<C_UNLIKELY>>>)

GCC 11.2, Clang 13.0.1.


__NOTES__(<<<C_UNLIKELY>>>)

- This macro is inspired by the `unlikely()` macro in the Linux kernel
  [@kernel-newbies:likely-unlikely].
- Marking a predicate as likely with `C_UNLIKELY()` when it is not so will
  have the contrary effect of degrading performance.


__COPYRIGHT__


__SEEALSO__(<<<C_UNLIKELY>>>)

__SWITCHMX__(
<<<**libchrysalis:extensions(7)**, **libchrysalis:C_LIKELY(3)**>>>,
<<<TODO>>>)


__COLOPHON__


__CITATIONS__

