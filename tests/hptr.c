/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * libchrysalid/tests/heap.c - heap pointer tests
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


/* Libchrysalid dependencies */
#include "../include/hptr.h"

/* Criterion testing framework */
#include <criterion/criterion.h>

/* Standard library dependencies */
#include <assert.h>
#include <math.h>
#include <string.h>


/* Test data structure  */


/*                                                             %type:hptr:test_t
 * __NAME__
 *      {{test_t}} - test data structure
 *
 * __SYNOPSIS__
 *      typedef struct {
 *              int      x;
 *              float    y;
 *              int     *px;
 *              float   *py;
 *      } test_t;
 *
 * __DESCRIPTION__
 *      The {{test_t}} type is a test data structure simulating a real abstract
 *      data type. This type is used by the heap pointer tests and is **not**
 *      part of the heap pointer interface.
 *
 *      The {{test_t}} type has four fields, two of which are scalar ({{x}} and
 *      {{y}}), and the other two being pointers to the scalar fields. These
 *      fields have no inherent meaning except that of representing the fields
 *      of an ADT in production code.
 */
typedef struct {
        int      x;
        float    y;
        int     *px;
        float   *py;
} test_t;


/* Prototypes for test_t support functions */
static void     test_t_free(test_t *[static 1]);
static bool     test_yeq(const test_t[static 1], float);


/* Tests for cy_hptr_new() */


/*                                               %test:cy_hptr_new:positive_size
 * __SCENARIO__
 *      {{cy_hptr_new()}} returns a valid heap pointer instance for a positive
 *      size value
 *
 * __GIVEN__
 *      - a sample test data structure {{test_t}}
 *      - {{cy_hptr_new()}} is called to create an instance of {{test_t}}
 *
 * __WHEN__
 *      - {{sz}} == size of {{test_t}}
 *
 * __THEN__
 *      - a non-null heap pointer instance is returned
 *      - the instance has a size at least that of {{test_t}}
 *      - the instance has a reference count of 1
 *      - the instance has all its data bytes set to 0
 */
Test(cy_hptr_new, positive_size)
{
        CY_AUTO(test_t) *t = cy_hptr_new(sizeof *t);
        cr_expect(t);

        size_t sz = cy_hptr_sz((const cy_hptr_t *) t);
        cr_expect(sz >= sizeof (test_t));

        size_t r = cy_hptr_refc((cy_hptr_t *) t);
        cr_expect(r == 1);

        static const char c[sizeof (test_t)];
        cr_expect(memcmp(c, t + sizeof (size_t), sizeof (test_t)));
}


/*                                                   %test:cy_hptr_new:zero_size
 * __SCENARIO__
 *      {{cy_hptr_new()}} returns a valid heap pointer instance for a size value
 *      of zero
 *
 * __GIVEN__
 *      - a sample test data structure {{test_t}}
 *      - {{cy_hptr_new()}} is called to create an instance of {{test_t}}
 *
 * __WHEN__
 *      - {{sz}} == 0
 *
 * __THEN__
 *      - a non-null heap pointer instance is returned
 *      - the instance has a size at least that of {{size_t}}
 *      - the instance has a reference count of 1
 *      - the instance has all its data bytes set to 0
 */
Test(cy_hptr_new, zero_size)
{
        CY_AUTO(test_t) *t = cy_hptr_new(0);
        cr_expect(t);

        size_t sz = cy_hptr_sz((const cy_hptr_t *) t);
        cr_expect(sz >= sizeof (size_t));

        size_t r = cy_hptr_refc((cy_hptr_t *) t);
        cr_expect(r == 1);

        static const char c[sizeof (size_t)];
        cr_expect(memcmp(c, t + sizeof (size_t), sizeof (size_t)));
}


/*                                               %test:cy_hptr_new:negative_size
 * __SCENARIO__
 *      {{cy_hptr_new()}} returns a valid heap pointer instance for a negative
 *      size value
 *
 * __GIVEN__
 *      - a sample test data structure {{test_t}}
 *      - {{cy_hptr_new()}} is called to create an instance of {{test_t}}
 *
 * __WHEN__
 *      - {{sz}} == 0
 *
 * __THEN__
 *      - a non-null heap pointer instance is returned
 *      - the instance has a size at least that of {{size_t}}
 *      - the instance has a reference count of 1
 *      - the instance has all its data bytes set to 0
 */
Test(cy_hptr_new, negative_size)
{
        CY_AUTO(test_t) *t = cy_hptr_new(-1);
        cr_expect(t);

        size_t sz = cy_hptr_sz((const cy_hptr_t *) t);
        cr_expect(sz >= sizeof (size_t));

        size_t r = cy_hptr_refc((cy_hptr_t *) t);
        cr_expect(r == 1);

        static const char c[sizeof (size_t)];
        cr_expect(memcmp(c, t + sizeof (size_t), sizeof (size_t)));
}


