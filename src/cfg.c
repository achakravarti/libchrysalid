/* Libchrysalid dependencies */
#include "../include/cfg.h"
#include "../include/hptr.h"

/* External dependencies */
#include "../external/iniparser/src/iniparser.h"

/* Standard library dependencies */
#include <assert.h>
#include <stdio.h>
#include <malloc.h>


struct cy_cfg__ {
        cy_utf8_t   *path;
        dictionary  *hnd;
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
                fprintf(stderr, "Failed to load config file \"%s\"!\n", path);
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
cy_cfg_t_free__(cy_cfg_t **ctx)
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
cy_cfg_bool(const cy_cfg_t *ctx, const char *key)
{
        assert(ctx);
        assert(key);
        assert(*key);

        return iniparser_getboolean(ctx->hnd, key, 0);
}


long
cy_cfg_int(const cy_cfg_t *ctx, const char *key)
{
        assert(ctx);
        assert(key);
        assert(*key);

        return iniparser_getlongint(ctx->hnd, key, 0);
}


double
cy_cfg_flt(const cy_cfg_t *ctx, const char *key)
{
        assert(ctx);
        assert(key);
        assert(*key);

        return iniparser_getdouble(ctx->hnd, key, 0.0);
}


const char *
cy_cfg_str(const cy_cfg_t *ctx, const char *key)
{
        assert(ctx);

        return iniparser_getstring(ctx->hnd, key, "");
}


cy_utf8_t *
cy_cfg_print(const cy_cfg_t *ctx)
{
        assert(ctx);

        /* https://stackoverflow.com/questions/3747086/ */

        FILE *f = fopen(ctx->path, "rb");

        if (CY_UNLIKELY(!f)) {
                fputs("Failed to open configuration file!\n", stderr);
                abort();
        }

        fseek(f, 0, SEEK_END);
        long sz = ftell(f);
        rewind(f);

        char *bfr = calloc(1, sz + 1);

        if (CY_UNLIKELY(!bfr)) {
                fclose(f);
                fputs("Failed to allocate memory for buffer!\n", stderr);
                abort();
        }

        if (CY_UNLIKELY(fread(bfr, sz, 1, f) != 1)) {
                fclose(f);
                fputs("Failed to read entire file to buffer!\n", stderr);
                abort();
        }

        cy_utf8_t *s = cy_utf8_new(bfr);
        fclose(f);
        free(bfr);

        return s;
}
