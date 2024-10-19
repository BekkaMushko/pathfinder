#include "../inc/libmx.h"

static int calculsize(int number) {
    int size = 1;
    if (number < 0)
        ++size;
    while (number / 10 != 0) {
        number /= 10;
        ++size;
    }
    return size;
}

static void fillres(int size, char res[size], int start, int number) {
    int delim;
    for (int i = 0; i <= size; ++i) {
        delim = (int)mx_pow(10, size - i);
        res[start + i] = number / delim + 48;
        number %= delim;
    }
}

char *mx_itoa(int number) {
    int size = calculsize(number);
    char *res = mx_strnew(size);
    if (res == NULL)
        return NULL;
    --size;
    if (number < 0) {
        res[0] = '-';
        --size;
        if (number == -2147483648) {
            res[1] = '2';
            number = -147483648;
            --size;
        }
        number *= -1;
    }
    int start = 0;
    while (res[start] != '\0')
        ++start;
    fillres(size, res, start, number);
    return res;
}

