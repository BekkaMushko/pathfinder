#include "../inc/libmx.h"

void mx_printchar(char c) {
    char *out = &c;
    write(1, out, 1);
}

