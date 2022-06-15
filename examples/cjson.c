#include "../include/utf8.h"
#include "../external/cJSON/cJSON.h"
#include <stdio.h>
#include <stdlib.h>


typedef void cy_json_t;


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
json_has(cJSON *ctx, const char *item)
{
        return cJSON_HasObjectItem(ctx, item);
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

        printf("%d\n", json_has(j, "resolution"));

        return EXIT_SUCCESS;
}
