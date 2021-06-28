#ifndef DEFINES_H_
#define DEFINES_H_

#define B_TREE_ORDER 20
#define FIELD_LEN 50
#define STRING_FIELD_SIZE 255
#define STUDENT_SIZE (8 + STRING_FIELD_SIZE * 3)
#define NODE_MAX_ENTRIES (B_TREE_ORDER - 1)
#define NODE_SIZE (16 + (16 * (NODE_MAX_ENTRIES)))
#define INDEX_FILE "nodes.dat"
#define DATA_FILE "data.dat"
#define DELIMITERCHAR ','
#define HEADER_OFFSET 8
#define PARENT_NODE_OFFSET 12

#endif
