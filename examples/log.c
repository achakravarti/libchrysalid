#include "../include/log.h"

#include <stdlib.h>


int main(void)
{
        cy_log_init(CY_LOG_FACILITY_LOCAL7, "libchrysalid-test");

        cy_log_emerg("Test emergency log message");
        cy_log_alert("Test alert log message");
        cy_log_crit("Test critical log message");
        cy_log_warning("Test warning log message");
        cy_log_notice("Test notice log message");
        cy_log_info("Test info log message");
        cy_log_debug("Test debug log message");

        cy_log_exit();
        return EXIT_SUCCESS;
}
