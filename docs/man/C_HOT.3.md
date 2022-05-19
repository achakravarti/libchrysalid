% LIBCHRYSALID:C_HOT(3) libchrysalid 0.0.1
% 
% 2022
 

# NAME

`C_HOT` - hints a function as hot


# SYNOPSIS

```
#include "libchrysalid/api.h"

#define C_HOT
```


# DESCRIPTION

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


# FILES

*/usr/local/src/libchrysalid/include/ext.h*
: Definition of `C_HOT` macro.

*/usr/local/include/libchrysalid/ext.h*
: Symbolic link to */usr/local/src/libchrysalid/include/ext.h*; required by
client code to correctly resolve `#include <libchrysalid/api.h>`.

*/usr/local/src/libchrysalid/doc/man/C_HOT.3.md*
: Markdown documentation in man layout.

*/usr/local/man/man3/libchrysalid:C_HOT.3.gz*
: Man page documentation.
 

# EXAMPLES

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


# CONFORMING TO

C99, C11, GCC, Clang.



# NOTES

- `C_HOT` is ignored by GCC if the `-fprofile-use` flag is used during
  compilation [@gcc:function-attributes].
- Although Clang recognises the `__attribute__((hot))` decorator, it drops it
  silently; however, there is a proposal to implement this
  [@llvm-dev:hot-cold-attributes].


# COPYRIGHT

Copyright &copy; 2022 Abhishek Chakravarti `<abhishek@taranjali.org>`

`libchrysalid` along with its documentation are released under the BSD 2-Clause
License. See **libchrysalid:license(7)** for the full license text.


# SEE ALSO

**libchrysalid:extensions(7)**, **libchrysalid:C_COLD(3)**


# COLOPHON

This page is part of release 0.0.1 of the `libchrysalid` project. The latest
version of this project can be found at
[GitHub](https://github.com/achakravarti/libchrysalid).