/* Tests for cy_hptr_new_aligned() */


/*                                        %test:cy_hptr_new_aligned:valid_params
 * __SCENARIO__
 *      {{cy_hptr_new_aligned()}} returns a valid aligned heap pointer instance
 *      when passed valid parameters
 *
 * __GIVEN__
 *      - a 32-bit / 64-bit platform
 *      - a sample test data structure {{test_t}}
 *      - {{cy_hptr_new_aligned()}} is called to create an instance of
 *        {{test_t}}
 *
 * __WHEN__
 *      - {{sz}} == size of {{test_t}}
 *      - {{aln}} == 32
 *
 * __THEN__
 *      - a non-null heap pointer instance is returned
 *      - the instance has a size at least that of {{test_t}}
 *      - the instance is aligned to the requested boundary
 *      - the instance has a reference count of 1
 *      - the instance has all its data bytes set to 0
 */
Test(cy_hptr_new_aligned, valid_params)
{
        static_assert(sizeof (void *) == 4 || sizeof (void *) == 8,
                      "Expected 32/64-bit platform");

        CY_AUTO(test_t) *t = cy_hptr_new_aligned(sizeof *t, 32);
        cr_expect(t);

        size_t sz = cy_hptr_sz((const cy_hptr_t *) t);
        cr_expect(sz >= sizeof (test_t));

        bool a = cy_hptr_aligned((const cy_hptr_t *) t, 32);
        cr_expect(a);

        size_t r = cy_hptr_refc((cy_hptr_t *) t);
        cr_expect(r == 1);

        static const char c[sizeof (test_t)];
        cr_expect(memcmp(c, t + sizeof (size_t), sizeof (test_t)));
}


/*                                             %test:cy_hptr_new_aligned:zero_sz
 * __SCENARIO__
 *      {{cy_hptr_new_aligned()}} returns a valid aligned heap pointer instance
 *      when passed a size of 0
 *
 * __GIVEN__
 *      - a 32-bit / 64-bit platform
 *      - a sample test data structure {{test_t}}
 *      - {{cy_hptr_new_aligned()}} is called to create an instance of
 *        {{test_t}}
 *
 * __WHEN__
 *      - {{sz}} == 0
 *      - {{aln}} == 32
 *
 * __THEN__
 *      - a non-null heap pointer instance is returned
 *      - the instance has a size at least that of {{size_t}}
 *      - the instance is aligned to the requested boundary
 *      - the instance has a reference count of 1
 *      - the instance has all its data bytes set to 0
 */
Test(cy_hptr_new_aligned, zero_sz)
{
        static_assert(sizeof (void *) == 4 || sizeof (void *) == 8,
                      "Expected 32/64-bit platform");

        CY_AUTO(test_t) *t = cy_hptr_new_aligned(0, 32);
        cr_expect(t);

        size_t sz = cy_hptr_sz((const cy_hptr_t *) t);
        cr_expect(sz >= sizeof (size_t));

        bool a = cy_hptr_aligned((const cy_hptr_t *) t, 32);
        cr_expect(a);

        size_t r = cy_hptr_refc((cy_hptr_t *) t);
        cr_expect(r == 1);

        static const char c[sizeof (size_t)];
        cr_expect(memcmp(c, t + sizeof (size_t), sizeof (size_t)));
}


/*                                         %test:cy_hptr_new_aligned:negative_sz
 * __SCENARIO__
 *      *cy_hptr_new_aligned()* returns a valid aligned heap pointer instance
 *      when passed a negative size
 *
 * __GIVEN__
 *      - a 32-bit / 64-bit platform
 *      - a sample test data structure *test_t*
 *      - *cy_hptr_new_aligned()* is called to create an instance of *test_t*
 *
 * __WHEN__
 *      - *sz* == -2
 *      - *aln* == 32
 *
 * __THEN__
 *      - a non-null heap pointer instance is returned
 *      - the instance has a size at least that of `size_t`
 *      - the instance is aligned to the requested boundary
 *      - the instance has a reference count of 1
 *      - the instance has all its data bytes set to 0
 */
Test(cy_hptr_new_aligned, negative_sz)
{
        static_assert(sizeof (void *) == 4 || sizeof (void *) == 8,
                      "Expected 32/64-bit platform");

        CY_AUTO(test_t) *t = cy_hptr_new_aligned(-2, 32);
        cr_expect(t);

        size_t sz = cy_hptr_sz((const cy_hptr_t *) t);
        cr_expect(sz >= sizeof (test_t));

        bool a = cy_hptr_aligned((const cy_hptr_t *) t, 32);
        cr_expect(a);

        size_t r = cy_hptr_refc((cy_hptr_t *) t);
        cr_expect(r == 1);

        static const char c[sizeof (test_t)];
        cr_expect(memcmp(c, t + sizeof (size_t), sizeof (test_t)));
}


