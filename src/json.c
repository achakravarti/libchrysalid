/* Libchrysalid dependencies */
#include "../include/hptr.h"
#include "../include/json.h"

/* Standard library dependenices */
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


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


cy_json_t *
cy_json_copy(cy_json_t ctx[static 1])
{
       return cy_hptr_copy((cy_hptr_t *) ctx);
}


cy_json_t *
cy_json_clone(const cy_json_t ctx[static 1])
{
        CY_AUTO(cy_utf8_t) *str = cy_json_print(ctx, false);

        return cy_json_new(str);
}


void
cy_json_t_free__(cy_json_t *ctx[static 1])
{
        cJSON *j;

        if (ctx && (j = *ctx))
                cJSON_Delete(j);

        *ctx = NULL;
}


bool
cy_json_has(const cy_json_t ctx[static 1], const char key[static 1])
{
        return cJSON_HasObjectItem(ctx, key);
}


const cy_json_t *
cy_json_get(const cy_json_t ctx[static 1], const char key[static 1])
{
        if (CY_LIKELY(cJSON_HasObjectItem(ctx, key)))
                return cJSON_GetObjectItemCaseSensitive(ctx, key);

        printf("JSON key \"%s\" not found!\n", key);
        abort();
}


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


double
cy_json_number(const cy_json_t ctx[static 1])
{
        if (CY_LIKELY(cJSON_IsNumber(ctx)))
                return ctx->valuedouble;

        return NAN;
}


bool
cy_json_bool(const cy_json_t ctx[static 1])
{
        if (CY_LIKELY(cJSON_IsBool(ctx)))
                return cJSON_IsTrue(ctx);

        return false;
}


cy_utf8_t *
cy_json_print(const cy_json_t ctx[static 1], bool pretty)
{
        return cy_utf8_new(pretty
                           ? cJSON_Print(ctx) : cJSON_PrintUnformatted(ctx));
}


void
cy_json_map(const cy_json_t ctx[static 1], cy_json_itr_f *itr, void *opt)
{
        const cJSON *i;

        if (CY_LIKELY(cJSON_IsArray(ctx) && itr)) {
                cJSON_ArrayForEach(i, ctx)
                        itr(i, opt);
        }
}
