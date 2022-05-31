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


## Constant CY_HPTR_REFC_MAX

__NAME__(<<<CY_HPTR_REFC_MAX>>>)
: include(<<<const_CY_HPTR_REFC_MAX.name>>>)

__SYNOPSIS__(<<<CY_HPTR_REFC_MAX>>>)
: include(<<<const_CY_HPTR_REFC_MAX.synopsis>>>)

__DESCRIPTION__(<<<CY_HPTR_REFC_MAX>>>)
: include(<<<const_CY_HPTR_REFC_MAX.description>>>)

__NOTES__(<<<CY_HPTR_REFC_MAX>>>)
: include(<<<const_CY_HPTR_REFC_MAX.notes>>>)


## Constant HEAD_INDEX

__NAME__(<<<HPTR_HEAD_INDEX>>>)
: include(<<<build/docs/const_hptr_HEAD_INDEX.name>>>)

__SYNOPSIS__(<<<HPTR_HEAD_INDEX>>>)
: include(<<<build/docs/const_hptr_HEAD_INDEX.synopsis>>>)

__DESCRIPTION__(<<<HPTR_HEAD_INDEX>>>)
: include(<<<build/docs/const_hptr_HEAD_INDEX.description>>>)

__NOTES__(<<<HPTR_HEAD_INDEX>>>)
: include(<<<build/docs/const_hptr_HEAD_INDEX.notes>>>)


## Constant HEAD_OFFSET

__NAME__(<<<HPTR_HEAD_OFFSET>>>)
: include(<<<build/docs/const_hptr_HEAD_OFFSET.name>>>)

__SYNOPSIS__(<<<HPTR_HEAD_OFFSET>>>)
: include(<<<build/docs/const_hptr_HEAD_OFFSET.synopsis>>>)

__DESCRIPTION__(<<<HPTR_HEAD_OFFSET>>>)
: include(<<<build/docs/const_hptr_HEAD_OFFSET.description>>>)

__NOTES__(<<<HPTR_HEAD_OFFSET>>>)
: include(<<<build/docs/const_hptr_HEAD_OFFSET.notes>>>)


## Constant HEAD_SZ

__NAME__(<<<HPTR_HEAD_SZ>>>)
: include(<<<build/docs/const_hptr_HEAD_SZ.name>>>)

__SYNOPSIS__(<<<HPTR_HEAD_SZ>>>)
: include(<<<build/docs/const_hptr_HEAD_SZ.synopsis>>>)

__DESCRIPTION__(<<<HPTR_HEAD_SZ>>>)
: include(<<<build/docs/const_hptr_HEAD_SZ.description>>>)

__NOTES__(<<<HPTR_HEAD_SZ>>>)
: include(<<<build/docs/const_hptr_HEAD_SZ.notes>>>)


## Constant BODY_INDEX

__NAME__(<<<HPTR_BODY_INDEX>>>)
: include(<<<build/docs/const_hptr_BODY_INDEX.name>>>)

__SYNOPSIS__(<<<HPTR_BODY_INDEX>>>)
: include(<<<build/docs/const_hptr_BODY_INDEX.synopsis>>>)

__DESCRIPTION__(<<<HPTR_BODY_INDEX>>>)
: include(<<<build/docs/const_hptr_BODY_INDEX.description>>>)

__NOTES__(<<<HPTR_BODY_INDEX>>>)
: include(<<<build/docs/const_hptr_BODY_INDEX.notes>>>)


# MACROS
## Macro REFC_INIT()

__NAME__(<<<HPTR_REFC_INIT>>>)
: include(<<<build/docs/macro_hptr_REFC_INIT.name>>>)

__SYNOPSIS__(<<<HPTR_REFC_INIT>>>)
: include(<<<build/docs/macro_hptr_REFC_INIT.synopsis>>>)

__DESCRIPTION__(<<<HPTR_REFC_INIT>>>)
: include(<<<build/docs/macro_hptr_REFC_INIT.description>>>)

__NOTES__(<<<HPTR_REFC_INIT>>>)
: include(<<<build/docs/macro_hptr_REFC_INIT.notes>>>)


## Macro REFC_CURRENT()

