/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * libchrysalid/src/heap.c - heap pointer implementation
 * Copyright (c) 2022 Abhishek Chakravarti
 * See libchrysalid:heap(3) for documentation.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * 4. Redistributions of any form whatsoever must retain the following
 *    acknowledgment: 'This product includes software developed by "Montão AB"
 *    (https://montao.github.io/).'
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


/* Libchrysalid dependencies */
#include "../include/ext.h"
#include "../include/hptr.h"

/* Standard library dependencies */
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Extended malloc() related features */
#ifdef __FreeBSD__
#       include <malloc_np.h>
#elif defined __APPLE__
#       include <malloc/malloc.h>
#else
#       include <malloc.h>
#endif


/* Constants */


/*
 * __NAME__
 *      HEAD_INDEX - index of head segment
 *
 * __SYNOPSIS__
 *      #define HEAD_INDEX 0
 *
 * __DESCRIPTION__
 *      The *HEAD_INDEX* symbolic constant represents the index at which the
 *      head segment (relative to itself) starts in a heap pointer instance.
 *      This symbolic constant is used by the implementation of the heap pointer
 *      interface and is **not** part of the interface.
 *
 * __NOTES__
 *      The head segment of a heap pointer instance is located in the first
 *      *uintptr_t* of the instance; hence, relative to itself, it has an index
 *      of **0**.
 */
#define HEAD_INDEX      0


/*
 * __NAME__
 *      HEAD_OFFSET - head segment index offset
 *
 * __SYNOPSIS__
 *      #define REFC_OFFSET 1
 *
 * __DESCRIPTION__
 *      The *HEAD_OFFSET* symbolic constant represents the *uintptr_t* offset of
 *      the head segment from the body of a heap pointer instance. This constant
 *      is used internally by the heap pointer implementation and is **not**
 *      part of the interface.
 *
 * __NOTES__
 *      Since the head segment of a heap pointer instance is one *uintptr_t*
 *      **before** the body segment, the *HEAD_OFFSET* symbolic constant is
 *      defined as **-1**.
 */
#define HEAD_OFFSET     -1


/*
 * __NAME__
 *      HEAD_SZ - size of head segment
 *
 * __SYNOPSIS__
 *      #define HEAD_SZ sizeof (uintptr_t)
 *
 * __DESCRIPTION__
 *      The *HEAD_SZ* symbolic constant represents the size of the head segment
 *      of a heap pointer instance that contains the reference count metadata.
 *      This constant is used internally by the heap pointer implementation and
 *      is **not** part of the interface.
 *
 * __NOTES__
 *      By design, the heap pointer type has the capacity to track *size_t*
 *      number of references. Therefore, one *size_t* is sufficient to hold the
 *      reference counts. Accordingly, the *HEAD_SZ* constant is defined as the
 *      size of *uintptr_t* (which is equivalent to *size_t* but better conveys
 *      its context as a pointer type).
 *
 */
#define HEAD_SZ         sizeof (uintptr_t)


/*
 * __NAME__
 *      BODY_INDEX - index of body segment
 *
 * __SYNOPSIS__
 *      #define BODY_INDEX 1
 *
 * __DESCRIPTION__
 *      The *BODY_INDEX* symbolic constant represents the index of the body
 *      segment (relative to head segment) in a heap pointer instance.  This
 *      symbolic constant is implementation-specific and is **not** part of the
 *      heap pointer interface.
 *
 * __NOTES__
 *      The body segment starts one *uintptr_t* after the head segment of a heap
 *      pointer instance; hence, relative to the head segment, the body segment
 *      has an index of **1**.
 */
#define BODY_INDEX      1




/* Macros  */


/*
 * __NAME__
 *      REFC_INIT() - initialises reference count
 *
 * __SYNOPSIS__
 *      #define REFC_INIT(ctx)
 *
 * __DESCRIPTION__
 *      The *REFC_INIT()* macro initialises the reference count of a new heap
 *      pointer instance *ctx* by setting it to 1. This macro is used internally
 *      by the heap pointer implemnetation and is **not** part of the interface.
 *
 * __NOTES__
 *      The *REFC_INIT()* macro is called by the *cy_hptr_new()* family of
 *      factory functions immediately after allocating a heap pointer instance.
 *      Since heap pointer instances point to the head segment immediately after
 *      allocation, the *REFC_INIT()* operates directly on the head segment of
 *      the heap pointer instance *ctx*.
 */
#define REFC_INIT(ctx)      ctx[HEAD_INDEX] = 1


/*
 * __NAME__
 *      REFC_CURRENT() - gets current reference count
 *
 * __SYNOPSIS__
 *      #define REFC_CURRENT(ctx)
 *
 * __DESCRIPTION__
 *      The *REFC_CURRENT()* macro expands to the current reference count of a
 *      heap pointer instance *ctx* that is pointing to the body segment.  This
 *      macro is implementation-specific and is **not** meant to be part of the
 *      heap pointer interface.
 *
 * __NOTES__
 *      Since *REFC_CURRENT()* receives *ctx* as a heap pointer pointing to the
 *      body segement, the reference count metadata needs to be extracted from
 *      the offset.
 */
#define REFC_CURRENT(ctx)   ctx[HEAD_OFFSET]


/*
 * __NAME__
 *      REFC_INCREMENT() - increments reference count
 *
 * __SYNOPSIS__
 *      #define REFC_INCREMENT(ctx)
 *
 * __DESCRIPTION__
 *      The *REFC_INCREMENT()* macro is used to increment the current reference
 *      count of a heap pointer instance *ctx* that is pointing to the body
 *      segment. This macro is used only internally and is **not** meant to be
 *      part of the heap pointer interface.
 *
 * __NOTES__
 *      Since *ctx* is passed to *REFC_CURRENT()* as a heap pointer pointing to
 *      the body segment, the reference count metadata needs to be manipulated
 *      at the offset to the body.
 */
#define REFC_INCREMENT(ctx)     ctx[HEAD_OFFSET]++


/*
 * __NAME__
 *      REFC_DECREMENT() - decrements reference count
 *
 * __SYNOPSIS__
 *      #define REFC_DECREMENT(ctx)
 *
 * __DESCRIPTION__
 *      The *REFC_DECREMENT()* macro decrements the current reference count of a
 *      heap pointer instance *ctx* that is pointing to the body segment.
 *      This macro is the opposite of the *REFC_INCREMENT()* macro, and like the
 *      latter, is implementation-specific and so **not** part of the heap
 *      pointer interface.
 *
 * __NOTES__
 *      The *REFC_DECREMENT()* macro receives *ctx* as heap pointer that is
 *      pointing to the body segment, and so needs to operate on the reference
 *      count metadata on the offset.
 */
#define REFC_DECREMENT(ctx)     ctx[HEAD_OFFSET]--


/*
 * __NAME__
 *      CAST_HEAD() - casts head of heap pointer instance
 *
 * __SYNOPSIS__
 *      #define CAST_HEAD(ctx)
 *
 * __DESCRIPTION__
 *      The *CAST_HEAD()* macro casts a heap pointer instance *ctx* to a *void
 *      ** pointer pointing to the head segment of the instance. This function
 *      is implementation-specific and **not** part of the heap pointer
 *      interface.
 *
 * __NOTES__
 *      The *CAST_HEAD()* macro receives *ctx* as a heap pointer instance that
 *      points to the body segment. Hence, the head segment lies in the offset
 *      before *ctx*.
 */
#define CAST_HEAD(ctx) (void *) &ctx[HEAD_OFFSET]


/*
 * __NAME__
 *      CAST_BODY() - casts body of heap pointer instance
 *
 * __SYNOPSIS__
 *      #define CAST_BODY(ctx)
 *
 * __DESCRIPTION__
 *      The *CAST_BODY()* macro is similar to the *CAST_HEAD()* macro, except
 *      that the casting to *void ** is done on the body segment of a heap
 *      pointer instance *ctx*. Like its sibling, the *CAST_BODY()* macro is
 *      specific to the heap pointer implementation and is **not** part of the
 *      interface.
 *
 * __NOTES__
 *      The *CAST_BODY()* macro receives *ctx* as a heap pointer instance that
 *      points to the head segment; hence, the body segment starts at the body
 *      index relative to the head of *ctx*.
 */
#define CAST_BODY(ctx) (void *) &ctx[BODY_INDEX]


/*
 * __NAME__
 *      ALIGN_VALID() - checks if alignment is valid
 *
 * __SYNOPSIS__
 *      #define ALIGN_VALID(aln)
 *
 * __DESCRIPTION__
 *      The *ALIGN_VALID()* macro checks whether a given *size_t* alignment
 *      *aln* is valid. This macro expands to either *true* or *false* depending
 *      on whether or not the alignment is valid. This macro is **not** part of
 *      the heap pointer interface as it is used only by the implementation.
 *
 * __NOTES__
 *      Internally, *cy_hptr_new_aligned()* uses *posix_memalign()*, which
 *      requires that the alignment be a power of 2 that is a multiple of the
 *      size of *void **.  Accordingly, the *ALIGN_VALID()* macro checks for
 *      this condition.
 */
#define ALIGN_VALID(aln)    (aln && !(aln & (aln - 1)) \
                             && !(aln % sizeof (void *)))


