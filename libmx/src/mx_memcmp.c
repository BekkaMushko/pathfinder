#include "../inc/libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    char *first = (char *)s1;
    char *second = (char *)s2;
    for (unsigned long i = 0; i < n; ++i) {
        if (first[i] != second[i])
            return first[i] - second[i];
    }
    return 0;
}

