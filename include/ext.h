/* Start header guard. */
#ifndef __LIBCHRYSALIS_INCLUDE_EXT_H_INCLUDED__
#define __LIBCHRYSALIS_INCLUDE_EXT_H_INCLUDED__


/* Open C++ compatibility wrapper. */
#ifdef __cplusplus
extern "C" {
#endif


/** [base:ext:nonull]
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
 *      - The `__attribute__((nonnull))` decorator optionally allows you to
 *        specify the 1-based index of the function parameters that are to be
 *        considered non-null; C_NONULL doesn't do this both for the sake of
 *        brevity and also because we consider null pointer parameters to be a
 *        code smell.
 *      - Clang allows the `__attribute__((nonnull))` decorator to be applied
 *        directly to a function parameter, but GCC does not. Therefore,
 *        C_NONULL may be used to mark specific function parameters when
 *        compiled with Clang; however, it is better not to do so in the
 *        interest of portability.
 *
 * SEE ALSO
 *      - web GCC (11.2.0:6.33.1)
 *        [https://gcc.gnu.org/onlinedocs/gcc-11.2.0/gcc
 *              /Common-Function-Attributes.html#Common-Function-Attributes]
 *      - web Clang (15.0.0)
 *        [https://clang.llvm.org/docs/AttributeReference.html]
 **/
#if (defined __GNUC__ || defined __clang__)
#       define C_NONULL __attribute__((nonnull))
#else
#       define C_NONULL
#       if !(defined C_SUPPRESS_EXTENSION_WARNINGS
#               warning "C_NONULL has no effect in current compiler"
#       endif
#endif


/** [base:ext:hot]
 * NAME
 *      C_HOT - hints a function as hot
 *
 * SYNOPSIS
 *      #include "libchrysalis/chrysalis.h"
 *
 *      #define C_HOT __attribute__((hot))
 *
 * DESCRIPTION
 *      The C_HOT macro is used to hint that a function is hot, i.e. it is
 *      called often. When C_HOT is applied to a function, the compiler _may_
 *      optimise it more aggressively, reordering the function so that it
 *      appears in a special section with other hot functions so as to improve
 *      locality.
 *
 *      This macro uses the non-standard `__attribute__((hot))` decorator, and
 *      is available for both GCC and Clang. On other compilers, the default
 *      behaviour of this macro is to degrade safely to a no-op with a suitable
 *      warning message. If you don't want this warning message to be displayed,
 *      then define the macro `C_SUPPRESS_EXTENSION_WARNINGS` at compile time.
 *
 * FILES
 *      C_HOT is defined in /usr/local/libchrysalis/include/ext.h.
 *
 * EXAMPLES
 *      C_HOT int foo(char *, int *);   // standard declaration
 *      void bar(float *) C_HOT;        // alternate declaration
 *     
 *      // can also be applied on definitions
 *      C_HOT static int foobar(char *foo, char c)
 *      {
 *              c = *foo;
 *              return (int) c;
 *      }
 *
 * NOTES
 *      - C_HOT is ignored by GCC if the `-fprofile-use` flag is used during
 *        compilation.
 *      - Although Clang recognises the `__attribute__((hot)) decorator, it
 *        drops it silently; however, there is a proposal to implement this.
 *
 * SEE ALSO
 *      - ref C_COLD
 *        [base:ext:cold]
 *      - web GCC (11.2.0:6.33.1)
 *        [https://gcc.gnu.org/onlinedocs/gcc-11.2.0/gcc
 *              /Common-Function-Attributes.html#Common-Function-Attributes]
 *      - web llvm-dev@lists.llvm.org
 *        [https://lists.llvm.org/pipermail/llvm-dev/2020-December/147104.html]
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

