include(`macros.m4')


ifdef(<<<MAN>>>,
<<<% LIBCHRYSALIS:EXTENSIONS(7) libchrysalis 0.0.1
%
% 2022>>>)


__NAME__(<<<Extensions>>>)

Extensions Component - commonly used compiler extensions


__SYNOPSIS__(<<<Extensions>>>)

```
#include <libchrysalis/api.h>
 
#define C_AUTO
#define C_COLD
#define C_HOT
#define C_IMMUTABLE
#define C_LIKELY(_P_)
#define C_PSAFE
#define C_RSAFE
#define C_STABLE
#define C_UNLIKELY(_P_)
```


__DESCRIPTION__(<<<Extensions>>>)

The *Extensions* component of `libchrysalis` defines the compiler extensions
that are often useful for optimising code. Optimisation can be both in terms of
performance and desirable features which are otherwise not availabe in the C11
standard.

These extensions are defined as macros relying on non-standard features provided
by the GCC and Clang compilers, and as such are only available for use when
these two compilers are used. On other compilers, these extension macros degrade
safely to a no-op with an appropriate warning message. If you don't want these
warning messages to emitted, then define the symbolic constant
`C_SUPPRESS_EXTENSION_WARNINGS` at compile time.


__FILES__(<<<Extensions>>>)

*/usr/local/src/libchrysalis/include/ext.h*
: Extension macro definitions.

*/usr/local/include/libchrysalis/ext.h*
: Symbolic link to */usr/local/src/libchrysalis/include/ext.h*; required by
client code to correctly resolve `#include <libchrysalis/api.h>`.

*/usr/local/share/doc/libchrysalis/components/ext.m4*
: *m4* template for documentation.

*/usr/local/share/man/man7/libchrysalis:extensions.7.gz*
__SWITCHMX__(
<<<: Man page documentation (this page).>>>,
<<<: Man page documentation.>>>)


__CONFORMINGTO__(<<<Extensions>>>)

GCC 11.2, Clang 13.0.1.


__COPYRIGHT__


__SEEALSO__(<<<C_IMMUTABLE>>>)

__SWITCHMX__(
<<<**libchrysalis:C_AUTO(3)**, **libchrysalis:C_COLD(3)**,
**libchrysalis:C_HOT(3)**, **libchrysalis:C_IMMUTABLE(3)**,
**libchrysalis:C_LIKELY(3)**, **libchrysalis:C_PSAFE(3)**,
**libchrysalis:C_RSAFE(3)**, **libchrysalis:C_STABLE(3)**,
**libchrysalis:C_UNLIKELY(3)**>>,
<<<TODO>>>)


__COLOPHON__