/*                          %test:cy_hptr_new_aligned:invalid_positive_alignment
 * __SCENARIO__
 *      {{cy_hptr_new_aligned()}} returns a valid heap pointer instance aligned
 *      to the nearest rounded up valid boundary when passed an invalid positive
 *      alignment
 *
 * __GIVEN__
 *      - a 32-bit / 64-bit platform
 *      - a sample test data structure {{test_t}}
 *      - {{cy_hptr_new_aligned()}} is called to create an instance of
 *        {{test_t}}
 *
 * __WHEN__
 *      - {{sz}} == size of {{test_t}}
 *      - {{aln}} == 11
 *
 * __THEN__
 *      - a non-null heap pointer instance is returned
 *      - the instance has a size at least that of {{test_t}}
 *      - the instance is aligned to 16
 *      - the instance has a reference count of 1
 *      - the instance has all its data bytes set to 0
 */
Test(cy_hptr_new_aligned, invalid_positive_alignment)
{
        static_assert(sizeof (void *) == 4 || sizeof (void *) == 8,
                      "Expected 32/64-bit platform");

        CY_AUTO(test_t) *t = cy_hptr_new_aligned(sizeof *t, 11);
        cr_expect(t);

        size_t sz = cy_hptr_sz((const cy_hptr_t *) t);
        cr_expect(sz >= sizeof (test_t));

        bool a = cy_hptr_aligned((const cy_hptr_t *) t, 16);
        cr_expect(a);

        size_t r = cy_hptr_refc((cy_hptr_t *) t);
        cr_expect(r == 1);

        static const char c[sizeof (test_t)];
        cr_expect(memcmp(c, t + sizeof (test_t), sizeof (test_t)));
}


/*                                      %test:cy_hptr_new_aligned:zero_alignment
 * __SCENARIO__
 *      {{cy_hptr_new_aligned()}} returns a valid heap pointer instance aligned
 *      to the size of {{void *}} when passed an alignment value of 0
 *
 * __GIVEN__
 *      - a 32-bit / 64-bit platform
 *      - a sample test data structure {{test_t}}
 *      - {{cy_hptr_new_aligned()}} is called to create an instance of
 *        {{test_t}}
 *
 * __WHEN__
 *      - {{sz}} == size of {{test_t}}
 *      - {{aln}} == 0
 *
 * __THEN__
 *      - a non-null heap pointer instance is returned
 *      - the instance has a size at least that of {{test_t}}
 *      - the instance is aligned to the size of {{void *}}
 *      - the instance has a reference count of 1
 *      - the instance has all its data bytes set to 0
 */
Test(cy_hptr_new_aligned, zero_alignment)
{
        static_assert(sizeof (void *) == 4 || sizeof (void *) == 8,
                      "Expected 32/64-bit platform");

        CY_AUTO(test_t) *t = cy_hptr_new_aligned(sizeof *t, 0);
        cr_expect(t);

        size_t sz = cy_hptr_sz((const cy_hptr_t *) t);
        cr_expect(sz >= sizeof (test_t));

        bool a = cy_hptr_aligned((const cy_hptr_t *) t, sizeof (void *));
        cr_expect(a);

        size_t r = cy_hptr_refc((cy_hptr_t *) t);
        cr_expect(r == 1);

        static const char c[sizeof (test_t)];
        cr_expect(memcmp(c, t + sizeof (test_t), sizeof (test_t)));
}


/*                                  %test:cy_hptr_new_aligned:negative_alignment
 * __SCENARIO__
 *      {{cy_hptr_new_aligned()}} returns a valid heap pointer instance aligned
 *      to the size of {{void *}} when passed a negative alignment value
 *
 * __GIVEN__
 *      - a 32-bit / 64-bit platform
 *      - a sample test data structure {{test_t}}
 *      - {{cy_hptr_new_aligned()}} is called to create an instance of
 *        {{test_t}}
 *
 * __WHEN__
 *      - {{sz}} == size of {{test_t}}
 *      - {{aln}} == -3
 *
 * __THEN__
 *      - a non-null heap pointer instance is returned
 *      - the instance has a size at least that of {{test_t}}
 *      - the instance is aligned to the size of {{void *}}
 *      - the instance has a reference count of 1
 *      - the instance has all its data bytes set to 0
 */
