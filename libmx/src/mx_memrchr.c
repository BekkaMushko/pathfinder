#include "../inc/libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
    unsigned char *string = (unsigned char *)s;
    for (unsigned long i = n; i > 0; --i) {
        if (string[i - 1] == c)
            return string + i - 1;
    }
    return NULL;
}

