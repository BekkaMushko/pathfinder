#include "../inc/libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    const char *ptr = str;
    int count = 0;
    if (str == NULL || sub == NULL)
        return -1;
    if (mx_strncmp(sub, "", 1) == 0)
        return 0;
    while (ptr != NULL) {
        ptr = mx_strstr(ptr, sub);
        if (ptr != NULL)
            ++count;
        else
            break;
        ++ptr;
    }
    return count;
}

