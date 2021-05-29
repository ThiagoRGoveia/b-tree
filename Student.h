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

#endif
