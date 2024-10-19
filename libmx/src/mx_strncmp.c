#include "../inc/libmx.h"

int mx_strncmp(const char *s1, const char *s2, int n) {
    int i = 0;
    if (n < 0) {
        while (*(s1 + i) != '\0' || *(s2 + i) != '\0') {
            if (*(s1 + i) != *(s2 + i))
                return *(s1 + i) - *(s2 + i);
            ++i;
        }
    }
    else if (n > 0) {
        while ((*(s1 + i) != '\0' || *(s2 + i) != '\0') && i < n) {
            if (*(s1 + i) != *(s2 + i))
                return *(s1 + i) - *(s2 + i);
            ++i;
        }
    }
    return 0;
}