/* Prototypes for support functions */
static size_t   align_fix(size_t);


/*
 * __NAME__
 *      *cy_hptr_new() - allocates heap pointer instance
 *
 * __SYNOPSIS__
 *      ```
 *      #include <libchrysalid/libchrysalid.h>
 *      void *cy_hptr_new(size_t sz)
 *      ```
 *
 * __DESCRIPTION__
 *      The *cy_hptr_new()* function allocates a new instance of the *cy_hptr_t*
 *      type on the heap memory, returning a pointer to the usable segment of
 *      the instance. The size of the allocated instance is specified through
 *      the *sz* parameter, which is expected to be positive *size_t* value. In
 *      case a size of 0 is passed, then *sz* is automatically set to the native
 *      size of *size_t*.
 *
 * __RETURN__
 *      The *cy_hptr_new()* function returns a *void ** pointer pointing to the
 *      body segment of a newly allocated *cy_hptr_t* instance that is of the
 *      requested size. The returned pointer is guaranteed not to be null.
 *
 * __NOTES__
 *      The *cy_hptr_new()* function uses *calloc()* for allocation to ensure
 *      that all the the bytes of the body segment are set to 0. In contrast,
 *      the head segment holds a value of 1, which is the reference count of the
 *      instanct at initialisation. In case of an allocation failure, the
 *      behaviour is to abort with a failure message, but this may change in
 *      future.
 */