Test(cy_hptr_new_aligned, negative_alignment)
{
        static_assert(sizeof (void *) == 4 || sizeof (void *) == 8,
                      "Expected 32/64-bit platform");

        CY_AUTO(test_t) *t = cy_hptr_new_aligned(sizeof *t, -3);
        cr_expect(t);

        size_t sz = cy_hptr_sz((const cy_hptr_t *) t);
        cr_expect(sz >= sizeof (test_t));

        bool a = cy_hptr_aligned((const cy_hptr_t *) t, sizeof (void *));
        cr_expect(a);

        size_t r = cy_hptr_refc((cy_hptr_t *) t);
        cr_expect(r == 1);

        static const char c[sizeof (test_t)];
        cr_expect(memcmp(c, t + sizeof (test_t), sizeof (test_t)));
}


/* Tests for cy_hptr_copy() */


/*                                                     %test:cy_hptr_copy:single
 * __SCENARIO__
 *      {{cy_hptr_copy()}} returns a shallow copy of an existing heap pointer
 *      instance
 *
 * __GIVEN__
 *      - an existing heap pointer instance of type {{test_t}}
 *      - {{cy_hptr_copy()}} is called to create a shallow copy of the instance
 *
 * __WHEN__
 *      - {{ctx}} == instance of type {{test_t}}
 *
 * __THEN__
 *      - a non-null heap pointer instance is returned
 *      - the copy has the same address as the source
 *      - the copy has the same size as its source
 *      - the copy and its source both have a reference count of 2
 *      - the copy has the same data as its source
 */
Test(cy_hptr_copy, single)
{
        CY_AUTO(test_t) *t = cy_hptr_new(sizeof (test_t));
        t->x = 555;
        t->y = 123.456;
        t->px = &t->x;
        t->py = &t->y;

        CY_AUTO(test_t) *cp = cy_hptr_copy((cy_hptr_t *) t);
        cr_expect(cp);
        cr_expect(cp == t);

        size_t sz = cy_hptr_sz((const cy_hptr_t *) t);
        cr_expect(sz == cy_hptr_sz((const cy_hptr_t *) cp));

        cr_expect(cy_hptr_refc((const cy_hptr_t *) t) == 2);
        cr_expect(cy_hptr_refc((const cy_hptr_t *) cp) == 2);

        cr_expect(t->x == cp->x);
        cr_expect(t->y == cp->y);
        cr_expect(t->px == cp->px);
        cr_expect(t->py == cp->py);
}


/*                                             %test:cy_hptr_copy:single_aligned
 * __SCENARIO__
 *      {{cy_hptr_copy()}} returns a shallow copy of an existing aligned heap
 *      pointer instance
 *
 * __GIVEN__
 *      - an existing 32-bit aligned heap pointer instance of type {{test_t}}
 *      - {{cy_hptr_copy()}} is called to create a shallow copy of the instance
 *
 * __WHEN__
 *      - {{ctx}} == instance of type {{test_t}}
 *
 * __THEN__
 *      - a non-null heap pointer instance is returned
 *      - the copy has the same address as the source
 *      - the copy has the same size as its source
 *      - the copy and its source both have an alignment of 32
 *      - the copy and its source both have a reference count of 2
 *      - the copy has the same data as its source
 */
Test(cy_hptr_copy, single_aligned)
{
        CY_AUTO(test_t) *t = cy_hptr_new_aligned(sizeof (test_t), 32);
        t->x = 555;
        t->y = 123.456;
        t->px = &t->x;
        t->py = &t->y;

        CY_AUTO(test_t) *cp = cy_hptr_copy((cy_hptr_t *) t);
        cr_expect(cp);
        cr_expect(cp == t);

        size_t sz = cy_hptr_sz((const cy_hptr_t *) t);
        cr_expect(sz == cy_hptr_sz((const cy_hptr_t *) cp));

        cr_expect(cy_hptr_aligned((const cy_hptr_t *) t, 32));
        cr_expect(cy_hptr_aligned((const cy_hptr_t *) cp, 32));

        cr_expect(cy_hptr_refc((const cy_hptr_t *) t) == 2);
        cr_expect(cy_hptr_refc((const cy_hptr_t *) cp) == 2);

        cr_expect(t->x == cp->x);
        cr_expect(t->y == cp->y);
        cr_expect(t->px == cp->px);
        cr_expect(t->py == cp->py);
}


/*                                                   %test:cy_hptr_copy:multiple
 * __SCENARIO__
 *      {{cy_hptr_copy()}} creates the same shallow copy of an existing heap
 *      pointer instance when invoked multiple times
 *
 * __GIVEN__
 *      - an existing heap pointer instance of type {{test_t}}
 *      - {{cy_hptr_copy()}} is called to create 3 shallow copies of the
 *        instance
 *
 * __WHEN__
 *      - {{ctx}} == instance of type {{test_t}}
 *
 * __THEN__
 *      - each copy is a non-null pointer
 *      - each copy has the same address as the source
 *      - each copy has the same size as ther source
 *      - each copy and their source have a reference count of 4
 *      - each copy has the same data as the source
 */
