#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "../libmx/inc/libmx.h"

typedef struct s_bundle {
    int first;
    int second;
    unsigned int dist;
}              t_bundle;

typedef struct s_island {
    int position;
    unsigned int weight;
}              t_island;

int mx_err_open_file(int argc, char *argv[], int *fd, char ***names);
int mx_err_read_file(int fd, char *file, long int *island_n, t_bundle **bundles, int *bundle_n, char ***names, long int *names_size);
int mx_err_file_content(long int island_n, t_bundle **bundles, int bundle_n, char ***names, long int names_size);
void mx_process_paths(t_island **islands, long int island_n, t_bundle *bundles, int bundle_n, char **names);
void mx_print_path(t_island *islands, t_bundle *bundles, int bundle_n, int from, int to, char **names);

#endif

