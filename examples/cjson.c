#include "../include/utf8.h"
#include "../external/cJSON/cJSON.h"
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


static cy_json_t *
cy_json_new(void)
{
       cJSON *ctx = cJSON_Parse(sample);

       if (!ctx) {
                printf("JSON parsing failed!\n");
                abort();
        }

       return ctx;
}


static void
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
        return cy_utf8_new(pretty
                           ? cJSON_Print(ctx)
                           : cJSON_PrintUnformatted(ctx));
}


static bool
cy_json_has(const cy_json_t *ctx, const char *key)
{
        return cJSON_HasObjectItem(ctx, key);
}


static const cy_json_t *
cy_json_node(const cy_json_t *ctx, const char *key)
{
        if (cJSON_HasObjectItem(ctx, key))
                return cJSON_GetObjectItemCaseSensitive(ctx, key);

        printf("Node not found!\n");
        abort();
}


static enum cy_json_type
cy_json_type(const cy_json_t *ctx)
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

int main(int argc, char *argv[static 1])
{
        (void) argc;
        (void) argv;

        CY_AUTO(cy_json_t) *j = cy_json_new();

        CY_AUTO(cy_utf8_t) *pretty = cy_json_print(j, true);
        printf("%s\n", pretty);

        CY_AUTO(cy_utf8_t) *raw = cy_json_print(j, false);
        printf("%s\n", raw);

        printf("Node exists: %d\n", cy_json_has(j, "resolution"));

        const cy_json_t *name = cy_json_node(j, "name");
        const cy_json_t *res = cy_json_node(j, "resolutions");

        printf("Root type: %d\n", cy_json_type(j));
        printf("name type: %d\n", cy_json_type(name));
        printf("res type: %d\n", cy_json_type(res));

        return EXIT_SUCCESS;
}
