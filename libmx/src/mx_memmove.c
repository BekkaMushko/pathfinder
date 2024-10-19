#include "../inc/libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
    char *dststr = (char *)dst;
    char *srcstr = (char *)src;
    if (dst <= src) {
        for (unsigned long i = 0; i < len; ++i)
            dststr[i] = srcstr[i];
    }
    else {
        for (unsigned long i = len; i > 0; --i)
            dststr[i - 1] = srcstr[i - 1];
    }
    return dststr;
}

