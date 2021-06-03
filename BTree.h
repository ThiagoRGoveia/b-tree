#ifndef BTREE_H_
#define BTREE_H_

#include "Includes.h"

typedef struct BTree {
    int numberOfNodes;
    Node *node;
} BTree;

int insertNewElement(Node *node, Node *parentNode, Entry *newEntry);
int hadleLeaveNodeOverflow(Node *node, Node *parentNode, Entry *newEntry);
void handleRootNodeOverflow(Node *node, Entry *newEntry);
Node *splitNode(Node *node);
int promoteEntry(Node *childNode, Node *parentNode);

#endif
