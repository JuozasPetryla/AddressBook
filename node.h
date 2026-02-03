#ifndef NODE_H
#define NODE_H

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

Node* create_node(void *data);

#endif