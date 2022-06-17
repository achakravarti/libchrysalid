#include "../include/utf8.h"
#include "../include/json.h"
#include <float.h>
#include <math.h>
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


void
mymap(const cy_json_t *ctx, void *opt)
{
        (void) opt;

        printf("MAPPING...\n");

        /* cppcheck-suppress AssignmentAddressToInteger */
        CY_AUTO(cy_utf8_t) * str = cy_json_print(ctx, true);
        printf("%s\n", str);
}


int main(int argc, char *argv[static 1])
{
        (void) argc;
        (void) argv;

        CY_AUTO(cy_json_t) *j = cy_json_new(sample);

        /* cppcheck-suppress AssignmentAddressToInteger */
        CY_AUTO(cy_utf8_t) *pretty = cy_json_print(j, true);
        printf("%s\n", pretty);

        /* cppcheck-suppress AssignmentAddressToInteger */
        CY_AUTO(cy_utf8_t) *raw = cy_json_print(j, false);
        printf("%s\n", raw);

        printf("Node exists: %d\n", cy_json_has(j, "resolution"));

        const cy_json_t *name = cy_json_get(j, "name");
        const cy_json_t *res = cy_json_get(j, "resolutions");

        printf("Root type: %d\n", cy_json_type(j));
        printf("name type: %d\n", cy_json_type(name));
        printf("res  type: %d\n", cy_json_type(res));

        /* cppcheck-suppress AssignmentAddressToInteger */
        CY_AUTO(cy_utf8_t) *root_s = cy_json_string(j);
        /* cppcheck-suppress AssignmentAddressToInteger */
        CY_AUTO(cy_utf8_t) *name_s = cy_json_string(name);
        /* cppcheck-suppress AssignmentAddressToInteger */
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

        cJSON *n = cJSON_CreateNull();
        printf("%s\n", cy_json_print(n, true));
        printf("%d\n", cy_json_type(n));

        cy_json_map(res, mymap, NULL);

        return EXIT_SUCCESS;
}
