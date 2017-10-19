#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "builtins.h"

builtin_spec BUILTINS[] = {
    {"cd", builtin_cd},
    {"echo", builtin_echo},
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

void builtin_echo(int argc, char** argv) {
    assert(strcmp(argv[0], "echo") == 0);

    for (size_t i = 1; i < argc; i++) {
        printf("%s", argv[i]);
        if (i + 1 != argc) printf(" ");
    }
    puts("");
}

void builtin_exit(int argc, char** argv) {
    assert(strcmp(argv[0], "exit") == 0);

    if (argc == 1) exit(0);
    fprintf(stderr, "exit: Too many arguments\n");
}