Test(cy_hptr_copy, multiple)
{
        CY_AUTO(test_t) *t = cy_hptr_new(sizeof (test_t));
        t->x = 555;
        t->y = 123.456;
        t->px = &t->x;
        t->py = &t->y;

        CY_AUTO(test_t) *cp = cy_hptr_copy((cy_hptr_t *) t);
        CY_AUTO(test_t) *cp2 = cy_hptr_copy((cy_hptr_t *) t);
        CY_AUTO(test_t) *cp3 = cy_hptr_copy((cy_hptr_t *) cp);

        cr_expect(cp);
        cr_expect(cp2);
        cr_expect(cp3);

        cr_expect(cp == t);
        cr_expect(cp2 == t);
        cr_expect(cp3 == t);

        size_t sz = cy_hptr_sz((const cy_hptr_t *) t);
        cr_expect(sz == cy_hptr_sz((const cy_hptr_t *) cp));
        cr_expect(sz == cy_hptr_sz((const cy_hptr_t *) cp2));
        cr_expect(sz == cy_hptr_sz((const cy_hptr_t *) cp3));

        cr_expect(cy_hptr_refc((const cy_hptr_t *) t) == 4);
        cr_expect(cy_hptr_refc((const cy_hptr_t *) cp) == 4);
        cr_expect(cy_hptr_refc((const cy_hptr_t *) cp2) == 4);
        cr_expect(cy_hptr_refc((const cy_hptr_t *) cp3) == 4);

        cr_expect(t->x == cp->x);
        cr_expect(t->y == cp->y);
        cr_expect(t->px == cp->px);
        cr_expect(t->py == cp->py);
        cr_expect(t->x == cp2->x);
        cr_expect(t->y == cp2->y);
        cr_expect(t->px == cp2->px);
        cr_expect(t->py == cp2->py);
        cr_expect(t->x == cp3->x);
        cr_expect(t->y == cp3->y);
        cr_expect(t->px == cp3->px);
        cr_expect(t->py == cp3->py);
}


/*                                           %test:cy_hptr_copy:multiple_aligned
 * __SCENARIO__
 *      {{cy_hptr_copy()}} creates the same shallow copy of an existing aligned
 *      heap pointer instance when invoked multiple times
 *
 * __GIVEN__
 *      - an existing 16-bit aligned heap pointer instance of type {{test_t}}
 *      - {{cy_hptr_copy()}} is called to create 2 shallow copies of the
 *        instance
 *
 * __WHEN__
 *      - {{ctx}} == instance of type {{test_t}}
 *
 * __THEN__
 *      - each copy is a non-null pointer
 *      - each copy has the same address as the source
 *      - each copy has the same size as ther source
 *      - each copy and the source have an alignment of 16
 *      - each copy and their source have a reference count of 3
 *      - each copy has the same data as the source
 */
Test(cy_hptr_copy, multiple_aligned)
{
        CY_AUTO(test_t) *t = cy_hptr_new_aligned(sizeof (test_t), 16);
        t->x = 555;
        t->y = 123.456;
        t->px = &t->x;
        t->py = &t->y;

        CY_AUTO(test_t) *cp = cy_hptr_copy((cy_hptr_t *) t);
        CY_AUTO(test_t) *cp2 = cy_hptr_copy((cy_hptr_t *) t);

        cr_expect(cp);
        cr_expect(cp2);

        cr_expect(cp == t);
        cr_expect(cp2 == t);

        size_t sz = cy_hptr_sz((const cy_hptr_t *) t);
        cr_expect(sz == cy_hptr_sz((const cy_hptr_t *) cp));
        cr_expect(sz == cy_hptr_sz((const cy_hptr_t *) cp2));

        cr_expect(cy_hptr_aligned((const cy_hptr_t *) t, 16));
        cr_expect(cy_hptr_aligned((const cy_hptr_t *) cp, 16));

        cr_expect(cy_hptr_refc((const cy_hptr_t *) t) == 3);
        cr_expect(cy_hptr_refc((const cy_hptr_t *) cp) == 3);
        cr_expect(cy_hptr_refc((const cy_hptr_t *) cp2) == 3);

        cr_expect(t->x == cp->x);
        cr_expect(t->y == cp->y);
        cr_expect(t->px == cp->px);
        cr_expect(t->py == cp->py);
        cr_expect(t->x == cp2->x);
        cr_expect(t->y == cp2->y);
        cr_expect(t->px == cp2->px);
        cr_expect(t->py == cp2->py);
}


