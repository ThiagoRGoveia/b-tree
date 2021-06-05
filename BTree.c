#include "Includes.h"

BTree *createBTree() {
    BTree *bTree;
    bTree = (BTree *) malloc(sizeof(BTree));

    bTree->numberOfNodes = 0;
    bTree->rootNode = createNewNode(bTree);
    return bTree;
}

BTree *loadOrCreateBTree() {
    FILE *fp;
    fp = fopen(INDEX_FILE, "r");
    fseek(fp, 0, SEEK_END);
    long int size = ftell(fp);
    if (size > 0) {
        return readBTreeFromFile(fp);
    } else {
        return createBTree();
    }
}

Node *createNewNode(BTree *bTree) {
    Node *node;
    node = createNodeObject();
    node->index = bTree->numberOfNodes;
    bTree->numberOfNodes++;
    return node;
}
