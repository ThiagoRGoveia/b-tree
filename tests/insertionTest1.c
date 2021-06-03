#include "Includes.h"

int main()
{
    Node *node;

    node = createNodeObject();
    node->entries[0].key = 1;
    node->entries[0].rrn = 10;
    node->entries[1].key = 5;
    node->entries[1].rrn = 10;
    node->entries[2].key = 8;
    node->entries[2].rrn = 10;
    node->numberOfEntries = 3;

    Entry *entry;

    entry = (Entry *) malloc(12);
    entry->key = 6;
    entry->rrn = 20;

    addEntryToNode(entry, node);
    free(entry);
    printf("%d\n", node->entries[0].key);
    printf("%ld\n", node->entries[0].rrn);
    printf("%d\n", node->entries[1].key);
    printf("%ld\n", node->entries[1].rrn);
    printf("%d\n", node->entries[2].key);
    printf("%ld\n", node->entries[2].rrn);
    printf("%d\n", node->entries[3].key);
    printf("%ld\n", node->entries[3].rrn);

}