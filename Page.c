#include "Includes.h"

Page *createPageObject() {
    Page *page;
    page = (Page *) malloc(sizeof(Page));
    for (int i = 0; i < B_TREE_ORDER -1; i++) {
        page->entries[i].key = -1;
        page->entries[i].rrn = -1;
    }
    for (int i = 0; i < B_TREE_ORDER; i++) {
        page->pageChildren[i] = -1;
    }
    page->numberOfEntries = 0;
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


int addNewPageToFile(Page *page) {
    FILE *fp;
    fp = fopen(INDEX_FILE, "r+");
    fseek(fp, 0, SEEK_END);
    writePageToFile(fp, page);
    int fileSize = ftell(fp);
    fclose(fp);
    return fileSize/PAGE_SIZE;
}

int getNumberOfPagesFromFile() {
    FILE *fp;
    fp = fopen(INDEX_FILE, "r");
    fseek(fp, 0, SEEK_END);
    int fileSize = ftell(fp);
    fclose(fp);
    return fileSize/PAGE_SIZE;
}

void addEntryToPage(Entry *entry, Page *page) {
    if (page->numberOfEntries == 0) {
        page->entries[0] = *entry;
    }
    for (int i = page->numberOfEntries - 1; i >= 0; i--) {
        if (page->entries[i].key > entry->key) {
            for (int j = page->numberOfEntries - 1; j >= i; j--) {
                page->entries[j + 1] = page->entries[j];
            }
            page->entries[i] = *entry;
            break;
        }
    }
}

int checkIfPageEntriesAreFull(Page *page) {
    return page->numberOfEntries == PAGE_MAX_ENTRIES ? 1 : 0;
}

int checkIfPageChildrenAreFull(Page *page) {
    return page->numberOfEntries == PAGE_MAX_CHILDREN ? 1 : 0;
}