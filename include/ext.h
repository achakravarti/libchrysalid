/* Start header guard. */
#ifndef __LIBCHRYSALIS_INCLUDE_EXT_H_INCLUDED__
#define __LIBCHRYSALIS_INCLUDE_EXT_H_INCLUDED__


/* Open C++ compatibility wrapper. */
#ifdef __cplusplus
extern "C" {
#endif


/** [base:ext:psafe]
 * NAME
 *      C_PSAFE - hints a function has no null parameters
 *
 * SYNOPSIS
 *      #include "libchrysalis/chrysalis.h"
 *
 *      #define C_PSAFE __attribute__((nonull))
 *
 * DESCRIPTION
 *      The `C_PSAFE` macro indicates that _all_ pointer parameters of a
 *      function are required to be non-null. A warning is issued if a null
 *      pointer is passed to any of the parameters of such a function. This
 *      macro has no effect on non-pointer parameters, and so must be used to
 *      decorate functions with at least one pointer parameter. A warning is
 *      issued if this macro is used to decorate a function without any pointer
 *      parameters.
 *
 *      This macro uses the non-standard `__attribute__((nonnull))` decorator,
 *      and is available for both GCC and Clang. On other compilers, the default
 *      behaviour of this macro is to degrade safely to a no-op with a suitable
 *      warning message. If you don't want this warning message to be displayed,
 *      then define the macro `C_SUPPRESS_EXTENSION_WARNINGS` at compile time.
 *
 * FILES
 *      `C_PSAFE` is defined in /usr/local/libchrysalis/include/ext.h.
 *
 * EXAMPLES
 *      C_PSAFE int foo(char *, int *);     // standard declaration
 *      void bar(float *) C_PSAFE;          // alternate declaration
 *     
 *      // can also be applied on definitions
 *      C_PSAFE static int foobar(char *foo, char c)
 *      {
 *              c = *foo;
 *              return (int) c;
 *      }
 *
 * NOTES
 *      - The `__attribute__((nonnull))` decorator optionally allows you to
 *        specify the 1-based index of the function parameters that are to be
 *        considered non-null; `C_PSAFE` doesn't do this both for the sake of
 *        brevity and also because we consider null pointer parameters to be a
 *        code smell.
 *      - Clang allows the `__attribute__((nonnull))` decorator to be applied
 *        directly to a function parameter, but GCC does not. Therefore,
 *        `C_PSAFE` may be used to mark specific function parameters when
 *        compiled with Clang; however, it is better not to do so in the
 *        interest of portability.
 *      - Clang also provides the non-standard attribute `_Nonnull`, which is
 *        semantically identical to `__attribute__((nonnull))`; however, GCC
 *        does not support this.
 *
 * SEE ALSO
 *      - ref C_RSAFE
 *        [base:ext:rsafe]
 *      - web GCC (11.2.0:6.33.1)
 *        [https://gcc.gnu.org/onlinedocs/gcc-11.2.0/gcc
 *              /Common-Function-Attributes.html#Common-Function-Attributes]
 *      - web Clang (15.0.0)
 *        [https://clang.llvm.org/docs/AttributeReference.html]
 **/
#if (defined __GNUC__ || defined __clang__)
#       define C_PSAFE __attribute__((nonnull))
#else
#       define C_PSAFE
#       if (!defined C_SUPPRESS_EXTENSION_WARNINGS)
#               warning "C_PFAFE has no effect in current compiler"
#       endif
#endif


/** [base:ext:rsafe]
 * NAME
 *      C_RSAFE - hints a function never returns a null pointer
 *
 * SYNOPSIS
 *      #include "libchrysalis/chrysalis.h"
 *
 *      #define C_RSAFE __attribute__((returns_nonnull))
 *
 * DESCRIPTION
 *      The `C_RSAFE` macro hints that a function will never return a null
 *      pointer. When a function is marked with this macro, the compiler can
 *      make suitable optimisations for that function. The `C_RSAFE` macro may
 *      only be applied to functions that return a pointer type; a compiler
 *      warning will be issued if applied to functions returning other types.
 *
 *      This macro uses the non-standard `__attribute__((returns_nonnull))`
 *      decorator, and is available for both GCC and Clang. On other compilers,
 *      the default behaviour of this macro is to degrade safely to a no-op with
 *      a suitable warning message. If you don't want this warning message to be
 *      displayed, then define the macro `C_SUPPRESS_EXTENSION_WARNINGS` at
 *      compile time.
 *
 * FILES
 *      `C_RSAFE` is defined in /usr/local/libchrysalis/include/ext.h.
 *
 * EXAMPLES
 *      C_RSAFE int *foo(char *, int *);    // standard declaration
 *      void *bar(float *) C_PSAFE;         // alternate declaration
 *     
 *      // can also be applied on definitions
 *      C_RSAFE static int *foobar(char *foo, char c)
 *      {
 *              c = *foo;
 *              return (int) c;
 *      }
 *
 * SEE ALSO
 *      - ref C_PSAFE
 *        [base:ext:psafe]
 *      - web GCC (11.2.0:6.33.1)
 *        [https://gcc.gnu.org/onlinedocs/gcc-11.2.0/gcc
 *              /Common-Function-Attributes.html#Common-Function-Attributes]
 **/
#if (defined __GNUC__ || defined __clang__)
#       define C_RSAFE __attribute__((returns_nonnull))
#else
#       define C_RSAFE
#       if (!defined C_SUPPRESS_EXTENSION_WARNINGS)
#               warning "C_RSAFE has no effect in current compiler"
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
 *      The `C_HOT` macro is used to hint that a function is hot, i.e. it is
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
 *      `C_HOT` is defined in /usr/local/libchrysalis/include/ext.h.
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
 *      - `C_HOT` is ignored by GCC if the `-fprofile-use` flag is used during
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
#if (defined __GNUC__ || defined __clang__)
#       define C_HOT __attribute__((hot))
#else
#       define C_HOT
#       if (!defined C_SUPPRESS_EXTENSION_WARNINGS)
#               warning "C_HOT has no effect in current compiler"
#       endif
#endif


/** [base:ext:cold]
 * NAME
 *      C_COLD - hints a function as cold
 *
 * SYNOPSIS
 *      #include "libchrysalis/chrysalis.h"
 *
 *      #define C_COLD __attribute__((cold))
 *
 * DESCRIPTION
 *      The `C_COLD` macro is used to hint that a function is cold, i.e. it is
 *      unlikely to called. Functions that are marked with `C_COLD` are
 *      optimised by the compiler for size rather than speed, and are placed
 *      into a special cold section in order to improve locality of code with
 *      other cold functions. Exception handlers are good candidates for marking
 *      with `C_COLD`.
 *
 *      This macro uses the non-standard `__attribute__((cold))` decorator, and
 *      is available for both GCC and Clang. On other compilers, the default
 *      behaviour of this macro is to degrade safely to a no-op with a suitable
 *      warning message. If you don't want this warning message to be displayed,
 *      then define the macro `C_SUPPRESS_EXTENSION_WARNINGS` at compile time.
 *
 * FILES
 *      C_COLD is defined in /usr/local/libchrysalis/include/ext.h.
 *
 * EXAMPLES
 *      C_COLD int foo(char *, int *);  // standard declaration
 *      void bar(float *) C_COLD;       // alternate declaration
 *     
 *      // can also be applied on definitions
 *      C_COLD static int foobar(char *foo, char c)
 *      {
 *              c = *foo;
 *              return (int) c;
 *      }
 *
 * NOTES
 *      - `C_COLD` is ignored by GCC if the `-fprofile-use` flag is used during
 *        compilation.
 *      - Unlike the case of `C_HOT`, Clang does _not_ silently drop this macro.
 *
 * SEE ALSO
 *      - ref C_HOT
 *        [base:ext:hot]
 *      - web GCC (11.2.0:6.33.1)
 *        [https://gcc.gnu.org/onlinedocs/gcc-11.2.0/gcc
 *              /Common-Function-Attributes.html#Common-Function-Attributes]
 *      - web llvm-dev@lists.llvm.org
 *        [https://lists.llvm.org/pipermail/llvm-dev/2020-December/147104.html]
 **/
#if (defined __GNUC__ || defined __clang__)
#       define C_COLD __attribute__((cold))
#else
#       define C_COLD
#       if (!defined C_SUPPRESS_EXTENSION_WARNINGS)
#               warning "C_COLD has no effect in current compiler"
#       endif
#endif


/**
 ** ^ C_PURE: Marks a variable as pure.
 **/
#define C_STABLE __attribute__((pure))


#define C_IMMUTABLE __attribute__((pure))


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

