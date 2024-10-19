#include "../inc/libmx.h"

void mx_printstr(const char *s) {
    if (s != NULL) {
        int length = mx_strlen(s);
        for (int i = 0; i < length; ++i)
            mx_printchar(*(s + i));
    }
}

