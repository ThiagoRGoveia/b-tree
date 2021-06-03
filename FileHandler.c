#include "Includes.h"

// Lê registros para a struct Student
Student *readStudentFromFile(FILE *fp) {
    Student *student;
    student = (Student *) malloc(STUDENT_SIZE);
    fread(&student->nUSP, sizeof(int), 1, fp);
    fread(student->name, STRING_FIELD_SIZE, 1, fp);
    fread(student->surname, STRING_FIELD_SIZE, 1, fp);
    fread(student->course, STRING_FIELD_SIZE, 1, fp);
    fread(&student->grade, sizeof(float), 1, fp);
    return student;
}

void writeSudentToFile (FILE *fp, Student *student) {
    fwrite(&student->nUSP, sizeof(int), 1, fp);
    fwrite(student->name, STRING_FIELD_SIZE, 1, fp);
    fwrite(student->surname, STRING_FIELD_SIZE, 1, fp);
    fwrite(student->course, STRING_FIELD_SIZE, 1, fp);
    fwrite(&student->grade, sizeof(float), 1, fp);
}

// MUDAR PARA PERMITIR VARIAS PAGINAS
Page *readPageFromFile(FILE *fp) {
    Page *page;
    page = createPageObject();
    fread(&page->numberOfEntries, sizeof(int), 1, fp);
    fread(&page->numberOfChildren, sizeof(int), 1, fp);
    for (int i = 0; i < B_TREE_ORDER - 1; i++) {
        fread(&page->entries[i].key, sizeof(int), 1, fp);
        fread(&page->entries[i].rrn, sizeof(long int), 1, fp);
        fread(&page->entries[i].child, sizeof(int), 1, fp);
    }
    fread(&page->isLeave, sizeof(int), 1, fp);
    return page;
}

// MUDAR PARA PERMITIR VARIAS PAGINAS
void writePageToFile(FILE *fp, Page *page) {
    fwrite(&page->numberOfEntries, sizeof(int), 1, fp);
    fwrite(&page->numberOfChildren, sizeof(int), 1, fp);
    for (int i = 0; i < B_TREE_ORDER - 1; i++) {
        fwrite(&page->entries[i].key, sizeof(int), 1, fp);
        fwrite(&page->entries[i].rrn, sizeof(long int), 1, fp);
        fwrite(&page->entries[i].child, sizeof(int), 1, fp);
    }
    fwrite(&page->isLeave, sizeof(int), 1, fp);
}

