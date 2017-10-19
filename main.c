#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bytebuf.h"
#include "token.h"

void printwd()
{
    static char wd[4096];
    getcwd(wd, sizeof(wd));
    printf("%s$ ", wd);
}

int main() {
    fflush(stdout);
    setbuf(stdout, NULL);

    bytebuf* line = bytebuf_new();

    printwd();

    char buf[4];
    ssize_t n = 0;
    while ((n = read(0, buf, sizeof(buf))) > 0) {
        char *endl = NULL;
        if ((endl = memchr((void*) buf, '\n', n))) {
            bytebuf_extend(line, buf, (char*)endl - buf + 1);
            bytebuf_append(line, '\0');
            printf("%lu %s", strlen(line->data), line->data);
            bytebuf_clear(line);

            char *remain = line->data;
            while (*remain != '\n') {
                token* tok = token_try_ident(&remain);
                if (tok) {
                    printf("%d %s\n", tok->type, ((bytebuf*)tok->content)->data);
                }
                token_free(tok);
            }

            bytebuf_extend(line, endl+1, (size_t)(buf + n - endl - 1));
            printwd();
        } else {
            bytebuf_extend(line, buf, n);
        }
    }
}
