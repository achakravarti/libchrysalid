#include "../include/ext.h"
#include "../include/heap.h"
#include <stddef.h>
#include <string.h>


#ifdef __FreeBSD__
#       include <malloc_np.h>
#elif defined __APPLE__
#       include <malloc/malloc.h>
#else
#       include <malloc.h>
#endif




static c_heap *
clone(const c_heap *ctx);


static c_heap *
clone_aligned(const c_heap *ctx, size_t align);


static enum c_cmp
cmp(const c_heap *ctx, const c_heap *cmp);


static size_t
sz_total(const c_heap *ctx);


static void
resize(c_heap **ctx, size_t newsz);


static void
resize_aligned(c_heap **ctx, size_t newsz, size_t align);


static const char *
str(const c_heap *ctx);




static const struct c_heap_vtable_ g_vt = {
        .clone          = &clone,
        .clone_aligned  = &clone_aligned,
        .free           = &free,
        .cmp            = &cmp,
        .sz_total       = &sz_total,
        .resize         = &resize,
        .resize_aligned = &resize_aligned,
        .str            = &str
};




c_heap *
clone(const c_heap *ctx)
{
        size_t sz = c_heap_sz(ctx);
        c_heap *cp = c_heap_std_new(sz, 1);
        memcpy(cp, ctx, sz);
        
        return cp;
}


c_heap *
clone_aligned(const c_heap *ctx, size_t align)
{
        size_t sz = c_heap_sz(ctx);
        c_heap *cp = c_heap_std_new_aligned(sz, 1, align);
        memcpy(cp, ctx, sz);

        return cp;
}


enum c_cmp
cmp(const c_heap *ctx, const c_heap *cmp)
{
        return ctx == cmp ? C_CMP_EQ : memcmp(ctx, cmp, c_heap_sz(ctx));
}


size_t
sz_total(const c_heap *ctx)
{
#ifdef __APPLE__
        return malloc_size(c_heap_sz(ctx));
#else
        return malloc_usable_size(c_heap_head_(ctx));
#endif
}


void
resize(c_heap **ctx, size_t newsz)
{
        c_heap *h = *ctx;
        size_t oldsz = c_heap_sz(h);

        c_heap *cp = c_heap_std_new(newsz, 1);
        memcpy(cp, h, newsz < oldsz ? newsz : oldsz);

        c_heap_free(ctx);
        *ctx = cp;
}


void
resize_aligned(c_heap **ctx, size_t newsz, size_t align)
{
        c_heap *h = *ctx;
        size_t oldsz = c_heap_sz(h);

        c_heap *cp = c_heap_std_new_aligned(newsz, 1, align);
        memcpy(cp, h, newsz < oldsz ? newsz : oldsz);

        c_heap_free(ctx);
        *ctx = cp;
}


const char *
str(const c_heap *ctx)
{
        static char bfr[1024];
        sprintf("address = %p, data sz = %lu, total data size = %lu,"
                        " refc = %lu", (void *) c_heap_head_(ctx),
                        c_heap_sz(ctx), c_heap_sz_total(ctx), 
                        c_heap_refc(ctx));

        return bfr;
}




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

