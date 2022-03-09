% LIBCHRYSALIS:EXTENSIONS(7) libchrysalis 0.0.1
%
% 2022


# NAME

`libchrysalis` Extensions - commonly used compiler extensions


# SYNOPSIS

```
#include <libchrysalis/api.h>
 
#define C_PSAFE
#define C_RSAFE
#define C_HOT
#define C_COLD
#define C_STABLE
#define C_IMMUTABLE
#define C_TLOCAL
#define C_AUTO
#define C_LIKELY(_P_)
#define C_UNLIKELY(_P_)
```


# DESCRIPTION

The **Extensions** component is part of the **Base** module of `libchrysalis`.
This component defines the compiler extensions are often useful for optimising
code. Optimisation can be both in terms of performance and desirable features
which are otherwise not availabe in the C standards.

These extensions are defined as macros relying on non-standard features provided
by the GCC and Clang compilers, and as such are only available for use when
these two compilers are used. On other compilers, these extension macros degrade
safely to a no-op with an appropriate warning message. If you don't want these
warning messages to emitted, then define the symbolic constant
`C_SUPPRESS_EXTENSION_WARNINGS` at compile time.


# FILES

*/usr/local/src/libchrysalis/include/base/ext.h*
: Extension macro definitions.

*/usr/local/include/libchrysalis/base/ext.h*
: Symbolic link to */usr/local/src/libchrysalis/include/base/ext.h*; required by
client code to correctly resolve `#include <libchrysalis/api.h>`.

*/usr/local/src/libchrysalis/doc/base/extensions.md*
: Markdown documentation in man layout.

*/usr/local/man/man7/libchrysalis:extensions.7.gz*
: Installed man page documentation (this page).


# CONFORMING TO

C99, C11, GCC, Clang.


# COPYRIGHT

Copyright &copy; 2022 Abhishek Chakravarti `<abhishek@taranjali.org>`

`libchrysalis` along with its documentation are released under the BSD 2-Clause
License. See **libchrysalis:license(7)** for the full license text.


# SEE ALSO:

**libchrysalis:C_PSAFE(3)**, **libchrysalis:C_RSAFE(3)**,
**libchrysalis:C_HOT(3)**, **libchrysalis:C_COLD(3)**,
**libchrysalis:C_STABLE(3)**, **libchrysalis:C_IMMUTABLE(3)**,
**libchrysalis:C_TLOCAL(3)**, **libchrysalis:C_AUTO(3)**,
**libchrysalis:C_LIKELY(3)**, **libchrysalis:C_UNLIKELY(3)**


# COLOPHON

This page is part of release 0.0.1 of the `libchrysalis` project. The latest
version of this project can be found at
[GitHub](https://github.com/achakravarti/libchrysalis).

