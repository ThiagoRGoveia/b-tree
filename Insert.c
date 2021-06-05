#include "Includes.h"

int insertNewElement(BTree *bTree, Node *node, Entry *newEntry) {
    if (node->numberOfEntries == NODE_MAX_ENTRIES) {
        if (node->parentNode > 0) {
            return hadleLeaveNodeOverflow(bTree, node, newEntry);
        } else {
            // printf("0\n");
            handleRootNodeOverflow(bTree, node, newEntry);
            return 0;
        }
    } else {
        return addEntryToNode(newEntry, node);
    }
}

int hadleLeaveNodeOverflow(BTree *bTree, Node *node, Entry *newEntry) {
    Node *newLeaveNode, *parentNode;
    parentNode = getNodeByIndex(node->index);

    newLeaveNode = splitNode(bTree, node, newEntry);
    addEntryToNode(newEntry, newLeaveNode);
    newLeaveNode->entries[0].child = node->index;

    int promotedNewIndex = promoteEntry(bTree, newLeaveNode, parentNode);
    if (parentNode->entries[promotedNewIndex + 1].key >= 0) {
        parentNode->entries[promotedNewIndex + 1].child = newLeaveNode->index;
    } else {
        parentNode->nextNode = newLeaveNode->index;
    }

    addNewNodeToFile(newLeaveNode);
    updateNode(node);
    updateNode(parentNode);
    updateNode(newLeaveNode);
}

void handleRootNodeOverflow(BTree *bTree, Node *node, Entry *newEntry) {
    Node *newRootNode, *newLeaveNode;

    newRootNode = createNewNode(bTree);
    newLeaveNode = splitNode(bTree, node, newEntry);

    bTree->rootNode = newRootNode;

    newLeaveNode->entries[0].child = node->index;
    newRootNode->nextNode = newLeaveNode->index;
    newLeaveNode->parentNode = newRootNode->index;
    node->parentNode = newRootNode->index;

    promoteEntry(bTree, newLeaveNode, newRootNode);

    updateNode(newRootNode);
    updateNode(node);
    updateNode(newLeaveNode);
    free(newLeaveNode);
    free(node);
}

Node *splitNode(BTree *bTree, Node *node, Entry *newEntry) {
    int middle = NODE_MAX_ENTRIES / 2, splitIndex, isNewKeySmaller;
    Node *newNode;
    newNode = createNewNode(bTree);
    if (node->entries[middle].key > newEntry->key) {
        isNewKeySmaller = 1;
        splitIndex = middle - 1;
    } else {
        isNewKeySmaller = 0;
        splitIndex = middle;
    }
    for (int i = splitIndex; i < NODE_MAX_ENTRIES; i++) {
        addSortedEntryToNode(&node->entries[i], newNode);
        removeEntry(&node->entries[i]);
        node->numberOfEntries--;
    }
    if (isNewKeySmaller) {
        addEntryToNode(newEntry, node);
    } else {
        addEntryToNode(newEntry, newNode);
    }
    newNode->parentNode = node->parentNode;
    node->numberOfEntries = splitIndex;
    return newNode;
}

int promoteEntry(BTree *bTree, Node *childNode, Node *parentNode) {
    int index = insertNewElement(
        bTree,
        parentNode,
        &childNode->entries[0]
    );
    removeEntryAndRearrangeNode(&childNode->entries[0], childNode);
    return index;
}


