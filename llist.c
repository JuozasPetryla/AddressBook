#include <stdlib.h>
#include <stdio.h>
#include "llist.h"

extern LList* llist_init()
{
    Node *head = create_node(NULL);
    Node *tail = create_node(NULL);

    LList *llist = malloc(sizeof(LList));

    llist->head = head;
    llist->tail = tail;

    return llist;
}

extern void llist_append(LList *llist, void *data) 
{
    Node *ptr = create_node(data);

    ptr->next = llist->head->next;
    llist->head->next = ptr;
}
