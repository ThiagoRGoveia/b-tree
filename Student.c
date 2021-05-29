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
    return student;
}