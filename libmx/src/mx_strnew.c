#include "../inc/libmx.h"

char *mx_strnew(const int size) {
    if (size < 0)
        return NULL;
    char *res = malloc(size + 1);
    if (res == NULL)
        return NULL;
    for (int i = 0; i <= size; ++i)
        res[i] = '\0';
    return res;
}

