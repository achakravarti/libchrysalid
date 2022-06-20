/* Header guard */
#ifndef __LIBCHRYSALID_INCLUDE_CFG_H__
#define __LIBCHRYSALID_INCLUDE_CFG_H__


#include "utf8.h"



/* C++ compatiblity */
#ifdef __cplusplus
extern "C" {
#endif


/* Types */

typedef struct cy_cfg__     cy_cfg_t;


/* Prototypes for factory functions */
extern cy_cfg_t *cy_cfg_new(const char *);
extern cy_cfg_t *cy_cfg_copy(cy_cfg_t *);
extern cy_cfg_t *cy_cfg_clone(const cy_cfg_t *);
extern void cy_cfg_free__(cy_cfg_t **);

#define cy_cfg_free(ctx) cy_cfg_free__(ctx)

/* Prototypes for accessor functions */
bool cy_cfg_bool(const cy_cfg_t *);
long cy_cfg_int(const cy_cfg_t *);
double cy_cfg_flt(const cy_cfg_t *t);
const char *cy_cfg_str(const cy_cfg_t *);

extern cy_utf8_t *cy_cfg_print(const cy_cfg_t *);


/* C++ compatibility */
#ifdef __cplusplus
}
#endif


/* Header guard */
#endif /* !__LIBCHRYSALID_INCLUDE_CFG_H__ */
