#ifndef PAGE_H_
#define PAGE_H_

#include "Includes.h"

typedef struct Page {
    int numberOfIndexes;
    int keys[B_TREE_ORDER -1];
    int pageChildren[B_TREE_ORDER];
    int isLeave;
} Page;

void writePageToFile(FILE *fp, Page page);
Page readPageFromFile(FILE *fp, int index);

#endif