/* Tests for cy_hptr_free() */


/*                                            %test:cy_hptr_free:hnd_to_null_ptr
 * __SCENARIO__
 *      {{cy_hptr_free()}} results in a safe no-op if passed a handle to a null
 *      pointer
 *
 * __GIVEN__
 *      - a handle to a null pointer
 *      - {{cy_hptr_free()}} is called
 *
 * __WHEN__
 *      - {{ctx}} == handle to null pointer
 *
 * __THEN__
 *      - a safe no-op occurs
 */
Test(cy_hptr_free, hnd_to_null_ptr)
{
        test_t *null = NULL;
        cy_hptr_free((cy_hptr_t **) &null);
}


/*                                                     %test:cy_hptr_free:single
 * __SCENARIO__
 *      {{cy_hptr_free()}} releases the memory of a single heap pointer instance
 *
 * __GIVEN__
 *      - a heap pointer instance
 *      - {{cy_hptr_free()}} is called
 *
 * __WHEN__
 *      - {{ctx}} == handle to heap pointer instance
 *
 * __THEN__
 *      - the instance is released and set to NULL
 */
Test(cy_hptr_free, single)
{
        test_t *t = cy_hptr_new(sizeof *t);
        cy_hptr_free((cy_hptr_t **) &t);
        cr_expect(!t);
}


/*                                           %test:cy_hptr_free:copies_preserved
 * __SCENARIO__
 *      {{cy_hptr_free()}} does not affect shallow copies when releasing the
 *      memory of a heap pointer instance
 *
 * __GIVEN__
 *      - a heap pointer instance
 *      - two shallow copies of the instance
 *      - {{cy_hptr_free()}} is called only for the source instance
 *
 * __WHEN__
 *      - {{ctx}} == handle to heap pointer instance
 *
 * __THEN__
 *      - the instance is released and set to NULL
 *      - the copies are not set to null
 *      - the copies have a reference count of 2
 *      - the copies retain their data
 */
Test(cy_hptr_free, copies_preserved)
{
        CY_AUTO(test_t) *t = cy_hptr_new(sizeof (test_t));
        t->x = 555;
        t->y = 123.456;
        t->px = &t->x;
        t->py = &t->y;

        CY_AUTO(test_t) *cp = cy_hptr_copy((cy_hptr_t *) t);
        CY_AUTO(test_t) *cp2 = cy_hptr_copy((cy_hptr_t *) t);

        cy_hptr_free((cy_hptr_t **) &t);
        cr_expect(!t);

        cr_expect(cp);
        cr_expect(cp2);

        cr_expect(cy_hptr_refc((const cy_hptr_t *) cp) == 2);
        cr_expect(cy_hptr_refc((const cy_hptr_t *) cp2) == 2);

        cr_expect(cp->x == 555);
        cr_expect(test_yeq(cp, 123.456));
        cr_expect(cp->px == &cp->x);
        cr_expect(cp->py == &cp->y);
        cr_expect(cp2->x == 555);
        cr_expect(test_yeq(cp2, 123.456));
        cr_expect(cp2->px == &cp2->x);
        cr_expect(cp2->py == &cp2->y);
}


/*                                         %test:cy_hptr_free:copies_all_release
 * __SCENARIO__
 *      {{cy_hptr_free()}} releases a heap pointer instance and its shallow
 *      copies when invoked for each of them.
 *
 * __GIVEN__
 *      - a heap pointer instance
 *      - two shallow copies of the instance
 *      - {{cy_hptr_free()}} is called on the instance and its copies
 *
 * __WHEN__
 *      - {{ctx}} == handle to heap pointer instance / shallow copy
 *
 * __THEN__
 *      - the instance is released and set to NULL
 *      - the copies are released and set to null
 */
Test(cy_hptr_free, multiple_copies_all_release)
{
        CY_AUTO(test_t) *t = cy_hptr_new(sizeof (test_t));
        CY_AUTO(test_t) *cp = cy_hptr_copy((cy_hptr_t *) t);
        CY_AUTO(test_t) *cp2 = cy_hptr_copy((cy_hptr_t *) t);

        cy_hptr_free((cy_hptr_t **) &t);
        cr_expect(!t);

        cy_hptr_free((cy_hptr_t **) &cp);
        cr_expect(!cp);

        cy_hptr_free((cy_hptr_t **) &cp2);
        cr_expect(!cp2);
}


/*                                             %test:cy_hptr_free:single_aligned
 * __SCENARIO__
 *      {{cy_hptr_free()}} releases the memory of a single aligned heap pointer
 *      instance
 *
 * __GIVEN__
 *      - a heap pointer instance aligned to 16 bits
 *      - {{cy_hptr_free()}} is called
 *
 * __WHEN__
 *      - {{ctx}} == handle to aligned heap pointer instance
 *
 * __THEN__
 *      - the instance is released and set to NULL
 */
