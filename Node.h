#ifndef NODE_H_
#define NODE_H_

#include "Includes.h"

Node *getNodeByIndex(int index);
void updateNodeByIndex(int index, Node *node);
Node *createNodeObject();
int addNewNodeToFile(Node *node);
int getNumberOfNodesFromFile();
int addEntryToNode(Entry *entry, Node *node);
int checkIfNodeIsFull(Node *node);
void addSortedEntryToNode(Entry *entry, Node *node);
void removeEntryAndRearrangeNode(Entry *entry, Node *node);
void removeEntry(Entry *entry);

#endif
