#include "../inc/libmx.h"

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *)) {
    if (lst == NULL || cmp == NULL)
        return lst;
    bool cycle = true;
    while (cycle) {
        bool swap = false;
        t_list *temp = lst;
        while (temp->next != NULL) {
            if (cmp(temp->data, temp->next->data)) {
                void *buffer = temp->data;
                temp->data = temp->next->data;
                temp->next->data = buffer;
                swap = true;
            }
            temp = temp->next;
        }
        cycle = swap;
    }
    return lst;
}

