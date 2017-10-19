#include <ctype.h>
#include <stdlib.h>

#include "bytebuf.h"
#include "token.h"

char* skip_whitespace(char *c) {
    while (*c && isspace(*c)) c++;
    return c;
}

void token_free(token* tok) {
    switch (tok->type) {
        case 1:
            bytebuf_destroy((bytebuf*) tok->content);
            break;
    }
    free(tok);
}

token* token_try_ident(char **buf) {
    *buf = skip_whitespace(*buf);
    if (!*buf) return NULL;

    token* tok = calloc(sizeof(token), 1);
    tok->content= bytebuf_new();
    tok->type = Ident;
    while (**buf && !isspace(**buf)) {
        bytebuf_append(tok->content, **buf);
        (*buf)++;
    }

    bytebuf_append(tok->content, '\0');
    return tok;
}
