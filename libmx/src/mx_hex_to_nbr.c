#include "../inc/libmx.h"

static void calculres(unsigned long *res, const char *hex, int len) {
    unsigned long n;
    for (int i = 0; i < len; ++i) {
        if (mx_isdigit(hex[len - 1 - i]))
            n = hex[len - 1 - i] - 48;
        else if (mx_isalpha(hex[len - 1 - i])) {
            if (mx_islower(hex[len - 1 - i])
                && hex[len - 1 - i] >= 97 && hex[len - 1 - i] <= 102)
                n = hex[len - 1 - i] - 87;
            else if (mx_isupper(hex[len - 1 - i])
                     && hex[len - 1 - i] >= 65 && hex[len - 1 - i] <= 70)
                n = hex[len - 1 - i] - 55;
            else {
                *res = 0;
                return;
            }
        }
        else {
            *res = 0;
            return;
        }
        for (int j = 1; j <= i; ++j)
            n *= 16;
        *res += n;
    }
}

unsigned long mx_hex_to_nbr(const char *hex) {
    if (hex == NULL)
        return 0;
    unsigned long res = 0;
    int len = 0;
    while (*(hex + len) != '\0')
        ++len;
    if (len < 1 || len > 16)
        return 0;
    calculres(&res, hex, len);
    return res;
}

