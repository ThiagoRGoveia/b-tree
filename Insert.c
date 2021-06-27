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
    printf("INSERTING TO NODE %d\n", nodeIndex);
    int insertedEntryIndex;
    if (node->numberOfEntries == NODE_MAX_ENTRIES) {
        if (node->index != bTree->rootNode) {
            printf("SPLIT_LEAVE_NODE\n");
            free(node);
            return hadleLeaveNodeOverflow(bTree, nodeIndex, newEntry, search);
        } else {
            printf("SPLIT_ROOT_NODE\n");
            free(node);
            handleRootNodeOverflow(bTree, nodeIndex, newEntry, search);
            return 0;
        }
    } else {
        printf("ADD_ENTRY\n");
        insertedEntryIndex = addEntryToNode(newEntry, node);
        printNode(node);
        free(node);
        return insertedEntryIndex;
    }
}


int hadleLeaveNodeOverflow(BTree *bTree, int nodeIndex, Entry *newEntry, Search *search) {
    Node *newLeaveNode, *node;

    node = getNodeByIndex(nodeIndex);

    // printf("CREATE NEW LEAVE NODE\n");
    newLeaveNode = splitNode(bTree, node, newEntry);
    node->nextNode = newLeaveNode->entries[0].child; // O nó original terá como next node o filho da chave a ser promovida
    newLeaveNode->entries[0].child = newLeaveNode->index; // A chave a ser promovida terá o novo nó como filho, esse filho será trocado com a chave seguinte no nó pai

    updateNode(node);
    updateNode(newLeaveNode);
    int promotedNewIndex = promoteEntry(bTree, newLeaveNode, search);
    // printf("PROMOTING KEY %d\n", promotedNewIndex);

    // printf("NEW LEAVE NODE \n");
    // printNode(newLeaveNode);
    // printf("ORIGIN NODE \n");
    // printNode(node);

    updateNode(node);
    updateNode(newLeaveNode);
    printf("ORIGN NODE \n");
    printNode(node);
    printf("NEW LEAVE NODE \n");
    printNode(newLeaveNode);
    free(node);
    free(newLeaveNode);
    return promotedNewIndex;
}

int handleRootNodeOverflow(BTree *bTree, int nodeIndex, Entry *newEntry, Search *search) {
    Node *newRootNode, *newLeaveNode, *node;
    // printf("SPLIT_ROOT_NODE.1\n");
    node = getNodeByIndex(nodeIndex);

    newRootNode = createNewNode(bTree);
    // printf("SPLIT_ROOT_NODE.2\n");
    newLeaveNode = splitNode(bTree, node, newEntry);
    // printf("SPLIT_ROOT_NODE.3\n");

    // printf("FFFCCASCASASCSDABNKVJDNVNSDLVKLSDNASÇAÇLMMÇASLC %d\n", node->nextNode);
    node->nextNode = newLeaveNode->entries[0].child; // nextNode do nó original será o o filho da chave a ser promovida
    newLeaveNode->entries[0].child = node->index; // O nó original tera como nextNode o filho da chave a ser promovida
    newRootNode->nextNode = newLeaveNode->index; // O nextNode do novo nó raiz é o novo nó folha
    // newLeaveNode->parentNode = newRootNode->index;
    // node->parentNode = newRootNode->index;
    updateNode(newRootNode);
    bTree->rootNode = newRootNode->index; // Atualizar nó raiz da btree
    updateNode(newLeaveNode);
    updateNode(node);
    int promotedNewIndex = promoteEntry(bTree, newLeaveNode, search);
    // printf("PROMOTING KEY %d\n", promotedNewIndex);
    // printf("SPLIT_ROOT_NODE.4\n");
    // printf("PARENT NODE \n");
    // // printNode(newRootNode);
    // printf("NEW LEAVE NODE \n");
    // // printNode(newLeaveNode);
    // printf("ORIGIN NODE \n");
    // printNode(node);

    updateNode(node);
    updateNode(newLeaveNode);
    // printf("SPLIT_ROOT_NODE.5\n");
    printf("ORIGN NODE \n");
    printNode(node);
    printf("NEW LEAVE NODE \n");
    printNode(newLeaveNode);
    free(newRootNode);
    free(newLeaveNode);
    free(node);
    // printf("SPLIT_ROOT_NODE.6\n");
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
        printf("PRINT NODE SPLIT\n");
        printNode(node);
    }
    if (isNewKeySmaller) {
        printf("IS SMMALLER\n");
        addEntryToNode(newEntry, node);
        printf("PRINT NODE AFTER INSERT\n");
        printNode(node);
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


