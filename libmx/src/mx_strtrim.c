#include "../inc/libmx.h"

char *mx_strtrim(const char *str) {
    if (str == NULL)
        return NULL;
    int length = mx_strlen(str);
    while (mx_isspace(*str) && *str != '\0') {
        --length;
        ++str;
    }
    while (length > 0 && mx_isspace(*(str + length - 1)))
        --length;
    char *newstr = mx_strnew(length);
    if (newstr == NULL)
        return NULL;
    mx_strncpy(newstr, str, length);
    return newstr;
}

