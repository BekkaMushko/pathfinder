#include "../inc/libmx.h"

int mx_factorial(int n) {
    long int result = 1;
    if (n < 0)
        return 0;
    for (int i = n; i > 1; --i)
        result *= i;
    return result > 2147483647 ? 0 : result;
}

