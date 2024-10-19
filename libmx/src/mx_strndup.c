#include "../inc/libmx.h"

char *mx_strndup(const char *s1, size_t n) {
    unsigned long length = mx_strlen(s1);
    length = n < length ? n : length;
    char *res = mx_strnew(length);
    if (res == NULL)
        return NULL;
    for (unsigned long i = 0; i < length; ++i)
        res[i] = s1[i];
    return res;
}

