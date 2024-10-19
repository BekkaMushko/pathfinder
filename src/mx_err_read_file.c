#include "../inc/pathfinder.h"

static void print_line_error(int line, char **str, int fd,
                             t_bundle **bundles, char ***names) {
    char *n = mx_itoa(line);
    mx_printerr("error: line ");
    mx_printerr(n);
    mx_printerr(" is not valid\n");
    mx_strdel(&n);
    mx_strdel(str);
    free(*bundles);
    mx_del_strarr(names);
    close(fd);
}

static int search_index(char *str, char ***names, long int *names_size) {
    for (long int i = 0; i < *names_size; ++i) {
        if (mx_strcmp(str, (*names)[i]) == 0)
            return i;
    }
    (*names) = (char **)mx_realloc((*names), (*names_size + 2) * sizeof(char *));
    (*names)[*names_size] = mx_strdup(str);
    (*names)[*names_size + 1] = NULL;
    ++(*names_size);
    return *names_size - 1;
}

static int read_data(int fd, char delim, t_bundle **bundles,
                     int bundle_n, char ***names, long int *names_size) {
    char *str = NULL;
    int n = mx_read_line(&str, 1, delim, fd);
    if (n == -1)
        return 0;
    bool correct = true;
    for (int i = 0; n > 0 && str[i] != '\0'; ++i) {
        if ((delim != '\n' && !mx_isalpha(str[i])) || (delim == '\n'
            && (!mx_isdigit(str[i]) || (i == 0 && str[0] == '0'))))
            correct = false;
    }
    if (n < 1 || !correct) {
        print_line_error(bundle_n + 2, &str, fd, bundles, names);
        return -1;
    }
    if (delim == '\n')
        (*bundles)[bundle_n].dist = mx_atoi(str);
    else if (delim == ',') {
        (*bundles)[bundle_n].second = search_index(str, names, names_size);
        if ((*bundles)[bundle_n].first == (*bundles)[bundle_n].second) {
            print_line_error(bundle_n + 2, &str, fd, bundles, names);
            return -1;
        }
    }
    else {
        *bundles = mx_realloc(*bundles, (bundle_n + 1) * sizeof(t_bundle));
        (*bundles)[bundle_n].first = search_index(str, names, names_size);
    }
    mx_strdel(&str);
    return 1;
}

static int read_first_line(int fd, char *file, long int *island_n, char ***names) {
    char *str = NULL;
    int n = mx_read_line(&str, 1, '\n', fd);
    bool correct = true;
    for (int i = 0; n > 0 && str[i] != '\0'; ++i) {
        if (!mx_isdigit(str[i]) || (i == 0 && str[0] == '0'))
            correct = false;
    }
    if (n < 1 || !correct || mx_atoi(str) > INT_MAX) {
        if (n < 0) {
            mx_printerr("error: file ");
            mx_printerr(file);
            mx_printerr(" is empty\n");
        }
        else
            mx_printerr("error: line 1 is not valid\n");
        mx_strdel(&str);
        mx_del_strarr(names);
        close(fd);
        return -1;
    }
    *island_n = mx_atoi(str);
    mx_strdel(&str);
    return 1;
}

int mx_err_read_file(int fd, char *file, long int *island_n, t_bundle **bundles,
                     int *bundle_n, char ***names, long int *names_size) {
    int n = read_first_line(fd, file, island_n, names);
    if (n == -1)
        return -1;
    while (true) {
        n = read_data(fd, '-', bundles, *bundle_n, names, names_size);
        if (n == 0)
            break;
        else if (n == -1)
            return -1;
        n = read_data(fd, ',', bundles, *bundle_n, names, names_size);
        if (n < 1)
            return -1;
        n = read_data(fd, '\n', bundles, *bundle_n, names, names_size);
        if (n < 1)
            return -1;
        ++(*bundle_n);
    }
    close(fd);
    return 1;
}

