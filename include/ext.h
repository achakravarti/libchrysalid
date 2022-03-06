/*******************************************************************************
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * libchrysalis/base/ext.h - commonly used compiler extensions
 * Copyright (c) 2022 Abhishek Chakravarti
 * See libchrysalis/doc/base/libchrysalis:extensions.7.md for documentation.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software 
 *    without specific prior written permission.
 *
 * 4. Redistributions of any form whatsoever must retain the following
 *    acknowledgment: 'This product includes software developed by "Montão AB"
 *    (https://montao.github.io/).'
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************/


/* Start header guard. */
#ifndef __LIBCHRYSALIS_INCLUDE_EXT_H_INCLUDED__
#define __LIBCHRYSALIS_INCLUDE_EXT_H_INCLUDED__


/* Open C++ compatibility wrapper. */
#ifdef __cplusplus
extern "C" {
#endif


/* Define C_PSAFE macro; see libchrysalis/docs/base/C_PSAFE.7.md for
 * documentation.
 */
#if (defined __GNUC__ || defined __clang__)
#       define C_PSAFE __attribute__((nonnull))
#else
#       define C_PSAFE
#       if (!defined C_SUPPRESS_EXTENSION_WARNINGS)
#               warning "C_PSAFE has no effect in current compiler"
#       endif
#endif


/* Define C_RSAFE macro; see libchrysalis/docs/base/C_RSAFE.7.md for
 * documentation.
 */
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
 *      #include "libchrysalis/api.h"
 *
 *      #define C_HOT
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
 * EXAMPLE
 *      C_HOT int foo(char *, int *);   // standard declaration
 *      void bar(float *) C_HOT;        // alternate declaration
 *     
 *      // can also be applied on definitions
 *      C_HOT static int foobar(char *foo, char c)
 *      {
 *              *foo = c;
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
 *      #include "libchrysalis/api.h"
 *
 *      #define C_COLD
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
 *      `C_COLD` is defined in /usr/local/libchrysalis/include/ext.h.
 *
 * EXAMPLE
 *      C_COLD int foo(char *, int *);  // standard declaration
 *      void bar(float *) C_COLD;       // alternate declaration
 *     
 *      // can also be applied on definitions
 *      C_COLD static int foobar(char *foo, char c)
 *      {
 *              *foo = c;
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


/** [base:ext:likely]
 * NAME
 *      C_LIKELY() - hints predicate as likely to be true
 *
 * SYNOPSIS
 *      #include "libchrysalis/api.h"
 *
 *      #define C_LIKELY(_P_)
 *
 * DESCRIPTION
 *      The `C_LIKELY()` macro provides a branch prediction hint to the
 *      compiler, indicating that a predicate expression `_P_` is likely to be
 *      true. `_P_` is expected to be an integral predicate expression that
 *      evaluates to a Boolean value.
 *
 *      This macro uses the non-standard `__builtin_expect()` macro, and is
 *      available for both GCC and Clang. On other compilers, the default
 *      behaviour of this macro is to degrade safely to a no-op with a suitable
 *      warning message. If you don't want this warning message to be displayed,
 *      then define the macro `C_SUPPRESS_EXTENSION_WARNINGS` at compile time.
 *
 * RETURN VALUE
 *      The Boolean value which the predicate `_P_` evaluates to is returned.
 *
 * FILES
 *      `C_LIKELY` is defined in /usr/local/libchrysalis/include/ext.h.
 *
 * EXAMPLE
 *      int foobar(char *foo, char c)
 *      {
 *              if (C_LIKELY (foo != NULL)) {
 *                      *foo = c;
 *                      return (int) c;
 *              }
 *
 *              return -1;
 *      }
 *
 * NOTES
 *      - This macro is inspired by the `likely()` macro in the Linux kernel.
 *      - Marking a predicate as likely with `C_LIKELY()` when it is not so will
 *        have the contrary effect of degrading performance.
 *
 * SEE ALSO
 *      - ref C_UNLIKELY()
 *        [base:ext:unlikely]
 *      - web Kernel Newbies
 *        [https://kernelnewbies.org/FAQ/LikelyUnlikely]
 *      - web GCC Online Docs
 *        [https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
 *      - web LLVM Documentation
 *        [https://llvm.org/docs/BranchWeightMetadata.html]
 **/
#if (defined __GNUC__ || defined __clang__)
#       define C_LIKELY(_P_) __builtin_expect(!!(_P_), 1)
#else
#       define C_LIKELY(_P_) _P_
#       if (!defined C_SUPPRESS_EXTENSION_WARNINGS)
#               warning "C_LIKELY() has no effect in current compiler"
#       endif
#endif


/** [base:ext:unlikely]
 * NAME
 *      C_UNLIKELY() - hints predicate as unlikely to be true
 *
 * SYNOPSIS
 *      #include "libchrysalis/api.h"
 *
 *      #define C_UNLIKELY(_P_)
 *
 * DESCRIPTION
 *      The `C_UNLIKELY()` macro provides a branch prediction hint to the
 *      compiler, indicating that a predicate expression `_P_` is UNlikely to be
 *      true. `_P_` is expected to be an integral predicate expression that
 *      evaluates to a Boolean value.
 *
 *      This macro uses the non-standard `__builtin_expect()` macro, and is
 *      available for both GCC and Clang. On other compilers, the default
 *      behaviour of this macro is to degrade safely to a no-op with a suitable
 *      warning message. If you don't want this warning message to be displayed,
 *      then define the macro `C_SUPPRESS_EXTENSION_WARNINGS` at compile time.
 *
 * RETURN VALUE
 *      The Boolean value which the predicate `_P_` evaluates to is returned.
 *
 * FILES
 *      `C_UNLIKELY` is defined in /usr/local/libchrysalis/include/ext.h.
 *
 * EXAMPLE
 *      int foobar(char *foo, char c)
 *      {
 *              if (C_LIKELY (foo != NULL)) {
 *                      *foo = c;
 *                      return (int) c;
 *              }
 *
 *              return -1;
 *      }
 *
 * NOTES
 *      - This macro is inspired by the `unlikely()` macro in the Linux kernel.
 *      - Marking a predicate as likely with `C_UNLIKELY()` when it is not so
 *        will have the contrary effect of degrading performance.
 *
 * SEE ALSO
 *      - ref C_LIKELY()
 *        [base:ext:likely]
 *      - web Kernel Newbies
 *        [https://kernelnewbies.org/FAQ/LikelyUnlikely]
 *      - web GCC Online Docs
 *        [https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html
 *      - web LLVM Documentation
 *        [https://llvm.org/docs/BranchWeightMetadata.html]
 **/
#if (defined __GNUC__ || defined __clang__)
#       define C_UNLIKELY(_P_) __builtin_expect(!!(_P_), 0)
#else
#       define C_LIKELY(_P_) _P_
#       if (!defined C_SUPPRESS_EXTENSION_WARNINGS)
#               warning "C_LIKELY() has no effect in current compiler"
#       endif
#endif


/* Close C++ compatibility wrapper. */
#ifdef __cplusplus
}
#endif

/* Close header guard. */
#endif  /* !__LIBCHRYSALIS_INCLUDE_EXT_H_INCLUDED__ */

