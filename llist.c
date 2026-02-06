#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "util.h"
#include "llist.h"

// LINKED LIST METHODS

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

    llist->size++;
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

    llist->size++;
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

        llist->size++;
    }
}

extern void* llist_find_pos(LList *llist, int pos) 
{
    if (pos >= (int)llist->size) {
        return NULL;
    } else {
        Node *curr = llist->head;
        for (int i = 0; i < pos; ++i) {
            curr = curr->next;
        }
        return curr->data;
    }
}

extern void* llist_find_str(LList *llist, const char* input_str)
{
    Node *curr = llist->head;
    while (curr != NULL) {
        if (contains(curr->data, input_str)) {
            return curr->data;
        }
        curr = curr->next;
    }
    return NULL;
}

// LINKED LIST ITERATOR

extern LListIter* llist_iter_create(LList *llist)
{
    LListIter *llist_iter = (LListIter*)malloc(sizeof(LListIter));
    if (!llist_iter) return NULL;

    llist_iter->llist = llist;
    llist_iter->curr = llist->head;

    return llist_iter;
}

extern bool llist_iter_condition(LListIter *llist_iter) 
{

    return llist_iter->curr != NULL;
}

extern void* llist_iter_next(LListIter *llist_iter) 
{
    if (!llist_iter->curr) return NULL;

    void *data = llist_iter->curr->data;
    llist_iter->curr = llist_iter->curr->next;

    return data;
}

extern void llist_iter_free(LListIter *llist_iter)
{
    free(llist_iter);
}
