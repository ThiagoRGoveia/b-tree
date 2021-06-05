#include "Includes.h"

int main()
{
    BTree *bTree;
    bTree = createBTree();
    addNewNodeToFile(bTree->rootNode);
    Entry entry;
    entry.key = 5;
    entry.child = 0;
    entry.rrn = 20;
    insertNewElement(bTree, bTree->rootNode, &entry);

    entry.key = 6;
    entry.child = 0;
    entry.rrn = 30;
    insertNewElement(bTree, bTree->rootNode, &entry);

    entry.key = 4;
    entry.child = 0;
    entry.rrn = 40;
    insertNewElement(bTree, bTree->rootNode, &entry);
    Node *node;
    node = bTree->rootNode;

    // printf("%d\n", node->entries[0].key);
    // printf("%ld\n", node->entries[0].rrn);
    // printf("---\n");
    // node = getNodeByIndex(node->entries[0].child);
    // printf("%d\n", node->entries[0].key);
    // printf("%ld\n", node->entries[0].rrn);
    // printf("---\n");
    // node = getNodeByIndex(bTree->rootNode->nextNode);
    // printf("%d\n", node->entries[0].key);
    // printf("%ld\n", node->entries[0].rrn);
    // printf("---\n");
    // printf("---\n");
    // node = createNodeObject();
    // node->index = 0;
    // node->entries[0].key = 1;
    // node->entries[0].rrn = 1;
    // addNewNodeToFile(node);
    // node->index = 1;
    // node->entries[0].key = 2;
    // node->entries[0].rrn = 2;
    // addNewNodeToFile(node);
    // node->index = 2;
    // node->entries[0].key = 3;
    // node->entries[0].rrn = 3;
    // addNewNodeToFile(node);

    // node->index = 0;
    // node->entries[0].key = 4;
    // node->entries[0].rrn = 4;
    // updateNode(node);
    // node->index = 1;
    // node->entries[0].key = 5;
    // node->entries[0].rrn = 5;
    // updateNode(node);
    // node->index = 2;
    // node->entries[0].key = 6;
    // node->entries[0].rrn = 6;
    // updateNode(node);

    node = getNodeByIndex(0);
    printf("%d\n", node->entries[0].key);
    printf("%d\n", node->entries[0].child);
    printf("%d\n", node->nextNode);
    printf("---\n");

    node = getNodeByIndex(1);
    printf("%d\n", node->entries[0].key);
    printf("%d\n", node->entries[0].child);
    printf("%d\n", node->nextNode);
    printf("---\n");

    node = getNodeByIndex(2);
    printf("%d\n", node->entries[0].key);
    printf("%d\n", node->entries[0].child);
    printf("%d\n", node->nextNode);

}