/* Header guard */
#ifndef __LIBCHRYSALID_INCLUDE_UTF8_H__
#define __LIBCHRYSALID_INCLUDE_UTF8_H__

/* Libchrysalid dependencies */
#include "cmp.h"
#include "ext.h"

/* Standard library dependencies */
#include <stdbool.h>
#include <stddef.h>


/* C++ compatiblity */
#ifdef __cplusplus
extern "C" {
#endif


/*
 * __NAME__
 *      {{cy_utf8_t}} - UTF-8 string
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/api.h>
 *      typedef char cy_utf8_t;
 *
 * __DESCRIPTION__
 *
 * __NOTES__
 */
typedef char    cy_utf8_t;


/* Prototypes for factory functions  */
extern CY_HOT CY_RSAFE cy_utf8_t    *cy_utf8_new(const char[static 1]);
extern CY_HOT CY_RSAFE cy_utf8_t    *cy_utf8_copy(cy_utf8_t[static 1]);
extern CY_HOT CY_RSAFE cy_utf8_t    *cy_utf8_clone(const cy_utf8_t[static 1]);
extern CY_HOT void                   cy_utf8_t_free__(cy_utf8_t *[static 1]);


/*
 * __NAME__
 *      {{cy_utf8_new_empty()}} - creates a new empty UTF-8 string
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/api.h>
 *      #define cy_utf8_new_empty() cy_utf8_new("");
 *
 * __DESCRIPTION__
 *
 * __NOTES__
 */
#define cy_utf8_new_empty()     cy_utf8_new("");


/*
 * __NAME__
 *      {{cy_utf8_free()}} - releases a UTF-8 string instance
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/api.h>
 *      #define cy_utf8_free(ctx) cy_utf8_t_free__(ctx)
 *
 * __DESCRIPTION__
 *
 * __NOTES__
 */
#define cy_utf8_free(ctx)   cy_utf8_t_free__(ctx)


/* Prototype for comparator function  */
extern CY_HOT enum cy_cmp   cy_utf8_cmp(const cy_utf8_t[static 1],
                                        const cy_utf8_t[static 1]);


/*
 * __NAME__
 *      {{cy_utf8_lt()}} - checks if a UTF-8 string is lexicographically lower
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/api.h>
 *      #define cy_utf8_lt(lhs, rhs) (cy_utf8_cmp(lhs, rhs) == CY_CMP_LT)
 *
 * __DESCRIPTION__
 *
 * __NOTES__
 */
#define cy_utf8_lt(lhs, rhs)    (cy_utf8_cmp(lhs, rhs) == CY_CMP_LT)


/*
 * __NAME__
 *      {{cy_utf8_eq()}} - checks if a UTF-8 string is lexicographically equal
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/api.h>
 *      #define cy_utf8_gt(lhs, rhs) (cy_utf8_cmp(lhs, rhs) == CY_CMP_EQ)
 *
 * __DESCRIPTION__
 *
 * __NOTES__
 */
#define cy_utf8_eq(lhs, rhs)    (cy_utf8_cmp(lhs, rhs) == CY_CMP_EQ)


/*
 * __NAME__
 *      {{cy_utf8_gt()}} - checks if a UTF-8 string is lexicographically higher
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/api.h>
 *      #define cy_utf8_gt(lhs, rhs) (cy_utf8_cmp(lhs, rhs) == CY_CMP_GT)
 *
 * __DESCRIPTION__
 *
 * __NOTES__
 */
#define cy_utf8_gt(lhs, rhs)    (cy_utf8_cmp(lhs, rhs) == CY_CMP_GT)


/* Prototypes for accessor functions  */
extern bool     cy_utf8_empty(const cy_utf8_t[static 1]);
extern size_t   cy_utf8_len(const cy_utf8_t[static 1]);
extern size_t   cy_utf8_refc(const cy_utf8_t[static 1]);
extern size_t   cy_utf8_sz(const cy_utf8_t[static 1]);
extern bool     cy_utf8_match(const cy_utf8_t[static 1], const char[static 1]);


/* C++ compatibility */
#ifdef __cplusplus
}
#endif


/* Header guard */
#endif
