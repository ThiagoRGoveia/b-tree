#include "Includes.h"

int main()
{
    Page *page;

    page = createPageObject();
    page->entries[0].key = 1;
    page->entries[0].rrn = 10;
    page->entries[1].key = 5;
    page->entries[1].rrn = 10;
    page->entries[2].key = 8;
    page->entries[2].rrn = 10;
    page->numberOfEntries = 3;

    Entry *entry;

    entry = (Entry *) malloc(12);
    entry->key = 6;
    entry->rrn = 20;

    addEntryToPage(entry, page);
    free(entry);
    printf("%d\n", page->entries[0].key);
    printf("%ld\n", page->entries[0].rrn);
    printf("%d\n", page->entries[1].key);
    printf("%ld\n", page->entries[1].rrn);
    printf("%d\n", page->entries[2].key);
    printf("%ld\n", page->entries[2].rrn);
    printf("%d\n", page->entries[3].key);
    printf("%ld\n", page->entries[3].rrn);

}