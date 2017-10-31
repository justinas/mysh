#include <stdbool.h>

#ifndef COMMAND_H
#define COMMAND_H

#include "bytebuf.h"
#include "token.h"

typedef struct command {
    char **argv;
    size_t argc;
    char *stdin_path;
    char *stdout_path;
    bool stdout_append;
} command;

command* command_new(token** toks, size_t n);
void command_free(command *c);

#endif
