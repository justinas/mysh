#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "token.h"

command* command_new(token** toks, size_t n) {
    command* c = malloc(sizeof(command));
    c->argv = calloc(sizeof(char*), n);
    c->argc = 0;

    for (size_t i = 0; i < n; i++) {
        if (toks[i]->type == Ident) {
            bytebuf* buf = (bytebuf*) toks[i]->content;
            c->argv[c->argc] = strdup((char*) buf->data);
            c->argc++;
        }
    }

    return c;
}

void command_free(command *c) {
    for (size_t i = 0; i < c->argc; i++) {
        free(c->argv[i]);
    }
    free(c);
}