void *cy_hptr_new(size_t sz)
{
        const size_t tsz = (CY_LIKELY(sz) ? sz : sizeof (size_t)) + HEAD_SZ;
        cy_hptr_t *ctx = calloc(1, tsz);

        if (CY_UNLIKELY(!ctx)) {
                printf("PANIC: Failed to allocate memory of size %zu!\n", sz);
                abort();
        }

        REFC_INIT(ctx);
        return CAST_BODY(ctx);
}


/*
 * __NAME__
 *      *cy_hptr_new_aligned() - allocates aligned heap pointer instance
 *
 * __SYNOPSIS__
 *      ```
 *      #include <libchrysalid/libchrysalid.h>
 *      void *cy_hptr_new_aligned(size_t sz, size_t aln)
 *      ```
 *
 * __DESCRIPTION__
 *      The *cy_hptr_new_aligned()* function is similar to the *cy_hptr_new()*
 *      function except that in addition to returning a heap pointer instance of
 *      a given size *sz* it is also aligned to the boundary specified by *aln*.
 *      The alignment boundary must be a power of two that is a multiple of the
 *      native size of *void ** pointers; if not, *aln* is automatically rounded
 *      up to the nearest valid boundary.
 *
 * __RETURN__
 *      This function returns a *void ** pointer to the usable segment of a
 *      newly allocated heap pointer instance that is of the requested size and
 *      aligned to the requested boundary. The returned pointer is guaranteed
 *      not to be null.
 *
 * __NOTES__
 *      Just as in the case of *cy_hptr_new()*, the *cy_hptr_new_aligned()*
 *      function sets all bytes of the body segment to 0 and the head segment to
 *      1. It does so using a combination of *posix_memalign()* and *memset()*
 *      instead of *calloc()* as in the case of *cy_hptr_new()*. In case of an
 *      allocation failure, the current behaviour is to abort with a failure
 *      message, but this may change in future.
 */
