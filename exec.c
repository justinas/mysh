#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

#include "exec.h"

void exec_external(char **argv) {
    pid_t pid;
    switch (pid = fork()) {
        case -1:
            perror("fork");
            return;
        case 0:
            // Restore the default SIGINT action on the child.
            // This way, when a command is running, Ctrl+C
            // kills the child, but not the shell.
            signal(SIGINT, SIG_DFL);
            if (execvp(argv[0], argv) == -1) {
                perror("execvp");
            }
            return;
        default:
            break;
    }

    pid_t ret_pid = 0;
    int ret_status = 0;
    while ((ret_pid = waitpid(pid, &ret_status, 0))) {
        if (ret_pid == -1) puts("NOT YET");
        else break;
    }
    printf("Ret pid: %d\n", ret_pid);
    printf("Ret status: %d\n", ret_status);
    return;
}
