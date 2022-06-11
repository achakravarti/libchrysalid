#include "../include/hptr.h"
#include "../include/utf8.h"

#include "../external/utf8.h/utf8.h"
#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>

#include <string.h>
#include <stdio.h>


/* Factory functions  */


/*
 * __NAME__
 *      cy_utf8_new() - creates new UTF-8 string
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/api.h>
 *
 *      extern CY_HOT CY_RSAFE cy_utf8_t *
 *      cy_utf8_new(const char src[static 1]);
 *
 * __DESCRIPTION__
 *      The {{cy_utf8_new()}} function creates a new {{cy_utf8_t}} instance from
 *      a raw C-string literal {{src}}. The string literal may be an empty
 *      string, an ASCII string, or a stream of bytes encoded in UTF-8.
 *
 * __RETURN__
 *      {{cy_utf8_new()}} returns a pointer to a new {{cy_utf8_t}} created on
 *      the heap that is lexicographically equal to {{src}}. This function is
 *      guaranteed to return a valid pointer; in case of memory allocation
 *      failure, its default behaviour is to abort.
 *
 * __NOTES__
 *      The {{cy_utf8_new()}} function works by allocating a {{cy_hptr_t}}
 *      buffer of the same size as {{src}} (along with one extra byte for the
 *      terminating null character) and copying the contents {{src}}  into it.
 */
cy_utf8_t *
cy_utf8_new(const char src[static 1])
{
        const size_t len = strlen(src);
        cy_utf8_t *ctx = cy_hptr_new(len + 1);

        strcpy(ctx, src);
        ctx[len] = '\0';

        return ctx;
}


/*
 * __NAME__
 *      cy_utf8_copy() - creates shallow copy of UTF-8 string
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/api.h>
 *
 *      extern CY_HOT CY_RSAFE cy_utf8_t *
 *      cy_utf8_copy(cy_utf8_t ctx[static 1]);
 *
 * __DESCRIPTION__
 *      The {{cy_utf8_copy()}} interface function creates a shallow copy of an
 *      existing instance of a {{cy_utf8_t}} UTF-8 string {{ctx}}. {{ctx}} is
 *      expected to be a valid pointer; if not a compiler diagnostic is issued.
 *      Although the value of {{ctx}} does not change, its internal reference
 *      count does; hence, {{ctx}} is not passed as a {{const}} parameter.
 *
 *      It is important to remember that shallow copies returned by
 *      {{cy_utf8_copy()}} should only be used as immutable values in order to
 *      prevent accidentally changing the original value (and other shallow
 *      copies). Be warned that there are no compile-time or runtime checks to
 *      ensure that the shallow copy is *not* used in a mutable context.
 *
 *      The benefit of using shallow copies is performance, since they do not
 *      involve any new allocation on the heap memory.
 *
 * __RETURN__
 *      {{cy_utf8_copy()}} returns a pointer to the {{ctx}} instance with its
 *      internal reference count state updated. This function is guaranteed to
 *      return a valid pointer.
 *
 * __NOTES__
 *      Since {{cy_utf8_t}} instances are allocated on the heap as {{cy_hptr_t}}
 *      instances, their internal reference count is managed through by the
 *      {{cy_hptr_copy()}} function.
 */
cy_utf8_t *
cy_utf8_copy(cy_utf8_t ctx[static 1])
{
        return cy_hptr_copy((cy_hptr_t *) ctx);
}


/*
 * __NAME__
 *      cy_utf8_clone() - creates deep copy of UTF-8 string
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/api.h>
 *
 *      extern CY_HOT CY_RSAFE cy_utf8_t *
 *      cy_utf8_clone(const cy_utf8_t ctx[static 1]);
 *
 * __DESCRIPTION__
 *      The {{cy_utf8_clone()}} function creates a deep copy of a {{cy_utf8_t}}
 *      instance {{ctx}}. {{ctx}} is expected to be a valid pointer to an
 *      existing {{cy_utf8_t}} instance; if not, then a compiler diagnostic will
 *      be issued.
 *
 *      The deep copy does not affect the reference count of {{ctx}} (as in the
 *      case of {{cy_utf8_copy()}}), and its own reference count is one. The
 *      deep copy contains the same data bytes as {{ctx}}. As a result, it is
 *      safe to use the deep copy as a mutable value. However, this flexibility
 *      comes at a performance cost since it entails memory allocation on the
 *      heap (unlike the case of {{cy_utf8_copy()}}).
 *
 * __RETURN__
 *      The {{cy_utf8_clone()}} function returns a pointer to a deep copy of
 *      {{ctx}}.  This function is guaranteed to return a valid pointer. In case
 *      of heap memory allocation failure, the default behaviour is to abort.
 *
 * __NOTES__
 *      Cloning {{ctx}} is a simple operation---we simply need to create a new
 *      {{cy_utf8_t}} instance on the heap through {{cy_utf8_new()}} with the
 *      same data as {{ctx}}.
 */