void *cy_hptr_new_aligned(size_t sz, size_t aln)
{
        static_assert(sizeof (void *) == 4 || sizeof (void *) == 8,
                      "Expected 32-bit / 64-bit platform");

        sz = (CY_LIKELY(sz) ? sz : sizeof (size_t)) + HEAD_SZ;
        aln = CY_LIKELY(ALIGN_VALID(aln)) ? aln : align_fix(aln);

        cy_hptr_t *ctx;

        if (CY_UNLIKELY(posix_memalign((void **) &ctx, aln, sz))) {
                printf("PANIC: Failed to allocate memory of size %zu"
                       " and alignment %zu!\n", sz, aln);
                abort();
        }

        memset(ctx, 0, sz);
        REFC_INIT(ctx);

        return CAST_BODY(ctx);
}


/*
 * __NAME__
 *      *cy_hptr_copy() - copies heap pointer instance
 *
 * __SYNOPSIS__
 *      __MCODE__(
 *      #include <libchrysalid/libchrysalid.h>
 *      void *cy_hptr_copy(cy_hptr_t ctx[static 1])
 *      )
 *
 * __DESCRIPTION__
 *      The *cy_hptr_copy()* function creates a shallow copy of an existing heap
 *      pointer instance *ctx*, internally keeping track of the reference count.
 *      Shallow copies provide a performance gain since they avoid the cost of
 *      repeated allocation; however, care must be taken to ensure that they are
 *      not modified accidentally.
 *
 * __RETURN__
 *      The *cy_hptr_copy()* function returns a shallow copy of the contextual
 *      heap pointer instance *ctx* passed to it. This function is guaranteed to
 *      return a pointer to the same address as *ctx*.
 *
 * __NOTES__
 *      The *cy_hptr_copy()* function simply increments the reference count of
 *      *ctx* and returns a copy of the pointer. A check is made to ensure that
 *      the maximum number of reference counts has not been reached, the current
 *      behaviour being to abort in such a case.
 */
void *cy_hptr_copy(cy_hptr_t ctx[static 1])
{
        if (CY_UNLIKELY(REFC_CURRENT(ctx) == CY_HPTR_REFC_MAX)) {
                printf("PANIC: maximum number of reference counts reached!\n");
                abort();
        }

        REFC_INCREMENT(ctx);
        return ctx;
}


