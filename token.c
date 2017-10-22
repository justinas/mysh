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
        case 2:
        case 3:
        case 4:
            bytebuf_destroy((bytebuf*) tok->content);
            break;
        default:
            abort();
    }
    free(tok);
}

token* token_try(char **buf) {
    *buf = skip_whitespace(*buf);
    token *tok;

    tok = token_try_redir(buf);
    if (tok == (token*)TOKEN_SYNTAX_ERROR || tok != 0) return tok;
    tok = token_try_ident(buf);
    if (tok == (token*)TOKEN_SYNTAX_ERROR || tok != 0) return tok;

    return NULL;
}

token* token_try_redir(char **buf) {
    token *tok = NULL;

    char c;
    switch ((c = **buf)) {
        case '<':
        case '>':
            (*buf)++;
            *buf = skip_whitespace(*buf);
            tok = calloc(sizeof(token), 1);
            tok->type = c == '<' ? StdinRedir : StdoutRedir;

            token* file = token_try_ident(buf);
            // No filename, syntax error
            if (file == NULL || file == TOKEN_SYNTAX_ERROR) {
                free(tok);
                tok = TOKEN_SYNTAX_ERROR;
                break;
            }
            tok->content = bytebuf_clone((bytebuf*) file->content);
            token_free(file);
    }

    return tok;
}

token* token_try_ident(char **buf) {
    if (!*buf) return NULL;

    token* tok = calloc(sizeof(token), 1);
    tok->content= bytebuf_new();
    tok->type = Ident;
    while (**buf && !isspace(**buf)) {
        bytebuf_append(tok->content, **buf);
        (*buf)++;
    }

    if ( ((bytebuf*)tok->content)->len == 0) {
        token_free(tok);
        return NULL;
    }

    bytebuf_append(tok->content, '\0');
    return tok;
}
