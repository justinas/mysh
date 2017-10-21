#ifndef TOKEN_H
#define TOKEN_H

#define TOKEN_SYNTAX_ERROR ((token*)-1)

typedef enum token_type {
    Ident = 1, // content: bytebuf
    StdinRedir = 2, // content: bytebuf
    StdoutRedir = 3, // content: bytebuf
    StderrRedir = 4, // content: bytebuf
} token_type;

typedef struct token {
    token_type type;
    void* content;
} token;

void token_free(token* tok);
token* token_try(char **buf);
token* token_try_ident(char **buf);
token* token_try_redir(char **buf);

#endif
