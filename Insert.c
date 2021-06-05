#include "Includes.h"

int insertNewElement(BTree *bTree, Node *node, Entry *newEntry) {
    if (node->numberOfEntries == NODE_MAX_ENTRIES) {
        if (node->parentNode > 0) {
            return hadleLeaveNodeOverflow(bTree, node, newEntry);
        } else {
            handleRootNodeOverflow(bTree, node, newEntry);
            return 0;
        }
    } else {
        return addEntryToNode(newEntry, node);
    }
}

int hadleLeaveNodeOverflow(BTree *bTree, Node *node, Entry *newEntry) {
    Node *newLeaveNode;

    newLeaveNode = splitNode(bTree, node);
    addEntryToNode(newEntry, newLeaveNode);
    newLeaveNode->entries[0].child = node->index;

    Node *parentNode;
    parentNode = getNodeByIndex(node->parentNode);

    int promotedNewIndex = promoteEntry(bTree, newLeaveNode);
    if (parentNode->entries[promotedNewIndex + 1].key >= 0) {
        parentNode->entries[promotedNewIndex + 1].child = newLeaveNode->index;
    } else {
        parentNode->nextNode = newLeaveNode->index;
    }

    addNewNodeToFile(newLeaveNode);
    updateNodeByIndex(parentNode->index, parentNode);
}

void handleRootNodeOverflow(BTree *bTree, Node *node, Entry *newEntry) {
    Node *newRootNode, *newLeaveNode;
    newRootNode = createNewNode(bTree);
    newLeaveNode = splitNode(bTree, node);
    addEntryToNode(newEntry, newLeaveNode);

    newLeaveNode->entries[0].child = node->index;
    newRootNode->nextNode = newLeaveNode->index;
    newLeaveNode->parentNode = newRootNode->index;
    node->parentNode = newRootNode->index;

    promoteEntry(bTree, newLeaveNode);

    addNewNodeToFile(newLeaveNode);
    addNewNodeToFile(newRootNode);
}

Node *splitNode(BTree *bTree, Node *node) {
    int splitIndex = NODE_MAX_ENTRIES / 2;
    Node *newNode;
    newNode = createNewNode(bTree);
    for (int i = splitIndex + 1; i < NODE_MAX_ENTRIES; i++) {
        addSortedEntryToNode(&node->entries[i], newNode);
        removeEntry(&node->entries[i]);
    }
    newNode->parentNode = node->parentNode;
    return newNode;
}

int promoteEntry(BTree *bTree, Node *childNode) {
    int index = insertNewElement(
        bTree,
        getNodeByIndex(childNode->parentNode),
        &childNode->entries[0]
    );
    removeEntryAndRearrangeNode(&childNode->entries[0], childNode);
    return index;
}


