#include "../inc/libmx.h"

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n) {
    char *dststr = (char *)dst;
    char *srcstr = (char *)src;
    for (unsigned long i = 0; i < n; ++i)
        dststr[i] = srcstr[i];
    return dststr;
}

