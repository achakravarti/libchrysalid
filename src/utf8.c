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
 *      The {{cy_utf8_t_free__()}} function is responsible for releasing the
 *      heap memory allocated to a {{cy_utf8_t}} instance {{ctx}}. This is an
 *      implementation-specific function and is **not** part of the UTF-8
 *      interface.
 *
 * __NOTES__
 *      The implementation of {{cy_utf8_t_free__()}} is quite straightforward
 *      since we only need to pass a pointer to {{ctx}} to {{cy_hptr_free()}}.
 *      This function is required to be named in this unusual manner so that it
 *      can be invoked by the {{CY_AUTO()}} macro.
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
 *      The {{cyt_utf8_cmp()}} function compares a {{cy_utf8_t}} UTF-8 string
 *      instance {{ctx}} with another instance {{cmp}} in order determine
 *      determine for lexicographical order of the former relative to the
 *      latter. This comparison is case-sensitive, with lowercase glyphs being
 *      considered higher than their uppercase equivalents (where applicable).
 *
 *      Both {{ctx}} and {{cmp}} are required to be valid pointers to
 *      {{cy_utf8_t}} string instances; if not, then a compiler diagnostic is
 *      issued.
 *
 * __RETURN__
 *      The {{cy_utf8_cmp()}} function returns one of the following {{CY_CMP}}
 *      enumerators:
 *
 *        - {{CY_CMP_LT}} if {{ctx}} is lexicographically lower than {{cmp}}
 *        - {{CY_CMP_EQ}} if {{ctx}} is lexicographically equal to {{cmp}}
 *        - {{CY_CMP_GT}} if {{ctx}} is lexicographically greater than {{cmp}}
 *
 * __NOTES__
 *      The actual comparison is performed by the {{utf8cmp()}} function of the
 *      external *utf8.h* single header library. The source code for this
 *      library is available locally in the *external/utf8.h/utf8.h* file.
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
 *      The {{cy_utf8_empty()}} function checks whether a given {{cy_utf8_t}}
 *      string instance {{ctx}} is an empty string. {{ctx}} is expected to be
 *      a valid pointer to a {{cy_utf8_t}} instance; if not, then a compiler
 *      diagnostic is issued.
 *
 * __RETURN__
 *      The {{cy_utf8_empty()}} function returns one of the following Boolean
 *      values:
 *
 *        - {{true}} if {{ctx}} is an empty string
 *        - {{false}} if {{ctx}} is not an empty string
 *
 * __NOTES__
 *      The implementationi of {{cy_utf8_empty()}} is straightforward, with it
 *      just checking whether or not the first character of {{ctx}} is the null
 *      character {{\0}}.
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
 *      The {{cy_utf8_len()}} function computes the lexicographic length of a
 *      given {{cy_utf8_t}} string instance {{ctx}}. {{ctx}} is expected to be a
 *      valid pointer to an existing instance; if not, then a compiler
 *      diagnostic is issued.
 *
 * __RETURN__
 *      {{cy_utf8_len()}} returns 0 for an empty string, or else a positive
 *      integer that is the lexicographic length of {{ctx}} (excluding the
 *      trailing null character {{'\0'}}).
 *
 * __NOTES__
 *      The {{cy_utf8_len()}} function internally uses the {{utf8len()}}
 *      function of the external *utf8.h* library. The source code for this
 *      function can be found in the *external/utf8.h/utf8.h* header file.
 *
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
 *      The {{cy_utf8_refc()}} function computes the current reference count for
 *      a given {{cy_utf8_t}} instance {{ctx}}. {{ctx}} is required to be a
 *      valid pointer to an existing {{cy_utf8_t}} instance; if not, then a
 *      compiler diagnostic is issued.
 *
 * __RETURN__
 *      This function returns the current reference count of {{ctx}}, and is
 *      guaranteed to be an integer >= 1. If {{ctx}} is an original copy (or a
 *      deep copy), {{cy_utf8_refc()}} returns 1. If {{ctx}} is a shallow copy,
 *      then {{cy_utf8_refc()}} returns a value > 1 indicating the total number
 *      of copies (including the original) currently in existence.
 *
 * __NOTES__
 *      {{cy_utf8_len()}} internallyy uses the {{cy_hptr_refc()}} function to
 *      determine the reference count of {{ctx}}. See *libchrysalid:hptr(3)* for
 *      more details on how {{cy_hptr_refc()}} works.
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
 *      The {{cy_utf8_sz()}} computes the size in bytes of the amount of heap
 *      memory allocated to a {{cy_utf8_t}} instance {{ctx}}. {{ctx}} must be a
 *      valid pointer to a {{cy_utf8_t}} instance; if not, a compiler diagnostic
 *      is issued.
 *
 * __RETURN__
 *      The {{cy_utf8_sz()}} function returns the total allocated size of
 *      {{ctx}}, taking into consideration metadata and alignment
 *      considerations. As a consequence, the size returned by {{cy_utf8_sz()}}
 *      is guaranteed to be greater than the sum of the sizes of the component
 *      UTF-8 glyphs stored in {{{ctx}}}.
 *
 * __NOTES__
 *      The {{cy_utf8_sz()}} function internally works simply as a wrapper
 *      around the {{cy_hptr_sz()}} function. See libchrysalid:hptr(3) for more
 *      details on the implementation of {{cy_hptr_sz()}}.
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
 *      The {{cy_utf8_match()}} function checks whether a given {{cy_utf8_t}}
 *      string instance matches a given UTF-8 regular expression {{regex}}. Both
 *      {{{ctx}} and {{regex}} are required to be valid pointers to instances of
 *      {{cy_utf8_t}}; if not, then a compiler diagnostic is issued. In case of
 *      a regular expression processing exception, the default behaviour of this
 *      function is to abort.
 *
 * __RETURN__
 *      The {{cy_utf8_match()}} function is guaranteed to return either one of
 *      the Boolean values {{true}} / {{false}} depending on whether or not
 *      {{ctx}} matches the regular expression pattern {{regex}}. This function
 *      always returns {{false}} if either {{{ctx}} or {{{regex}} is an empty
 *      string.
 *
 * __NOTES__
 *      The matching functionality provided by {{cy_utf8_match()}} is implemented
 *      through the PCRE2 Library, adapting the demo code available at
 *      *https://www.pcre.org/current/doc/html/pcre2demo.html*. The demo code is
 *      documented extensively, and referring to it will make the implementation
 *      of {{cy_utf8_match()}} obvious.
 *
 *      Since we need to support UTF-8 strings, we must use the UTF-8 version
 *      for the PCRE2 Library. This is achieved with the following steps:
 *
 *        1. defining the {{PCRE2_CODE_UNIT_WIDTH}} macro as **8** before
 *           including the *<pcre2.h>* header file,
 *        2. passing the {{PCRE2_UTF}} option to {{pcre2_compile()}}, and
 *        3. linking with the *-lpcre2-8* build flag.
 *
 *      Note that by ensuring we return {{false}} if either {{ctx}} or {{regex}}
 *      is an empty string, we avoid raising an exception from the PCRE2 engine.
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
               fprintf(stderr, "PCRE2 compilation failed at offset %d: %s\n",
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
