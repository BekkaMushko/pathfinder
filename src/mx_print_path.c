#include "../inc/pathfinder.h"

static void print_chain(t_island *isl, t_bundle *bun, int bundle_n,
                        int from, int to, char **names, char indicator) {
    int curr = from;
    bool found = false;
    while (true) {
        found = false;
        for (int i = 0; i < bundle_n && !found; ++i) {
            if ((isl[curr].name == bun[i].first && isl[bun[i].second].position != -1
                && isl[bun[i].second].weight == isl[curr].weight + bun[i].dist)
                || (isl[curr].name == bun[i].second && isl[bun[i].first].position != -1
                && isl[bun[i].first].weight == isl[curr].weight + bun[i].dist)) {
                found = true;
                if (bun[i].first == to || bun[i].second == to) {
                    if (indicator == 'r') {
                        mx_printstr(names[isl[curr].name]);
                        mx_printstr(" -> ");
                        mx_printstr(names[isl[to].name]);
                    }
                    else {
                        if (bun[i].first != from && bun[i].second != from) {
                            mx_printint(bun[i].dist);
                            mx_printstr(" = ");
                        }
                        mx_printint(isl[to].weight);
                    }
                    return;
                }
                else {
                    if (indicator == 'r')
                        mx_printstr(names[isl[curr].name]);
                    else
                        mx_printint(bun[i].dist);
                    mx_printstr(indicator == 'r' ? " -> " : " + ");
                    curr = isl[curr].name == bun[i].first ? bun[i].second : bun[i].first;
                }
            }
        }
    }
}

void mx_print_path(t_island *islands, t_bundle *bundles,
                     int bundle_n, int from, int to, char **names) {
    mx_printstr("========================================\nPath: ");
    mx_printstr(names[from]);
    mx_printstr(" -> ");
    mx_printstr(names[to]);
    mx_printstr("\nRoute: ");
    print_chain(islands, bundles, bundle_n, from, to, names, 'r');
    mx_printstr("\nDistance: ");
    print_chain(islands, bundles, bundle_n, from, to, names, 'd');
    mx_printstr("\n========================================\n");
}

