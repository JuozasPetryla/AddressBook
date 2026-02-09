#ifndef LLIST_H
#define LLIST_H

#include <stdbool.h>
#include <stdlib.h>
#include "node.h"

typedef struct {
    Node *head;
    Node *tail;
    size_t size;
} LList;

typedef struct {
    LList *llist;
    Node *curr;
} LListIter;


// LINKED LIST METHODS
void llist_init(LList *llist);
bool llist_remove_all(LList *llist);
void llist_prepend(LList *llist, void *data);
void llist_append(LList *llist, void *data);
bool llist_insert(LList *llist, void *data, int pos);
void* llist_remove(LList *llist, int pos);
void* llist_find_pos(LList *llist, int pos);
LList* llist_find_str(LList *llist, const char* str);

// LINKED LIST ITERATOR METHODS
LListIter* llist_iter_create(LList *llist);
bool llist_iter_condition(LListIter *llist_iter);
void* llist_iter_next(LListIter *llist_iter);
void llist_iter_free(LListIter *llist_iter);

#endif