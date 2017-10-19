#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "builtins.h"

builtin_spec BUILTINS[] = {
    {"cd", builtin_cd},
    {"exit", builtin_exit},
    {NULL, NULL},
};

void builtin_cd(int argc, char** argv) {
    assert(strcmp(argv[0], "cd") == 0);

    if (argc == 1) return;
    else if (argc == 2) {
        if (chdir(argv[1]) != 0) {
            perror("chdir");
        }
    }
    else if (argc > 2) {
        fprintf(stderr, "cd: Too many arguments\n");
    }
}

void builtin_exit(int argc, char** argv) {
    assert(strcmp(argv[0], "exit") == 0);

    if (argc == 1) exit(0);
    fprintf(stderr, "exit: Too many arguments\n");
}
