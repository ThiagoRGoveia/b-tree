#ifndef INSERT_H_
#define INSERT_H_

#include "Includes.h"

int insertNewElement(BTree *bTree, Node *node, Entry *newEntry);
int hadleLeaveNodeOverflow(BTree *bTree, Node *node, Entry *newEntry);
void handleRootNodeOverflow(BTree *bTree, Node *node, Entry *newEntry);
Node *splitNode(BTree *bTree, Node *node);
int promoteEntry(BTree *bTree, Node *childNode);


#endif
