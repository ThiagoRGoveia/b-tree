#ifndef INSERT_H_
#define INSERT_H_

#include "Includes.h"

int insertNewElement(Node *node, Entry *newEntry);
int hadleLeaveNodeOverflow(Node *node, Entry *newEntry);
void handleRootNodeOverflow(Node *node, Entry *newEntry);
Node *splitNode(Node *node);
int promoteEntry(Node *childNode);


#endif
