#include "../inc/pathfinder.h"

int mx_err_open_file(int argc, char *argv[], int *fd, char ***names) {
    if (argc != 2) {
        mx_printerr("usage: ./pathfinder [filename]\n");
        mx_del_strarr(names);
        return -1;
    }
    *fd = open(argv[1], O_RDWR);
    if (*fd == -1) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" does not exist\n");
        mx_del_strarr(names);
        return -1;
    }
    return 1;
}

