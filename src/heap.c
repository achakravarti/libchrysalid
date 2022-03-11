#include "../include/ext.h"
#include "../include/heap.h"
#include <stdint.h>


c_heap *
c_heap_copy(const c_heap *ctx)
{
        // TODO
        return NULL;
}


c_heap *
c_heap_clone(const c_heap *ctx)
{
        // TODO
        return NULL;
}


c_heap *
c_heap_clone_aligned(const c_heap *ctx, size_t align)
{
        // TODO
        return NULL;
}


void
c_heap_free(c_heap **ctx)
{
}


enum c_cmp
c_heap_cmp(const c_heap *ctx, c_heap *cmp)
{
        // TODO
        return 0;
}


size_t
c_heap_sz(const c_heap *ctx)
{
        // TODO
        return 0;
}


size_t
c_heap_sz_total(const c_heap *ctx)
{
        // TODO
        return 0;
}


size_t
c_heap_refc(const c_heap *ctx)
{
        // TODO
        return 0;
}


bool
c_heap_aligned(const c_heap *ctx, size_t align)
{
        // TODO
        return false;
}


void
c_heap_resize(c_heap **ctx, size_t newsz)
{
}


void
c_heap_resize_aligned(c_heap **ctx, size_t newsz, size_t align)
{
}


const char *
c_heap_str(const c_heap *ctx)
{
        // TODO
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
c_heap_vtable_set_(c_heap *ctx, const struct c_heap_vtable_ *vt)
{
        ((size_t *) ctx)[-3] = (uintptr_t) vt;
}


void
c_heap_sz_set_(c_heap *ctx, size_t sz)
{
        ((size_t *) ctx)[-2] = sz;
}


void
c_heap_refc_set_(c_heap *ctx, size_t refc)
{
        ((size_t *) ctx)[-1] = refc;
}

