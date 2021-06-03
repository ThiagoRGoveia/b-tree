#include "Includes.h"

Page *createPageObject() {
    Page *page;
    page = (Page *) malloc(sizeof(Page));
    for (int i = 0; i < B_TREE_ORDER -1; i++) {
        page->keys[i].key = -1;
        page->keys[i].rrn = -1;
    }
    for (int i = 0; i < B_TREE_ORDER; i++) {
        page->pageChildren[i] = -1;
    }
    page->numberOfIndexes = 0;
    page->numberOfChildren = 0;

    return page;
}

Page *getPageByIndex(int index) {
    FILE *fp;
    Page *page;
    long int pageRRN = index * PAGE_SIZE;
    fp = fopen(INDEX_FILE, "r");
    fseek(fp, pageRRN, SEEK_SET);
    page = readPageFromFile(fp);
    fclose(fp);
    return page;
}

void updatePageByIndex(int index, Page *page) {
    FILE *fp;
    long int pageRRN = index * PAGE_SIZE;
    fp = fopen(INDEX_FILE, "r+");
    fseek(fp, pageRRN, SEEK_SET);
    writePageToFile(fp, page);
    fclose(fp);
}


void insertNewPageToFile(Page *page) {
    FILE *fp;
    fp = fopen(INDEX_FILE, "r+");
    fseek(fp, 0, SEEK_END);
    writePageToFile(fp, page);
    fclose(fp);
}

int getNumberOfPagesFromFile() {
    FILE *fp;
    fp = fopen(INDEX_FILE, "r");
    fseek(fp, 0, SEEK_END);
    int fileSize = ftell(fp);
    fclose(fp);
    return fileSize/PAGE_SIZE;
}