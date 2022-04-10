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
**libchrysalis:C_UNLIKELY(3)**>>>,
<<<TODO>>>)


__COLOPHON__
