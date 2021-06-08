#ifndef STUDENT_H_
#define STUDENT_H_

#include "Includes.h"

typedef struct Student
{
    int nUSP;
    char name[STRING_FIELD_SIZE];
    char surname[STRING_FIELD_SIZE];
    char course[STRING_FIELD_SIZE];
    float grade;
} Student;

Student *getStudentByRRN(long int RRN);
void setStudentByRRN(long int RRN, Student *student);
Student *entrada_student(const char *string);
#endif
