#include "Includes.h"

Student *getStudentByRRN(long int RRN) {
    FILE *fp;
    Student *student;
    fp = fopen(DATA_FILE, "r");
    fseek(fp, RRN, SEEK_SET);
    student = readStudentFromFile(fp);
    fclose(fp);
    return student;
}

void setStudentByRRN(long int RRN, Student *student) {
    FILE *fp;
    fp = fopen(DATA_FILE, "r+");
    fseek(fp, RRN, SEEK_SET);
    writeSudentToFile(fp, student);
    fclose(fp);
}

long int saveNewStudent(Student *student) {
    FILE *fp;
    long int rrn;
    fp = fopen(DATA_FILE, "r+");
    fseek(fp, 0, SEEK_END);
    rrn =ftell(fp);
    writeSudentToFile(fp, student);
    fclose(fp);
    return rrn;
}

void printStudent(Student *student) {
    printf("-------------------------------\n");
    printf("nUSP: %d\n", student->nUSP);
    printf("Nome: %s\n", student->name);
    printf("Sobrenome: %s\n", student->surname);
    printf("Curso: %s\n", student->course);
    printf("Nota: %.2f\n", student->grade);
    printf("-------------------------------\n");
}
