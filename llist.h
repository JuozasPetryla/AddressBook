#ifndef LLIST_H
#define LLIST_H

#include "node.h"

typedef struct {
    Node *head;
    Node *tail;
} LList;

LList* llist_init();
void llist_append(LList *llist, void *data);

#endif