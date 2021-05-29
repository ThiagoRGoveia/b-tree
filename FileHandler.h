#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_

#include "Includes.h"

Student *readStudentFromFile(FILE *fp);
void writeSudentToFile (FILE *fp, Student *student);
Page *readPageFromFile(FILE *fp);
void writePageToFile(FILE *fp, Page *page);

#endif