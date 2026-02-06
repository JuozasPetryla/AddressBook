#ifndef LLIST_H
#define LLIST_H

#include <stdbool.h>
#include "node.h"

typedef struct {
    Node *head;
    Node *tail;
} LList;

typedef struct {
    LList *llist;
    Node *curr;
} LListIter;

void llist_prepend(LList *llist, void *data);
void llist_append(LList *llist, void *data);
void llist_insert(LList *llist, void *data, int pos);

LListIter* llist_iter_create(LList *llist);
bool llist_iter_condition(LListIter *llist_iter);
void* llist_iter_next(LListIter *llist_iter);
void llist_iter_free(LListIter *llist_iter);

#endif