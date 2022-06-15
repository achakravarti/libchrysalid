#include "../external/cJSON/cJSON.h"
#include <stdlib.h>


const char *example = "{"
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


int main(int argc, char *argv[static 1])
{
        (void) argc;
        (void) argv;

        return EXIT_SUCCESS;
}
