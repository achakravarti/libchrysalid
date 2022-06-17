#include "../include/log.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>


/*                                                             %func:cy_log_init
 * __NAME__
 *      cy_log_init() - initialises log manager
 */
void
cy_log_init(const char id[static 1])
{
        openlog(id, LOG_CONS | LOG_PID | LOG_NDELAY, LOG_USER);
        cy_log_info("Log manager started");
}


/*                                                             %func:cy_log_exit
 * __NAME__
 *      cy_log_exit() - shuts down log manager
 */
void
cy_log_exit(void)
{
        cy_log_info("Stopping log manager");
        closelog();
}


/*                                                          %func:cy_log_write__
 * __NAME__
 *      cy_log_write__() - writes log message
 */
void
cy_log_write__(const char func[static 1], const char file[static 1], int line,
               int priority, const char msg[static 1], ...)
{
        const size_t MAXLEN = 1024;
        char meta[MAXLEN];
        snprintf(meta, MAXLEN, "[%s() @ %s:%d]", func, file, line);

        char body[MAXLEN];
        va_list ap;
        va_start(ap, msg);
        vsnprintf(body, MAXLEN, msg, ap);
        va_end(ap);

        syslog(priority, "%s %s", body, meta);
}
