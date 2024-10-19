#include "../inc/libmx.h"

void mx_push_index(t_list **list, void *data, int index) {
    if (list == NULL)
        return;
    if (index < 1 || *list == NULL) {
        mx_push_front(list, data);
        return;
    }
    t_list *temp = *list;
    for (int i = 1; i < index; ++i) {
        if (temp->next == NULL) {
            mx_push_back(list, data);
            return;
        }
        temp = temp->next;
    }
    t_list *node = mx_create_node(data);
    if (node == NULL)
        return;
    node->next = temp->next;
    temp->next = node;
}

