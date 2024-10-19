#include "../inc/libmx.h"

bool mx_isspace(char c) {
    if (c == 32 || (c > 8 && c < 14))
        return 1;
    else
        return 0;
}

