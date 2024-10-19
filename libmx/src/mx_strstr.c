#include "../inc/libmx.h"

char *mx_strstr(const char *haystack, const char *needle) {
    if (needle == NULL || mx_strcmp(needle, "") == 0)
        return (char *)haystack;
    const char *ptr = haystack;
    while (1) {
        ptr = mx_strchr(ptr, needle[0]);
        if (ptr == NULL)
            return NULL;
        if (mx_strncmp(ptr, needle, mx_strlen(needle)) == 0)
            return (char *)ptr;
        ++ptr;
    }
}

