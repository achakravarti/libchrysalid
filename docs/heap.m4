include(`macros.m4')


ifdef(<<<MAN>>>,
<<<
% LIBCHRYSALID:HPTR(3) libchrysalid 0.0.1
%
% 2022


# NAME
hptr - heap pointer interface


# SYNOPSIS
```
#include <libchrysalid/api.h>

typedef uintptr_t cy_hptr_t;

#define CY_HPTR_REFC_MAX UINTPTR_MAX;

extern CY_HOT CY_RSAFE void *cy_hptr_new(size_t);
extern CY_HOT CY_RSAFE void *cy_hptr_new_aligned(size_t, size_t);
extern CY_HOT CY_RSAFE void *cy_hptr_copy(cy_hptr_t [static 1]);
extern CY_HOT void           cy_hptr_free(cy_hptr_t *[static 1]);

extern bool          cy_hptr_aligned(const cy_hptr_t [static 1], size_t);
extern size_t        cy_hptr_refc(const cy_hptr_t [static 1]);
extern size_t        cy_hptr_sz(const cy_hptr_t [static 1]);
extern const char   *cy_hptr_str(const cy_hptr_t [static 1]);
```


# DESCRIPTION
The *Heap Pointer* interface of *libchrysalid* allows common operations related
to to the allocation and release of heap memory to be conveniently managed by
client code. The interface provides the `cy_hptr_t` type to abstract a block of
heap memory, and the interface functions are built around this type.

This document is meant to be comprehensive; hence documentation for both the
interface and its implementation are provided. The interface documentation is
meant for both users and maintainers of `libchrysalid`, whereas the
implementation documentation is only meant for the latter.

The interface documentation is covered in the following sections:

  - **PUBLIC TYPES**
  - **PUBLIC CONSTANTS**
  - **PUBLIC FUNCTIONS**

The implementation-specific documentation is provided in the following sections:

  - **FILES**
  - **SUPPORTING TYPES**
  - **PRIIVATE CONSTANTS**
  - **MACROS**
  - **SUPPORTING FUNCTIONS**
  - **TEST CASES**
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


# PUBLIC TYPES

dnl Interface types
__type__(<<<cy_hptr_t>>>, <<<cy_hptr_t>>>)


# SUPPORTING TYPES

dnl Test types
__type__(<<<test_t>>>, <<<hptr_test_t>>>)


dnl Interface constants
# PUBLIC CONSTANTS

__const__(<<<CY_HPTR_REFC_MAX>>>, <<<CY_HPTR_REFC_MAX>>>)


dnl Implementation constants
# PRIVATE CONSTANTS

__const__(<<<HEAD_INDEX>>>, <<<hptr_HEAD_INDEX>>>)
__const__(<<<HEAD_OFFSET>>>, <<<hptr_HEAD_OFFSET>>>)
__const__(<<<HEAD_SZ>>>, <<<hptr_HEAD_SZ>>>)
__const__(<<<BODY_INDEX>>>, <<<hptr_BODY_INDEX>>>)


# MACROS

dnl Implementation macros
__macro__(<<<REFC_INIT>>>, <<<hptr_REFC_INIT>>>)
__macro__(<<<REFC_CURRENT>>>, <<<hptr_REFC_CURRENT>>>)
__macro__(<<<REFC_INCREMENT>>>, <<<hptr_REFC_INCREMENT>>>)
__macro__(<<<REFC_DECREMENT>>>, <<<hptr_REFC_DECREMENT>>>)
__macro__(<<<CAST_HEAD>>>, <<<hptr_CAST_HEAD>>>)
__macro__(<<<CAST_BODY>>>, <<<hptr_CAST_BODY>>>)
__macro__(<<<ALIGN_VALID>>>, <<<hptr_ALIGN_VALID>>>)


# PUBLIC FUNCTIONS

dnl Factory functions
__func__(<<<cy_hptr_new>>>, <<<cy_hptr_new>>>)
__func__(<<<cy_hptr_new_aligned>>>, <<<cy_hptr_new_aligned>>>)
__func__(<<<cy_hptr_copy>>>, <<<cy_hptr_copy>>>)
__func__(<<<cy_hptr_free>>>, <<<cy_hptr_free>>>)

dnl Accessor functions
__func__(<<<cy_hptr_aligned>>>, <<<cy_hptr_aligned>>>)
__func__(<<<cy_hptr_refc>>>, <<<cy_hptr_refc>>>)
__func__(<<<cy_hptr_sz>>>, <<<cy_hptr_sz>>>)
__func__(<<<cy_hptr_str>>>, <<<cy_hptr_str>>>)


# SUPPORTING FUNCTIONS

dnl Support functions
__func__(<<<align_fix>>>, <<<hptr_align_fix>>>)
__func__(<<<test_t_free>>>, <<<hptr_test_t_free>>>)
__func__(<<<test_yeq>>>, <<<hptr_test_yeq>>>)


# TEST CASES

dnl Tests for cy_hptr_new()
__test_num_reset__
__test__(<<<cy_hptr_new>>>, <<<positive_size>>>, __test_num__)
__test__(<<<cy_hptr_new>>>, <<<zero_size>>>, __test_num__)
__test__(<<<cy_hptr_new>>>, <<<negative_size>>>, __test_num__)

dnl Tests for cy_hptr_new_aligned()
__test_num_reset__
__test__(<<<cy_hptr_new_aligned>>>, <<<valid_params>>>, __test_num__)
__test__(<<<cy_hptr_new_aligned>>>, <<<zero_sz>>>, __test_num__)
__test__(<<<cy_hptr_new_aligned>>>, <<<zero_alignment>>>, __test_num__)
__test__(<<<cy_hptr_new_aligned>>>, <<<negative_alignment>>>, __test_num__)

dnl Tests for cy_hptr_copy()
__test_num_reset__
__test__(<<<cy_hptr_copy>>>, <<<single>>>, __test_num__)
__test__(<<<cy_hptr_copy>>>, <<<single_aligned>>>, __test_num__)
__test__(<<<cy_hptr_copy>>>, <<<multiple>>>, __test_num__)
__test__(<<<cy_hptr_copy>>>, <<<multiple_aligned>>>, __test_num__)

dnl Tests for cy_hptr_free()
__test_num_reset__
__test__(<<<cy_hptr_free>>>, <<<hnd_to_null_ptr>>>, __test_num__)
__test__(<<<cy_hptr_free>>>, <<<single>>>, __test_num__)
__test__(<<<cy_hptr_free>>>, <<<copies_preserved>>>, __test_num__)
__test__(<<<cy_hptr_free>>>, <<<copies_all_release>>>, __test_num__)
__test__(<<<cy_hptr_free>>>, <<<single_aligned>>>, __test_num__)
__test__(<<<cy_hptr_free>>>, <<<copies_preserved>>>, __test_num__)
__test__(<<<cy_hptr_free>>>, <<<copies_all_release>>>, __test_num__)

dnl Tests for cy_hptr_aligned()
__test_num_reset__
__test__(<<<cy_hptr_aligned>>>, <<<true_valid>>>, __test_num__)
__test__(<<<cy_hptr_aligned>>>, <<<false_valid>>>, __test_num__)
__test__(<<<cy_hptr_aligned>>>, <<<false_invalid>>>, __test_num__)

dnl Tests for cy_hptr_str()
__test_num_reset__
__test__(<<<cy_hptr_str>>>, <<<desc>>>, __test_num__)


__COPYRIGHT__


__COLOPHON__


__CITATIONS__
