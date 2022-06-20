/* Libchrysalid dependencies */
#include "../include/cfg.h"
#include "../include/hptr.h"

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

        cy_cfg_t *ctx = cy_hptr_new(sizeof *ctx);
        ctx->path = cy_utf8_new(path);
        ctx->hnd = iniparser_load(path);

        if (CY_UNLIKELY(!ctx->hnd)) {
                printf("Failed to load config file \"%s\"!\n", path);
                abort();
        }

        return ctx;
}


cy_cfg_t *
cy_cfg_copy(cy_cfg_t *ctx)
{
        assert(ctx);

        return cy_hptr_copy((cy_hptr_t *) ctx);
}


cy_cfg_t *
cy_cfg_clone(const cy_cfg_t *ctx)
{
        assert(ctx);

        return cy_cfg_new(ctx->path);
}


void
cy_cfg_free__(cy_cfg_t **ctx)
{
        cy_cfg_t *c;

        if (CY_LIKELY(ctx && (c = *ctx))) {
                if (cy_hptr_refc((cy_hptr_t *) c) == 1) {
                        cy_utf8_free(&c->path);

                        if (CY_LIKELY(c->hnd))
                                iniparser_freedict(c->hnd);
                }
        }

        cy_hptr_free((cy_hptr_t **) ctx);
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
