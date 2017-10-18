#include <stdlib.h>

#ifndef BYTEBUF_H
#define BYTEBUF_H

#define BYTEBUF_INITIAL_CAP 128

#define bytebuf_append_str(b, s) bytebuf_append(b, s, strlen(s));

typedef struct bytebuf {
    char *data;
    size_t len;
    size_t cap;
} bytebuf;

bytebuf* bytebuf_new();
char* bytebuf_at(bytebuf* b, size_t i);
void bytebuf_extend(bytebuf* b, char *cont, size_t n);
void bytebuf_destroy(bytebuf *b);

#endif
