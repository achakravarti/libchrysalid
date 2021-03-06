/* Header guard */
#ifndef __LIBCHRYSALID_INCLUDE_JSON_H__
#define __LIBCHRYSALID_INCLUDE_JSON_H__

/* Libchrysalid dependencies */
#include "ext.h"
#include "utf8.h"

/* Third-party external dependencies */
#include "../external/cJSON/cJSON.h"

/* Standard library dependencies */
#include <stdint.h>

/* C++ compatiblity */
#ifdef __cplusplus
extern "C" {
#endif


/* Types */


/*                                                               %type:cy_json_t
 * __NAME__
 *      {{cy_json_t}} - JSON node
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/libchrsalid.h>
 */
typedef cJSON cy_json_t;


/*                                                            %type:cy_json_type
 * __NAME__
 *      {{cy_json_type}} - enumerates JSON data types
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/libchrsalid.h>
 */
enum cy_json_type {
        CY_JSON_TYPE_NULL,
        CY_JSON_TYPE_BOOL,
        CY_JSON_TYPE_NUMBER,
        CY_JSON_TYPE_STRING,
        CY_JSON_TYPE_OBJECT,
        CY_JSON_TYPE_ARRAY
};


/*                                                           %type:cy_json_itr_f
 * __NAME__
 *      {{cy_json_itr_f}} - iterator for JSON arrays
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/libchrsalid.h>
 */
typedef void (cy_json_itr_f)(const cy_json_t [static 1], void *);


/* Prototypes for factory functions */
extern CY_HOT CY_RSAFE cy_json_t    *cy_json_new(const char [static 1]);
extern CY_HOT CY_RSAFE cy_json_t    *cy_json_copy(cy_json_t [static 1]);
extern CY_HOT CY_RSAFE cy_json_t    *cy_json_clone(const cy_json_t [static 1]);
extern CY_HOT void                   cy_json_t_free__(cy_json_t *[static 1]);


/*                                                           %macro:cy_json_free
 * __NAME__
 *      {{cy_json_free()}} - releases JSON node
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/libchrsalid.h>
 */
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
#endif /* !__LIBCHRYSALID_INCLUDE_JSON_H__ */
