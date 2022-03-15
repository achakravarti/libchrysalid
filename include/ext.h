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


#ifndef __LIBCHRYSALIS_INCLUDE_EXT_H_INCLUDED__
#define __LIBCHRYSALIS_INCLUDE_EXT_H_INCLUDED__


#ifdef __cplusplus
extern "C" {
#endif


/*
 * C_PSAFE - hints a function has no null parameters
 * Ref: libchrysalis/docs/man/C_PSAFE.3.md
 */
#if (defined __GNUC__ || defined __clang__)
#       define C_PSAFE __attribute__((nonnull))
#else
#       define C_PSAFE
#       if (!defined C_SUPPRESS_EXTENSION_WARNINGS)
#               warning "C_PSAFE has no effect in current compiler"
#       endif
#endif


/*
 * C_RSAFE - hints a function never returns a null pointer
 * Ref: libchrysalis/docs/man/C_RSAFE.3.md
 */
#if (defined __GNUC__ || defined __clang__)
#       define C_RSAFE __attribute__((returns_nonnull))
#else
#       define C_RSAFE
#       if (!defined C_SUPPRESS_EXTENSION_WARNINGS)
#               warning "C_RSAFE has no effect in current compiler"
#       endif
#endif


/*
 * C_HOT - hints a function as hot
 * Ref: libchrysalis/docs/man/C_HOT.3.md
 */
#if (defined __GNUC__ || defined __clang__)
#       define C_HOT __attribute__((hot))
#else
#       define C_HOT
#       if (!defined C_SUPPRESS_EXTENSION_WARNINGS)
#               warning "C_HOT has no effect in current compiler"
#       endif
#endif


/*
 * C_COLD - hints a function as cold
 * Ref: libchrysalis/docs/man/C_COLD.3.md
 */
#if (defined __GNUC__ || defined __clang__)
#       define C_COLD __attribute__((cold))
#else
#       define C_COLD
#       if (!defined C_SUPPRESS_EXTENSION_WARNINGS)
#               warning "C_COLD has no effect in current compiler"
#       endif
#endif


/*
 * C_STABLE - marks a function as stable
 * Ref: libchrysalis/docs/man/C_STABLE.3.md
 */
#if (defined __GNUC__ || defined __clang__)
#       define C_STABLE __attribute__((pure))
#else
#       define C_STABLE
#       if (!defined C_SUPPRESS_EXTENSION_WARNINGS)
#               warning "C_STABLE has no effect in current compiler"
#       endif
#endif


/*
 * C_IMMUTABLE - marks a function as immutable
 * Ref: libchrysalis/docs/man/C_IMMUTABLE.3.md
 */
#if (defined __GNUC__ || defined __clang__)
#       define C_IMMUTABLE __attribute__((const))
#else
#       define C_IMMUTABLE
#       if (!defined C_SUPPRESS_EXTENSION_WARNINGS)
#               warning "C_IMMUTABLE has no effect in current compiler"
#       endif
#endif


/*
 * C_TLOCAL - marks a file scope variable as thread local
 * Ref: libchrysalis/docs/man/C_TLOCAL.3.md
 */
#if (defined __GNUC__ || defined __clang__)
#       define C_TLOCAL __thread
#else
#       define C_TLOCAL
#       if (!defined C_SUPPRESS_EXTENSION_WARNINGS)
#               warning "C_TLOCAL has no effect in current compiler"
#       endif
#endif


/*
 * C_AUTO - marks an automatic heap pointer
 * Ref: libchrysalis/docs/man/C_AUTO.3.md
 */
#if (defined __GNUC__ || defined __clang__)
#       define C_AUTO(_T_) __attribute__((cleanup(_T_##_free))) _T_
#else
#       define C_AUTO
#       if (!defined C_SUPPRESS_EXTENSION_WARNINGS)
#               warning "C_AUTO has no effect in current compiler"
#       endif
#endif


/*
 * C_LIKELY - hints predicate as likely to be true
 * Ref: libchrysalis/docs/man/C_LIKELY.3.md
 */
#if (defined __GNUC__ || defined __clang__)
#       define C_LIKELY(_P_) __builtin_expect(!!(_P_), 1)
#else
#       define C_LIKELY(_P_) _P_
#       if (!defined C_SUPPRESS_EXTENSION_WARNINGS)
#               warning "C_LIKELY() has no effect in current compiler"
#       endif
#endif


/*
 * C_UNLIKELY - hints predicate as unlikely to be true
 * Ref: libchrysalis/docs/man/C_UNLIKELY.3.md
 */
#if (defined __GNUC__ || defined __clang__)
#       define C_UNLIKELY(_P_) __builtin_expect(!!(_P_), 0)
#else
#       define C_LIKELY(_P_) _P_
#       if (!defined C_SUPPRESS_EXTENSION_WARNINGS)
#               warning "C_LIKELY() has no effect in current compiler"
#       endif
#endif


#ifdef __cplusplus
}
#endif

#endif  /* !__LIBCHRYSALIS_INCLUDE_EXT_H_INCLUDED__ */

