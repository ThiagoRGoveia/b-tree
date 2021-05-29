#include "Includes.h"

Page *getPageByIndex(int index) {
    FILE *fp;
    Page *page;
    int pageRRN = index * PAGE_SIZE;
    fp = fopen(INDEX_FILE, "r");
    fseek(fp, pageRRN, SEEK_SET);
    page = readPageFromFile(fp);
    fclose(fp);

    return page;
}

void setPageByIndex(int index, Page *page) {
    FILE *fp;
    int pageRRN = index * PAGE_SIZE;
    fp = fopen(INDEX_FILE, "r+");
    fseek(fp, pageRRN, SEEK_SET);
    writePageToFile(fp, page);
    fclose(fp);
}
