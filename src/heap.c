#include "../include/ext.h"
#include "../include/heap.h"
#include <stdint.h>
#include <stdlib.h>


c_heap *
c_heap_copy(const c_heap *ctx)
{
        // TODO
        (void) ctx;
        return NULL;
}


c_heap *
c_heap_clone(const c_heap *ctx)
{
        // TODO
        (void) ctx;
        return NULL;
}


c_heap *
c_heap_clone_aligned(const c_heap *ctx, size_t align)
{
        // TODO
        (void) ctx;
        (void) align;
        return NULL;
}


void
c_heap_free(c_heap **ctx)
{
        (void) ctx;
}


enum c_cmp
c_heap_cmp(const c_heap *ctx, c_heap *cmp)
{
        // TODO
        (void) ctx;
        (void) cmp;
        return 0;
}


size_t
c_heap_sz(const c_heap *ctx)
{
        return ((size_t *) ctx)[-2];
}


size_t
c_heap_sz_total(const c_heap *ctx)
{
        // TODO
        (void) ctx;
        return 0;
}


size_t
c_heap_refc(const c_heap *ctx)
{
        return ((size_t *) ctx)[-1];
}


bool
c_heap_aligned(const c_heap *ctx, size_t align)
{
        // TODO
        (void) ctx;
        (void) align;
        return false;
}


void
c_heap_resize(c_heap **ctx, size_t newsz)
{
        // TODO
        (void) ctx;
        (void) newsz;
}


void
c_heap_resize_aligned(c_heap **ctx, size_t newsz, size_t align)
{
        // TODO
        (void) ctx;
        (void) newsz;
        (void) align;
}


const char *
c_heap_str(const c_heap *ctx)
{
        // TODO
        (void) ctx;
        return "";
}


size_t *
c_heap_head_(const c_heap *ctx)
{
        return &((size_t *) ctx)[-3];
}


const struct c_heap_vtable_ *
c_heap_vtable_(const c_heap *ctx)
{
        return (const struct c_heap_vtable_ *) ((size_t *) ctx)[-3];
}


void
c_heap_vtable_set_(void *ctx, const struct c_heap_vtable_ *vt)
{
        ((size_t *) ctx)[0] = (uintptr_t) vt;
}


void
c_heap_sz_set_(void *ctx, size_t sz)
{
        ((size_t *) ctx)[1] = sz;
}


void
c_heap_refc_set_(void *ctx, size_t refc)
{
        ((size_t *) ctx)[2] = refc;
}


c_heap *
c_heap_cast_(void *ctx)
{
        return (c_heap *) &(((size_t *) ctx)[3]);
}


c_heap *
c_heap_std_new(size_t sz, size_t n)
{
        size_t tsz = (sz * n) + C_HEAP_METASZ_;
        size_t *ctx = calloc(1, tsz);

        c_heap_sz_set_(ctx, sz * n);
        c_heap_refc_set_(ctx, 1);
        c_heap_vtable_set_(ctx, NULL);

        return c_heap_cast_(ctx);
}

