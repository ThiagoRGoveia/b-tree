#ifndef BTREE_H_
#define BTREE_H_

#include "Includes.h"

BTree *createBTree();
BTree *loadOrCreateBTree();
Node *createNewNode(BTree *bTree);
void writeBTreeHeader(BTree *bTree);

#endif
