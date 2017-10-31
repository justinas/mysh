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
                if (cmd->stdin_path) {
                    int fin;
                    fin = open(cmd->stdin_path, O_RDONLY);
                    if (fin == -1) {
                        perror("open");
                        exit(1);
                    }
                    if (dup2(fin, STDIN_FILENO) == -1) {
                        perror("dup2");
                        exit(1);
                    }
                }
                if (cmd->stdout_path) {
                    int fout;
                    int mode = O_CREAT | O_WRONLY;
                    if (cmd->stdout_append) mode |= O_APPEND;

                    fout = open(cmd->stdout_path, mode, 0644);
                    if (fout == -1) {
                        perror("open");
                        exit(1);
                    }
                    if (dup2(fout, STDOUT_FILENO) == -1) {
                        perror("dup2");
                        exit(1);
                    }
                }

                // Restore the default SIGINT action on the child.
                // This way, when a command is running, Ctrl+C
                // kills the child, but not the shell.
                signal(SIGINT, SIG_DFL);
                if (execvp(cmd->argv[0], cmd->argv) == -1) {
                    perror("execvp");
                }
                exit(1);
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
    /*
    printf("Ret pid: %d\n", ret_pid);
    printf("Ret status: %d\n", ret_status);
    */
    return;
}
