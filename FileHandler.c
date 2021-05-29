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

Page *readPageFromFile(FILE *fp) {
    Page *page;
    page = (Page *) malloc(PAGE_SIZE);
    fread(&page->numberOfIndexes, sizeof(int), 1, fp);
    fread(page->keys, KEYS_VECTOR_SIZE, 1, fp);
    fread(page->pageChildren, PAGE_CHILDREN_VECTOR_SIZE, 1, fp);
    fread(&page->isLeave, sizeof(int), 1, fp);
    return page;
}

void writePageToFile(FILE *fp, Page *page) {
    fwrite(&page->numberOfIndexes, sizeof(int), 1, fp);
    fwrite(page->keys, KEYS_VECTOR_SIZE, 1, fp);
    fwrite(page->pageChildren, PAGE_CHILDREN_VECTOR_SIZE, 1, fp);
    fwrite(&page->isLeave, sizeof(int), 1, fp);
}

