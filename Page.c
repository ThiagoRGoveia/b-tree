#include "Includes.h"

Page *getPageByIndex(int index) {
    FILE *fp;
    Page *page;
    int pageRRN = index * PAGE_SIZE;
    fp = fopen(INDEX_FILE, "r");
    fseek(fp, pageRRN, SEEK_SET);
    page = readPageFromFile(fp);
    fclose(fp);
    printf("%d\n", page->numberOfIndexes);
    printf("%d\n", page->keys[0]);
    printf("%d\n", page->pageChildren[0]);
    printf("%d\n", page->isLeave);
    return page;
}