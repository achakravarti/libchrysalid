% LIBCHRYSALIS:C_COLD(3) libchrysalis 0.0.1
%
% 2022
 

# NAME

`C_COLD` - hints a function as cold


# SYNOPSIS

```
#include "libchrysalis/api.h"

#define C_COLD
```


# DESCRIPTION

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


# FILES

*/usr/local/src/libchrysalis/include/base/ext.h*
: Definition of `C_COLD` macro.

*/usr/local/include/libchrysalis/base/ext.h*
: Symbolic link to */usr/local/src/libchrysalis/include/base/ext.h*; required by
client code to correctly resolve `#include <libchrysalis/api.h>`.

*/usr/local/src/libchrysalis/doc/base/c_cold.md*
: Markdown documentation in man layout.

*/usr/local/man/man3/libchrysalis:C_HOT.3.gz*
: Man page documentation (this page).

 
# EXAMPLES

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


# CONFORMING TO

C99, C11, GCC, Clang.

 
# NOTES

- `C_COLD` is ignored by GCC if the `-fprofile-use` flag is used during
  compilation [@gcc:function-attributes].
- Unlike the case of `C_HOT`, Clang does _not_ silently drop this macro
  [@llvm-dev:hot-cold-attributes].


# COPYRIGHT

Copyright &copy; 2022 Abhishek Chakravarti `<abhishek@taranjali.org>`

`libchrysalis` along with its documentation are released under the BSD 2-Clause
License. See **libchrysalis:license(7)** for the full license text.


# SEE ALSO

**libchrysalis:C_COLD(3)**


# COLOPHON

This page is part of release 0.0.1 of the `libchrysalis` project. The latest
version of this project can be found at
[GitHub](https://github.com/achakravarti/libchrysalis).

