#include "../include/hptr.h"
#include "../include/utf8.h"


/* Factory functions  */


cy_utf8_t *
cy_utf8_new(const char src[static 1])
{

}


cy_utf8_t *
cy_utf8_copy(cy_utf8_t ctx[static 1])
{

}


cy_utf8_t *
cy_utf8_clone(const cy_utf8_t ctx[static 1])
{

}


void
cy_utf8_free(cy_utf8_t *ctx[static 1])
{

}


/* Comparator function */


enum cy_cmp
cy_utf8_cmp(const cy_utf8_t ctx[static 1], const cy_utf8_t cmp[static 1])
{

}


/* Accessor functions */

size_t
cy_utf8_len(const cy_utf8_t ctx[static 1])
{

}


size_t
cy_utf8_refc(const cy_utf8_t ctx[static 1])
{

}


bool
cy_utf8_match(const cy_utf8_t ctx[static 1])
{

}
