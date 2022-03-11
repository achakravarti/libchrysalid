#include "../include/ext.h"
#include "../include/heap.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


c_heap *
c_heap_copy(const c_heap *ctx)
{
        c_heap *cp = (c_heap *) ctx;
        ((size_t *) cp)[-1]++;

        return cp;

}


c_heap *
c_heap_clone(const c_heap *ctx)
{
        return c_heap_vtable_(ctx)->clone(ctx);
}


c_heap *
c_heap_clone_aligned(const c_heap *ctx, size_t align)
{
        return c_heap_vtable_(ctx)->clone_aligned(ctx, align);
}


void
c_heap_free(c_heap **ctx)
{
        size_t *h;

        if (C_LIKELY (ctx && (h = (size_t *) *ctx))) {
                if (!(--h[-1])) {
                        const struct c_heap_vtable_ *vt = c_heap_vtable_(h);
                        vt->free_cbk(h);
                        vt->free(&h[-3]);
                }

                *ctx = NULL;
        }
}


enum c_cmp
c_heap_cmp(const c_heap *ctx, c_heap *cmp)
{
        return c_heap_vtable_(ctx)->cmp(ctx, cmp);
}


size_t
c_heap_sz(const c_heap *ctx)
{
        return ((size_t *) ctx)[-2];
}


size_t
c_heap_sz_total(const c_heap *ctx)
{
        return c_heap_vtable_(ctx)->sz_total(ctx);
}


size_t
c_heap_refc(const c_heap *ctx)
{
        return ((size_t *) ctx)[-1];
}


bool
c_heap_aligned(const c_heap *ctx, size_t align)
{
        return !((uintptr_t) c_heap_head_(ctx) & (align -1));
}


void
c_heap_resize(c_heap **ctx, size_t newsz)
{
        c_heap_vtable_(*ctx)->resize(ctx, newsz);
}


void
c_heap_resize_aligned(c_heap **ctx, size_t newsz, size_t align)
{
        c_heap_vtable_(*ctx)->resize_aligned(ctx, newsz, align);
}


const char *
c_heap_str(const c_heap *ctx)
{
        return c_heap_vtable_(ctx)->str(ctx);
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


static c_heap *
clone(const c_heap *ctx)
{
        size_t sz = c_heap_sz(ctx);
        c_heap *cp = c_heap_std_new(sz, 1);
        memcpy(cp, ctx, sz);
        
        return cp;
}


static const struct c_heap_vtable_ g_vt = {
        .clone          = &clone,
        .clone_aligned  = NULL,
        .free           = free,
        .free_cbk       = NULL,
        .cmp            = NULL,
        .sz_total       = NULL,
        .resize         = NULL,
        .resize_aligned = NULL,
        .str            = NULL
};


c_heap *
c_heap_std_new(size_t sz, size_t n)
{
        size_t tsz = (sz * n) + C_HEAP_METASZ_;
        size_t *ctx = calloc(1, tsz);

        c_heap_sz_set_(ctx, sz * n);
        c_heap_refc_set_(ctx, 1);
        c_heap_vtable_set_(ctx, &g_vt);

        return c_heap_cast_(ctx);
}

