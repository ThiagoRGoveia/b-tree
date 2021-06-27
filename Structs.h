#ifndef STRUCTS_H_
#define STRUCTS_H_

#include "Includes.h"

typedef struct Entry {
    int key;
    long int rrn;
    int child;
} Entry;

typedef struct Node {
    int index;
    int numberOfEntries;
    int numberOfChildren;
    Entry entries[NODE_MAX_ENTRIES];
    int parentNode;
    int nextNode;
} Node;

typedef struct Student
{
    int nUSP;
    char name[STRING_FIELD_SIZE];
    char surname[STRING_FIELD_SIZE];
    char course[STRING_FIELD_SIZE];
    float grade;
} Student;

typedef struct BTree {
    int numberOfNodes;
    int rootNode;
} BTree;

typedef struct Search {
    int currentIndex;
    int *history;
} Search;

#endif
