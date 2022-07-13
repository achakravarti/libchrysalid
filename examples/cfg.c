#include "../include/cfg.h"

#include <stdio.h>
#include <stdlib.h>


int main(void)
{
        CY_AUTO(cy_cfg_t) *c = cy_cfg_new("examples/test.ini");

        CY_AUTO(cy_utf8_t) *s = cy_cfg_print(c);
        printf("INI FILE\n\n%s\n", s);

        printf("foo:bool_val = %d\n", cy_cfg_bool(c, "foo:bool_val"));
        printf("foo:int_val = %ld\n", cy_cfg_int(c, "foo:int_val"));
        printf("foo:flt_val = %f\n", cy_cfg_flt(c, "foo:flt_val"));
        printf("foo:str_val = %s\n", cy_cfg_str(c, "foo:str_val"));

        printf("bar:bool_val = %d\n", cy_cfg_bool(c, "bar:bool_val"));
        printf("bar:int_val = %ld\n", cy_cfg_int(c, "bar:int_val"));
        printf("bar:flt_val = %f\n", cy_cfg_flt(c, "bar:flt_val"));
        printf("bar:str_val = %s\n", cy_cfg_str(c, "bar:str_val"));

        return EXIT_SUCCESS;
}
