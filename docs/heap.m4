include(`macros.m4')


ifdef(<<<MAN>>>,
<<<
% LIBCHRYSALID:HPTR(3) libchrysalid 0.0.1
%
% 2022


# NAME
hptr - heap pointer component


# SYNOPSIS
```
#include <libchrysalid/api.h>
```


# DESCRIPTION
TODO
>>>)


_FILES_(<<<hptr>>>)

| *libchrysalid/include/hptr.h*
| */usr/local/include/libchrysalid/hptr.h*
|        Heap pointer interface.

| *libchrysalid/src/hptr.c*
| */usr/local/src/libchrysalid/hptr.c*
|        Heap pointer implementation.

| *libchrysalid/tests/hptr.c*
| */usr/local/local/src/libchrysalid/tests/hptr.c*
|        Heap pointer tests.

| *libchrysalid/docs/heap.m4*
| */usr/local/share/doc/libchrysalid/hptr.m4*
|        Heap pointer `m4` documentation template.

| *libchrysalid/build/docs/man/heap.md*
| */usr/local/share/doc/libchrysalid/hptr.m4*
|        Generated markdown documentation for man page.

| */usr/local/share/man/man3/libchrysalid:heap.3.gz*
|        __SWITCHMX__(<<<Man page documentation (this page).>>>,
<<<Man page documnetation.>>>)


# TYPES

__type__(<<<cy_hptr_t>>>, <<<cy_hptr_t>>>)

__type__(<<<test_t>>>, <<<hptr_test_t>>>)


# CONSTANTS

__const__(<<<CY_HPTR_REFC_MAX>>>, <<<CY_HPTR_REFC_MAX>>>)

__const__(<<<HEAD_INDEX>>>, <<<hptr_HEAD_INDEX>>>)

__const__(<<<HEAD_OFFSET>>>, <<<hptr_HEAD_OFFSET>>>)

__const__(<<<HEAD_SZ>>>, <<<hptr_HEAD_SZ>>>)

__const__(<<<BODY_INDEX>>>, <<<hptr_BODY_INDEX>>>)


# MACROS

__macro__(<<<REFC_INIT>>>, <<<hptr_REFC_INIT>>>)

__macro__(<<<REFC_CURRENT>>>, <<<hptr_REFC_CURRENT>>>)

__macro__(<<<REFC_INCREMENT>>>, <<<hptr_REFC_INCREMENT>>>)

__macro__(<<<REFC_DECREMENT>>>, <<<hptr_REFC_DECREMENT>>>)

__macro__(<<<CAST_HEAD>>>, <<<hptr_CAST_HEAD>>>)

__macro__(<<<CAST_BODY>>>, <<<hptr_CAST_BODY>>>)

__macro__(<<<ALIGN_VALID>>>, <<<hptr_ALIGN_VALID>>>)


# FUNCTIONS

__func__(<<<cy_hptr_new>>>, <<<cy_hptr_new>>>)

__func__(<<<cy_hptr_new_aligned>>>, <<<cy_hptr_new_aligned>>>)

__func__(<<<cy_hptr_copy>>>, <<<cy_hptr_copy>>>)

__func__(<<<cy_hptr_free>>>, <<<cy_hptr_free>>>)

__func__(<<<cy_hptr_aligned>>>, <<<cy_hptr_aligned>>>)

__func__(<<<cy_hptr_refc>>>, <<<cy_hptr_refc>>>)

__func__(<<<cy_hptr_sz>>>, <<<cy_hptr_sz>>>)

__func__(<<<cy_hptr_str>>>, <<<cy_hptr_str>>>)


# TESTS

__test__(<<<cy_hptr_new>>>, <<<cy_hptr_new_positive_size>>>)


__COPYRIGHT__


__COLOPHON__


__CITATIONS__