Test(cy_hptr_free, single_aligned)
{
        test_t *t = cy_hptr_new_aligned(sizeof *t, 16);
        cy_hptr_free((cy_hptr_t **) &t);
        cr_expect(!t);
}


/*                                   %test:cy_hptr_free:aligned_copies_preserved
 * __SCENARIO__
 *      {{cy_hptr_free()}} does not affect shallow copies when releasing the
 *      memory of an aligned heap pointer instance
 *
 * __GIVEN__
 *      - a heap pointer instance aligned to 32 bits
 *      - two shallow copies of the instance
 *      - {{cy_hptr_free()}} is called only for the source instance
 *
 * __WHEN__
 *      - {{ctx}} == handle to heap pointer instance
 *
 * __THEN__
 *      - the instance is released and set to NULL
 *      - the copies are not set to null
 *      - the copies have a reference count of 2
 *      - the copies retain their data
 */
Test(cy_hptr_free, aligned_copies_preserved)
{
        CY_AUTO(test_t) *t = cy_hptr_new_aligned(sizeof (test_t), 32);
        t->x = 555;
        t->y = 123.456;
        t->px = &t->x;
        t->py = &t->y;

        CY_AUTO(test_t) *cp = cy_hptr_copy((cy_hptr_t *) t);
        CY_AUTO(test_t) *cp2 = cy_hptr_copy((cy_hptr_t *) t);

        cy_hptr_free((cy_hptr_t **) &t);
        cr_expect(!t);

        cr_expect(cp);
        cr_expect(cp2);

        cr_expect(cy_hptr_refc((const cy_hptr_t *) cp) == 2);
        cr_expect(cy_hptr_refc((const cy_hptr_t *) cp2) == 2);

        cr_expect(cp->x == 555);
        cr_expect(test_yeq(cp, 123.456));
        cr_expect(cp->px == &cp->x);
        cr_expect(cp->py == &cp->y);
        cr_expect(cp2->x == 555);
        cr_expect(test_yeq(cp2, 123.456));
        cr_expect(cp2->px == &cp2->x);
        cr_expect(cp2->py == &cp2->y);
}


/*                                 %test:cy_hptr_free:aligned_copies_all_release
 * __SCENARIO__
 *      {{cy_hptr_free()}} releases an aligned heap pointer instance and its
 *      shallow copies when invoked for each of them.
 *
 * __GIVEN__
 *      - a heap pointer instance aligned to 32 bits
 *      - two shallow copies of the instance
 *      - {{cy_hptr_free()}} is called on the instance and its copies
 *
 * __WHEN__
 *      - {{ctx}} == handle to heap pointer instance / shallow copy
 *
 * __THEN__
 *      - the instance is released and set to NULL
 *      - the copies are released and set to null
 */
Test(cy_hptr_free, multiple_copies_aligned_all_release)
{
        CY_AUTO(test_t) *t = cy_hptr_new_aligned(sizeof (test_t), 32);
        CY_AUTO(test_t) *cp = cy_hptr_copy((cy_hptr_t *) t);
        CY_AUTO(test_t) *cp2 = cy_hptr_copy((cy_hptr_t *) t);

        cy_hptr_free((cy_hptr_t **) &t);
        cr_expect(!t);

        cy_hptr_free((cy_hptr_t **) &cp);
        cr_expect(!cp);

        cy_hptr_free((cy_hptr_t **) &cp2);
        cr_expect(!cp2);
}


/* Tests for cy_hptr_aligned() */


/*                                              %test:cy_hptr_aligned:true_valid
 * __SCENARIO__
 *      {{cy_hptr_aligned()}} returns true if a heap pointer instance is aligned
 *      to a given boundary
 *
 * __GIVEN__
 *      - a heap pointer instance aligned to 32 bits
 *      - {{cy_hptr_aligned()}} is called on the instance
 *
 * __WHEN__
 *      - {{ctx}} == handle to heap pointer instance
 *      - {{aln}} == 32
 *
 * __THEN__
 *      - *true* is returned
 */
Test(cy_hptr_aligned, true_valid)
{
        CY_AUTO(test_t) *t = cy_hptr_new_aligned(sizeof (test_t), 32);

        bool aln = cy_hptr_aligned((const cy_hptr_t *) t, 32);
        cr_expect(aln);
}


