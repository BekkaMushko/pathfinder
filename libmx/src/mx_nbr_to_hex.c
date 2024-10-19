#include "../inc/libmx.h"

char *mx_nbr_to_hex(unsigned long nbr) {
    int counter = 1;
    unsigned long original;
    if (nbr < 0 || nbr > ULONG_MAX)
        original = 0;
    else {
        original = nbr;
        while (nbr / 16 != 0) {
            ++counter;
            nbr /= 16;
        }
    }
    char *res = mx_strnew(counter);
    if (res == NULL)
        return NULL;
    for (int i = counter - 1; i >= 0; --i) {
        res[i] = original % 16 > 9 ? original % 16 + 87 : original % 16 + 48;
        original /= 16;
    }
    return res;
}

