#include "../inc/libmx.h"

static void count(int *words, int *spaces, char *arr) {
    int i = 0;
    while (*(arr + i) != 0) {
        if (mx_isspace(*(arr + i)))
            ++(*spaces);
        if (mx_isspace(*(arr + i))
            && !(mx_isspace(*(arr + i + 1))))
            ++(*words);
        ++i;
    }
}

static void writestr(char *src, char *dst) {
    int i = 0;
    int j = 0;
    while (*(src + i) != 0) {
        if (mx_isspace(*(src + i))) {
            *(dst + j) = ' ';
            ++j;
            ++i;
            while (mx_isspace(*(src + i)))
                ++i;
        }
        *(dst + j) = *(src + i);
        ++j;
        ++i;
    }
}

char *mx_del_extra_spaces(const char *str) {
    char *trimmed = mx_strtrim(str);
    if (trimmed == NULL)
        return NULL;
    int length = mx_strlen(trimmed);
    int words = 0;
    int spaces = 0;
    count(&words, &spaces, trimmed);
    length = length - spaces + words;
    char *res = mx_strnew(length);
    if (res == NULL) {
        mx_strdel(&trimmed);
        return NULL;
    }
    writestr(trimmed, res);
    mx_strdel(&trimmed);
    return res;
}

