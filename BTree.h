#ifndef BTREE_H_
#define BTREE_H_

#include "Includes.h"

typedef struct BTree {
    int numberOfPages;
    Page *page;
} BTree;



#endif
