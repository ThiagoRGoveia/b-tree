#include "Includes.h"

Node *createNodeObject() {
    Node *node;
    node = (Node *) malloc(sizeof(Node));
    for (int i = 0; i < NODE_MAX_ENTRIES; i++) {
        node->entries[i].key = -1;
        node->entries[i].rrn = -1;
        node->entries[i].child = -1;
    }
    node->numberOfEntries = 0;
    node->numberOfChildren = 0;
    node->parentNode = -1;
    node->nextNode = -1;
    return node;
}

Node *getNodeByIndex(int index) {
    FILE *fp;
    Node *node;
    long int nodeRRN = index * NODE_SIZE + HEADER_OFFSET;
    fp = fopen(INDEX_FILE, "r");
    fseek(fp, nodeRRN, SEEK_SET);
    node = readNodeFromFile(fp);
    fclose(fp);
    return node;
}

void updateNode(Node *node) {
    FILE *fp;
    long int nodeRRN = node->index * NODE_SIZE + HEADER_OFFSET;
    fp = fopen(INDEX_FILE, "r+");
    fseek(fp, nodeRRN, SEEK_SET);
    writeNodeToFile(fp, node);
    fclose(fp);
}


int addNewNodeToFile(Node *node) {
    FILE *fp;
    fp = fopen(INDEX_FILE, "a");
    fseek(fp, 0, SEEK_END);
    writeNodeToFile(fp, node);
    int fileSize = ftell(fp);
    fclose(fp);
    return (fileSize - 8)/NODE_SIZE;
}

int getNumberOfNodesFromFile() {
    FILE *fp;
    fp = fopen(INDEX_FILE, "r");
    fseek(fp, 0, SEEK_END);
    int fileSize = ftell(fp);
    fclose(fp);
    return (fileSize - 8)/NODE_SIZE;
}

int addEntryToNode(Entry *entry, Node *node) {
    int childHolder;
    if (node->numberOfEntries == 0) {
        node->entries[0] = *entry;
        node->numberOfEntries = 1;
        updateNode(node);
        return 0;
    }
    for (int i = 0; i < node->numberOfEntries; i++) {
        if (node->entries[i].key > entry->key) {
            for (int j = node->numberOfEntries - 1; j >= i; j--) {
                node->entries[j + 1] = node->entries[j];
            }
            node->entries[i] = *entry;
            node->numberOfEntries++;
            // Se a entrada nova possui um filho então trata-se de uma promoção,
            // inverter o filho da entrada nova com o filho da proxima entrada ou nextNode
            if (entry->child > 0) {
                if (i < node->numberOfEntries - 1) {
                    childHolder = node->entries[i].child;
                    node->entries[i].child = node->entries[i + 1].child;
                    node->entries[i + 1].child = childHolder;
                } else {
                    childHolder = node->entries[i].child;
                    node->entries[i].child = node->nextNode;
                    node->nextNode = childHolder;
                }
            }
            updateNode(node);
            return i;
        }
    }
    node->entries[node->numberOfEntries] = *entry;
    // Se a entrada nova possui um filho então trata-se de uma promoção,
    // inverter o filho da entrada nova com o filho da proxima entrada ou nextNode
    if (entry->child > 0) {
        childHolder = node->entries[node->numberOfEntries].child;
        node->entries[node->numberOfEntries].child = node->nextNode;
        node->nextNode = childHolder;
    }
    node->numberOfEntries++;

    updateNode(node);
    return node->numberOfEntries;
}

int checkIfNodeIsFull(Node *node) {
    return node->numberOfEntries == NODE_MAX_ENTRIES ? 1 : 0;
}

void addSortedEntryToNode(Entry *entry, Node *node) {
    node->entries[node->numberOfEntries] = *entry;
    node->numberOfEntries += 1;
}

void removeEntryAndRearrangeNode(Entry *entry, Node *node) {
    if (entry->key != node->entries[node->numberOfEntries - 1].key) {
        int indexToBeRemoved = - 1;
        int i = 0;
        while (indexToBeRemoved < 0 && i < node->numberOfEntries) {
            if (node->entries[i].key == entry->key) {
                indexToBeRemoved = i;
            }
        }
        if (indexToBeRemoved < 0) {
            return;
        }
        for (int j = i; j < node->numberOfEntries; j++) {
            node->entries[j] = node->entries[j + 1];
        }
    }
    node->entries[node->numberOfEntries - 1].key = -1;
    node->entries[node->numberOfEntries - 1].rrn = -1;
    node->entries[node->numberOfEntries - 1].child = -1;
    node->numberOfEntries--;
}

void removeEntry(Entry *entry) {
    entry->key = -1;
    entry->rrn = -1;
    entry->child = -1;
}

void printNode(Node *node) {
    printf("---\n");
    printf("Index %d\n",node->index);
    for (int i = 0; i < NODE_MAX_ENTRIES; i++) {
        printf("Key [%d] %d\n", i,node->entries[i].key);
        printf("Child [%d] %d\n", i,node->entries[i].child);
    }
    printf("Next node %d\n",node->nextNode);
    printf("Parent %d\n",node->parentNode);
    printf("Number of entries %d\n",node->numberOfEntries);
    printf("---\n");
}

void updateParentNode(int nodeIndex, int newParentIndex) {
    FILE *fp;
    long int fieldRRN = nodeIndex * NODE_SIZE + HEADER_OFFSET + PARENT_NODE_OFFSET;
    fp = fopen(INDEX_FILE, "r+");
    fseek(fp, fieldRRN, SEEK_SET);
    writeParentNodeToFile(fp, newParentIndex);
    fclose(fp);
}