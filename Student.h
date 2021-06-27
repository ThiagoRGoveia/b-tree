#ifndef STUDENT_H_
#define STUDENT_H_

#include "Includes.h"

Student *getStudentByRRN(long int RRN);
void setStudentByRRN(long int RRN, Student *student);
long int saveNewStudent(Student *student);
void printStudent(Student *student);
#endif