/*
 * __NAME__
 *      *cy_hptr_free() - releases heap pointer instance
 *
 * __SYNOPSIS__
 *      ```
 *      #include <libchrysalid/libchrysalid.h>
 *      void cy_hptr_free(cy_hptr_t *ctx[static 1])
 *      ```
 *
 * __DESCRIPTION__
 *      The *cy_hptr_free()* function releases the heap memory allocated to a
 *      heap pointer instance *ctx*. The heap pointer instance pointed to by
 *      *ctx* is expected to be valid, but in case it is invalid then a safe
 *      no-op occurs. After release, the heap pointer instance pointed to by
 *      *ctx* is set to NULL in order to indicate that it is no longer usable.
 *
 * __NOTES__
 *      If *ctx* is a shallow copy, then its reference count is decremented
 *      rather that it being actually released; this is however opaque to the
 *      client code. From the perspective of the client code, there is no
 *      difference whether *ctx* points to a single instance or a shallow copy
 *      since in both cases the pointer to the heap instance is set to *NULL*.
 *
 */
void cy_hptr_free(cy_hptr_t *ctx[static 1])
{
        cy_hptr_t *h;

        if (CY_LIKELY((h = *ctx))) {
                REFC_DECREMENT(h);

                if (!REFC_CURRENT(h))
                        free(h + HEAD_OFFSET);

                *ctx = NULL;
        }
}


/*
 * __NAME__
 *      *cy_hptr_aligned() - checks alignment of heap pointer instance
 *
 * __SYNOPSIS__
 *      ```
 *      #include <libchrysalid/libchrysalid.h>
 *      bool cy_hptr_aligned(const cy_hptr_t ctx[static 1], size_t aln)
 *      ```
 *
 * __DESCRIPTION__
 *      The *cy_hptr_aligned() function determines whether a given heap pointer
 *      instance *ctx* is aligned to a given alignment *aln*. The value of *aln*
 *      must be a power of 2 that is a multiple of the native size of *void **
 *      pointers; if not, then the alignment is considered invalid and this
 *      function will return *false*.
 *
 * __RETURN__
 *      This function returns one of the following *bool* values depending on
 *      the result of the alignment computation:
 *        - *true* if *ctx* is aligned to *aln*
 *        - *flase* if *ctx* is not aligned to *aln*
 *
 * __NOTES__
 *      Since *ctx* points to the body segment, we need to first determine the
 *      address of its segment before performing the bitwise operation that
 *      checks for alignment.
 */
bool cy_hptr_aligned(const cy_hptr_t ctx[static 1], size_t aln)
{
        if (CY_LIKELY(ALIGN_VALID(aln)))
                return !((uintptr_t) CAST_HEAD(ctx) & (aln - 1));

        return false;
}


/*
 * __NAME__
 *      *cy_hptr_refc() - gets reference count of heap pointer instance
 *
 * __SYNOPSIS__
 *      ```
 *      #include <libchrysalid/libchrysalid.h>
 *      size_t cy_hptr_refc(const cy_hptr_t ctx[static 1])
 *      ```
 *
 * __DESCRIPTION__
 *      The *cy_hptr_refc()* function gets the current reference count of a heap
 *      pointer instance *ctx*. If *ctx* does not have any copies, then 1 is
 *      returned; if otherwise, then *n + 1* is returned where *n* is the number
 *      of cunrrent shallow copies.
 *
 * __RETURN__
 *      This function returns the current reference count of *ctx*, which is
 *      guaranteed to be greater than or equal to 1.
 */
size_t cy_hptr_refc(const cy_hptr_t ctx[static 1])
{
        return REFC_CURRENT(ctx);
}


/*
 * __NAME__
 *      *cy_hptr_sz() - gets size of heap pointer instance
 *
 * __SYNOPSIS__
 *      ```
 *      #include <libchrysalid/libchrysalid.h>
 *      size_t cy_hptr_sz(const cy_hptr_t ctx[static 1])
 *      ```
 *
 * __DESCRIPTION__
 *      The *cy_hptr_sz()* function determines the allocated size of a heap
 *      pointer instance *ctx*. This value is always greater than the orignally
 *      requested size since it accounts for additional metadata and alignment
 *      issues.
 *
 * __RETURN__
 *      This function returns the total allocated size of *ctx*.
 *
 * __NOTES__
 *      The total allocated size is determined through the implementation
 *      specific *malloc_size()* and *malloc_usable_size()* functions. The
 *      former is available on Apple platforms, whereas the latter is available
 *      for Linux/FreeBSD. There is no guarantee that both of these functions
 *      return the same value.
 *
 *      At the very least, the total size returned by *cy_hptr_sz()* is greater
 *      than the requested size by *HEAD_SZ*, and more so if alignment and CPU
 *      byte ordering issues are taken into consideration by the underlying
 *      *malloc()* implementation.
 */
