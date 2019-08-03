#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bytebuf.h"

void bytebuf_grow(bytebuf *b);

bytebuf *bytebuf_new() {
    bytebuf *b = malloc(sizeof(bytebuf));
    b->data = malloc(BYTEBUF_INITIAL_CAP);
    if (b->data == NULL) {
        abort();
    }
    b->cap = BYTEBUF_INITIAL_CAP;
    b->len = 0;

    return b;
}

char *bytebuf_at(bytebuf *b, size_t i) {
    if (i >= b->len) {
        abort();
    }

    return &b->data[i];
}

void bytebuf_append(bytebuf *b, char c) {
    char a[1] = {c};
    bytebuf_extend(b, a, 1);
}

bytebuf *bytebuf_clone(bytebuf *b) {
    bytebuf *my = bytebuf_new();
    bytebuf_extend(my, b->data, b->len);
    return my;
}

void bytebuf_clear(bytebuf *b) { b->len = 0; }

void bytebuf_extend(bytebuf *b, char *cont, size_t n) {
    while (b->len + n > b->cap) {
        bytebuf_grow(b);
    }
    memcpy(b->data + b->len, cont, n);
    b->len += n;
}

void bytebuf_grow(bytebuf *b) {
    b->data = realloc(b->data, b->cap * 2);
    if (b->data == NULL) {
        abort();
    }
    b->cap = b->cap * 2;
}

void bytebuf_destroy(bytebuf *b) {
    free(b->data);
    free(b);
}
