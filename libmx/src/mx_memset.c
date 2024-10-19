#include "../inc/libmx.h"

void *mx_memset(void *b, int c, size_t len) {
    char *a = b;
    for (unsigned long i = 0; i < len; ++i)
        a[i] = c;
    return a;
}

