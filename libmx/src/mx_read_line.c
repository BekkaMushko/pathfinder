#include "../inc/libmx.h"

static int fill_stat(char **stat_buf, int size, char *buf, int start) {
    if (size < 1)
        return 1;
    *stat_buf = mx_strnew(size);
    if (*stat_buf == NULL)
        return -2;
    for (int i = 0; i < size; ++i)
        (*stat_buf)[i] = buf[start + i];
    return 0;
}

static void concat_stat(char **stat_buf, char *buf, int *n) {
    int stat_len = mx_strlen(*stat_buf);
    *stat_buf = mx_realloc(*stat_buf, sizeof(char) * (stat_len + *n + 1));
    if (*stat_buf == NULL)
        return;
    for (int i = 0; i < *n; ++i)
        (*stat_buf)[stat_len + i] = buf[i];
    (*stat_buf)[stat_len + *n] = '\0';
    *n = 0;
}

static int read_from_stat(char **lineptr, char delim, char **stat_buf, int *res,
                          bool *alloc) {
    int stat_len = mx_strlen(*stat_buf);
    int delim_index = mx_get_char_index(*stat_buf, delim);
    char stat_rests[stat_len - delim_index - 1];
    int temp = *res;
    *res += delim_index >= 0 ? delim_index : stat_len;
    *lineptr = mx_strnew(sizeof(char) * (*res + 1));
    if (*lineptr == NULL)
        return -2;
    *alloc = false;
    (*lineptr)[*res] = '\0';
    for (int i = 0; i < delim_index || (delim_index < 0 && i < stat_len); ++i)
        (*lineptr)[temp + i] = (*stat_buf)[i];
    if (delim_index >= 0) {
        for (int i = 0; i < stat_len - delim_index - 1; ++i)
            stat_rests[i] = (*stat_buf)[delim_index + 1 + i];
    }
    mx_strdel(stat_buf);
    if (delim_index >= 0)
        return fill_stat(stat_buf, stat_len - delim_index - 1, stat_rests, 0);
    return 0;
}

static int read_from_file(char **lineptr, char *buf, char delim, int *res, int n,
                          char **stat_buf, bool *alloc) {
    int delim_index = mx_get_char_index(buf, delim);
    int temp = *res;
    *res += delim_index >= 0 ? delim_index : n;
    *lineptr = *alloc ? mx_strnew(sizeof(char) * (*res + 1)) : mx_realloc(*lineptr, sizeof(char) * (*res + 1));
    if (*lineptr == NULL)
        return -2;
    *alloc = false;
    (*lineptr)[*res] = '\0';
    for (int i = 0; i < delim_index || (delim_index < 0 && i < n); ++i)
        (*lineptr)[temp + i] = buf[i];
    if (delim_index >= 0)
        return fill_stat(stat_buf, n - delim_index - 1, buf, delim_index + 1);
    return 0;
}

int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd) {
    static char *stat_buf = NULL;
    int res = 0;
    int err_handle = 0;
    bool alloc = true;
    char buf[buf_size + 1];
    buf[buf_size] = '\0';
    int n = read(fd, buf, buf_size);
    if (n < 1)
        err_handle = n < 0 ? -2 : n == 0 && stat_buf == NULL ? -1 : 0;
    if (stat_buf != NULL && err_handle == 0) {
        concat_stat(&stat_buf, buf, &n);
        err_handle = stat_buf ? read_from_stat(lineptr, delim, &stat_buf, &res, &alloc) : -2;
    }
    while (stat_buf == NULL && err_handle == 0) {
        err_handle = n != 0 ? read_from_file(lineptr, buf, delim, &res, n, &stat_buf, &alloc) : 0;
        if (stat_buf == NULL && err_handle == 0) {
            n = read(fd, buf, buf_size);
            if (n < 1)
                err_handle = n < 0 ? -2 : n == 0 && res == 0 ? -1 : 1;
        }
    }
    return err_handle < 0 ? err_handle : res;
}

