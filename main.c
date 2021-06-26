#include "Includes.h"

Node *read(int i) {
    Node *node;
    node = getNodeByIndex(i);
    // printf("---\n");
    // printf("Index %d\n", node->index);
    // printf("Key [0] %d\n", node->entries[0].key);
    // printf("Child [0] %d\n", node->entries[0].child);
    // printf("Key [1] %d\n", node->entries[1].key);
    // printf("Child [1] %d\n", node->entries[1].child);
    // printf("Next node %d\n", node->nextNode);
    // printf("Parent %d\n", node->parentNode);
    // printf("Number of entries %d\n", node->numberOfEntries);
    // printf("---\n");
    return node;
}

void printNode(Node *node) {
    printf("---\n");
    printf("Index %d\n", node->index);
    for (int i = 0; i < NODE_MAX_ENTRIES; i++) {
        printf("Key [%d] %d\n", i, node->entries[i].key);
        printf("Child [%d] %d\n", i, node->entries[i].child);
    }
    printf("Next node %d\n", node->nextNode);
    printf("Parent %d\n", node->parentNode);
    printf("Number of entries %d\n", node->numberOfEntries);
    printf("---\n");
}

void insert(BTree *bTree, Node *node, int i) {
    Entry entry;
    entry.key = i;
    entry.child = -1;
    entry.rrn = i * 10;
    insertNewElement(bTree, node, &entry);
}

int main()
{
    BTree *bTree;
    bTree = createBTree();
    addNewNodeToFile(bTree->rootNode);
    insert(bTree, bTree->rootNode, 0);
    insert(bTree, bTree->rootNode, 1);
    insert(bTree, bTree->rootNode, 2);
    read(0);
    read(1);
    Node *node;
    node = getNodeByIndex(2);
    insert(bTree, node, 3);
    insert(bTree, node, 4);

    for (int i = 0; i <= 3; i++) {
        node = getNodeByIndex(i);
        // printNode(node);
    }
}