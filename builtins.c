#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "builtins.h"

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