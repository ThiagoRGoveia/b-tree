#include "Includes.h"

// Quebra a linha de entrada e retorna parte por parte 
/*
Student *entrada_student(const char *string) {
    if (string == NULL){
    return NULL;
    }
    char *entrada_aux = strdup((char *)string);

    Student *student_aux = calloc(1, sizeof(Student));
    if (student_aux == NULL){
    return NULL;
    }

    char *nusp = strtok(entrada_aux, ",");
    if (nusp) {

        char *pt_aux;
        student_aux->nUSP = strtol(nusp, &pt_aux, 10);

        if (nusp == pt_aux) {
            free(entrada_aux);
            return NULL;
        }
    }
    else {
        free(entrada_aux);
        return NULL;
    }


    char *nome = strtok(NULL, ",");
    if (nome) {
        strlcpy(student_aux->name, nome, FIELD_LEN);
    }
    else {
        free(entrada_aux);
        return NULL;
    }


    char *sobrenome = strtok(NULL, ",");
    if (nome) {
        strlcpy(student_aux->surname, sobrenome, FIELD_LEN);
    }
    else {
        free(entrada_aux);
        return NULL;
    }


    char *curso = strtok(NULL, ",");
    if (nome) {
        strlcpy(student_aux->course, curso, FIELD_LEN);
    }
    else {
        free(entrada_aux);

        return NULL;
    }

    char *nota = strtok(NULL, ",");
    if (nota) {

        char *pt_aux;
        student_aux->grade = strtol(nota, &pt_aux, 10);

        if (nota == pt_aux) {
            free(entrada_aux);
            return NULL;
        }
    }
    else {
        free(entrada_aux);
        return NULL;
    }

    free(entrada_aux);
    return student_aux;
}


void updateToFile(FILE *fp, Student *student, long int RRN) {

    long int seekaux = RRN * STUDENT_SIZE;
    
    fseek(fp, seekaux, SEEK_SET);
    fwrite(&student->nUSP, sizeof(int), 1, fp);
    fwrite(student->name, STRING_FIELD_SIZE, 1, fp);
    fwrite(student->surname, STRING_FIELD_SIZE, 1, fp);
    fwrite(student->course, STRING_FIELD_SIZE, 1, fp);
    fwrite(&student->grade, sizeof(float), 1, fp);
} */

void update(Student *student){

    Result * result = getRRNByPrimaryKey(0, student->nUSP);
        if (result->node == 0) {
        // Caso falhe com código 0, significa que não existe
        printf("O Registro não foi encontrado!\n");
        }
        else {
        setStudentByRRN(result->node, student);
        }

}
