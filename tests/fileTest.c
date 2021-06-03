#include "Includes.h"

void printPage(Page *page) {
    printf("%d\n", page->numberOfEntries);
    printf("%d\n", page->numberOfChildren);
    printf("%d\n", page->entries[0].key);
    printf("%ld\n", page->entries[0].rrn);
    printf("%d\n", page->pageChildren[0]);
    printf("%d\n", page->isLeave);
    printf("\n");
}

int main() {
    Page *page;
    FILE *fp;
    fp = fopen(INDEX_FILE, "w");
    page = createPageObject();
    page->numberOfEntries = 2;
    page->numberOfChildren = 3;
    page->entries[0].key = 3;
    page->entries[0].rrn = 3;
    page->pageChildren[0] = 2;
    page->isLeave = 1;

    writePageToFile(fp, page);

    page->numberOfEntries = 3;
    page->numberOfChildren = 4;
    page->entries[0].key = 2;
    page->entries[0].rrn = 2;
    page->pageChildren[0] = 5;
    page->isLeave = 0;
    writePageToFile(fp, page);

    page->numberOfEntries = 4;
    page->numberOfChildren = 5;
    page->entries[0].key = 1;
    page->entries[0].rrn = 1;
    page->pageChildren[0] = 6;
    page->isLeave = 0;
    writePageToFile(fp, page);
    fclose(fp);

    Page *page2;

    page2 = getPageByIndex(2);
    printPage(page2);
    free(page2);
    page2 = getPageByIndex(1);
    printPage(page2);
    free(page2);
    page2 = getPageByIndex(0);
    printPage(page2);
    free(page2);


    page->numberOfEntries = 1;
    page->entries[0].key = 2;
    page->entries[0].rrn = 2;
    page->pageChildren[0] = 3;
    page->isLeave = 0;

    setPageByIndex(2, page);
    page2 = getPageByIndex(2);

    printPage(page);

}