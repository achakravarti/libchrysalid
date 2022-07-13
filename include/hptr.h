/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * libchrysalid/src/heap.c - heap pointer interface
 * Copyright (c) 2022 Abhishek Chakravarti
 * See libchhrysalid:heap(3) for documentation.
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
 *    acknowledgment: "This product includes software developed by Abhishek
 *    Chakravarti (abhishek@taranjali.org)."
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


/* Header guard */
#ifndef __LIBCHRYSALID_INCLUDE_HPTR_H__
#define __LIBCHRYSALID_INCLUDE_HPTR_H__

/* Libchrysalid dependencies */
#include "ext.h"

/* Standard library dependencies */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* C++ compatiblity */
#ifdef __cplusplus
extern "C" {
#endif


/* Types */

/*                                                               %type:cy_hptr_t
 * __NAME__
 *      {{cy_hptr_t}} - pointer to heap memory buffer
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/api.h>
 *      typedef uintptr_t cy_hptr_t;
 *
 * __DESCRIPTION__
 *      The {{cy_hptr_t}} abstract data type represents a buffer in the heap
 *      memory.  It is the primary data type of the heap interface, and is
 *      manipulated by all functions of the interface. The {{cy_hptr_t}} type
 *      includes additional metadata for reference counting, but this is opaque
 *      to the client code.
 *
 *      The {{cy_hptr_t}} type has been typedef'd to {{uintptr_t}} and not
 *      {{void *}} in order to distinguish that it is simply not any other heap
 *      pointer returned by {{malloc()}} and friends, and also because the
 *      implementation operates on it as {{uintptr_t}} bytes. As a consequence,
 *      it is necessary to explicitly cast to a pointer to {{cy_hptr_t}} when
 *      using its interface; it is hoped that this makes the code much more
 *      explicit and helps avoid subtle bugs.
 *
 *      Since the {{cy_hptr_t}} type tracks its reference count, it allows for
 *      shallow copying; this is often desirable for performance reasons.
 *
 * __NOTES__
 *      Internally, the {{cy_hptr_t}} type is manipulated as an array of
 *      {{uintptr_t}} bytes partitioned into a head and body segment. The head
 *      segment is a single {{uintptr_t}} that is padded in front of the body
 *      segment containting the actual data.
 *
 *      The heap pointer instances returned by the {{cy_hptr_t}} interface point
 *      to the body segment; for this reason these functions are shown as
 *      returning {{void *}} and not {{cy_hptr_t *}}. Consequently, these
 *      pointers can be used transparently just like any other heap memory
 *      buffer returned by {{malloc()}} and friends.
 *
 *      Since the reference count is held in the head segment, {{cy_hptr_t}}
 *      instances can track {{size_t}} (which is equivalent to {{uintptr_t}})
 *      number of references; anything beyond this is considered to be an
 *      abnormal situation and leads to an abort.
 */
typedef uintptr_t   cy_hptr_t;


/* Constants */


/*                                                       %const:CY_HPTR_REFC_MAX
 * __NAME__
 *      {{CY_HPTR_REFC_MAX}} - maximum number of reference counts
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/api.h>
 *      #define CY_HPTR_REFC_MAX UINTPTR_MAX
 *
 * __DESCRIPTION__
 *      The {{CY_HPTR_REFC_MAX}} symbolic constant represents the maximum number
 *      of references a heap pointer can have. This constant has been provided
 *      so that client code can check whether or not the current reference count
 *      of a heap pointer instance (as determined through {{cy_hptr_refc()}}) is
 *      within bounds.
 *
 * __NOTES__
 *      Since reference counts are {{size_t}} values held inside a single
 *      {{uinptr_t}}, the maximum number of reference counts is {{UINTPTR_MAX}}.
 */
#define CY_HPTR_REFC_MAX    UINTPTR_MAX


/* Prototypes for factory functions  */
extern CY_HOT CY_RSAFE void     *cy_hptr_new(size_t);
extern CY_HOT CY_RSAFE void     *cy_hptr_new_aligned(size_t, size_t);
extern CY_HOT CY_RSAFE void     *cy_hptr_copy(cy_hptr_t [static 1]);
extern CY_HOT void               cy_hptr_free(cy_hptr_t *[static 1]);


/* Prototypes for accessor functions  */
extern bool          cy_hptr_aligned(const cy_hptr_t [static 1], size_t);
extern size_t        cy_hptr_refc(const cy_hptr_t [static 1]);
extern size_t        cy_hptr_sz(const cy_hptr_t [static 1]);
extern const char   *cy_hptr_str(const cy_hptr_t [static 1]);


/* C++ compatibility */
#ifdef __cplusplus
}
#endif

/* Header guard */
#endif /* !__LIBCHRYSALID_INCLUDE_HPTR_H__ */
