#include "../inc/libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n) {
    char *dststr = (char *)dst;
    char *srcstr = (char *)src;
    for (unsigned long i = 0; i < n; ++i) {
        dststr[i] = srcstr[i];
        if (srcstr[i] == c)
            return dststr + i + 1;
    }
    return NULL;
}

