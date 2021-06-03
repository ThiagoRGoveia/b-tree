#ifndef PAGE_H_
#define PAGE_H_

#include "Includes.h"

typedef struct Entry {
    int key;
    long int rrn;
    int child;
} Entry;

typedef struct Page {
    int number;
    int numberOfEntries;
    int numberOfChildren;
    Entry entries[PAGE_MAX_ENTRIES];
    int isLeave;
    int nextPage;
} Page;

Page *getPageByIndex(int index);
void updatePageByIndex(int index, Page *page);
Page *createPageObject();
int addNewPageToFile(Page *page);
int getNumberOfPagesFromFile();
int addEntryToPage(Entry *entry, Page *page);
int checkIfPageIsFull(Page *page);
void addSortedEntryToPage(Entry *entry, Page *page);
void removeEntryAndRearrangePage(Entry *entry, Page *page);
void removeEntry(Entry *entry);

#endif
