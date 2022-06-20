/* Libchrysalid dependencies */
#include "../include/cfg.h"

/* External dependencies */
#include "../external/iniparser/src/iniparser.h"

/* Standard library dependencies */
#include <assert.h>


struct cy_cfg__ {
        cy_utf8_t       *path;
        dictionary      *hnd;
};


cy_cfg_t *
cy_cfg_new(const char *path)
{
        assert(path);
        assert(*path);
}


cy_cfg_t *
cy_cfg_copy(cy_cfg_t *ctx)
{
        assert(ctx);
}


cy_cfg_t *
cy_cfg_clone(const cy_cfg_t *ctx)
{
        assert(ctx);
}


void
cy_cfg_free__(cy_cfg_t **ctx)
{
}



bool
cy_cfg_bool(const cy_cfg_t *ctx)
{
        assert(ctx);
}


long
cy_cfg_int(const cy_cfg_t *ctx)
{
        assert(ctx);
}


double
cy_cfg_flt(const cy_cfg_t *ctx)
{
        assert(ctx);
}


const char *
cy_cfg_str(const cy_cfg_t *ctx)
{
        assert(ctx);
}


cy_utf8_t *
cy_cfg_print(const cy_cfg_t *ctx)
{
        assert(ctx);
}
