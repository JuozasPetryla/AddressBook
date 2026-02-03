#include <stdlib.h>
#include "node.h"

Node* create_node(void *data) 
{
    Node *node = malloc(sizeof(Node));

    node->next = NULL;
    node->data = data;

    return node;
}
