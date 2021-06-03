#ifndef DEFINES_H_
#define DEFINES_H_

#define B_TREE_ORDER 9
#define STRING_FIELD_SIZE 255
#define STUDENT_SIZE (8 + STRING_FIELD_SIZE * 3)
#define PAGE_CHILDREN_VECTOR_SIZE (4 * B_TREE_ORDER)
#define KEYS_VECTOR_SIZE ((4 + 8) * (B_TREE_ORDER - 1))
#define PAGE_SIZE (12 + (16 * (B_TREE_ORDER - 1)))
#define PAGE_MAX_ENTRIES (B_TREE_ORDER - 1)
#define INDEX_FILE "pages.dat"
#define DATA_FILE "data.dat"

#endif
