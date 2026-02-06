#ifndef LLIST_H
#define LLIST_H

#include "node.h"

typedef struct {
    Node *head;
    Node *tail;
} LList;

void llist_prepend(LList *llist, void *data);
void llist_append(LList *llist, void *data);
void llist_insert(LList *llist, void *data, int pos);

#endif