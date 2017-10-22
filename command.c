#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "token.h"

// This function appends a NULL pointer to the end of argv,
// to be compatible with the execv family.
// argc is NOT incremented accordingly.
command* command_new(token** toks, size_t n) {
    command* c = calloc(sizeof(command), 1);
    c->argv = calloc(sizeof(char*), n + 1);
    c->argc = 0;
    c->stdin_path = NULL;
    c->stdout_path = NULL;

    for (size_t i = 0; i < n; i++) {
        if (toks[i]->type == Ident) {
            bytebuf* buf = (bytebuf*) toks[i]->content;
            c->argv[c->argc] = strdup(buf->data);
            c->argc++;
        }
        else if (toks[i]->type == StdinRedir) {
            bytebuf* buf = (bytebuf*) toks[i]->content;
            c->stdin_path = strdup(buf->data);
        }
        else if (toks[i]->type == StdoutRedir) {
            bytebuf* buf = (bytebuf*) toks[i]->content;
            c->stdout_path = strdup(buf->data);
        }
    }
    c->argv[c->argc] = NULL;

    return c;
}

void command_free(command *c) {
    for (size_t i = 0; i < c->argc; i++) {
        free(c->argv[i]);
    }
    if (c->stdin_path) free(c->stdin_path);
    if (c->stdout_path) free(c->stdout_path);
    free(c);
}
