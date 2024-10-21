#include "../inc/pathfinder.h"

static void reset_position(t_island **islands, long int island_n,
                           int positions[island_n], int indicator) {
    for (long int i = 0; i < island_n; ++i)
        (*islands)[i].position = indicator == -1 ? -1 : positions[i];
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
                    if (i == bun[j].first
                        && (((*isl)[bun[j].second].weight == 0 && bun[j].second != from)
                        || (*isl)[bun[j].second].weight > (*isl)[i].weight + bun[j].dist)) {
                        (*isl)[bun[j].second].weight = (*isl)[i].weight + bun[j].dist;
                        (*isl)[bun[j].second].position = count + 1;
                        settled = true;
                    }
                    else if (i == bun[j].second
                        && (((*isl)[bun[j].first].weight == 0 && bun[j].first != from)
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

static void set_paths(t_island **isl, int island_n, t_bundle *bun, int bundle_n,
                      int from, int to, char **names, int start, int index) {
    (*isl)[from].position = index;
    for (int i = 0; i < island_n; ++i) {
        if (i != from) {
            for (int j = 0; j < bundle_n; ++j) {
                if (from == bun[j].first && i == bun[j].second
                    && (*isl)[bun[j].second].weight == (*isl)[from].weight + bun[j].dist) {
                    if (bun[j].second == to) {
                        (*isl)[bun[j].second].position = index + 1;
                        mx_print_path(*isl, bun, bundle_n, start, to, names);
                        (*isl)[bun[j].second].position = -1;
                    }
                    else
                        set_paths(isl, island_n, bun, bundle_n, bun[j].second, to, names, start, index + 1);
                }
                else if (from == bun[j].second && i == bun[j].first
                    && (*isl)[bun[j].first].weight == (*isl)[from].weight + bun[j].dist) {
                    if (bun[j].first == to) {
                        (*isl)[bun[j].first].position = index + 1;
                        mx_print_path(*isl, bun, bundle_n, start, to, names);
                        (*isl)[bun[j].first].position = -1;
                    }
                    else
                        set_paths(isl, island_n, bun, bundle_n, bun[j].first, to, names, start, index + 1);
                }
            }
        }
    }
    (*isl)[from].position = -1;
}

void mx_process_paths(t_island **islands, long int island_n,
                      t_bundle *bundles, int bundle_n, char **names) {
    int positions[island_n];
    for (long int i = 0; i < island_n - 1; ++i) {
        set_weights(islands, island_n, bundles, bundle_n, i);
        for (long int j = 0; j < island_n; ++j)
            positions[j] = (*islands)[j].position;
        for (long int j = i + 1; j < island_n; ++j) {
            if ((*islands)[j].position != -1) {
                reset_position(islands, island_n, positions, -1);
                set_paths(islands, island_n, bundles, bundle_n, i, j, names, i, 0);
                reset_position(islands, island_n, positions, 0);
            }
        }
        reset_position(islands, island_n, positions, -1);
        reset_weight(islands, island_n);
    }
}

