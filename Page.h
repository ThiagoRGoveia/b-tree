#ifndef PAGE_H_
#define PAGE_H_

#include "Includes.h"

typedef struct Key {
    int key;
    long int rrn;
} Key;

typedef struct Page {
    int numberOfIndexes;
    int numberOfChildren;
    Key keys[B_TREE_ORDER - 1];
    int pageChildren[B_TREE_ORDER];
    int isLeave;
} Page;

Page *getPageByIndex(int index);
void setPageByIndex(int index, Page *page);
Page *createPageObject();

#endif
