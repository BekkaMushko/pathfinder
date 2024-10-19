#include "../inc/pathfinder.h"

static void reset_position(t_island **islands, long int island_n) {
    for (long int i = 0; i < island_n; ++i)
        (*islands)[i].position = -1;
}

static void reset_weight(t_island **islands, long int island_n) {
    for (long int i = 0; i < island_n; ++i)
        (*islands)[i].weight = 0;
}

static void set_weights(t_island **isl, long int island_n,
                        t_bundle *bun, int bundle_n, int from) {
    int count = 0;
    bool settled = true;
    (*isl)[from].position = count;
    while (settled) {
        settled = false;
        for (long int i = 0; i < island_n; ++i) {
            if ((*isl)[i].position == count) {
                for (int j = 0; j < bundle_n; ++j) {
                    if ((*isl)[i].name == bun[j].first
                        && (((*isl)[bun[j].second].weight == 0
                        && (*isl)[bun[j].second].name != from)
                        || (*isl)[bun[j].second].weight > (*isl)[i].weight + bun[j].dist)) {
                        (*isl)[bun[j].second].weight = (*isl)[i].weight + bun[j].dist;
                        (*isl)[bun[j].second].position = count + 1;
                        settled = true;
                    }
                    else if ((*isl)[i].name == bun[j].second
                        && (((*isl)[bun[j].first].weight == 0
                        && (*isl)[bun[j].first].name != from)
                        || (*isl)[bun[j].first].weight > (*isl)[i].weight + bun[j].dist)) {
                        (*isl)[bun[j].first].weight = (*isl)[i].weight + bun[j].dist;
                        (*isl)[bun[j].first].position = count + 1;
                        settled = true;
                    }
                }
            }
        }
        ++count;
    }
}

static void set_paths(t_island **isl, t_bundle *bun, int bundle_n,
                      int from, int to, char **names, int start) {
    (*isl)[from].position = 0;
    for (int i = 0; i < bundle_n; ++i) {
        if ((*isl)[from].name == bun[i].first
            && (*isl)[bun[i].second].weight == (*isl)[from].weight + bun[i].dist) {
            if ((*isl)[bun[i].second].name == to) {
                (*isl)[bun[i].second].position = 0;
                mx_print_path(*isl, bun, bundle_n, start, to, names);
                (*isl)[bun[i].second].position = -1;
            }
            else
                set_paths(isl, bun, bundle_n, bun[i].second, to, names, start);
        }
        else if ((*isl)[from].name == bun[i].second
            && (*isl)[bun[i].first].weight == (*isl)[from].weight + bun[i].dist) {
            if ((*isl)[bun[i].first].name == to) {
                (*isl)[bun[i].first].position = 0;
                mx_print_path(*isl, bun, bundle_n, start, to, names);
                (*isl)[bun[i].first].position = -1;
            }
            else
                set_paths(isl, bun, bundle_n, bun[i].first, to, names, start);
        }
    }
    (*isl)[from].position = -1;
}

void mx_process_paths(t_island **islands, long int island_n,
                      t_bundle *bundles, int bundle_n, char **names) {
    for (long int i = 0; i < island_n - 1; ++i) {
        for (int j = i + 1; j < island_n; ++j) {
            set_weights(islands, island_n, bundles, bundle_n, i);
            if ((*islands)[j].position != -1) {
                reset_position(islands, island_n);
                set_paths(islands, bundles, bundle_n, i, j, names, i);
            }
            reset_position(islands, island_n);
            reset_weight(islands, island_n);
        }
    }
}

