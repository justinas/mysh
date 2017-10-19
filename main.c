#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bytebuf.h"

void printwd()
{
    static char wd[4096];
    getcwd(wd, sizeof(wd));
    printf("%s$ ", wd);
}

int main() {
    fflush(stdout);
    setbuf(stdout, NULL);

    bytebuf* data = bytebuf_new();

    printwd();

    char buf[4];
    ssize_t n = 0;
    while ((n = read(0, buf, sizeof(buf))) > 0) {
        char *endl = NULL;
        if ((endl = memchr((void*) buf, '\n', n))) {
            bytebuf_extend(data, buf, (char*)endl - buf + 1);
            bytebuf_append(data, '\0');
            printf("%lu %s", strlen(data->data), data->data);
            bytebuf_clear(data);

            bytebuf_extend(data, endl+1, (size_t)(buf + n - endl - 1));
            printwd();
        } else {
            bytebuf_extend(data, buf, n);
        }
    }
}