size_t cy_hptr_sz(const cy_hptr_t ctx[static 1])
{
#ifdef __APPLE__
        return malloc_size(CAST_HEAD(ctx));
#else
        return malloc_usable_size(CAST_HEAD(ctx));
#endif
}


/*
 * __NAME__
 *      *cy_hptr_str() - gets string representation of heap pointer instance
 *
 * __SYNOPSIS__
 *      ```
 *      #include <libchrysalid/libchrysalid.h>
 *      const char *cy_hptr_str(const cy_hptr_t ctx[static 1])
 *      ```
 *
 * __DESCRIPTION__
 *      The *cy_hptr_str()* function gets the string representation of a given
 *      heap pointer instance *ctx*. This function has been providced mainly for
 *      debugging purporses, and includes the following information about *ctx*:
 *        - the address of its head segment,
 *        - the address of its body segment,
 *        - its usable size in bytes, and
 *        - its reference count.
 *
 * __RETURN__
 *      This function returns an immutable string containing relevant diagnostic
 *      information about *ctx*.
 *
 * __NOTES__
 *      The returned string does not contain information regarding alignment
 *      since there is currently no way to determine it without storing it as
 *      additional metadata.
 */
const char *cy_hptr_str(const cy_hptr_t ctx[static 1])
{
        static char bfr[1024];
        sprintf(bfr,
                "head addr: %p, body addr: %p, usable size: %zu, refc: %zu\n",
                CAST_HEAD(ctx),
                (void *) ctx,
                cy_hptr_sz(ctx),
                REFC_CURRENT(ctx));

        return bfr;
}


/* Support functions */


/*
 * __NAME__
 *      *align_fix()* - fixes alignment
 *
 * __SYNOPSIS__
 *      __CODE__(static size_t align_fix(size_t aln);)
 *
 * __DESCRIPTION__
 *      The *align_fix()* support function fixes a bad alignment value *aln* by
 *      rounding it up to the nearest valid value. This function is used only
 *      internally by the heap pointer implementation and is **not** part of the
 *      interface.
 *
 * __RETURN__
 *      This function returns an alignment that is rounded up to the nearest
 *      valid alignment of *aln*.
 *
 * __NOTES__
 *      The *align_fix()* function returns an alignment that is rounded up to
 *      the nearest power of two that is also a multiple of the native size of a
 *      *void ** pointer; this is as per the requirements of *posix_memalign()*.
 *
 *      The *align_fix()* function is meant to be used only with invalid values
 *      of *aln*; hence no check is made to determine whether or not *aln* is
 *      valid in the first case.
 *
 *      The case of negative values of *aln* are especially problematic since
 *      fixing them with the current algorithm leads to an invalid alignment of
 *      0; hence, and additional check is made to ensure that this function
 *      returns at least the size of a *void ** pointer (which is guaranteed to
 *      be a power of 2 through a compile-time assertion).
 */
size_t align_fix(size_t aln)
{
        static_assert(sizeof (void *) % 2 == 0,
                      "The size of void * must be a power of 2");

        const size_t sz = sizeof (void *);
        aln = aln ? aln : sz;

        size_t rem = aln % sz;
        aln = rem ? aln + sz - rem : aln;

        while (aln & (aln - 1))
                aln += sz;

        return aln ? aln : sizeof (void *); /* fix for negative alignments */
}
