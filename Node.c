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

    return node;
}

Node *getNodeByIndex(int index) {
    FILE *fp;
    Node *node;
    long int nodeRRN = index * NODE_SIZE;
    fp = fopen(INDEX_FILE, "r");
    fseek(fp, nodeRRN, SEEK_SET);
    node = readNodeFromFile(fp);
    fclose(fp);
    return node;
}

void updateNodeByIndex(int index, Node *node) {
    FILE *fp;
    long int nodeRRN = index * NODE_SIZE;
    fp = fopen(INDEX_FILE, "r+");
    fseek(fp, nodeRRN, SEEK_SET);
    writeNodeToFile(fp, node);
    fclose(fp);
}


int addNewNodeToFile(Node *node) {
    FILE *fp;
    fp = fopen(INDEX_FILE, "r+");
    fseek(fp, 0, SEEK_END);
    writeNodeToFile(fp, node);
    int fileSize = ftell(fp);
    fclose(fp);
    return fileSize/NODE_SIZE;
}

int getNumberOfNodesFromFile() {
    FILE *fp;
    fp = fopen(INDEX_FILE, "r");
    fseek(fp, 0, SEEK_END);
    int fileSize = ftell(fp);
    fclose(fp);
    return fileSize/NODE_SIZE;
}

int addEntryToNode(Entry *entry, Node *node) {
    if (node->numberOfEntries == 0) {
        node->entries[0] = *entry;
        return 0;
    }
    for (int i = node->numberOfEntries - 1; i >= 0; i--) {
        if (node->entries[i].key > entry->key) {
            for (int j = node->numberOfEntries - 1; j >= i; j--) {
                node->entries[j + 1] = node->entries[j];
            }
            node->entries[i] = *entry;
            node->numberOfEntries += 1;
            return i;
        }
    }

}

int checkIfNodeIsFull(Node *node) {
    return node->numberOfEntries == NODE_MAX_ENTRIES ? 1 : 0;
}

void addSortedEntryToNode(Entry *entry, Node *node) {
    node->entries[node->numberOfEntries - 1] = *entry;
    node->numberOfEntries += 1;
}

void removeEntryAndRearrangeNode(Entry *entry, Node *node) {
    if (entry->key != node->entries[node->numberOfEntries - 1].key) {
        int indexToBeRemoved = - 1;
        int i = 0;
        // MUDAR PRA BINARY SEARCH
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
}

void removeEntry(Entry *entry) {
    entry->key = -1;
    entry->rrn = -1;
    entry->child = -1;
}