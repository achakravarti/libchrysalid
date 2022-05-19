include(`macros.m4')


ifdef(<<<MAN>>>,
<<<
% LIBCHRYSALID:C_AUTO(3) libchrysalid 0.0.1
%
% 2022
>>>)


__NAME__(<<<C_AUTO>>>)

`C_AUTO` - marks an automatic heap pointer


__SYNOPSIS__(<<<C_AUTO>>>)

```
#include "libchrysalid/api.h"

#define C_AUTO(_T_)
```


__DESCRIPTION__(<<<C_AUTO>>>)

The `C_AUTO` macro is used to declare a pointer variable of a type `_T_` that is
automatically released from the heap when it goes out of scope without having to
explicitly invoke its destructor function. Type `_T_` must be a typedef'd type,
and the pointer variable must have automatic storage with function scope.

Furthermore, a suitable destructor function for type `_T_` is available in the
first place; this descructor is implicitly invoked by `C_AUTO` whenever the
variable it marks goes out of scope.

The destructor function must have the name of type `_T_` suffixed with `_free`.
Additionally, this destructor function must return void and have only one
parameter, which is a pointer to pointer of type `_T_`. So, if you would like to
apply the `C_AUTO` macro to a pointer of a hypothetical type `foo`, you would
also need to define a destructor function with the prototype `void foo_free(foo
**)` See __SWITCHMX__(<<<**EXAMPLES**>>>, <<<{sec:C_AUTO:examples}>>>) below for
a concrete example.


__FILES__(<<<C_AUTO>>>)

*/usr/local/src/libchrysalid/ext.h*
: Definition of `C_AUTO` macro.

*/usr/local/include/libchrysalid/ext.h*
: Symbolic link to */usr/local/src/libchrysalid/include/ext.h*; required by
client code to correctly resolve `#include <libchrysalid/api.h>`.

*/usr/local/share/doc/libchrysalid/units/ext/C_AUTO.m4*
: *m4* template for documentation.

*/usr/local/share/man/man3/libchrysalid:C_AUTO.3.gz*
__SWITCHMX__(
<<<: Man page documentation (this page).>>>,
<<<: Man page documentation.>>>)


__EXAMPLES__(<<<C_AUTO>>>)

```
#include <stdlib.h>


/* Declare a typedef'd point struct; C_AUTO works only with typedef'd types */
typedef struct {
	int x;
	int y;
} point;


/* Define destructor function to be called by C_AUTO */
void point_free(point **pt)
{
	if (pt && *pt) {
		free(*pt);
		*pt = NULL;
	}
}


int main(void)
{
	/* Declare pt to be cleaned up automatically */
	C_AUTO(point) *pt = malloc(sizeof *pt);
	
	pt->x = 2;
	pt->y = 3;

	/* point_free(&pt) is called implicitly here */
	return 0;
}

```


__CONFORMINGTO__(<<<C_AUTO>>>)

GCC 11.2, Clang 13.0.1.


__NOTES__(<<<C_AUTO>>>)

This macro uses the non-standard `__attribute__((cleanup))` decorator
[@gcc:variable-attributes], and is available for both GCC and Clang. On other
compilers, the default behaviour of this macro is to degrade safely to a no-op
with a suitable warning message. If you don't want this warning message to be
displayed, then define the macro `C_SUPPRESS_EXTENSION_WARNINGS` at compile
time.


__COPYRIGHT__


__SEEALSO__(<<<C_AUTO>>>)

__SWITCHMX__(
<<<**libchrysalid:extensions(7)**, **libchrysalid:C_HEAP(3)**>>>,
<<<Section X.X.X>>>)


__COLOPHON__


__CITATIONS__

