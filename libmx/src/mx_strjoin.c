#include "../inc/libmx.h"

char *mx_strjoin(const char *s1, const char *s2) {
    if (s1 == NULL && s2 == NULL)
        return NULL;
    if (s1 == NULL)
        return mx_strdup(s2);
    else if (s2 == NULL)
        return mx_strdup(s1);
    int length = mx_strlen(s1) + mx_strlen(s2) + 1;
    char res[length];
    mx_strcpy(res, s1);
    mx_strcat(res, s2);
    return mx_strdup(res);
}

