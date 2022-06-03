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


typedef char cy_utf8_t;


/* Prototypes for factory functions  */
extern cy_utf8_t *cy_utf8_new(const char *);
extern cy_utf8_t *cy_utf8_copy(const cy_utf8_t *);
extern cy_utf8_t *cy_utf8_clone(const cy_utf8_t *);
extern void cy_utf8_free(cy_utf8_t **);


/* Prototype for comparator function  */
extern enum cy_cmp cy_utf8_cmp(const cy_utf8_t *, const cy_utf8_t *);


/* Prototypes for accessor functions  */
extern size_t cy_utf8_len(const cy_utf8_t *);
extern bool cy_utf8_match(const cy_utf8_t *);


#define cy_utf8_lt(lhs, rhs) (cy_utf8_cmp(lhs, rhs) == CY_CMP_LT)


#define cy_utf8_eq(lhs, rhs) (cy_utf8_cmp(lhs, rhs) == CY_CMP_EQ)


#define cy_utf8_gt(lhs, rhs) (cy_utf8_cmp(lhs, rhs) == CY_CMP_GT)


/* C++ compatibility */
#ifdef __cplusplus
}
#endif


/* Header guard */
#endif
