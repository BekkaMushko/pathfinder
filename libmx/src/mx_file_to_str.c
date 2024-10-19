#include "../inc/libmx.h"

char *mx_file_to_str(const char *file) {
    int source = open(file, O_RDWR);
    if (source == -1)
        return NULL;
    char buffer;
    int length = 0;
    while (read(source, &buffer, 1) != 0)
        ++length;
    close(source);
    char *res = mx_strnew(length);
    if (res == NULL)
        return NULL;
    source = open(file, O_RDWR);
    if (source == -1) {
        free(res);
        return NULL;
    }
    read(source, res, length);
    close(source);
    return res;
}

