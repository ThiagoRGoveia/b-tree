#include "Includes.h"
// int nodeCounter = 0;

Node *read(int i) {
    Node *node;
    node = getNodeByIndex(i);
    printf("---\n");
    printf("Index %d\n", node->index);
    for (int i=0; i < 8; i++) {
        printf("Key [%d] %d\n", i, node->entries[i].key);
        printf("Child [%d] %d\n", i, node->entries[i].child);
    }
    printf("Next node %d\n", node->nextNode);
    printf("Parent %d\n", node->parentNode);
    printf("Number of entries %d\n", node->numberOfEntries);
    printf("---\n");
    return node;
}

// void printNode(Node *node) {
    // printf("---\n");
    // printf("Index %d\n", node->index);
    // for (int i = 0; i < NODE_MAX_ENTRIES; i++) {
    //     printf("Key [%d] %d\n", i, node->entries[i].key);
    //     printf("Child [%d] %d\n", i, node->entries[i].child);
    // }
    // printf("Next node %d\n", node->nextNode);
    // printf("Parent %d\n", node->parentNode);
    // printf("Number of entries %d\n", node->numberOfEntries);
    // printf("---\n");
// }

// void insert(BTree *bTree, Node *node, int i) {
//     Entry entry;
//     entry.key = i;
//     entry.child = -1;
//     entry.rrn = i * 10;
//     insertNewElement(bTree, node, &entry);
// }

// int main()
// {
//     BTree *bTree;
//     bTree = createBTree();
//     addNewNodeToFile(bTree->rootNode);
//     insert(bTree, bTree->rootNode, 0);
//     insert(bTree, bTree->rootNode, 1);
//     insert(bTree, bTree->rootNode, 2);
//     read(0);
//     read(1);
//     Node *node;
//     node = getNodeByIndex(2);
//     insert(bTree, node, 3);
//     insert(bTree, node, 4);

//     for (int i = 0; i <= 3; i++) {
//         node = getNodeByIndex(i);
//         // printNode(node);
//     }
// }


int main()
{
    FILE *dataFilePointer;
    Student *student;
    Result result;
    int numberOfEntries = 0;
    long int newStudentRrn;
    char *option;
    BTree *bTree;
    bTree = loadOrCreateBTree();
    int nUsp;
    // Node *rootNode;
    // printf("%d\n", bTree->rootNode);
    while (!feof(stdin)) {
        option = getOptionFromCSV();
        // rootNode = getNodeByIndex(bTree->rootNode);
        if (!strcmp(option, "insert")) {
            student = readStudentFromCSV();
            // printStudent(student);
            // printf("-1\n");
            getRRNByPrimaryKey(&result, bTree->rootNode, student->nUSP);
            // printf("0\n");
            if (result.entry.key >= 0) {
                printf("O Registro ja existe!\n");
            } else {
                printf("INSERT %d\n", student->nUSP);
                Entry newEntry;
                // printf("1\n");
                newEntry.rrn = saveNewStudent(student);
                // printf("2\n");
                newEntry.key = student->nUSP;
                newEntry.child = -1;
                insertNewElement(bTree, getNodeByIndex(result.node->index), &newEntry);
                // read(result.node->index);
                // printf("3\n");
            }
            free(student);
        } else if (!strcmp(option, "search")) {
            scanf("%d", &nUsp);
            printf("%d\n" , nUsp);
            getRRNByPrimaryKey(&result, bTree->rootNode, nUsp);

            if(result.node == NULL){
                printf("Registro nao encontrado!\n");
            }else{
                // printf("%ld", result->entry.rrn);
                Student * student = getStudentByRRN(result.entry.rrn);
                printStudent(student);
                free(student);
                result.entry.key = -1;
                result.node = NULL;
            }

        } else if (!strcmp(option, "update")) {
        } else if (!strcmp(option, "exit")) {
            break;
        }
        // free(rootNode);
        free(option);
	}
    writeBTreeHeader(bTree);
    // rootNode = getNodeByIndex(bTree->rootNode);
    Node *node;
    for (int i = 0; i < bTree->numberOfNodes; i++) {
        read(i);
    }
}

// printf("---\n");
// printf("Index %d\n",rootNode->index);
// for (int i = 0; i < NODE_MAX_ENTRIES; i++) {
//     printf("Key [%d] %d\n", i,rootNode->entries[i].key);
//     printf("Child [%d] %d\n", i,rootNode->entries[i].child);
// }
// printf("Next node %d\n",rootNode->nextNode);
// printf("Parent %d\n",rootNode->parentNode);
// printf("Number of entries %d\n",rootNode->numberOfEntries);
// printf("---\n");