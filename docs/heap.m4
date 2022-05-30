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
include(<<<build/docs/type_cy_hptr_t.md>>>)


# CONSTANTS
## Constant CY_HPTR_REFC_MAX
include(<<<build/docs/const_CY_HPTR_REFC_MAX.md>>>)

## Constant HEAD_INDEX
include(<<<build/docs/const_hptr_HEAD_INDEX.md>>>)

## Constant HEAD_OFFSET
include(<<<build/docs/const_hptr_HEAD_OFFSET.md>>>)

## Constant HEAD_SZ
include(<<<build/docs/const_hptr_HEAD_SZ.md>>>)

## Constant BODY_INDEX
include(<<<build/docs/const_hptr_BODY_INDEX.md>>>)


# MACROS
## Macro REFC_INIT()
include(<<<build/docs/macro_hptr_REFC_INIT.md>>>)

## Macro REFC_CURRENT()
include(<<<build/docs/macro_hptr_REFC_CURRENT.md>>>)

## Macro REFC_INCREMENT()
include(<<<build/docs/macro_hptr_REFC_INCREMENT.md>>>)

## Macro REFC_DECREMENT()
include(<<<build/docs/macro_hptr_REFC_DECREMENT.md>>>)

## Macro CAST_HEAD()
include(<<<build/docs/macro_hptr_CAST_HEAD.md>>>)

## Macro CAST_BODY()
include(<<<build/docs/macro_hptr_CAST_BODY.md>>>)

## Macro ALIGN_VALID()
include(<<<build/docs/macro_hptr_ALIGN_VALID.md>>>)


# FUNCTIONS


# TEST


__COPYRIGHT__


__COLOPHON__


__CITATIONS__
