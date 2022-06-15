#include "../include/utf8.h"
#include "../external/cJSON/cJSON.h"
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


typedef void cy_json_t;

enum cy_json_type {
        CY_JSON_TYPE_NULL,
        CY_JSON_TYPE_BOOL,
        CY_JSON_TYPE_NUMBER,
        CY_JSON_TYPE_STRING,
        CY_JSON_TYPE_OBJECT,
        CY_JSON_TYPE_ARRAY
};

static const cJSON *NULL_JSON = NULL;

const char *sample = "{"
          "\"name\": \"Awesome 4K\","
          "\"resolutions\": ["
          "  {"
          "    \"width\": 1280,"
          "    \"height\": 720"
          "  },"
          "  {"
          "    \"width\": 1920,"
          "    \"height\": 1080"
          "  },"
          "  {"
          "  \"width\": 3840,"
          "  \"height\": 2160"
          "  }"
          "]"
        "}";


cy_json_t *
cy_json_new(const char *src)
{
       cJSON *ctx = cJSON_Parse(src);

       if (CY_UNLIKELY (!ctx)) {
                ctx = cJSON_Parse("\"null\": null");

                if (CY_UNLIKELY (!ctx)) {
                        printf("JSON parsing failed!\n");
                        abort();
                }
       }

       return ctx;
}


void
cy_json_t_free__(cy_json_t **ctx)
{
        cJSON *j;

        if (ctx && (j = *ctx))
                cJSON_Delete(j);

        *ctx = NULL;
}


static cy_utf8_t *
cy_json_print(const cy_json_t *ctx, bool pretty)
{
        const cJSON *j = (cJSON *) ctx;

        return cy_utf8_new(pretty ? cJSON_Print(j) : cJSON_PrintUnformatted(j));
}


static bool
cy_json_has(const cy_json_t *ctx, const char *key)
{
        return cJSON_HasObjectItem((cJSON *) ctx, key);
}


static const cy_json_t *
cy_json_node(const cy_json_t *ctx, const char *key)
{
        const cJSON *j = (cJSON *) ctx;

        if (CY_LIKELY (cJSON_HasObjectItem(j, key)))
                return cJSON_GetObjectItemCaseSensitive(j, key);

        printf("Node not found!\n");
        abort();
}


static enum cy_json_type
cy_json_type(const cy_json_t *ctx)
{
        const cJSON *j = (cJSON *) ctx;

        if (cJSON_IsArray(j))
            return CY_JSON_TYPE_ARRAY;

        if (cJSON_IsObject(j))
            return CY_JSON_TYPE_OBJECT;

        if (cJSON_IsString(j))
            return CY_JSON_TYPE_STRING;

        if (cJSON_IsNumber(j))
            return CY_JSON_TYPE_NUMBER;

        if (cJSON_IsBool(j))
            return CY_JSON_TYPE_BOOL;

        return CY_JSON_TYPE_NULL;
}

cy_utf8_t *
cy_json_string(const cy_json_t *ctx)
{
        const cJSON *j = (cJSON *) ctx;

        if (CY_LIKELY(cJSON_IsString(j)))
                return cy_utf8_new(j->valuestring);

        if (cJSON_IsNull(j))
                return cy_utf8_new("(null)");

        if (cJSON_IsBool(j)) {
                if (cJSON_IsFalse(j))
                        return cy_utf8_new("false");

                return "true";
        }

        if (cJSON_IsNumber(j)) {
                // https://stackoverflow.com/questions/1701055/
                const size_t len = 3 + DBL_MANT_DIG - DBL_MIN_EXP;
                char bfr[len + 1];
                snprintf(bfr, len, "%f", j->valuedouble);
                return cy_utf8_new(bfr);
        }

        return cy_utf8_new(cJSON_Print(j));
}

double
cy_json_number(const cy_json_t *ctx)
{
        const cJSON *j = (cJSON *) ctx;

        if (CY_LIKELY(cJSON_IsNumber(j)))
                return j->valuedouble;

        return NAN;
}


bool
cy_json_bool(const cy_json_t *ctx)
{
        const cJSON *j = (cJSON *) ctx;

        if (CY_LIKELY(cJSON_IsBool(j)))
                return cJSON_IsTrue(j);

        return false;
}


int main(int argc, char *argv[static 1])
{
        (void) argc;
        (void) argv;

        CY_AUTO(cy_json_t) *j = cy_json_new(sample);

        CY_AUTO(cy_utf8_t) *pretty = cy_json_print(j, true);
        printf("%s\n", pretty);

        CY_AUTO(cy_utf8_t) *raw = cy_json_print(j, false);
        printf("%s\n", raw);

        printf("Node exists: %d\n", cy_json_has(j, "resolution"));

        const cy_json_t *name = cy_json_node(j, "name");
        const cy_json_t *res = cy_json_node(j, "resolutions");

        printf("Root type: %d\n", cy_json_type(j));
        printf("name type: %d\n", cy_json_type(name));
        printf("res  type: %d\n", cy_json_type(res));

        CY_AUTO(cy_utf8_t) *root_s = cy_json_string(j);
        CY_AUTO(cy_utf8_t) *name_s = cy_json_string(name);
        CY_AUTO(cy_utf8_t) *res_s = cy_json_string(res);

        printf("Root string: %s\n", root_s);
        printf("name string: %s\n", name_s);
        printf("res  string: %s\n", res_s);

        printf("Root number: %f\n", cy_json_number(j));
        printf("name number: %f\n", cy_json_number(name));
        printf("res  number: %f\n", cy_json_number(res));

        printf("Root bool: %d\n", cy_json_bool(j));
        printf("name bool: %d\n", cy_json_bool(name));
        printf("res  bool: %d\n", cy_json_bool(res));

        return EXIT_SUCCESS;
}
