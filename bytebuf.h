#ifndef BYTEBUF_H
#define BYTEBUF_H

#include <stdlib.h>

#define BYTEBUF_INITIAL_CAP 128

#define bytebuf_append_str(b, s) bytebuf_append(b, s, strlen(s));

typedef struct bytebuf {
    char *data;
    size_t len;
    size_t cap;
} bytebuf;

bytebuf* bytebuf_new();
void bytebuf_append(bytebuf* b, char c);
char* bytebuf_at(bytebuf* b, size_t i);
void bytebuf_clear(bytebuf* b);
void bytebuf_extend(bytebuf* b, char *cont, size_t n);
void bytebuf_destroy(bytebuf *b);

#endif
