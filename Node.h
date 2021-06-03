#ifndef NODE_H_
#define NODE_H_

#include "Includes.h"

typedef struct Entry {
    int key;
    long int rrn;
    int child;
} Entry;

typedef struct Node {
    int number;
    int numberOfEntries;
    int numberOfChildren;
    Entry entries[NODE_MAX_ENTRIES];
    int parentNode;
    int nextNode;
} Node;

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