cy_utf8_t *
cy_utf8_clone(const cy_utf8_t ctx[static 1])
{
        return cy_utf8_new(ctx);
}


/*
 * __NAME__
 *      cy_utf8_free__() - releases UTF-8 string
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/api.h>
 *
 *      extern CY_HOT void
 *      cy_utf8_t_free__(cy_utf8_t *ctx[static 1]);
 *
 * __DESCRIPTION__
 *
 * __NOTES__
 */
void
cy_utf8_t_free__(cy_utf8_t *ctx[static 1])
{
        cy_hptr_free((cy_hptr_t **) ctx);
}


/* Comparator function */


/*
 * __NAME__
 *      cy_utf8_cmp() - compares two UTF-8 strings
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/api.h>
 *
 *      extern CY_HOT enum cy_cmp
 *      cy_utf8_cmp(const cy_utf8_t ctx[static 1],
 *                  const cy_utf8_t cmp[static 1]);
 *
 * __DESCRIPTION__
 *
 * __RETURN__
 *
 * __NOTES__
 */
enum cy_cmp
cy_utf8_cmp(const cy_utf8_t ctx[static 1], const cy_utf8_t cmp[static 1])
{
        int rc = utf8cmp(ctx, cmp);

        if (rc == 0)
                return CY_CMP_EQ;

        if (rc < 0)
                return CY_CMP_LT;
        else
                return CY_CMP_GT;
}


/* Accessor functions */


/*
 * __NAME__
 *      cy_utf8_empty() - checks if UTF-8 string is empty
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/api.h>
 *
 *      extern bool
 *      cy_utf8_empty(const cy_utf8_t ctx[static 1]);
 *
 * __DESCRIPTION__
 *
 * __RETURN__
 *
 * __NOTES__
 */
bool
cy_utf8_empty(const cy_utf8_t ctx[static 1])
{
        return !*ctx;
}


/*
 * __NAME__
 *      cy_utf8_len() - gets length of UTF-8 string
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/api.h>
 *
 *      extern size_t
 *      cy_utf8_len(const cy_utf8_t ctx[static 1]);
 *
 * __DESCRIPTION__
 *
 * __RETURN__
 *
 * __NOTES__
 */
size_t
cy_utf8_len(const cy_utf8_t ctx[static 1])
{
        return utf8len(ctx);
}


/*
 * __NAME__
 *      cy_utf8_refc() - gets reference count of UTF-8 string
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/api.h>
 *
 *      extern size_t
 *      cy_utf8_refc(const cy_utf8_t ctx[static 1]);
 *
 * __DESCRIPTION__
 *
 * __RETURN__
 *
 * __NOTES__
 */
size_t
cy_utf8_refc(const cy_utf8_t ctx[static 1])
{
        return cy_hptr_refc((const cy_hptr_t *) ctx);
}


/*
 * __NAME__
 *      cy_utf8_sz() - gets size of UTF-8 string
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/api.h>
 *
 *      extern size_t
 *      cy_utf8_sz(const cy_utf8_t ctx[static 1]);
 *
 * __DESCRIPTION__
 *
 * __RETURN__
 *
 * __NOTES__
 */
size_t
cy_utf8_sz(const cy_utf8_t ctx[static 1])
{
        return cy_hptr_sz((const cy_hptr_t *) ctx);
}


/*
 * __NAME__
 *      cy_utf8_match() - checks if UTF-8 string matches regex
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/api.h>
 *
 *      extern bool
 *      cy_utf8_match(const cy_utf8_t ctx[static 1],
 *                    const char regex[static 1]);
 *
 * __DESCRIPTION__
 *
 * __RETURN__
 *
 * __NOTES__
 */
bool
cy_utf8_match(const cy_utf8_t ctx[static 1], const char regex[static 1])
{
        if (CY_UNLIKELY(!*ctx || !*regex))
                return false;

        PCRE2_SPTR sub = (PCRE2_SPTR) ctx;
        PCRE2_SPTR pat = (PCRE2_SPTR) regex;

        int eno;
        PCRE2_SIZE eoff;
        pcre2_code *re = pcre2_compile(pat, PCRE2_ZERO_TERMINATED, PCRE2_UTF,
                                       &eno, &eoff, NULL);

        if (CY_UNLIKELY(!re)) {
               PCRE2_UCHAR bfr[256];
               pcre2_get_error_message(eno, bfr, sizeof (bfr));
               printf("PCRE2 compilation failed at offset %d: %s\n",
                      (int) eoff, bfr);

               abort();
        }

        pcre2_match_data *m = pcre2_match_data_create_from_pattern(re, NULL);
        int rc = pcre2_match(re, sub, strlen((char *) sub), 0, 0, m, NULL);

        pcre2_match_data_free(m);
        pcre2_code_free(re);

        if (rc > 0)
                return true;

        if (rc == PCRE2_ERROR_NOMATCH)
                return false;

        printf("PCRE2 matching error: %d\n", rc);
        abort();
}