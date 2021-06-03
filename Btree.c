#include "Includes.h"

int insertNewElement(Node *node, Node *parentNode, Entry *newEntry) {
    if (node->numberOfEntries == NODE_MAX_ENTRIES) {
        if (node->parentNode) {
            return hadleLeaveNodeOverflow(node, parentNode, newEntry);
        } else {
            handleRootNodeOverflow(node, newEntry);
            return 0;
        }
    } else {
        return addEntryToNode(newEntry, node);
    }
}

int hadleLeaveNodeOverflow(Node *node, Node *parentNode, Entry *newEntry) {
    Node *newLeaveNode;

    newLeaveNode = splitNode(node);
    addEntryToNode(newEntry, newLeaveNode);

    newLeaveNode->entries[0].child = node->number;
    int promotedNewIndex = promoteEntry(newLeaveNode, parentNode);
    if (parentNode->entries[promotedNewIndex + 1].key >= 0) {
        parentNode->entries[promotedNewIndex + 1].child = newLeaveNode->number;
    } else {
        parentNode->nextNode = newLeaveNode->number;
    }

    addNewNodeToFile(newLeaveNode);
    updateNodeByIndex(parentNode->number, parentNode);
}

void handleRootNodeOverflow(Node *node, Entry *newEntry) {
    Node *newRootNode, *newLeaveNode;
    newRootNode = createNodeObject();
    newLeaveNode = splitNode(node);
    addEntryToNode(newEntry, newLeaveNode);

    newLeaveNode->entries[0].child = node->number;
    newRootNode->nextNode = newLeaveNode->number;

    promoteEntry(newLeaveNode, newRootNode);

    addNewNodeToFile(newLeaveNode);
    addNewNodeToFile(newRootNode);
}

Node *splitNode(Node *node) {
    int splitIndex = NODE_MAX_ENTRIES / 2;
    Node *newNode;
    newNode = createNodeObject();
    for (int i = splitIndex + 1; i < NODE_MAX_ENTRIES; i++) {
        addSortedEntryToNode(&node->entries[i], newNode);
        removeEntry(&node->entries[i]);
    }
    return newNode;
}

int promoteEntry(Node *childNode, Node *parentNode) {
    // int index = insertNewElement(parentNode, parentNode->parent, &childNode->entries[0]);
    // removeEntryFromNode(&childNode->entries[0], childNode);
    // return index;
}


