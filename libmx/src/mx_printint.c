#include "../inc/libmx.h"

void mx_printint(int n) {
    char c;
    if (n < 0) {
        write(1, "-", 1);
        if (n == -2147483648) {
            write(1, "2", 1);
            n = -147483648;
        }
        n *= -1;
    }
    if (n / 10 == 0)
        c = n + 48;
    else {
        mx_printint(n / 10);
        c = n % 10 + 48;
    }
    write(1, &c, 1);
}

