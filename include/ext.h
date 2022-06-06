/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * libchrysalid/base/ext.h - commonly used compiler extensions
 * Copyright (c) 2022 Abhishek Chakravarti
 * See libchrysalid/doc/base/libchrysalid:extensions.7.md for documentation.
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
 *    acknowledgment: "This product includes software developed by Abhishek
 *    Chakravarti (abhishek@taranjali.org)."
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
 */


/* Header guard */
#ifndef __LIBCHRYSALID_INCLUDE_EXT_H_INCLUDED__
#define __LIBCHRYSALID_INCLUDE_EXT_H_INCLUDED__


/* C++ compatibility */
#ifdef __cplusplus
extern "C" {
#endif


/*
 * C_PSAFE - hints a function has no null parameters
 * Ref: libchrysalid/docs/man/C_PSAFE.3.md
 */
#if (defined __GNUC__ || defined __clang__)
#       define CY_PSAFE __attribute__((nonnull))
#else
#       define CY_PSAFE
#       if (!defined CY_SUPPRESS_EXTENSION_WARNINGS)
#               warning "CY_PSAFE has no effect in current compiler"
#       endif
#endif


/*
 * C_RSAFE - hints a function never returns a null pointer
 * Ref: libchrysalid/docs/man/C_RSAFE.3.md
 */
#if (defined __GNUC__ || defined __clang__)
#       define CY_RSAFE __attribute__((returns_nonnull))
#else
#       define CY_RSAFE
#       if (!defined CY_SUPPRESS_EXTENSION_WARNINGS)
#               warning "CY_RSAFE has no effect in current compiler"
#       endif
#endif


/*
 * C_HOT - hints a function as hot
 * Ref: libchrysalid/docs/man/C_HOT.3.md
 */
#if (defined __GNUC__ || defined __clang__)
#       define CY_HOT __attribute__((hot))
#else
#       define CY_HOT
#       if (!defined CY_SUPPRESS_EXTENSION_WARNINGS)
#               warning "CY_HOT has no effect in current compiler"
#       endif
#endif


/*
 * C_COLD - hints a function as cold
 * Ref: libchrysalid/docs/man/C_COLD.3.md
 */
#if (defined __GNUC__ || defined __clang__)
#       define CY_COLD __attribute__((cold))
#else
#       define CY_COLD
#       if (!defined CY_SUPPRESS_EXTENSION_WARNINGS)
#               warning "CY_COLD has no effect in current compiler"
#       endif
#endif


/*
 * C_STABLE - marks a function as stable
 * Ref: libchrysalid/docs/man/C_STABLE.3.md
 */
#if (defined __GNUC__ || defined __clang__)
#       define CY_STABLE __attribute__((pure))
#else
#       define CY_STABLE
#       if (!defined CY_SUPPRESS_EXTENSION_WARNINGS)
#               warning "CY_STABLE has no effect in current compiler"
#       endif
#endif


/*
 * C_IMMUTABLE - marks a function as immutable
 * Ref: libchrysalid/docs/man/C_IMMUTABLE.3.md
 */
#if (defined __GNUC__ || defined __clang__)
#       define CY_IMMUTABLE __attribute__((const))
#else
#       define CY_IMMUTABLE
#       if (!defined CY_SUPPRESS_EXTENSION_WARNINGS)
#               warning "CY_IMMUTABLE has no effect in current compiler"
#       endif
#endif


/*
 * C_AUTO - marks an automatic heap pointer
 * Ref: libchrysalid/docs/man/C_AUTO.3.md
 */
#if (defined __GNUC__ || defined __clang__)
#       define CY_AUTO(_T_) __attribute__((cleanup(_T_##_free__))) _T_
#else
#       define CY_AUTO
#       if (!defined CY_SUPPRESS_EXTENSION_WARNINGS)
#               warning "CY_AUTO has no effect in current compiler"
#       endif
#endif


/*
 * C_LIKELY - hints predicate as likely to be true
 * Ref: libchrysalid/docs/man/C_LIKELY.3.md
 */
#if (defined __GNUC__ || defined __clang__)
#       define CY_LIKELY(_P_) __builtin_expect(!!(_P_), 1)
#else
#       define CY_LIKELY(_P_) _P_
#       if (!defined CY_SUPPRESS_EXTENSION_WARNINGS)
#               warning "CY_LIKELY() has no effect in current compiler"
#       endif
#endif


/*
 * C_UNLIKELY - hints predicate as unlikely to be true
 * Ref: libchrysalid/docs/man/C_UNLIKELY.3.md
 */
#if (defined __GNUC__ || defined __clang__)
#       define CY_UNLIKELY(_P_) __builtin_expect(!!(_P_), 0)
#else
#       define CY_LIKELY(_P_) _P_
#       if (!defined CY_SUPPRESS_EXTENSION_WARNINGS)
#               warning "CY_LIKELY() has no effect in current compiler"
#       endif
#endif


/* C++ compatibility */
#ifdef __cplusplus
}
#endif


/* Header guard */
#endif
