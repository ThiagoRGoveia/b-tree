#ifndef PAGE_H_
#define PAGE_H_

#include "Includes.h"

typedef struct Entry {
    int key;
    long int rrn;
} Entry;

typedef struct Page {
    int numberOfEntries;
    int numberOfChildren;
    Entry entries[PAGE_MAX_ENTRIES];
    int pageChildren[PAGE_MAX_CHILDREN];
    int isLeave;
} Page;

Page *getPageByIndex(int index);
void updatePageByIndex(int index, Page *page);
Page *createPageObject();
int addNewPageToFile(Page *page);
int getNumberOfPagesFromFile();
void addEntryToPage(Entry *entry, Page *page);
int checkIfPageIsFull(Page *page);

#endif
