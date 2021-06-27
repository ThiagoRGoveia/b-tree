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
    writeSudentToFile(fp, student);
    rrn = ftell(fp);
    fclose(fp);
    return rrn;
}

void printStudent(Student *student) {
    printf("-------------------------------\n");
    printf("%d\n", student->nUSP);
    printf("%s\n", student->name);
    printf("%s\n", student->surname);
    printf("%s\n", student->course);
    printf("%.2f\n", student->grade);
    printf("-------------------------------\n");
}
