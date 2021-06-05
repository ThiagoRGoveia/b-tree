#include "Includes.h"


int insertNewElement(Node *node, Entry *newEntry) {
    if (node->numberOfEntries == NODE_MAX_ENTRIES) {
        if (node->parentNode > 0) {
            return hadleLeaveNodeOverflow(node, newEntry);
        } else {
            handleRootNodeOverflow(node, newEntry);
            return 0;
        }
    } else {
        return addEntryToNode(newEntry, node);
    }
}

int hadleLeaveNodeOverflow(Node *node, Entry *newEntry) {
    Node *newLeaveNode;

    newLeaveNode = splitNode(node);
    addEntryToNode(newEntry, newLeaveNode);
    newLeaveNode->entries[0].child = node->index;

    Node *parentNode;
    parentNode = getNodeByIndex(node->parentNode);

    int promotedNewIndex = promoteEntry(newLeaveNode);
    if (parentNode->entries[promotedNewIndex + 1].key >= 0) {
        parentNode->entries[promotedNewIndex + 1].child = newLeaveNode->index;
    } else {
        parentNode->nextNode = newLeaveNode->index;
    }

    addNewNodeToFile(newLeaveNode);
    updateNodeByIndex(parentNode->index, parentNode);
}

void handleRootNodeOverflow(Node *node, Entry *newEntry) {
    Node *newRootNode, *newLeaveNode;
    newRootNode = createNodeObject();
    newLeaveNode = splitNode(node);
    addEntryToNode(newEntry, newLeaveNode);

    newLeaveNode->entries[0].child = node->index;
    newRootNode->nextNode = newLeaveNode->index;
    newLeaveNode->parentNode = newRootNode->index;
    node->parentNode = newRootNode->index;

    promoteEntry(newLeaveNode);

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
    newNode->parentNode = node->parentNode;
    return newNode;
}

int promoteEntry(Node *childNode) {
    int index = insertNewElement(
        getNodeByIndex(childNode->parentNode),
        &childNode->entries[0]
    );
    removeEntryAndRearrangeNode(&childNode->entries[0], childNode);
    return index;
}


