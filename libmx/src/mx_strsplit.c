#include "../inc/libmx.h"

char **mx_strsplit(const char *s, char c) {
    if (s == NULL)
        return NULL;
    int words = mx_count_words(s, c);
    char **arr = (char **)malloc((words + 1) * sizeof(char *));
    if (arr == NULL)
        return NULL;
    for (int i = 0; i < words; ++i) {
        while (*s == c)
            ++s;
        int size = 0;
        while (*(s + size) != c && *(s + size) != 0)
            ++size;
        arr[i] = mx_strnew(size);
        if (arr[i] == NULL) {
            for (int j = 0; j < i; ++j)
                mx_strdel(&arr[j]);
            free(arr);
            return NULL;
        }
        mx_strncpy(arr[i], s, size);
        s += size;
    }
    arr[words] = NULL;
    return arr;
}

