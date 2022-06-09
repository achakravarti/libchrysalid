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
 *      cy_utf8_new() -
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/api.h>
 *
 *      extern CY_HOT CY_RSAFE cy_utf8_t *
 *      cy_utf8_new(const char src[static 1]);
 *
 * __DESCRIPTION__
 *
 * __RETURN__
 *
 * __NOTES__
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
 *      cy_utf8_copy() -
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/api.h>
 *
 *      extern CY_HOT CY_RSAFE cy_utf8_t *
 *      cy_utf8_copy(cy_utf8_t ctx[static 1]);
 *
 * __DESCRIPTION__
 *
 * __RETURN__
 *
 * __NOTES__
 */
cy_utf8_t *
cy_utf8_copy(cy_utf8_t ctx[static 1])
{
        return cy_hptr_copy((cy_hptr_t *) ctx);
}


/*
 * __NAME__
 *      cy_utf8_clone() -
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/api.h>
 *
 *      extern CY_HOT CY_RSAFE cy_utf8_t *
 *      cy_utf8_clone(const cy_utf8_t ctx[static 1]);
 *
 * __DESCRIPTION__
 *
 * __RETURN__
 *
 * __NOTES__
 */
cy_utf8_t *
cy_utf8_clone(const cy_utf8_t ctx[static 1])
{
        return cy_utf8_new(ctx);
}


/*
 * __NAME__
 *      cy_utf8_free__() -
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/api.h>
 *
 *      extern CY_HOT void
 *      cy_utf8_t_free__(cy_utf8_t *ctx[static 1]);
 *
 * __DESCRIPTION__
 *
 * __RETURN__
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
 *      cy_utf8_cmp() -
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
 *      cy_utf8_empty() -
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
 *      cy_utf8_len() -
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
 *      cy_utf8_refc() -
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
 *      cy_utf8_sz() -
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
 *      cy_utf8_match() -
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
