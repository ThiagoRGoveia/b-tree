#include "Includes.h"

BTree *createBTree() {
    BTree *bTree;
    bTree = (BTree *) malloc(sizeof(BTree));
    bTree->numberOfNodes = 0;
    bTree->rootNode = 0;
    writeBTreeHeader(bTree);
    addNewNodeToFile(
        createNewNode(bTree)
    );
    return bTree;
}

BTree *loadOrCreateBTree() {
    FILE *fp;
    fp = fopen(INDEX_FILE, "r");
    fseek(fp, 0, SEEK_END);
    long int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
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

void writeBTreeHeader(BTree *bTree) {
    FILE *fp;
    fp = fopen(INDEX_FILE, "r+");
    fseek(fp, 0, SEEK_SET);
    writeBtreeHeaderToFile(fp, bTree);
    fclose(fp);
}
