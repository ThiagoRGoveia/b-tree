#ifndef SEARCH_H_
#define SEARCH_H_

#include "Includes.h"

typedef struct result {
    Entry entry;
    Node * node;
} Result;

// Result * getRRNByPrimaryKey(long int rrnCurrent, int nUSP);
void getRRNByPrimaryKey(Result * result, long int nodeIndex, int nUSP);
int keyPositionSearch(Entry * entries, int start, int end, int value);

#endif