/*                                             %test:cy_hptr_aligned:false_valid
 * __SCENARIO__
 *      {{cy_hptr_aligned()}} returns false if a heap pointer instance is not
 *      aligned to a given boundary
 *
 * __GIVEN__
 *      - a heap pointer instance aligned to 16 bits
 *      - {{cy_hptr_aligned()}} is called on the instance
 *
 * __WHEN__
 *      - {{ctx}} == handle to heap pointer instance
 *      - {{aln}} == 32
 *
 * __THEN__
 *      - {{false}} is returned
 */
Test(cy_hptr_aligned, false_valid)
{
        CY_AUTO(test_t) *t = cy_hptr_new_aligned(sizeof (test_t), 16);

        bool aln = cy_hptr_aligned((const cy_hptr_t *) t, 32);
        cr_expect(!aln);
}


/*                                           %test:cy_hptr_aligned:false_invalid
 * __SCENARIO__
 *      {{cy_hptr_aligned()}} returns false if an invalid alignment boundary is
 *      passed
 *
 * __GIVEN__
 *      - a heap pointer instance aligned to 32 bits
 *      - {{cy_hptr_aligned()}} is called on the instance
 *
 * __WHEN__
 *      - {{ctx}} == handle to heap pointer instance
 *      - {{aln}} == 11
 *
 * __THEN__
 *      - {{false}} is returned
 */
Test(cy_hptr_aligned, false_invalid)
{
        CY_AUTO(test_t) *t = cy_hptr_new_aligned(sizeof (test_t), 32);

        bool aln = cy_hptr_aligned((const cy_hptr_t *) t, 11);
        cr_expect(!aln);
}


/*                                                        %test:cy_hptr_str:desc
 * __SCENARIO__
 *      {{cy_hptr_str()}} returns a string describing a heap pointer instance
 *
 * __GIVEN__
 *      - a heap pointer instance
 *      - {{cy_hptr_str()}} is called on the instance
 *
 * __WHEN__
 *      - {{ctx}} == handle to heap pointer instance
 *
 * __THEN__
 *      - a non-empty string is returned
 *      - the returned string mentions the instance head address
 *      - the returned string mentions the instance body address
 *      - the returned string mentions the instance size
 *      - the returned string mentions the instance reference count
 */
Test(cy_hptr_str, desc)
{
        CY_AUTO(test_t) *t = cy_hptr_new(sizeof (test_t));

        const char *s = cy_hptr_str((const cy_hptr_t *) t);
        cr_expect(s && *s);

        cr_expect(strstr(s, "head addr: "));

        cr_expect(strstr(s, "body addr: "));

        cr_expect(strstr(s, "usable size: "));

        cr_expect(strstr(s, "refc: "));
}


/* Support functions for test_t */


/*                                                        %func:hptr:test_t_free
 * __NAME__
 *      {{test_t_free()}} - releases test instance
 *
 * __SYNOPSIS__
 *      static void test_t_free(test_t *ctx[static 1]);
 *
 * __DESCRIPTION__
 *      The {{test_t_free()}} function is a support function that releases the
 *      heap memory allocated to a {{test_t}} instance {{ctx}}. This function is
 *      meant to be used only with the heap pointer tests and is **not** part of
 *      the heap pointer interface.
 *
 * __NOTES__
 *      The {{test_t_free()}} function is invoked automatically for any
 *      {{test_t}} instance declared with the {{CY_AUTO()}} macro when the
 *      instance goes out of scope.  The name of this function is as per the
 *      requirements of the {{CY_AUTO()}} macro.
 */
void test_t_free(test_t *ctx[static 1])
{
        cy_hptr_free((cy_hptr_t **) ctx);
}


/*                                                           %func:hptr:test_yeq
 * __NAME__
 *      {{test_yeq()}} - equality comparison for {{y}} field of test instance
 *
 * __SYNOPSIS__
 *      static void test_t_free(test_t *ctx[static 1]);
 *
 * __DESCRIPTION__
 *      The {{test_yeq()}} helper function checks whether the {{y}} field of a
 *      test instance {{ctx}} is approximately equal to another floating point
 *      value *cmp*. This function is used by the heap pointer tests where
 *      required, and is **not** part of the heap pointer interface.
 *
 * __RETURN__
 *      {{test_yeq()}} returns one of the following {{bool}} values depending on
 *      the result of the comparison:
 *        - {{true}} if the {{y}} field of {{ctx}} is approximately equal to
 *          {{cmp}}
 *        - {{false}} otherwise
 *
 * __NOTES__
 *      The {{test_yeq()}} function uses Knuth's approximately equal algorithm
 *      for comparing floating point numbers.
 */
bool test_yeq(const test_t ctx[static 1], float cmp)
{
        const float epsilon = 0.00001;

        return (fabs(ctx->y - cmp)
                <= ((fabs(ctx->y) < fabs(cmp)
                     ? fabs(cmp) : fabs(ctx->y)) * epsilon));
}
