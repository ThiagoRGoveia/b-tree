#include "Includes.h"

void printNode(Node *node) {
    printf("%d\n", node->numberOfEntries);
    printf("%d\n", node->numberOfChildren);
    printf("%d\n", node->entries[0].key);
    printf("%ld\n", node->entries[0].rrn);
    printf("%d\n", node->parentNode);
    printf("\n");
}

int main() {
    Node *node;
    FILE *fp;
    fp = fopen(INDEX_FILE, "w");
    node = createNodeObject();
    node->numberOfEntries = 2;
    node->numberOfChildren = 3;
    node->entries[0].key = 3;
    node->entries[0].rrn = 3;
    node->parentNode = 1;

    writeNodeToFile(fp, node);

    node->numberOfEntries = 3;
    node->numberOfChildren = 4;
    node->entries[0].key = 2;
    node->entries[0].rrn = 2;
    node->parentNode = 0;
    writeNodeToFile(fp, node);

    node->numberOfEntries = 4;
    node->numberOfChildren = 5;
    node->entries[0].key = 1;
    node->entries[0].rrn = 1;
    node->parentNode = 0;
    writeNodeToFile(fp, node);
    fclose(fp);

    Node *node2;

    node2 = getNodeByIndex(2);
    printNode(node2);
    free(node2);
    node2 = getNodeByIndex(1);
    printNode(node2);
    free(node2);
    node2 = getNodeByIndex(0);
    printNode(node2);
    free(node2);


    node->numberOfEntries = 1;
    node->entries[0].key = 2;
    node->entries[0].rrn = 2;
    node->parentNode = 0;

    setNodeByIndex(2, node);
    node2 = getNodeByIndex(2);

    printNode(node);

}