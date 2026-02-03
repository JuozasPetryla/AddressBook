#include <stdlib.h>
#include <stdio.h>
#include "llist.h"

extern void llist_append(Node *head, void *data) 
{
    Node *ptr = create_node(data);
    
    ptr->next = head->next;
    head->next = ptr;
}
