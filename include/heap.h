
#ifndef LIBCHRYSALIS_INCLUDE_HEAP_H_INCLUDED__
#define LIBCHRYSALIS_INCLUDE_HEAP_H_INCLUDED__

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


enum c_cmp { C_CMP_LT = -1, C_CMP_EQ, C_CMP_GT };


typedef void c_heap;


extern c_heap *
c_heap_copy(const c_heap *);


extern c_heap *
c_heap_clone(const c_heap *);


extern c_heap *
c_heap_clone_aligned(const c_heap *, size_t);


extern void
c_heap_free(c_heap **);


extern enum c_cmp
c_heap_cmp(const c_heap *, c_heap *);


extern size_t
c_heap_sz(const c_heap *);


extern size_t
c_heap_sz_total(const c_heap *);


extern size_t
c_heap_refc(const c_heap *);


extern bool
c_heap_aligned(const c_heap *, size_t);


extern void
c_heap_resize(c_heap **, size_t);


extern void
c_heap_resize_aligned(c_heap **, size_t, size_t);


extern const char *
str(const c_heap *);




typedef void (c_heap_freecbk)(c_heap *);


struct c_heap_vtable_ {
        //c_heap          *(*copy)(const c_heap *);
        c_heap          *(*clone)(const c_heap *);
        c_heap          *(*clone_aligned)(const c_heap *, size_t);
        c_heap_freecbk *free_cbk;
        enum c_cmp       (*cmp)(const c_heap *, c_heap *);
        //size_t           (*sz)(const c_heap *);
        size_t           (*sz_total)(const c_heap *);
        //size_t           (*refc)(const c_heap *);
        //bool             (*aligned)(const c_heap *, size_t);
        void             (*resize)(c_heap **, size_t);
        void             (*resize_aligned)(c_heap **, size_t, size_t);
        const char      *(*str)(const c_heap *);
};


extern size_t *
c_heap_head_(const c_heap *);


extern const struct c_heap_vtable_ *
c_heap_vtable_(const c_heap *);

extern void
c_heap_vtable_set_(c_heap *, const struct c_heap_vtable_ *);


extern void
c_heap_sz_set_(c_heap *, size_t);

extern void
c_heap_refc_set_(c_heap *, size_t);


c_heap *
c_heap_std_new(size_t, size_t);

c_heap *
c_heap_std_new_freecbk(size_t, size_t, c_heap_freecbk *);

c_heap *
c_heap_std_new_aligned(size_t, size_t, size_t);

c_heap *
c_heap_std_new_aligned_freecbk(size_t, size_t, size_t, c_heap_freecbk *);



#ifdef __cplusplus
}
#endif

#endif  /* !LIBCHRYSALIS_INCLUDE_HEAP_H_INCLUDED__ */

