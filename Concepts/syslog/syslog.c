#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>

int main() {
    // Initialize syslog with program name and flags
    openlog("log_example", LOG_PID | LOG_NDELAY, LOG_USER);

    // Log messages with different priorities
    syslog(LOG_INFO, "This is an informational message.");
    syslog(LOG_WARNING, "This is a warning message.");
    syslog(LOG_ERR, "This is an error message.");

    // Change logging priority dynamically
    setlogmask(LOG_UPTO(LOG_WARNING));  // Log messages up to warning level

    // Log messages after changing priority
    syslog(LOG_INFO, "This message should not be logged.");
    syslog(LOG_WARNING, "This is another warning message.");

    // Close syslog connection
    closelog();

    return 0;
}
