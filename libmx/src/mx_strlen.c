#include "../inc/libmx.h"

int mx_strlen(const char *s) {
    const char *ptr = s;
    int i = 0;
    while (*(ptr + i) != '\0')
        ++i;
    return i;
}

