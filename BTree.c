#include "Includes.h"

BTree *createBTree() {
    BTree *bTree;
    bTree = (BTree *) malloc(sizeof(BTree));

    bTree->numberOfNodes = 0;
    bTree->rootNode = createNodeObject(bTree);
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
