
#ifndef LIBCHRYSALIS_INCLUDE_HEAP_H_INCLUDED__
#define LIBCHRYSALIS_INCLUDE_HEAP_H_INCLUDED__

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


enum c_cmp { C_CMP_LT = -1, C_CMP_EQ, C_CMP_GT };


/*
 * c_heap - dynamic memory buffer
 * Ref:  libchrysalis/docs/man/c_heap.3.md
 */
typedef void c_heap;


/*
 * c_heap_copy - create shallow copy of heap buffer
 * Ref: libchrysalis/docs/man/c_heap_copy.3.md
 */
extern c_heap *
c_heap_copy(const c_heap *);


/*
 * c_heap_clone - create deep copy of heap buffer
 * Ref: libchrysalis/docs/man/c_heap_clone.3.md
 */
extern c_heap *
c_heap_clone(const c_heap *);


/*
 * c_heap_clone - clone heap buffer aligned to byte offset
 * Ref: libchrysalis/docs/man/c_heap_clone.3.md
 */
extern c_heap *
c_heap_clone_aligned(const c_heap *, size_t);


/*
 * c_heap_void - release heap memory buffer
 * Ref: libchrysalis/docs/man/c_heap_free.3.md
 */
extern void
c_heap_free(c_heap **);


/*
 * c_heap_void - compare two heap buffers
 * Ref: libchrysalis/docs/man/c_heap_cmp.3.md
 */
extern enum c_cmp
c_heap_cmp(const c_heap *, c_heap *);


/*
 * c_heap_sz - get allocated size of heap buffer
 * Ref: libchrysalis/docs/man/c_heap_sz.3.md
 */
extern size_t
c_heap_sz(const c_heap *);


/*
 * c_heap_sz_total - get total size of heap buffer
 * Ref: libchrysalis/docs/man/c_heap_sz.3.md
 */
extern size_t
c_heap_sz_total(const c_heap *);


/*
 * c_heap_sz_refc - get reference count of heap buffer
 * Ref: libchrysalis/docs/man/c_heap_sz.3.md
 */
extern size_t
c_heap_refc(const c_heap *);


/*
 * c_heap_sz_aligned - check alignment of heap buffer
 * Ref: libchrysalis/docs/man/c_heap_aligned.3.md
 */
extern bool
c_heap_aligned(const c_heap *, size_t);


/*
 * c_heap_resize - resize heap buffer
 * Ref: libchrysalis/docs/man/c_heap_resize.3.md
 */
extern void
c_heap_resize(c_heap **, size_t);


/*
 * c_heap_resize_aligned - resize heap buffer aligned to byte offset
 * Ref: libchrysalis/docs/man/c_heap_resize.3.md
 */
extern void
c_heap_resize_aligned(c_heap **, size_t, size_t);


/*
 * c_heap_str - get string representation of heap buffer
 * Ref: libchrysalis/docs/man/c_heap_resize.3.md
 */
extern const char *
c_heap_str(const c_heap *);




/*
 * c_heap_freecbk - callback to release heap buffer
 * Ref: libchrysalis/docs/man/c_heap_freecbk.3.md
 */
typedef void (c_heap_freecbk)(c_heap *);


/*
 * c_heap_vtable_ - v-table for heap interface
 * Ref: libchrysalis/docs/man/c_heap_vtable_.3.md
 */
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


/*
 * c_heap_head_ - gets head of heap buffer
 * Ref: libchrysalis/docs/man/c_heap_head_.3.md
 */
extern size_t *
c_heap_head_(const c_heap *);


/*
 * c_heap_vtable_ - gets v-table of heap buffer
 * Ref: libchrysalis/docs/man/c_heap_vtable_.3.md
 */
extern const struct c_heap_vtable_ *
c_heap_vtable_(const c_heap *);


/*
 * c_heap_vtable_set_ - sets v-table of heap buffer
 * Ref: libchrysalis/docs/man/c_heap_vtable_.3.md
 */
extern void
c_heap_vtable_set_(c_heap *, const struct c_heap_vtable_ *);


/*
 * c_heap_sz_set_ - sets size of heap buffer
 * Ref: libchrysalis/docs/man/c_heap_sz.3.md
 */
extern void
c_heap_sz_set_(c_heap *, size_t);


/*
 * c_heap_refc_set_ - sets reference count of heap buffer
 * Ref: libchrysalis/docs/man/c_heap_refc.3.md
 */
extern void
c_heap_refc_set_(c_heap *, size_t);


/*
 * c_heap_std_new - allocate new heap buffer using stdlib
 * Ref: libchrysalis/docs/c_heap_std.3.md
 */
c_heap *
c_heap_std_new(size_t, size_t);


/*
 * c_heap_std_new_freecbk - stdlib allocator with free callback
 * Ref: libchrysalis/docs/c_heap_std.3.md
 */
c_heap *
c_heap_std_new_freecbk(size_t, size_t, c_heap_freecbk *);


/*
 * c_heap_std_new_aligned - stdlib allocator with alignment
 * Ref: libchrysalis/docs/c_heap_std.3.md
 */
c_heap *
c_heap_std_new_aligned(size_t, size_t, size_t);


/*
 * c_heap_std_new_aligned_freecbk - stdlib allocator with alignment and free
 *                                  callback
 * Ref: libchrysalis/docs/c_heap_std.3.md
 */
c_heap *
c_heap_std_new_aligned_freecbk(size_t, size_t, size_t, c_heap_freecbk *);



#ifdef __cplusplus
}
#endif

#endif  /* !LIBCHRYSALIS_INCLUDE_HEAP_H_INCLUDED__ */

