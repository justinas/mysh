#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "builtins.h"
#include "bytebuf.h"
#include "command.h"
#include "exec.h"
#include "token.h"

void printwd()
{
    static char wd[4096];
    getcwd(wd, sizeof(wd));
    printf("%s$ ", wd);
}

void run_line(bytebuf* line) {
    size_t cap = 1;
    size_t len = 0;

    token** toks = malloc(sizeof(token**));
    if (!toks) abort();

    char *remain = line->data;
    while (*remain && *remain != '\n') {
        token* tok = token_try(&remain);
        if (tok == TOKEN_SYNTAX_ERROR) {
            puts("Syntax error");
        }
        else if (tok == 0) {
            continue;
        }
        else
        {
            if (len == cap) {
                cap *= 2;
                toks = realloc(toks, sizeof(token**) * cap);
                if (!toks) abort();
            }
            toks[len] = tok;
            len++;
        }
    }

    for (size_t i = 0; i < len; i++) {
        printf("%d\t%s\n",
                toks[i]->type,
                ((bytebuf*)toks[i]->content)->data);
    }

    command *cmd = command_new(toks, len);
    if (cmd->argc > 0) {
        builtin_spec *builtins = BUILTINS;
        while (builtins->name) {
            if (strcmp(builtins->name, cmd->argv[0]) == 0) {
                builtins->fn(cmd->argc, cmd->argv);
                goto free;
            }
            builtins++;
        }

        exec_external(cmd);
    }

    free:
    command_free(cmd);

    for (size_t i = 0; i < len; i++) {
        token_free(toks[i]);
    }
    free(toks);
}

int main() {
    fflush(stdout);
    setbuf(stdout, NULL);
    signal(SIGINT, SIG_IGN);

    bytebuf* line = bytebuf_new();

    printwd();

    char buf[4];
    ssize_t n = 0;
    while ((n = read(0, buf, sizeof(buf))) > 0) {
        char *endl = NULL;
        if ((endl = memchr((void*) buf, '\n', n))) {
            bytebuf_extend(line, buf, (char*)endl - buf + 1);
            bytebuf_append(line, '\0');

            run_line(line);

            bytebuf_clear(line);

            bytebuf_extend(line, endl+1, (size_t)(buf + n - endl - 1));
            printwd();
        } else {
            bytebuf_extend(line, buf, n);
        }
    }
}
