#include "Includes.h"

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
    while (!feof(stdin)) {
        option = getOptionFromCSV();
        if (!strcmp(option, "insert")) {
            student = readStudentFromCSV();
            search.history = (int *) malloc(sizeof(int));
            search.history[0] = bTree->rootNode;
            search.currentIndex = 0;
            getRRNByPrimaryKey(&result, bTree->rootNode, student->nUSP, &search);
            if (result.entry.key >= 0) {
                printf("O Registro ja existe!\n");
            } else {
                Entry newEntry;
                newEntry.rrn = saveNewStudent(student);
                newEntry.key = student->nUSP;
                newEntry.child = -1;
                insertNewEntry(bTree, &newEntry, &search);
            }
            search.currentIndex = -1;
            free(search.history);
            free(student);
        } else if (!strcmp(option, "search")) {
            scanf("%d", &nUsp);
            search.history = (int *) malloc(sizeof(int));
            search.history[0] = bTree->rootNode;
            search.currentIndex = 0;
            getRRNByPrimaryKey(&result, bTree->rootNode, nUsp, &search);

            if(result.entry.key < 0){
                printf("Registro nao encontrado!\n");
            } else{
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
        }
        free(option);
	}
    writeBTreeHeader(bTree);
}

