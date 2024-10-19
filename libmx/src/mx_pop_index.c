#include "../inc/libmx.h"

void mx_pop_index(t_list **list, int index) {
    if (list == NULL)
        return;
    if (index < 1 || *list == NULL || (*list)->next == NULL) {
        mx_pop_front(list);
        return;
    }
    t_list *temp = *list;
    for (int i = 1; i < index; ++i) {
        if (temp->next->next == NULL) {
            mx_pop_back(list);
            return;
        }
        temp = temp->next;
    }
    t_list *del = temp->next;
    temp->next = del->next;
    free(del);
}

