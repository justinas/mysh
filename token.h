#ifndef TOKEN_H
#define TOKEN_H

typedef enum token_type {
    Ident = 1, // content: bytebuf
} token_type;

typedef struct token {
    token_type type;
    void* content;
} token;

void token_free(token* tok);
token* token_try_ident(char **buf);

#endif
