#include "../include/cfg.h"

#include "../external/iniparser/src/iniparser.h"


struct cy_cfg__ {
        cy_utf8_t       *path;
        dictionary      *hnd;
};


cy_cfg_t *
cy_cfg_new(const char *path)
{

}


cy_cfg_t *
cy_cfg_copy(cy_cfg_t *ctx)
{

}


cy_cfg_t *
cy_cfg_clone(const cy_cfg_t *ctx)
{

}


void
cy_cfg_free__(cy_cfg_t **ctx)
{

}



bool
cy_cfg_bool(const cy_cfg_t *ctx)
{

}


long
cy_cfg_int(const cy_cfg_t *ctx)
{

}


double
cy_cfg_flt(const cy_cfg_t *ctx)
{

}


const char *
cy_cfg_str(const cy_cfg_t *ctx)
{

}


cy_utf8_t *
cy_cfg_print(const cy_cfg_t *ctx)
{

}
