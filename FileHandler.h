#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_

#include "Includes.h"

Student *readStudentFromFile(FILE *fp);
void writeSudentToFile (FILE *fp, Student *student);
Node *readNodeFromFile(FILE *fp);
void writeNodeToFile(FILE *fp, Node *node);
BTree *readBTreeFromFile(FILE *fp);
void writeBtreeHeaderToFile(FILE *fp, BTree *bTree);
#endif