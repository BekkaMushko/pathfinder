#include "../inc/pathfinder.h"

static void print_chain(t_island *isl, t_bundle *bun, int bundle_n,
                        int from, int to, char **names, char indicator) {
    int curr = from;
    int index = 1;
    bool found = false;
    while (true) {
        found = false;
        for (int i = 0; i < bundle_n && !found; ++i) {
            if ((curr == bun[i].first && isl[bun[i].second].position == index)
                || (curr == bun[i].second && isl[bun[i].first].position == index)) {
                found = true;
                ++index;
                if (bun[i].first == to || bun[i].second == to) {
                    if (indicator == 'r') {
                        mx_printstr(names[curr]);
                        mx_printstr(" -> ");
                        mx_printstr(names[to]);
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
                        mx_printstr(names[curr]);
                    else
                        mx_printint(bun[i].dist);
                    mx_printstr(indicator == 'r' ? " -> " : " + ");
                    curr = curr == bun[i].first ? bun[i].second : bun[i].first;
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

