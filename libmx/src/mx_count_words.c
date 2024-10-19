#include "../inc/libmx.h"

int mx_count_words(const char *str, char c) {
    if (str == NULL)
        return -1;
    int counter = 0;
    int i = 0;
    while (*(str + i) == c)
        ++i;
    while (*(str + i) != '\0') {
        if (counter == 0)
            counter = 1;
        if (*(str + i) == c && *(str + i + 1) != c && *(str + i + 1) != '\0')
            ++counter;
        ++i;
    }
    return counter;
}

