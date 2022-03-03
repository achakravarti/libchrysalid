/* Start header guard. */
#ifndef __LIBCHRYSALIS_INCLUDE_EXT_H_INCLUDED__
#define __LIBCHRYSALIS_INCLUDE_EXT_H_INCLUDED__


/* Open C++ compatibility wrapper. */
#ifdef __cplusplus
extern "C" {
#endif


/**
 * NAME
 *      C_NONULL - hints a function has no null parameters
 *
 * SYNOPSIS
 *      #include "libchrysalis/chrysalis.h"
 *
 *      #define C_NONULL __attribute__((nonull))
 *
 * DESCRIPTION
 *      The C_NONULL macro indicates that _all_ pointer parameters of a function
 *      are required to be non-null. A warning is issued if a null pointer is
 *      passed to any of the parameters of such a function. This macro has no
 *      effect on non-pointer parameters, and so must be used to decorate
 *      functions with at least one pointer parameter. A warning is issued if
 *      this macro is used to decorate a function without any pointer
 *      parameters.
 *
 *      This macro uses the non-standard `__attribute__((nonnull))` decorator,
 *      and is available for both GCC and Clang. On other compilers, the default
 *      behaviour of this macro is to degrade safely to a no-op with a suitable
 *      warning message. If you don't want this warning message to be displayed,
 *      then define the macro `C_SUPPRESS_EXTENSION_WARNINGS` at compile time.
 *
 * FILES
 *      C_NONULL is defined in /usr/local/libchrysalis/include/ext.h.
 *
 * EXAMPLES
 *      C_NONULL int foo(char *, int *);    // standard declaration
 *      void bar(float *) C_NONULL;         // alternate declaration
 *     
 *      // can also be applied on definitions
 *      C_NONULL static int foobar(char *foo, char c)
 *      {
 *              c = *foo;
 *              return (int) c;
 *      }
 *
 * NOTES
 *      1. The `__attribute__((nonnull))` decorator optionally allows you to
 *         specify the 1-based index of the function parameters that are to be
 *         considered non-null; C_NONULL doesn't do this both for the sake of
 *         brevity and also because we consider null pointer parameters to be a
 *         code smell.
 *
 * SEE ALSO
 *      - web GCC (11.2.0:6.33.1)[https://gcc.gnu.org/onlinedocs/gcc-11.2.0/...
 *          /gcc/Common-Function-Attributes.html#Common-Function-Attributes]
 **/
#if (defined __GNUC__ || defined __clang__)
#       define C_NONULL __attribute__((nonnull))
#else
#       define C_NONULL
#       if !(defined C_SUPPRESS_EXTENSION_WARNINGS
#               warning "C_NONULL has no effect in current compiler"
#       endif
#endif

/**
 ** ^ C_HOT: Marks a function as hot.
 **/
#define C_HOT __attribute__((hot))

/**
 ** ^ C_COLD: Marks a function as cold.
 **/
#define C_COLD __attribute__((cold))

/**
 ** ^ C_PURE: Marks a variable as pure.
 **/
#define C_PURE __attribute__((pure))

/**
 ** ^ C_TLOCAL: Marks a variable as thread local.
 **/
#define C_TLOCAL __thread


/**
 ** ^ C_AUTO(): Marks an automatic heap pointer.
 ** > _T_: Pointer type.
 **/
#define C_AUTO(_T_) __attribute__((cleanup(_T_##_free))) _T_


/**
 ** ^ C_LIKEY(): Marks predicate as likely to be true.
 ** > _P_: Boolean predicate to evaluate.
 **/
#define C_LIKELY(_P_) __builtin_expect(!!(_P_), 1)


/**
 ** ^ C_UNLIKEY(): Marks predicate as unlikely to be true.
 ** > _P_: Boolean predicate to evaluate.
 **/
#define C_UNLIKELY(_P_) __builtin_expect(!!(_P_), 0)


/* Close C++ compatibility wrapper. */
#ifdef __cplusplus
}
#endif

/* Close header guard. */
#endif  /* !__LIBCHRYSALIS_INCLUDE_EXT_H_INCLUDED__ */

