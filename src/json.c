/* Libchrysalid dependencies */
#include "../include/hptr.h"
#include "../include/json.h"

/* Standard library dependenices */
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


/*                                                             %func:cy_json_new
 * __NAME__
 *      {{cy_json_new()}} - creates new JSON node
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/libchrsalid.h>
 */
cy_json_t *
cy_json_new(const char src[static 1])
{
       cJSON *ctx = cJSON_Parse(src);

       if (CY_UNLIKELY (!ctx)) {
                ctx = cJSON_CreateNull();

                if (CY_UNLIKELY (!ctx)) {
                        printf("JSON parsing failed!\n");
                        abort();
                }
       }

       return ctx;
}


/*                                                            %func:cy_json_copy
 * __NAME__
 *      {{cy_json_copy()}} - creates shallow copy of JSON node
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/libchrsalid.h>
 */
cy_json_t *
cy_json_copy(cy_json_t ctx[static 1])
{
       return cy_hptr_copy((cy_hptr_t *) ctx);
}


/*                                                           %func:cy_json_clone
 * __NAME__
 *      {{cy_json_copy()}} - creates deep copy of JSON node
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/libchrsalid.h>
 */
cy_json_t *
cy_json_clone(const cy_json_t ctx[static 1])
{
        /* cppcheck-suppress AssignmentAddressToInteger */
        CY_AUTO(cy_utf8_t) *str = cy_json_print(ctx, false);

        return cy_json_new(str);
}


/*                                                          %func:cy_json_free__
 * __NAME__
 *      {{cy_json_free__()}} - releases JSON node
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/libchrsalid.h>
 */
void
cy_json_t_free__(cy_json_t *ctx[static 1])
{
        cJSON *j;

        if (ctx && (j = *ctx))
                cJSON_Delete(j);

        *ctx = NULL;
}


/*                                                             %func:cy_json_has
 * __NAME__
 *      {{cy_json_has()}} - checks if JSON node has key
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/libchrsalid.h>
 */
bool
cy_json_has(const cy_json_t ctx[static 1], const char key[static 1])
{
        return cJSON_HasObjectItem(ctx, key);
}


/*                                                             %func:cy_json_get
 * __NAME__
 *      {{cy_json_get()}} - gets JSON node by key
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/libchrsalid.h>
 */
const cy_json_t *
cy_json_get(const cy_json_t ctx[static 1], const char key[static 1])
{
        if (CY_LIKELY(cJSON_HasObjectItem(ctx, key)))
                return cJSON_GetObjectItemCaseSensitive(ctx, key);

        printf("JSON key \"%s\" not found!\n", key);
        abort();
}


/*                                                            %func:cy_json_type
 * __NAME__
 *      {{cy_json_get()}} - gets data type of JSON node
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/libchrsalid.h>
 */
enum cy_json_type
cy_json_type(const cy_json_t ctx[static 1])
{
        if (cJSON_IsArray(ctx))
            return CY_JSON_TYPE_ARRAY;

        if (cJSON_IsObject(ctx))
            return CY_JSON_TYPE_OBJECT;

        if (cJSON_IsString(ctx))
            return CY_JSON_TYPE_STRING;

        if (cJSON_IsNumber(ctx))
            return CY_JSON_TYPE_NUMBER;

        if (cJSON_IsBool(ctx))
            return CY_JSON_TYPE_BOOL;

        return CY_JSON_TYPE_NULL;
}


/*                                                          %func:cy_json_string
 * __NAME__
 *      {{cy_json_string()}} - casts JSON node to string
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/libchrsalid.h>
 */
cy_utf8_t *
cy_json_string(const cy_json_t ctx[static 1])
{
        if (CY_LIKELY(cJSON_IsString(ctx)))
                return cy_utf8_new(ctx->valuestring);

        if (cJSON_IsNull(ctx))
                return cy_utf8_new("(null)");

        if (cJSON_IsBool(ctx)) {
                if (cJSON_IsFalse(ctx))
                        return cy_utf8_new("false");

                return "true";
        }

        if (cJSON_IsNumber(ctx)) {
                // https://stackoverflow.com/questions/1701055/
                const size_t len = 3 + DBL_MANT_DIG - DBL_MIN_EXP;
                char bfr[len + 1];
                snprintf(bfr, len, "%f", ctx->valuedouble);
                return cy_utf8_new(bfr);
        }

        return cy_utf8_new(cJSON_Print(ctx));
}


/*                                                          %func:cy_json_number
 * __NAME__
 *      {{cy_json_number()}} - casts JSON node to number
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/libchrsalid.h>
 */
double
cy_json_number(const cy_json_t ctx[static 1])
{
        if (CY_LIKELY(cJSON_IsNumber(ctx)))
                return ctx->valuedouble;

        return NAN;
}


/*                                                            %func:cy_json_bool
 * __NAME__
 *      {{cy_json_bool()}} - casts JSON node to Boolean
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/libchrsalid.h>
 */
bool
cy_json_bool(const cy_json_t ctx[static 1])
{
        if (CY_LIKELY(cJSON_IsBool(ctx)))
                return cJSON_IsTrue(ctx);

        return false;
}


/*                                                           %func:cy_json_print
 * __NAME__
 *      {{cy_json_print()}} - prints JSON
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/libchrsalid.h>
 */
cy_utf8_t *
cy_json_print(const cy_json_t ctx[static 1], bool pretty)
{
        return cy_utf8_new(pretty
                           ? cJSON_Print(ctx) : cJSON_PrintUnformatted(ctx));
}


/*                                                           %func:cy_json_print
 * __NAME__
 *      {{cy_json_map()}} - maps iterator to JSON array node
 *
 * __SYNOPSIS__
 *      #include <libchrysalid/libchrsalid.h>
 */
void
cy_json_map(const cy_json_t ctx[static 1], cy_json_itr_f *itr, void *opt)
{
        const cJSON *i;

        if (CY_LIKELY(cJSON_IsArray(ctx) && itr)) {
                cJSON_ArrayForEach(i, ctx)
                        itr(i, opt);
        }
}
