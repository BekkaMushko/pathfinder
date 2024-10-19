#include "../inc/libmx.h"

void mx_push_back(t_list **list, void *data) {
    t_list *node = mx_create_node(data);
    if (node == NULL)
        return;
    if (*list == NULL) {
        *list = node;
        return;
    }
    t_list *temp = *list;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = node;
}

