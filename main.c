#include "Includes.h"

// #include <stdio.h>

// #define A 20
// #define B(C) A * C


int main() {
    Page page;
    FILE *fp;
    page.numberOfIndexes = 2;
    page.keys[0] = 1;
    page.pageChildren[0] = 2;
    page.isLeave = 1;

    fp = fopen(INDEX_FILE, "w");
    writePageToFile(fp, &page);

    page.numberOfIndexes = 3;
    page.keys[0] = 2;
    page.pageChildren[0] = 5;
    page.isLeave = 0;
    writePageToFile(fp, &page);

    page.numberOfIndexes = 4;
    page.keys[0] = 1;
    page.pageChildren[0] = 6;
    page.isLeave = 0;
    writePageToFile(fp, &page);
    fclose(fp);

    Page *page2;

    page2 = getPageByIndex(2);
    page2 = getPageByIndex(1);
    page2 = getPageByIndex(0);

    printf("%d\n", page.numberOfIndexes);
    printf("%d\n", page.keys[0]);
    printf("%d\n", page.pageChildren[0]);
    printf("%d\n", page.isLeave);
    printf("\n");

    page.numberOfIndexes = 1;
    page.keys[0] = 2;
    page.pageChildren[0] = 3;
    page.isLeave = 0;

    printf("%d\n", page.numberOfIndexes);
    printf("%d\n", page.keys[0]);
    printf("%d\n", page.pageChildren[0]);
    printf("%d\n", page.isLeave);
    printf("\n");

    setPageByIndex(2, &page);
    page2 = getPageByIndex(2);
    printf("%d\n", page2->numberOfIndexes);
    printf("%d\n", page2->keys[0]);
    printf("%d\n", page2->pageChildren[0]);
    printf("%d\n", page2->isLeave);
}