#ifndef BUILTINS_H
#define BUILTINS_H

#include <stddef.h>
#include <stdlib.h>

typedef struct builtin_spec {
    char* name;
    void (*fn)();
} builtin_spec;

void builtin_cd(int argc, char** argv);
void builtin_echo(int argc, char** argv);
void builtin_exit(int argc, char** argv);

extern builtin_spec BUILTINS[];
#endif
