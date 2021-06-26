#ifndef READ_CSV_INPUT
#define READ_CSV_INPUT
#include "Includes.h"

char *getField(char delimiter);
int getIntField();
float getFloatField();
void saveStudentsFromCSVInput();
char * getStringField();
char *getOptionFromCSV();
Student *readStudentFromCSV();

#endif
