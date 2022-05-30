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


## Type cy_hptr_t

__NAME__(<<<cy_hptr_t>>>)
: include(<<<build/docs/type_cy_hptr_t.name>>>)

__SYNOPSIS__(<<<cy_hptr_t>>>)
: include(<<<build/docs/type_cy_hptr_t.synopsis>>>)

__DESCRIPTION__(<<<cy_hptr_t>>>)
: include(<<<build/docs/type_cy_hptr_t.description>>>)

__NOTES__(<<<cy_hptr_t>>>)
: include(<<<build/docs/type_cy_hptr_t.notes>>>)


## Type test_t

__NAME__(<<<test_t>>>)
: include(<<<build/docs/type_hptr_test_t.name>>>)

__SYNOPSIS__(<<<test_t>>>)
: include(<<<build/docs/type_hptr_test_t.synopsis>>>)

__DESCRIPTION__(<<<cy_hptr_t>>>)
: include(<<<build/docs/type_hptr_test_t.description>>>)


# CONSTANTS


## Constant CY_HPTR_REFC_MAX

__NAME__(<<<CY_HPTR_REFC_MAX>>>)
: include(<<<build/docs/const_CY_HPTR_REFC_MAX.name>>>)

__SYNOPSIS__(<<<CY_HPTR_REFC_MAX>>>)
: include(<<<build/docs/const_CY_HPTR_REFC_MAX.synopsis>>>)

__DESCRIPTION__(<<<CY_HPTR_REFC_MAX>>>)
: include(<<<build/docs/const_CY_HPTR_REFC_MAX.description>>>)

__NOTES__(<<<CY_HPTR_REFC_MAX>>>)
: include(<<<build/docs/const_CY_HPTR_REFC_MAX.notes>>>)


## Constant HEAD_INDEX
dnl include(<<<build/docs/const_hptr_HEAD_INDEX.md>>>)

## Constant HEAD_OFFSET
dnl include(<<<build/docs/const_hptr_HEAD_OFFSET.md>>>)

## Constant HEAD_SZ
dnl include(<<<build/docs/const_hptr_HEAD_SZ.md>>>)

## Constant BODY_INDEX
dnl include(<<<build/docs/const_hptr_BODY_INDEX.md>>>)


# MACROS
## Macro REFC_INIT()
dnl include(<<<build/docs/macro_hptr_REFC_INIT.md>>>)

## Macro REFC_CURRENT()
dnl include(<<<build/docs/macro_hptr_REFC_CURRENT.md>>>)

## Macro REFC_INCREMENT()
dnl include(<<<build/docs/macro_hptr_REFC_INCREMENT.md>>>)

## Macro REFC_DECREMENT()
dnl include(<<<build/docs/macro_hptr_REFC_DECREMENT.md>>>)

## Macro CAST_HEAD()
dnl include(<<<build/docs/macro_hptr_CAST_HEAD.md>>>)

## Macro CAST_BODY()
dnl include(<<<build/docs/macro_hptr_CAST_BODY.md>>>)

## Macro ALIGN_VALID()
dnl include(<<<build/docs/macro_hptr_ALIGN_VALID.md>>>)


# FUNCTIONS


# TEST


__COPYRIGHT__


__COLOPHON__


__CITATIONS__
