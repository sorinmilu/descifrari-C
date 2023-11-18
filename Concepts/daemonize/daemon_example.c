// daemon_example.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <signal.h>

#define LOG_INTERVAL 10 // Log message every 10 seconds

void cleanup() {
    syslog(LOG_INFO, "Daemon is shutting down.");
    // Perform any cleanup tasks here.
    closelog();
}

void sigkill_handler(int signum) {
    // This does not work - sigkill is handled by OS
    syslog(LOG_INFO, "Oh, you killed me.");
}

void sighup_handler(int signum) {
    syslog(LOG_INFO, "I shall live forever!!");
}

int main() {
    // Open syslog
    openlog("daemon_example", LOG_PID | LOG_NDELAY, LOG_DAEMON);

    // Set up a signal handler for cleanup
    signal(SIGTERM, cleanup);

    // Set up a signal handler for SIGKILL
    signal(SIGKILL, sigkill_handler);

    // Set up a signal handler for SIGHUP
    signal(SIGHUP, sighup_handler);

    // Fork to create a child process
    pid_t pid = fork();

    if (pid < 0) {
        syslog(LOG_ERR, "Error forking");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        // Parent process (original process)
        syslog(LOG_INFO, "Daemon PID: %d", pid);
        closelog();
        exit(EXIT_SUCCESS);
    }

    // Child process (daemon)
    umask(0); // Unmask the file mode

    // Create a new session and become the leader of the session
    if (setsid() == -1) {
        syslog(LOG_ERR, "Error creating session");
        exit(EXIT_FAILURE);
    }

    // Change the current working directory to root
    if (chdir("/") == -1) {
        syslog(LOG_ERR, "Error changing directory");
        exit(EXIT_FAILURE);
    }

    // Close standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Redirect standard file descriptors to /dev/null
    open("/dev/null", O_RDONLY);
    open("/dev/null", O_WRONLY);
    open("/dev/null", O_RDWR);

    // Main daemon logic
    while (1) {
        syslog(LOG_INFO, "Daemon is active.");
        sleep(LOG_INTERVAL);
    }

    // Cleanup and shut down (this part will not be reached in the current logic)
    cleanup();

    return 0;
}
