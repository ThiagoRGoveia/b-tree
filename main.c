#include "Includes.h"
// int nodeCounter = 0;

Node *read(int i) {
    Node *node;
    node = getNodeByIndex(i);
    printf("---\n");
    printf("Index %d\n", node->index);
    for (int i=0; i < NODE_MAX_ENTRIES; i++) {
        printf("Key [%d] %d\n", i, node->entries[i].key);
        printf("Child [%d] %d\n", i, node->entries[i].child);
    }
    printf("Next node %d\n", node->nextNode);
    printf("Parent %d\n", node->parentNode);
    printf("Number of entries %d\n", node->numberOfEntries);
    printf("---\n");
    return node;
}


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
    Search search;
    // Node *rootNode;
    while (!feof(stdin)) {
        option = getOptionFromCSV();
        // rootNode = getNodeByIndex(bTree->rootNode);
        if (!strcmp(option, "insert")) {
            student = readStudentFromCSV();
            // printStudent(student);
            // printf("-1\n");
            search.history = (int *) malloc(sizeof(int));
            search.history[0] = bTree->rootNode;
            search.currentIndex = 0;
            getRRNByPrimaryKey(&result, bTree->rootNode, student->nUSP, &search);
            // printf("0\n");
            if (result.entry.key >= 0) {
                printf("O Registro ja existe!\n");
            } else {
                // printf("INSERT %d\n", student->nUSP);
                Entry newEntry;
                // printf("1\n");
                newEntry.rrn = saveNewStudent(student);
                // printf("2\n");
                newEntry.key = student->nUSP;
                newEntry.child = -1;
                insertNewEntry(bTree, &newEntry, &search);
                // read(result.node->index);
                // printf("3\n");
            }
            search.currentIndex = -1;
            free(search.history);
            free(student);
        } else if (!strcmp(option, "search")) {
            scanf("%d", &nUsp);
            // printf("%d\n" , nUsp);
            search.history = (int *) malloc(sizeof(int));
            search.history[0] = bTree->rootNode;
            search.currentIndex = 0;
            getRRNByPrimaryKey(&result, bTree->rootNode, nUsp, &search);

            if(result.entry.key < 0){
                printf("Registro nao encontrado!\n");
            } else{
                // printf("%ld", result->entry.rrn);
                Student * student = getStudentByRRN(result.entry.rrn);
                printStudent(student);
                free(student);
            }
            result.entry.key = -1;
            result.node = NULL;
            search.currentIndex = -1;
            free(search.history);

        } else if (!strcmp(option, "update")) {
            student = readStudentFromCSV();
            search.history = (int *) malloc(sizeof(int));
            search.history[0] = bTree->rootNode;
            search.currentIndex = 0;
            getRRNByPrimaryKey(&result, bTree->rootNode, student->nUSP, &search);
            if(result.entry.key < 0){
                printf("Registro nao encontrado!\n");
            } else{
                setStudentByRRN(result.entry.rrn, student);
                free(student);
            }
            result.entry.key = -1;
            result.node = NULL;
            search.currentIndex = -1;
            free(search.history);
        } else if (!strcmp(option, "exit")) {
            break;
        } else if (!strcmp(option, "root")) {
            printf("%d\n", bTree->rootNode);
        }
        // free(rootNode);
        free(option);
	}
    writeBTreeHeader(bTree);
    // rootNode = getNodeByIndex(bTree->rootNode);
    // Node *node;
    // for (int i = 0; i < bTree->numberOfNodes; i++) {
    //     read(i);
    // }
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