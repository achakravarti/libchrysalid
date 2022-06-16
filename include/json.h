/* Header guard */
#ifndef __LIBCHRYSALID_INCLUDE_JSON_H__
#define __LIBCHRYSALID_INCLUDE_JSON_H__


/* Libchrysalid dependencies */
#include "ext.h"
#include "utf8.h"

/* Standard library dependencies */
#include <stdint.h>


/* C++ compatiblity */
#ifdef __cplusplus
extern "C" {
#endif


typedef uintptr_t cy_json_t;

enum cy_json_type {
        CY_JSON_TYPE_NULL,
        CY_JSON_TYPE_BOOL,
        CY_JSON_TYPE_NUMBER,
        CY_JSON_TYPE_STRING,
        CY_JSON_TYPE_OBJECT,
        CY_JSON_TYPE_ARRAY
};


typedef void (cy_json_itr_f)(const cy_json_t [static 1], void *);


/* Prototypes for factory functions */
extern CY_HOT CY_RSAFE cy_json_t    *cy_json_new(const char [static 1]);
extern CY_HOT CY_RSAFE cy_json_t    *cy_json_copy(const cy_json_t [static 1]);
extern CY_HOT CY_RSAFE cy_json_t    *cy_json_clone(const cy_json_t [static 1]);
extern CY_HOT void                   cy_json_t_free__(cy_json_t *[static 1]);

#define cy_json_free(ctx)   cy_json_t_free__(ctx)


/* Prototypes for accessor functions */
extern bool                          cy_json_has(const cy_json_t [static 1],
                                                 const char [static 1]);
extern CY_RSAFE const cy_json_t     *cy_json_get(const cy_json_t [static 1],
                                                 const char [static 1]);
extern enum cy_json_type             cy_json_type(const cy_json_t [static 1]);
extern CY_RSAFE cy_utf8_t           *cy_json_string(const cy_json_t [static 1]);
extern double                        cy_json_number(const cy_json_t [static 1]);
extern bool                          cy_json_bool(const cy_json_t [static 1]);
extern CY_RSAFE cy_utf8_t           *cy_json_print(const cy_json_t [static 1],
                                                   bool);
extern void                          cy_json_map(const cy_json_t [static 1],
                                                 cy_json_itr_f *, void *);


/* C++ compatibility */
#ifdef __cplusplus
}
#endif


/* Header guard */
#endif
