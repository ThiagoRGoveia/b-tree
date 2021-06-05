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
    Node *newLeaveNode;
    newLeaveNode = splitNode(bTree, node);
    printf("2\n");
    addEntryToNode(newEntry, newLeaveNode);
    printf("3\n");
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
    updateNode(parentNode);
}

void handleRootNodeOverflow(BTree *bTree, Node *node, Entry *newEntry) {
    Node *newRootNode, *newLeaveNode;

    newRootNode = createNewNode(bTree);

    addNewNodeToFile(newRootNode);
    newLeaveNode = splitNode(bTree, node);
    addNewNodeToFile(newLeaveNode);

    addEntryToNode(newEntry, newLeaveNode);
    bTree->rootNode = newRootNode;

    newLeaveNode->entries[0].child = node->index;
    newRootNode->nextNode = newLeaveNode->index;
    newLeaveNode->parentNode = newRootNode->index;
    node->parentNode = newRootNode->index;

    promoteEntry(bTree, newLeaveNode);

    updateNode(newRootNode);
    updateNode(node);
    updateNode(newLeaveNode);

    free(newLeaveNode);
    free(node);
}

Node *splitNode(BTree *bTree, Node *node) {
    int splitIndex = NODE_MAX_ENTRIES / 2;
    Node *newNode;
    newNode = createNewNode(bTree);
    for (int i = splitIndex; i < NODE_MAX_ENTRIES; i++) {
        addSortedEntryToNode(&node->entries[i], newNode);
        removeEntry(&node->entries[i]);
        node->numberOfEntries--;
    }
    newNode->parentNode = node->parentNode;
    node->numberOfEntries = splitIndex;
    return newNode;
}

int promoteEntry(BTree *bTree, Node *childNode) {
    Node *parentNode;
    parentNode = getNodeByIndex(childNode->parentNode); // COLOCAR DENTRO DA CHAMADA DA FUNÇÃO

    int index = insertNewElement(
        bTree,
        parentNode,
        &childNode->entries[0]
    );
    removeEntryAndRearrangeNode(&childNode->entries[0], childNode);
    return index;
}


