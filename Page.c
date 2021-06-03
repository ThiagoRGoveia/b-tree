#include "Includes.h"

Page *createPageObject() {
    Page *page;
    page = (Page *) malloc(sizeof(Page));
    for (int i = 0; i < PAGE_MAX_ENTRIES; i++) {
        page->entries[i].key = -1;
        page->entries[i].rrn = -1;
        page->entries[i].child = -1;
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

int addEntryToPage(Entry *entry, Page *page) {
    if (page->numberOfEntries == 0) {
        page->entries[0] = *entry;
        return 0;
    }
    for (int i = page->numberOfEntries - 1; i >= 0; i--) {
        if (page->entries[i].key > entry->key) {
            for (int j = page->numberOfEntries - 1; j >= i; j--) {
                page->entries[j + 1] = page->entries[j];
            }
            page->entries[i] = *entry;
            page->numberOfEntries += 1;
            return i;
        }
    }

}

int checkIfPageIsFull(Page *page) {
    return page->numberOfEntries == PAGE_MAX_ENTRIES ? 1 : 0;
}

void addSortedEntryToPage(Entry *entry, Page *page) {
    page->entries[page->numberOfEntries - 1] = *entry;
    page->numberOfEntries += 1;
}

void removeEntryAndRearrangePage(Entry *entry, Page *page) {
    if (entry->key != page->entries[page->numberOfEntries - 1].key) {
        int indexToBeRemoved = - 1;
        int i = 0;
        // MUDAR PRA BINARY SEARCH
        while (indexToBeRemoved < 0 && i < page->numberOfEntries) {
            if (page->entries[i].key == entry->key) {
                indexToBeRemoved = i;
            }
        }
        if (indexToBeRemoved < 0) {
            return;
        }
        for (int j = i; j < page->numberOfEntries; j++) {
            page->entries[j] = page->entries[j + 1];
        }
    }
    page->entries[page->numberOfEntries - 1].key = -1;
    page->entries[page->numberOfEntries - 1].rrn = -1;
}

void removeEntry(Entry *entry) {
    entry->key = -1;
    entry->rrn = -1;
    entry->child = -1;
}