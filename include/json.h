/* Header guard */
#ifndef __LIBCHRYSALID_INCLUDE_JSON_H__
#define __LIBCHRYSALID_INCLUDE_JSON_H__


/* Libchrysalid dependencies */
#include "ext.h"
#include "utf8.h"


/* C++ compatiblity */
#ifdef __cplusplus
extern "C" {
#endif


typedef void cy_json_t;

enum cy_json_type {
        CY_JSON_TYPE_NULL,
        CY_JSON_TYPE_BOOL,
        CY_JSON_TYPE_NUMBER,
        CY_JSON_TYPE_STRING,
        CY_JSON_TYPE_OBJECT,
        CY_JSON_TYPE_ARRAY
};


typedef void (cy_json_itr_f)(const cy_json_t *, void *);


cy_json_t *cy_json_new(const char *src);


void cy_json_t_free__(cy_json_t **ctx);


cy_utf8_t *cy_json_print(const cy_json_t *ctx, bool pretty);


bool cy_json_has(const cy_json_t *ctx, const char *key);


const cy_json_t *cy_json_node(const cy_json_t *ctx, const char *key);


enum cy_json_type cy_json_type(const cy_json_t *ctx);

cy_utf8_t *cy_json_string(const cy_json_t *ctx);

double cy_json_number(const cy_json_t *ctx);


bool cy_json_bool(const cy_json_t *ctx);


void cy_json_map(const cy_json_t *ctx, cy_json_itr_f *itr, void *opt);


/* C++ compatibility */
#ifdef __cplusplus
}
#endif


/* Header guard */
#endif
