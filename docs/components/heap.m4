include(`macros.m4')


ifdef(<<<MAN>>>,
<<<% LIBCHRYSALIS:HEAP(7) libchrysalis 0.0.1
%
% 2022>>>)


__NAME__(<<<Heap>>>)

Heap Component - heap memory management


__SYNOPSIS__(<<<Heap>>>)

```
#include <libchrysalis/api.h>

typedef void c_heap;
typedef void (c_heap_free_cbk)(c_heap *);
struct c_heap_vtable_;

#define C_HEAP_METASZ_ (sizeof(size_t) * 3)

c_heap *c_heap_copy(const c_heap *);
c_heap *c_heap_clone(const c_heap *);
c_heap * c_heap_clone_aligned(const c_heap *, size_t);
void c_heap_free(c_heap **);
enum c_cmp c_heap_cmp(const c_heap *, c_heap *);
size_t c_heap_sz(const c_heap *);
size_t c_heap_sz_total(const c_heap *);
size_t c_heap_refc(const c_heap *);
bool c_heap_aligned(const c_heap *, size_t);
void c_heap_resize(c_heap **, size_t);
void c_heap_resize_aligned(c_heap **, size_t, size_t);
const char *c_heap_str(const c_heap *);

size_t *c_heap_head_(const c_heap *);
const struct c_heap_vtable_ *c_heap_vtable_(const c_heap *);
void c_heap_vtable_set_(void *, const struct c_heap_vtable_ *);
void c_heap_sz_set_(void *, size_t);
void c_heap_refc_set_(void *, size_t);
c_heap *c_heap_cast_(void *);
c_heap *c_heap_new(size_t, size_t);
c_heap *c_heap_new_aligned(size_t, size_t, size_t);
```


__DESCRIPTION__(<<<Heap>>>)

The *Heap* component of *libchrysalis* provides an interface to manage heap
memory. The Heap component is adopts the bridge pattern, providing a uniform
abstract interface for client code. Different implementations of the abstract
interface (referred to as *adapters*) can be selected at runtime as required. As
of now, *libchrysalis* provides only an adapter for the standard library
*malloc*, but there are plans in future to support both *Jemalloc* and a custom
memory pool.

The Heap component also provides an interface for client code to implement its
own adapter if required. This can be done by setting the v-table which is used
by the heap abstract interface. See **libchrysalis:c_heap_vtable_(3)** and
**libchrysalis:c_heap_vtable_set_(3)** for more details on how to do so.


__FILES__(<<<Heap>>>)

*/usr/local/src/libchrysalis/include/heap.h*
: Heap interface declaration.

*/usr/local/include/libchrysalis/heap.h*
: Symbolic link to */usr/local/src/libchrysalis/include/heap.h*; required by
client code to correctly resolve `#include <libchrysalis/api.h>`.

*/usr/local/src/libchrysalis/src/heap.c*
: Heap abstract interface definition.

*/usr/local/src/libchrysalis/src/heap.c*
: Heap abstract interface definition.

*/usr/local/src/libchrysalis/src/heap-std.c*
: Definition of standard malloc adapter.

*/usr/local/share/doc/libchrysalis/components/heap.m4*
: *m4* template for documentation.

*/usr/local/share/man/man7/libchrysalis:heap.7.gz*
__SWITCHMX__(
<<<: Man page documentation (this page).>>>,
<<<: Man page documentation.>>>)


__CONFORMINGTO__(<<<Heap>>>)

GCC 11.2, Clang 13.0.1.


__COPYRIGHT__


__SEEALSO__(<<<Heap>>>)

__SWITCHMX__(
<<<
**libchrysalis:c_heap(3)**,
**libchrysalis:c_heap_free_cbk(3)**,
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
