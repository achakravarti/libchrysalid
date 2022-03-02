/* Start header guard. */
#ifndef __LIBCHRYSALIS_EXT_H_INCLUDED__
#define __LIBCHRYSALIS_EXT_H_INCLUDED__


/* Open C++ compatibility wrapper. */
#ifdef __cplusplus
extern "C" {
#endif


/**
 ** NAME
 **     C_NONULL - hints a parameter as non-null
 **
 ** SYNOPSIS
 **     #include <libchrysalis/ext.h>
 **
 **     #define C_NONULL __attribute__((nonull))
 **
 ** DESCRIPTION
 **
 ** RETURN VALUE
 **     No value is returned.
 **
 ** SOURCE
 **     libchrysalis/base/ext.h
 **
 ** EXAMPLES
 **
 ** SEE ALSO
 **     C_HOT(3)
 **/
#define C_NONULL __attribute__((nonnull))

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
#endif  /* !__LIBCHRYSALIS_BASE_EXT_H_INCLUDED__ */

