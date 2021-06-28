#include "Includes.h"

int insertNewEntry(BTree *bTree, Entry *newEntry, Search *search) {
    Node *node;
    int nodeIndex;
    if (search->currentIndex == 0) {
        nodeIndex = bTree->rootNode;
    } else {
        nodeIndex = search->history[search->currentIndex--];
    }
    node = getNodeByIndex(nodeIndex);
    int insertedEntryIndex;
    if (node->numberOfEntries == NODE_MAX_ENTRIES) {
        if (node->index != bTree->rootNode) {
            free(node);
            return hadleLeaveNodeOverflow(bTree, nodeIndex, newEntry, search);
        } else {
            free(node);
            handleRootNodeOverflow(bTree, nodeIndex, newEntry, search);
            return 0;
        }
    } else {
        insertedEntryIndex = addEntryToNode(newEntry, node);
        free(node);
        return insertedEntryIndex;
    }
}


int hadleLeaveNodeOverflow(BTree *bTree, int nodeIndex, Entry *newEntry, Search *search) {
    Node *newLeaveNode, *node;

    node = getNodeByIndex(nodeIndex);

    newLeaveNode = splitNode(bTree, node, newEntry);
    newLeaveNode->entries[0].child = newLeaveNode->index; // A chave a ser promovida terá o novo nó como filho, esse filho será trocado com a chave seguinte no nó pai

    updateNode(node);
    updateNode(newLeaveNode);
    int promotedNewIndex = promoteEntry(bTree, newLeaveNode, search);

    updateNode(node);
    updateNode(newLeaveNode);

    free(node);
    free(newLeaveNode);
    return promotedNewIndex;
}

int handleRootNodeOverflow(BTree *bTree, int nodeIndex, Entry *newEntry, Search *search) {
    Node *newRootNode, *newLeaveNode, *node;
    node = getNodeByIndex(nodeIndex);

    newRootNode = createNewNode(bTree);
    bTree->rootNode = newRootNode->index; // Atualizar nó raiz da btree
    newLeaveNode = splitNode(bTree, node, newEntry);
    newLeaveNode->entries[0].child = node->index; // O nó original tera como nextNode o filho da chave a ser promovida

    newRootNode->nextNode = newLeaveNode->index; // O nextNode do novo nó raiz é o novo nó folha
    updateNode(newRootNode);
    updateNode(newLeaveNode);
    updateNode(node);
    int promotedNewIndex = promoteEntry(bTree, newLeaveNode, search);

    updateNode(node);
    updateNode(newLeaveNode);
    free(newRootNode);
    free(newLeaveNode);
    free(node);

    return promotedNewIndex;
}

Node *splitNode(BTree *bTree, Node *node, Entry *newEntry) {
    int middle = NODE_MAX_ENTRIES / 2, splitIndex, isNewKeySmaller;
    Node *newNode;
    newNode = createNewNode(bTree);
    newNode->nextNode = node->nextNode;

    if (node->entries[middle].key > newEntry->key) {
        isNewKeySmaller = 1;
        splitIndex = middle;
    } else {
        isNewKeySmaller = 0;
        splitIndex = middle + 1;
    }
    for (int i = splitIndex; i < NODE_MAX_ENTRIES; i++) {
        addSortedEntryToNode(&node->entries[i], newNode);
        removeEntry(&node->entries[i]);
        node->numberOfEntries--;
    }
    node->nextNode = newNode->entries[0].child; // nextNode do nó original será o o filho da chave a ser promovida

    if (isNewKeySmaller) {
        addEntryToNode(newEntry, node);
    } else {
        addEntryToNode(newEntry, newNode);
    }
    return newNode;
}

int promoteEntry(BTree *bTree, Node *childNode, Search *search) {
    int index = insertNewEntry(
        bTree,
        &childNode->entries[0],
        search
    );
    removeEntryAndRearrangeNode(&childNode->entries[0], childNode);
    return index;
}


