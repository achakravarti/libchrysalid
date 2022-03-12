% LIBCHRYSALIS:C_UNLIKELY(3) libchrysalis 0.0.1
%
% 2022


# NAME

`C_UNLIKELY` - hints predicate as unlikely to be true


# SYNOPSIS

```
#include "libchrysalis/api.h"

#define C_UNLIKELY(_P_)
```


# DESCRIPTION

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
 

# RETURN VALUE

The Boolean value which the predicate `_P_` evaluates to is returned.


# FILES

*/usr/local/src/libchrysalis/ext.h*
: Definition of `C_UNLIKELY` macro.

*/usr/local/include/libchrysalis/ext.h*
: Symbolic link to */usr/local/src/libchrysalis/include/ext.h*; required by
client code to correctly resolve `#include <libchrysalis/api.h>`.

*/usr/local/src/libchrysalis/doc/man/C_UNLIKELY.3.md*
: Markdown documentation in man layout.

*/usr/local/man/man3/libchrysalis:C_UNLIKELY.3.gz*
: Man page documentation.


# EXAMPLES

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


# CONFORMING TO

C99, C11, GCC, Clang.


# NOTES

- This macro is inspired by the `likely()` macro in the Linux kernel
  [@kernel-newbies:likely-unlikely].
- Marking a predicate as likely with `C_LIKELY()` when it is not so will
  have the contrary effect of degrading performance.


# COPYRIGHT

Copyright &copy; 2022 Abhishek Chakravarti `<abhishek@taranjali.org>`

`libchrysalis` along with its documentation are released under the BSD 2-Clause
License. See **libchrysalis:license(7)** for the full license text.


# SEE ALSO

**libchrysalis:C_LIKELY(3)**


# COLOPHON

This page is part of release 0.0.1 of the `libchrysalis` project. The latest
version of this project can be found at
[GitHub](https://github.com/achakravarti/libchrysalis).

