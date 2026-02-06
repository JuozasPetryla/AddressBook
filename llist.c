#include <stdlib.h>
#include <stdio.h>
#include "llist.h"

extern void llist_prepend(LList *llist, void *data) 
{
    Node *node = create_node(data);

    if (llist->head == NULL && llist->tail == NULL) {
        llist->head = node;
        llist->tail = node;
    } else {
        node->next = llist->head;
        llist->head = node;
    }
}

extern void llist_append(LList *llist, void *data)
{
    Node *node = create_node(data);

    if (llist->head == NULL && llist->tail == NULL) {
        llist->head = node;
        llist->tail = node;
    } else {
        llist->tail->next = node;
        llist->tail = node;
    }
}

extern void llist_insert(LList *llist, void *data, int pos)
{
    Node *curr = llist->head;
    for (int i = 0; i < pos - 1; ++i) {
        curr = curr->next;
    }
    
    if (curr == llist->tail) {
        llist_append(llist, data);
    } else if (curr == llist->head) {
        llist_prepend(llist, data);
    } else {
        Node *node = create_node(data);
        node->next = curr->next;
        curr->next = node;
    }
}
