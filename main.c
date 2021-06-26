#include "Includes.h"

Node *read(int i) {
    Node *node;
    node = getNodeByIndex(i);
    // printf("---\n");
    // printf("Index %d\n", node->index);
    // printf("Key [0] %d\n", node->entries[0].key);
    // printf("Child [0] %d\n", node->entries[0].child);
    // printf("Key [1] %d\n", node->entries[1].key);
    // printf("Child [1] %d\n", node->entries[1].child);
    // printf("Next node %d\n", node->nextNode);
    // printf("Parent %d\n", node->parentNode);
    // printf("Number of entries %d\n", node->numberOfEntries);
    // printf("---\n");
    return node;
}

void printNode(Node *node) {
    printf("---\n");
    printf("Index %d\n", node->index);
    for (int i = 0; i < NODE_MAX_ENTRIES; i++) {
        printf("Key [%d] %d\n", i, node->entries[i].key);
        printf("Child [%d] %d\n", i, node->entries[i].child);
    }
    printf("Next node %d\n", node->nextNode);
    printf("Parent %d\n", node->parentNode);
    printf("Number of entries %d\n", node->numberOfEntries);
    printf("---\n");
}

void insert(BTree *bTree, Node *node, int i) {
    Entry entry;
    entry.key = i;
    entry.child = -1;
    entry.rrn = i * 10;
    insertNewElement(bTree, node, &entry);
}

int main()
{
    char option[7];
    int nUSP;

    while(1){
        scanf(" %s", option);

        if(strcmp(option, "insert") == 0){


        }else if(strcmp(option, "search") == 0){
            scanf("%d", &nUSP);

            Result * result = getRRNByPrimaryKey(0, nUSP);

            if(result->node == NULL){
                printf("Registro nao encontrado!\n");
            }else{
                Student * student = getStudentByRRN(result->entry.key);

                printf("-------------------------------\n");

                printf("nUSP: %d\nNome: %s\nSobrenome: %s\nCurso: %s\nNota: %.2f\n",
                student->nUSP, student->name, student->surname, student->course, student->grade);

                printf("-------------------------------\n\n");

                free(student);
            }

            free(result);
        }else if(strcmp(option, "update") == 0){


        }else if(strcmp(option, "exit") == 0){
            exit(0);
        }
    }

    return 0;
}