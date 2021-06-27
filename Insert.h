#ifndef INSERT_H_
#define INSERT_H_

#include "Includes.h"

int insertNewEntry(BTree *bTree, Entry *newEntry, Search *search);
int hadleLeaveNodeOverflow(BTree *bTree, int nodeIndex, Entry *newEntry, Search *search);
int handleRootNodeOverflow(BTree *bTree, int nodeIndex, Entry *newEntry, Search *search);
Node *splitNode(BTree *bTree, Node *node, Entry *newEntry);
int promoteEntry(BTree *bTree, Node *childNode, Search *search);

#endif
