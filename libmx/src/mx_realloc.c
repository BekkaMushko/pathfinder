#include "../inc/libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    if (ptr == NULL)
        return malloc(size);
    if (size == 0) {
        free(ptr);
        return NULL;
    }
    if (size <= malloc_usable_size(ptr))
        return ptr;
    void *res = malloc(size);
    if (res == NULL)
        return res;
    mx_memcpy(res, ptr, malloc_usable_size(ptr));
    free(ptr);
    return res;
}

