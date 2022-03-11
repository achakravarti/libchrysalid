
#ifndef LIBCHRYSALIS_INCLUDE_HEAP_H_INCLUDED__
#define LIBCHRYSALIS_INCLUDE_HEAP_H_INCLUDED__

#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif


enum c_cmp { C_CMP_LT = -1, C_CMP_EQ, C_CMP_GT };

typedef struct c_heap c_heap;


struct c_heap_vtable_ {
        c_heap          *(*copy)(const c_heap *);
        c_heap          *(*clone)(const c_heap *);
        c_heap          *(*clone_aligned)(const c_heap *, size_t);
        void             (*free)(c_heap **);
        enum c_cmp       (*cmp)(const c_heap *, c_heap *);
        size_t           (*sz)(const c_heap *);
        size_t           (*sz_total)(const c_heap *);
        size_t           (*refc)(const c_heap *);
        bool             (*aligned)(const c_heap *, size_t);
        void             (*resize)(c_heap **, size_t);
        void             (*resize_aligned)(c_heap **, size_t, size_t);
        const char      *(*str)(const c_heap *);
};


#ifdef __cplusplus
}
#endif

#endif  /* !LIBCHRYSALIS_INCLUDE_HEAP_H_INCLUDED__ */

