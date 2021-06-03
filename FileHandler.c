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
Node *readNodeFromFile(FILE *fp) {
    Node *node;
    node = createNodeObject();
    fread(&node->numberOfEntries, sizeof(int), 1, fp);
    fread(&node->numberOfChildren, sizeof(int), 1, fp);
    for (int i = 0; i < B_TREE_ORDER - 1; i++) {
        fread(&node->entries[i].key, sizeof(int), 1, fp);
        fread(&node->entries[i].rrn, sizeof(long int), 1, fp);
        fread(&node->entries[i].child, sizeof(int), 1, fp);
    }
    fread(&node->isLeave, sizeof(int), 1, fp);
    return node;
}

// MUDAR PARA PERMITIR VARIAS PAGINAS
void writeNodeToFile(FILE *fp, Node *node) {
    fwrite(&node->numberOfEntries, sizeof(int), 1, fp);
    fwrite(&node->numberOfChildren, sizeof(int), 1, fp);
    for (int i = 0; i < B_TREE_ORDER - 1; i++) {
        fwrite(&node->entries[i].key, sizeof(int), 1, fp);
        fwrite(&node->entries[i].rrn, sizeof(long int), 1, fp);
        fwrite(&node->entries[i].child, sizeof(int), 1, fp);
    }
    fwrite(&node->isLeave, sizeof(int), 1, fp);
}

