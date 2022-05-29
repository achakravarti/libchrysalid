include(`macros.m4')


ifdef(<<<MAN>>>,
<<<
% LIBCHRYSALID:HEAP(3) libchrysalid 0.0.1
%
% 2022
>>>)


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
