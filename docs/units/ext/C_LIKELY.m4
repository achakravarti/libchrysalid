include(`macros.m4')


ifdef(<<<MAN>>>,
<<<% LIBCHRYSALID:C_LIKELY(3) libchrysalid 0.0.1
%
% 2022>>>)


__NAME__(<<<C_LIKELY>>>)

`C_LIKELY` - hints predicate as likely to be true


__SYNOPSIS__(<<<C_LIKELY>>>)

```
#include "libchrysalid/api.h"

#define C_LIKELY
```


__DESCRIPTION__(<<<C_LIKELY>>>)

The `C_LIKELY()` macro provides a branch prediction hint to the compiler,
indicating that a predicate expression `_P_` is likely to be true. `_P_` is
expected to be an integral predicate expression that evaluates to a Boolean
value.

This macro uses the non-standard `__builtin_expect()` macro
[@gcc:other-builtins], and is available for both GCC and Clang. On other
compilers, the default behaviour of this macro is to degrade safely to a no-op
with a suitable warning message. If you don't want this warning message to be
displayed, then define the macro `C_SUPPRESS_EXTENSION_WARNINGS` at compile
time.


__RETURN__(<<<C_LIKELY>>>)

The Boolean value which the predicate `_P_` evaluates to is returned.


__FILES__(<<<C_LIKELY>>>)

*/usr/local/src/libchrysalid/include/ext.h*
: Definition of `C_LIKELY` macro.

*/usr/local/include/libchrysalid/ext.h*
: Symbolic link to */usr/local/src/libchrysalid/include/ext.h*; required by
client code to correctly resolve `#include <libchrysalid/api.h>`.

*/usr/local/share/doc/libchrysalid/units/ext/C_LIKELY.m4*
: *m4* template for documentation.

*/usr/local/share/man/man3/libchrysalid:C_LIKELY.3.gz*
__SWITCHMX__(
<<<: Man page documentation (this page).>>>,
<<<: Man page documentation.>>>)


__EXAMPLES__(<<<C_LIKELY>>>)


```
int foobar(char *foo, char c)
{
	if (C_LIKELY (foo != NULL)) {
		*foo = c;
		return (int) c;
	}
 
	return -1;
}
```


__CONFORMINGTO__(<<<C_LIKELY>>>)

GCC 11.2, Clang 13.0.1.


__NOTES__(<<<C_LIKELY>>>)

- This macro is inspired by the `likely()` macro in the Linux kernel
  [@kernel-newbies:likely-unlikely].
- Marking a predicate as likely with `C_LIKELY()` when it is not so will
  have the contrary effect of degrading performance.


__COPYRIGHT__


__SEEALSO__(<<<C_LIKELY>>>)

__SWITCHMX__(
<<<**libchrysalid:extensions(7)**, **libchrysalid:C_UNLIKELY(3)**>>>,
<<<TODO>>>)


__COLOPHON__


__CITATIONS__

