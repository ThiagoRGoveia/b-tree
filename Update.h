#ifndef UPDATE_H_
#define UPDATE_H_

#include "Includes.h"

Student *entrada_student(const char *string);
void updateToFile(FILE *fp, Student *student, long int RRN);
void update(Student *student);
#endif