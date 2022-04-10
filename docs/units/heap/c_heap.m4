include(`macros.m4')


ifdef(<<<MAN>>>,
<<<% LIBCHRYSALIS:C_HEAP(3) libchrysalis 0.0.1
%
% 2022>>>)


__NAME__(<<<c_heap>>>)

`c_heap` - dynamic memory buffer


__SYNOPSIS__(<<<c_heap>>>)

```
#include <libchrysalis/api.h>

typedef void c_heap;
```


__DESCRIPTION__(<<<c_heap>>>)

1. represents a heap memory buffer
2. includes additional metadata on size and reference count
3. primary data type of interface
4. defined as void for readability
5. can be used wherever a void * is required

__FILES__(<<<c_heap>>>)

*/usr/local/src/libchrysalis/include/heap.h*
: Definition of `c_heap` type.

*/usr/local/include/libchrysalis/heap.h*
: Symbolic link to */usr/local/src/libchrysalis/include/heap.h*; required by
client code to correctly resolve `#include <libchrysalis/api.h>`.

*/usr/local/share/doc/libchrysalis/units/heap/c_heap.m4*
: *m4* template for documentation.

*/usr/local/share/man/man3/libchrysalis:c_heap.3.gz*
__SWITCHMX__(
<<<: Man page documentation (this page).>>>,
<<<: Man page documentation.>>>)


__EXAMPLES__(<<<c_heap>>>)

```
TODO
```


__CONFORMINGTO__(<<<c_heap>>>)

GCC 11.2, Clang 13.0.1.


__NOTES__(<<<c_heap>>>)

1. internally cast as size_t *
2. padded in front with three size_t blocks
3. first size_t block (index -3)  holds pointer to vtable
3. first size_t block (index -2)  holds size
4. second size_t block (index -1) holds reference count
4. second size_t block (index 0) beginning of heap body
5. head and body sections


<--             HEAD              --><--              BODY                 -->
--------------------------------------------------------------------------------------
|  V-TABLE  | BODY SIZE | REF COUNT |                DATA                   |
--------------------------------------------------------------------------------------
<--  [-3] --><--  [-2] --><-- [-1] --><--               [0]                 -->


__COPYRIGHT__


__SEEALSO__(<<<c_heap>>>)

__SWITCHMX__(
<<<**libchrysalis:heap(7)**>>>,
<<<TODO>>>)


__COLOPHON__


__CITATIONS__
