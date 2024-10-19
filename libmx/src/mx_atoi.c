#include "../inc/libmx.h"

long int mx_atoi(const char *str) {
    long int n = 0;
    int one = 1;
    int i = 0;
    while (mx_isspace(*(str + i)))
        ++i;
    if (*(str + i) == '-' || *(str + i) == '+') {
        one = *(str + i) == '-' ? -1 : 1;
        ++i;
    }
    while (mx_isdigit(*(str + i))) {
        if (n > LONG_MAX / 10 || (n == LONG_MAX / 10 && *(str + i) - 48 > 7))
            return one == 1 ? LONG_MAX : LONG_MIN;
        n = n * 10 + (*(str + i) - 48);
        ++i;
    }
    return n * one;
}

