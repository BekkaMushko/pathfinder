#include "../inc/pathfinder.h"

static void err_message(char *message, t_bundle **bundles, char ***names) {
    mx_printerr(message);
    free(*bundles);
    mx_del_strarr(names);
}

int mx_err_file_content(long int island_n, t_bundle **bundles,
                        int bundle_n, char ***names, long int names_size) {
    long int sum = 0;
    if (names_size != island_n) {
        err_message("error: invalid number of islands\n", bundles, names);
        return -1;
    }
    for (int i = 0; i < bundle_n - 1; ++i) {
        for (int j = i + 1; j < bundle_n; ++j) {
            if (((*bundles)[i].first == (*bundles)[j].first
                && (*bundles)[i].second == (*bundles)[j].second)
                || ((*bundles)[i].first == (*bundles)[j].second
                && (*bundles)[i].second == (*bundles)[j].first)) {
                err_message("error: duplicate bridges\n", bundles, names);
                return -1;
            }
        }
    }
    for (int i = 0; i < bundle_n; ++i) {
        sum += (*bundles)[i].dist;
        if (sum > INT_MAX) {
            err_message("error: sum of bridges lengths is too big\n", bundles, names);
            return -1;
        }
    }
    return 1;
}

