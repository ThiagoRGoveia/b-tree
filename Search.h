#ifndef SEARCH_H_
#define SEARCH_H_

#include "Includes.h"

long int getRRNByPrimaryKey(int nUSP);
int keyPositionSearch(Entry * entries, int end, int value);

#endif