#ifndef SEARCH_H_
#define SEARCH_H_

#include "Includes.h"

typedef struct result {
    Entry entry;
    Node * node;
} Result;

Result * getRRNByPrimaryKey(int nUSP);
int keyPositionSearch(Entry * entries, int start, int end, int value);

#endif