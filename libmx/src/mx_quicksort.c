#include "../inc/libmx.h"

static void swap_el(char **s1, char **s2, int *swaps) {
    char *buff = *s1;
    *s1 = *s2;
    *s2 = buff;
    ++(*swaps);
}

static int partition(char **arr, int *less, int *great) {
    int pivot = *great;
    int equal = *less;
    int swaps = 0;
    while (equal <= *great) {
        if (mx_strlen(arr[equal]) < mx_strlen(arr[pivot])) {
            if (mx_strlen(arr[equal]) < mx_strlen(arr[*less]))
                swap_el(&arr[equal], &arr[*less], &swaps);
            if (equal == *less)
                ++equal;
            ++(*less);
        }
        else if (mx_strlen(arr[equal]) > mx_strlen(arr[pivot])) {
            if (mx_strlen(arr[equal]) > mx_strlen(arr[*great]))
                swap_el(&arr[equal], &arr[*great], &swaps);
            --(*great);
        }
        else
            ++equal;
    }
    return swaps;
}

int mx_quicksort(char **arr, int left, int right) {
    if (arr == NULL)
        return -1;
    int swaps = 0;
    if (left >= 0 && left < right) {
        int less = left;
        int great = right;
        swaps += partition(arr, &less, &great);
        swaps += mx_quicksort(arr, left, less - 1);
        swaps += mx_quicksort(arr, great + 1, right);
    }
    return swaps;
}

