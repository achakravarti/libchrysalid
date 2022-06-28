#include "../include/log.h"

#include <syslog.h>

#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>


/*                                                             %func:cy_log_init
 * __NAME__
 *      cy_log_init() - initialises log manager
 */
void cy_log_init(enum cy_log_facility facility, const char *tag)
{
        assert(tag);
        assert(*tag);

        openlog(tag, LOG_CONS | LOG_PID | LOG_NDELAY, facility);
        cy_log_info("Log manager started");
}


/*                                                             %func:cy_log_exit
 * __NAME__
 *      cy_log_exit() - shuts down log manager
 */
void cy_log_exit(void)
{
        cy_log_info("Stopping log manager");
        closelog();
}


/*                                                            %func:cy_log_write
 * __NAME__
 *      cy_log_write() - writes log message
 */
void cy_log_write(const char *func, const char *file, int line,
                  enum cy_log_severity severity, const char *msg, ...)
{
        assert(func);
        assert(*func);
        assert(file);
        assert(*file);
        assert(msg);
        assert(*msg);

        const size_t MAXLEN = 1024;
        char meta[MAXLEN];
        snprintf(meta, MAXLEN, "[%s() @ %s:%d]", func, file, line);

        char body[MAXLEN];
        va_list ap;
        va_start(ap, msg);
        vsnprintf(body, MAXLEN, msg, ap);
        va_end(ap);

        syslog(severity, "%s %s", body, meta);
}
