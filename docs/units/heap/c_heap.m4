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

The `c_heap` abstract data type represents a buffer in the heap memory. It is
the primary data type of the heap interface, and is manipulated by all functions
of the interface. Although the `c_heap` type semantically functions as `void *`,
it has been declared as a type definition of `void`; this is so that it is
necessary to explicitly declare `c_heap` as a pointer, which helps improve
readability.

Although the `c_heap` type includes additional metadata, this is not transparent
to the client code. As a consequence, a `c_heap` pointer can be used in *any* C
function that expects a dynamically allocated buffer such as that returned by
*malloc*.

The metadata of the `c_heap` type allows it to provide the following desirable
features:

  1. Reporting the exact allocation size requested,
  2. Shallow copying by keeping track of reference counts, and
  3. Providing an abstract interface that can have different implementations by
     overriding the method v-table.


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

Internally, the `c_heap` type is manipulated as an array of `size_t` blocks
partitioned into a head and body section, as shown in the illustration below.

```
<--             HEAD              --><--              BODY                -->
-----------------------------------------------------------------------------
|  V-TABLE  | DATA SIZE | REF COUNT |                 DATA                  |
-----------------------------------------------------------------------------
<--  [-3] --><-- [-2] --><-- [-1] --><--             [0..n]               -->
```

The head section contains metadata that is padded in front of the body section
containing the actual data. There are three metadata items stored in the head
section, each item being one `size_t` block. The outermost item is a pointer to
the `c_heap` method v-table, followed by the allocated size of the body, and
then the reference count.

As illustrated above, the body section starts at index 0 and continues until
index *n*, which is allocated size requested by the client code. A `c_heap`
pointer points to the 0 index; hence, it can be used transparently just like any
other heap memory buffer returned by *malloc* and friends.

The head section starts at index -3, which points to the v-table pointer,
followed by the data size and reference count cells. These cells need to be
manipulated only if creating a custom implementation for the `c_heap` abstract
interface.


__COPYRIGHT__


__SEEALSO__(<<<c_heap>>>)

__SWITCHMX__(
<<<
**libchrysalis:heap(7)**
**libchrysalis:c_heap_new(3)**,
**libchrysalis:c_heap_copy(3)**,
**libchrysalis:c_heap_clone(3)**,
**libchrysalis:c_heap_free(3)**,
**libchrysalis:c_heap_sz(3)**,
**libchrysalis:c_heap_refc(3)**
**libchrysalis:c_heap_aligned(3)**
**libchrysalis:c_heap_str(3)**
**libchrysalis:c_heap_vtable_(3)**,
**libchrysalis:C_HEAP_METASZ_(3)**,
**libchrysalis:c_heap_head_(3)**
**libchrysalis:c_heap_vtable_(3)**
**libchrysalis:c_heap_vtable_set_(3)**
**libchrysalis:c_heap_sz_set_(3)**
**libchrysalis:c_heap_refc_set_(3)**
**libchrysalis:c_heap_refc_cast_(3)**
>>>,
<<<TODO>>>)


__COLOPHON__


__CITATIONS__