__NAME__(<<<HPTR_REFC_CURRENT>>>)
: include(<<<build/docs/macro_hptr_REFC_CURRENT.name>>>)

__SYNOPSIS__(<<<HPTR_REFC_INIT>>>)
: include(<<<build/docs/macro_hptr_REFC_CURRENT.synopsis>>>)

__DESCRIPTION__(<<<HPTR_REFC_INIT>>>)
: include(<<<build/docs/macro_hptr_REFC_CURRENT.description>>>)

__NOTES__(<<<HPTR_REFC_INIT>>>)
: include(<<<build/docs/macro_hptr_REFC_CURRENT.notes>>>)


## Macro REFC_INCREMENT()

__NAME__(<<<HPTR_REFC_INCREMENT>>>)
: include(<<<build/docs/macro_hptr_REFC_INCREMENT.name>>>)

__SYNOPSIS__(<<<HPTR_REFC_INCREMENT>>>)
: include(<<<build/docs/macro_hptr_REFC_INCREMENT.synopsis>>>)

__DESCRIPTION__(<<<HPTR_REFC_INCREMENT>>>)
: include(<<<build/docs/macro_hptr_REFC_INCREMENT.description>>>)

__NOTES__(<<<HPTR_REFC_INCREMENT>>>)
: include(<<<build/docs/macro_hptr_REFC_INCREMENT.notes>>>)


## Macro REFC_DECREMENT()

__NAME__(<<<HPTR_REFC_CURRENT>>>)
: include(<<<build/docs/macro_hptr_REFC_DECREMENT.name>>>)

__SYNOPSIS__(<<<HPTR_REFC_INIT>>>)
: include(<<<build/docs/macro_hptr_REFC_DECREMENT.synopsis>>>)

__DESCRIPTION__(<<<HPTR_REFC_INIT>>>)
: include(<<<build/docs/macro_hptr_REFC_DECREMENT.description>>>)

__NOTES__(<<<HPTR_REFC_INIT>>>)
: include(<<<build/docs/macro_hptr_REFC_DECREMENT.notes>>>)


## Macro CAST_HEAD()

__NAME__(<<<HPTR_REFC_CURRENT>>>)
: include(<<<build/docs/macro_hptr_CAST_HEAD.name>>>)

__SYNOPSIS__(<<<HPTR_REFC_INIT>>>)
: include(<<<build/docs/macro_hptr_CAST_HEAD.synopsis>>>)

__DESCRIPTION__(<<<HPTR_REFC_INIT>>>)
: include(<<<build/docs/macro_hptr_CAST_HEAD.description>>>)

__NOTES__(<<<HPTR_REFC_INIT>>>)
: include(<<<build/docs/macro_hptr_CAST_HEAD.notes>>>)


## Macro CAST_BODY()

__NAME__(<<<HPTR_REFC_CURRENT>>>)
: include(<<<build/docs/macro_hptr_CAST_BODY.name>>>)

__SYNOPSIS__(<<<HPTR_REFC_INIT>>>)
: include(<<<build/docs/macro_hptr_CAST_BODY.synopsis>>>)

__DESCRIPTION__(<<<HPTR_REFC_INIT>>>)
: include(<<<build/docs/macro_hptr_CAST_BODY.description>>>)

__NOTES__(<<<HPTR_REFC_INIT>>>)
: include(<<<build/docs/macro_hptr_CAST_BODY.notes>>>)


## Macro ALIGN_VALID()

__NAME__(<<<HPTR_REFC_CURRENT>>>)
: include(<<<build/docs/macro_hptr_ALIGN_VALID.name>>>)

__SYNOPSIS__(<<<HPTR_REFC_INIT>>>)
: include(<<<build/docs/macro_hptr_ALIGN_VALID.synopsis>>>)

__DESCRIPTION__(<<<HPTR_REFC_INIT>>>)
: include(<<<build/docs/macro_hptr_ALIGN_VALID.description>>>)

__NOTES__(<<<HPTR_REFC_INIT>>>)
: include(<<<build/docs/macro_hptr_ALIGN_VALID.notes>>>)


# FUNCTIONS


# TEST


__COPYRIGHT__


__COLOPHON__


__CITATIONS__
