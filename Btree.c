#include "Includes.h"

int insertNewElement(Page *page, Page *parentPage, Entry *newEntry) {
    if (page->numberOfEntries == PAGE_MAX_ENTRIES) {
        if (page->isLeave) {
            return hadleLeavePageOverflow(page, parentPage, newEntry);
        } else {
            handleRootPageOverflow(page, newEntry);
            return 0;
        }
    } else {
        return addEntryToPage(newEntry, page);
    }
}

int hadleLeavePageOverflow(Page *page, Page *parentPage, Entry *newEntry) {
    Page *newLeavePage;

    newLeavePage = splitPage(page);
    addEntryToPage(newLeavePage, newEntry);

    newLeavePage->entries[0].child = page->number;
    int promotedNewIndex = promoteEntry(newLeavePage, parentPage);
    if (parentPage->entries[promotedNewIndex + 1].key >= 0) {
        parentPage->entries[promotedNewIndex + 1].child = newLeavePage->number;
    } else {
        parentPage->nextPage = newLeavePage->number;
    }

    addNewPageToFile(newLeavePage);
    updatePageByIndex(parentPage, parentPage->number);
}

void handleRootPageOverflow(Page *page, Entry *newEntry) {
    Page *newRootPage, *newLeavePage;
    newRootPage = createPageObject();
    newLeavePage = splitPage(page);
    addEntryToPage(newLeavePage, newEntry);

    newLeavePage->entries[0].child = page->number;
    newRootPage->nextPage = newLeavePage->number;

    promoteEntry(newLeavePage, newRootPage);

    addNewPageToFile(newLeavePage);
    addNewPageToFile(newRootPage);
}

Page *splitPage(Page *page) {
    int splitIndex = PAGE_MAX_ENTRIES / 2;
    Page *newPage;
    newPage = createPageObject();
    for (int i = splitIndex + 1; i < PAGE_MAX_ENTRIES; i++) {
        addSortedEntryToPage(newPage, &page->entries[i]);
        removeEntry(&page->entries[i]);
    }
    return newPage;
}

int promoteEntry(Page *childPage, Page *parentPage) {
    int index = insertNewElement(childPage, parentPage, &childPage->entries[0]);
    removeEntryFromPage(&childPage->entries[0], childPage);
    return index;
}


