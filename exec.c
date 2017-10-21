#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

#include "command.h"
#include "exec.h"

void exec_external(command *cmd) {
    pid_t pid;
    switch (pid = fork()) {
        case -1:
            perror("fork");
            return;
        case 0:
            {
                int fin;
                if (cmd->stdin_path) {
                    fin = open(cmd->stdin_path, O_CREAT);
                    if (fin == -1) {
                        perror("fin");
                        return;
                    }
                    if (dup2(fin, STDIN_FILENO) == -1) {
                        perror("dup2");
                        return;
                    }
                }

                // Restore the default SIGINT action on the child.
                // This way, when a command is running, Ctrl+C
                // kills the child, but not the shell.
                signal(SIGINT, SIG_DFL);
                if (execvp(cmd->argv[0], cmd->argv) == -1) {
                    perror("execvp");
                }
                return;
            }
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
