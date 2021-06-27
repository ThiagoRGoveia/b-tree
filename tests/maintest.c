#include "Includes.h"

int main(){

    //pega a entrada
	char entrada[100];
    int func;

	fgets(entrada,100,stdin);

	while(fgets(entrada,100,stdin)!=NULL){

    //funcao para gerar uma string da funcionalidade
	char *token = strtok(entrada, " ");

    if (strcmp(token, "Insert") == 0){
        func = 1;
    }
	if (strcmp(token, "Search") == 0){
		func = 2;	
	}
    if (strcmp(token, "Update") == 0){
        func = 3;
    }
	if (strcmp(token, "Exit") == 0){
		func = 4;	
	}
    else continue;

    switch(func){
		//se for a funcionalidade 1 Insert
		case 1: 

         char *entrada_aux = entrada+strlen(token)+1;
         Student *student = entrada_student(entrada_aux);

         if (student == NULL) {
                printf("Input inválido!\n");
            } 
        else {
                int testebusca; //só pra compilar enquanto n arrumo
                if (testebusca == 0) {
                    // Caso falhe com código 0, significa que já existe
                    printf("O Registro ja existe!\n");
                }
                else {
                             /* BTree *bTree;
                             bTree = createBTree();
                             addNewNodeToFile(bTree->rootNode);
                             Entry entry;
                             entry.key = 5;
                             entry.child = 0;
                             entry.rrn = 20;
                            insertNewElement(bTree, bTree->rootNode, &entry); */

                        setStudentByRRN(student->nUSP, student);
                }
	
        }
		break;
		//se for a funcionalidade 2 Search
		case 2:


		break;

        //se for a funcionalidade 3 Update
		case 3:

        char * entrada_aux = entrada+strlen(token)+1;
        Student *student = entrada_student(entrada_aux);
    

         if (student == NULL) {
                printf("Input inválido!\n");
            } 
        else {
                char arquivo[10] = "arquivo";
                FILE * fp = fopen(arquivo , "w");
                update(student);
                /*Result * result = getRRNByPrimaryKey(0, student->nUSP);
                if (result->node ) {
                    // Caso falhe com código 0, significa que não existe
                    printf("O Registro não foi encontrado!\n");
                }
                else {
                        updateToFile(fp, student, result->node);
                        fclose(fp);	
                }*/
	
        }
            

		break;
        //se for a funcionalidade 4 Exit
		case 4:


		break;
		//caso nao exista a funcionalidade ainda
		default:
			printf("Funcionalidade %d não implementada.\n", func);
			return 0;
	}


 }
}