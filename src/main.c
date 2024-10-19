#include "../inc/pathfinder.h"

int main(int argc, char *argv[]) {
    int fd;
    t_island *islands = NULL;
    t_bundle *bundles = NULL;
    long int island_n = 0;
    int bundle_n = 0;
    long int names_size = 0;
    char **names = (char **)malloc(sizeof(char *));
    names[0] = NULL;

    if (mx_err_open_file(argc, argv, &fd, &names) == -1)
        return -1;
    if (mx_err_read_file(fd, argv[1], &island_n, &bundles, &bundle_n, &names, &names_size) == -1)
        return -1;
    if (mx_err_file_content(island_n, &bundles, bundle_n, &names, names_size) == -1)
        return -1;

    islands = malloc(island_n * sizeof(t_island));
    for (int i = 0; i < island_n; ++i) {
        islands[i].name = i;
        islands[i].position = -1;
        islands[i].weight = 0;
    }

    mx_process_paths(&islands, island_n, bundles, bundle_n, names);

    free(islands);
    free(bundles);
    mx_del_strarr(&names);
}

