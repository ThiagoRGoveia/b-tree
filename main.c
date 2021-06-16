#include "Includes.h"

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