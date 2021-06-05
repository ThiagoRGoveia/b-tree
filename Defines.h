#ifndef DEFINES_H_
#define DEFINES_H_

#define B_TREE_ORDER 3
#define STRING_FIELD_SIZE 255
#define STUDENT_SIZE (8 + STRING_FIELD_SIZE * 3)
#define NODE_MAX_ENTRIES (B_TREE_ORDER - 1)
#define NODE_SIZE (20 + (16 * (NODE_MAX_ENTRIES)))
#define INDEX_FILE "nodes.dat"
#define DATA_FILE "data.dat"

#endif
