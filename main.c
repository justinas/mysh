#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "bytebuf.h"

int main() {
    bytebuf* data = bytebuf_new();

    for (;;) {
        char buf[256];
        ssize_t n;
        while ((n = read(0, buf, 255)) > 0) {
            bytebuf_extend(data, buf, n);
            buf[n] = '\0';
            printf("%lu\n", data->len);
        }
    }
}
