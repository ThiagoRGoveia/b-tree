#include "Includes.h"

int insertNewElement(BTree *bTree, Node *node, Entry *newEntry) {
    // printf("NODE NUMBER_OF_ENTRIES %d\n", node->numberOfEntries);
    if (node->numberOfEntries == NODE_MAX_ENTRIES) {
        if (node->parentNode > 0) {
            // printf("SPLIT_LEAVE_NODE\n");
            return hadleLeaveNodeOverflow(bTree, node, newEntry);
        } else {
            // printf("SPLIT_ROOT_NODE\n");
            handleRootNodeOverflow(bTree, node, newEntry);
            return 0;
        }
    } else {
        // printf("ADD_ENTRY\n");
        return addEntryToNode(newEntry, node);
    }
}

int hadleLeaveNodeOverflow(BTree *bTree, Node *node, Entry *newEntry) {
    Node *newLeaveNode, *parentNode;
    // printf("SPLIT_LEAVE_NODE.1\n");
    parentNode = getNodeByIndex(node->parentNode);
    // printf("SPLIT_LEAVE_NODE.2\n");
    newLeaveNode = splitNode(bTree, node, newEntry);
    // printf("SPLIT_LEAVE_NODE.3\n");

    // newLeaveNode->entries[0].child = node->index;

    int promotedNewIndex = promoteEntry(bTree, newLeaveNode, parentNode);
    // printf("SPLIT_LEAVE_NODE.4\n");

    if (parentNode->entries[promotedNewIndex + 1].key >= 0) {
        parentNode->entries[promotedNewIndex + 1].child = newLeaveNode->index;
    } else {
        parentNode->nextNode = newLeaveNode->index;
    }

    parentNode->entries[promotedNewIndex].child = node->index;
    printf("---\n");
    printf("promotedNewIndex %d\n", promotedNewIndex);
    printf("Index %d\n", parentNode->index);
    for (int i=0; i < 8; i++) {
        printf("Key [%d] %d\n", i, parentNode->entries[i].key);
        printf("Child [%d] %d\n", i, parentNode->entries[i].child);
    }
    printf("Next node %d\n", parentNode->nextNode);
    printf("Parent %d\n", parentNode->parentNode);
    printf("Number of entries %d\n", parentNode->numberOfEntries);
    printf("---\n");
    // printf("SPLIT_LEAVE_NODE.5\n");

    updateNode(node);
    updateNode(parentNode);
    updateNode(newLeaveNode);
    free(parentNode);
    free(newLeaveNode);
    // printf("SPLIT_LEAVE_NODE.6\n");
}

void handleRootNodeOverflow(BTree *bTree, Node *node, Entry *newEntry) {
    Node *newRootNode, *newLeaveNode;
    // printf("SPLIT_ROOT_NODE.1\n");

    newRootNode = createNewNode(bTree);
    // printf("SPLIT_ROOT_NODE.2\n");
    newLeaveNode = splitNode(bTree, node, newEntry);
    // printf("SPLIT_ROOT_NODE.3\n");

    bTree->rootNode = newRootNode;

    newLeaveNode->entries[0].child = node->index;
    newRootNode->nextNode = newLeaveNode->index;
    newLeaveNode->parentNode = newRootNode->index;
    node->parentNode = newRootNode->index;

    promoteEntry(bTree, newLeaveNode, newRootNode);
    // printf("SPLIT_ROOT_NODE.4\n");
    updateNode(newRootNode);
    updateNode(node);
    updateNode(newLeaveNode);
    // printf("SPLIT_ROOT_NODE.5\n");
    free(newLeaveNode);
    free(node);
    // printf("SPLIT_ROOT_NODE.6\n");
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


