% LIBCHRYSALID:C_LIKELY(3) libchrysalid 0.0.1
%
% 2022


# NAME

`C_LIKELY` - hints predicate as likely to be true


# SYNOPSIS

```
#include "libchrysalid/api.h"

#define C_LIKELY(_P_)
```


# DESCRIPTION

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


# RETURN VALUE

The Boolean value which the predicate `_P_` evaluates to is returned.


# FILES

*/usr/local/src/libchrysalid/ext.h*
: Definition of `C_LIKELY` macro.

*/usr/local/include/libchrysalid/ext.h*
: Symbolic link to */usr/local/src/libchrysalid/include/ext.h*; required by
client code to correctly resolve `#include <libchrysalid/api.h>`.

*/usr/local/src/libchrysalid/doc/man/C_LIKELY.3.md*
: Markdown documentation in man layout.

*/usr/local/man/man3/libchrysalid:C_LIKELY.3.gz*
: Man page documentation.


# EXAMPLES

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


# CONFORMING TO

C99, C11, GCC, Clang.


# NOTES
 
- This macro is inspired by the `likely()` macro in the Linux kernel
  [@kernel-newbies:likely-unlikely].
- Marking a predicate as likely with `C_LIKELY()` when it is not so will
  have the contrary effect of degrading performance.


# COPYRIGHT

Copyright &copy; 2022 Abhishek Chakravarti `<abhishek@taranjali.org>`

`libchrysalid` along with its documentation are released under the BSD 2-Clause
License. See **libchrysalid:license(7)** for the full license text.


# SEE ALSO

**libchrysalid:extensions(7)**, **libchrysalid:C_UNLIKELY(3)**


# COLOPHON

This page is part of release 0.0.1 of the `libchrysalid` project. The latest
version of this project can be found at
[GitHub](https://github.com/achakravarti/libchrysalid).

