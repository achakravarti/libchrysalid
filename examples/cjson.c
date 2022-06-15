#include "../include/utf8.h"
#include "../external/cJSON/cJSON.h"
#include <stdio.h>
#include <stdlib.h>


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


static cJSON *
json_new(void)
{
       cJSON *ctx = cJSON_Parse(sample);

       if (!ctx) {
                printf("JSON parsing failed!\n");
                abort();
        }

       return ctx;
}


static void
json_free(cJSON **ctx)
{
        cJSON *j;

        if (ctx && (j = *ctx))
                cJSON_Delete(j);

        *ctx = NULL;
}


static cy_utf8_t *
json_print(cJSON *ctx, bool pretty)
{
        return cy_utf8_new(pretty
                           ? cJSON_Print(ctx)
                           : cJSON_PrintUnformatted(ctx));
}


int main(int argc, char *argv[static 1])
{
        (void) argc;
        (void) argv;

        cJSON *j = json_new();


        CY_AUTO(cy_utf8_t) *pretty = json_print(j, true);
        printf("%s\n", pretty);

        CY_AUTO(cy_utf8_t) *raw = json_print(j, false);
        printf("%s\n", raw);

        json_free(&j);
        return EXIT_SUCCESS;
}
