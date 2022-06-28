/* Header guard */
#ifndef __LIBCHRYSALID_INCLUDE_LOG_H__
#define __LIBCHRYSALID_INCLUDE_LOG_H__

/* Libchrysalid dependencies */
#include "ext.h"

/* C++ compatiblity */
#ifdef __cplusplus
extern "C" {
#endif


enum cy_log_facility {
        CY_LOG_FACILITY_KERN,
        CY_LOG_FACILITY_USER,
        CY_LOG_FACILITY_MAIL,
        CY_LOG_FACILITY_DAEMON,
        CY_LOG_FACILITY_AUTH,
        CY_LOG_FACILITY_SYSLOG,
        CY_LOG_FACILITY_LPR,
        CY_LOG_FACILITY_NEWS,
        CY_LOG_FACILITY_UUCP,
        CY_LOG_FACILITY_CRON,
        CY_LOG_FACILITY_AUTHPRIV,
        CY_LOG_FACILITY_FTP,
        CY_LOG_FACILITY_NTP,
        CY_LOG_FACILITY_SECURITY,
        CY_LOG_FACILITY_CONSOLE,
        CY_LOG_FACILITY_SOLARISCRON,
        CY_LOG_FACILITY_LOCAL0,
        CY_LOG_FACILITY_LOCAL1,
        CY_LOG_FACILITY_LOCAL2,
        CY_LOG_FACILITY_LOCAL3,
        CY_LOG_FACILITY_LOCAL4,
        CY_LOG_FACILITY_LOCAL5,
        CY_LOG_FACILITY_LOCAL6,
        CY_LOG_FACILITY_LOCAL7
};

enum cy_log_severity {
        CY_LOG_SEVERITY_EMERG,
        CY_LOG_SEVERITY_ALERT,
        CY_LOG_SEVERITY_CRIT,
        CY_LOG_SEVERITY_ERR,
        CY_LOG_SEVERITY_WARNING,
        CY_LOG_SEVERITY_NOTICE,
        CY_LOG_SEVERITY_INFO,
        CY_LOG_SEVERITY_DEBUG
};


/* Protoypes for factory functions. */

extern CY_PSAFE void
cy_log_init(enum cy_log_facility, const char *);

extern void
cy_log_exit(void);


/* Prototype for mutator function. */

extern CY_HOT CY_PSAFE void
cy_log_write(const char *, const char *, int, enum cy_log_severity,
             const char *, ...);


/* Mutator macros */


/*                                                           %macro:cy_log_emerg
 * __NAME__
 *      cy_log_emerg() - logs emergency message
 */
#define cy_log_emerg(msg, ...)                                         \
cy_log_write(__func__, __FILE__, __LINE__, CY_LOG_SEVERITY_EMERG, msg, \
             ##__VA_ARGS__)


/*                                                           %macro:cy_log_alert
 * __NAME__
 *      cy_log_alert() - logs alert message
 */
#define cy_log_alert(msg, ...)                                         \
cy_log_write(__func__, __FILE__, __LINE__, CY_LOG_SEVERITY_ALERT, msg, \
             ##__VA_ARGS__)


/*                                                            %macro:cy_log_crit
 * __NAME__
 *      cy_log_crit() - logs critical message
 */
#define cy_log_crit(msg, ...)                                         \
cy_log_write(__func__, __FILE__, __LINE__, CY_LOG_SEVERITY_CRIT, msg, \
             ##__VA_ARGS__)


/*                                                             %macro:cy_log_err
 * __NAME__
 *      cy_log_err() - logs error message
 */
#define cy_log_err(msg, ...)                                         \
cy_log_write(__func__, __FILE__, __LINE__, CY_LOG_SEVERITY_ERR, msg, \
             ##__VA_ARGS__)


/*                                                         %macro:cy_log_warning
 * __NAME__
 *      cy_log_warning() - logs warning message
 */
#define cy_log_warning(msg, ...)                                         \
cy_log_write(__func__, __FILE__, __LINE__, CY_LOG_SEVERITY_WARNING, msg, \
             ##__VA_ARGS__)


/*                                                          %macro:cy_log_notice
 * __NAME__
 *      cy_log_notice() - logs notice message
 */
#define cy_log_notice(msg, ...)                                         \
cy_log_write(__func__, __FILE__, __LINE__, CY_LOG_SEVERITY_NOTICE, msg, \
             ##__VA_ARGS__)


/*                                                            %macro:cy_log_info
 * __NAME__
 *      cy_log_info() - logs informational message
 */
#define cy_log_info(msg, ...)                                         \
cy_log_write(__func__, __FILE__, __LINE__, CY_LOG_SEVERITY_INFO, msg, \
             ##__VA_ARGS__)


/*                                                           %macro:cy_log_debug
 * __NAME__
 *      cy_log_debug() - logs debugging message
 */
#ifdef NDEBUG
#       define cy_log_debug(msg, ...)
#else
#       define cy_log_debug(msg, ...)                                          \
        cy_log_write(__func__, __FILE__, __LINE__, CY_LOG_SEVERITY_DEBUG, msg, \
                     ##__VA_ARGS__)
#endif


/* C++ compatiblity */
#ifdef __cplusplus
}
#endif

/* Header guard */
#endif /* !__LIBCHRYSALID_INCLUDE_LOG_H__ */
