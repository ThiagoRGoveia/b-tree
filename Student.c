#include "Includes.h"

Student *getStudentByRRN(long int RRN) {
    FILE *fp;
    Student *student;
    fp = fopen(DATA_FILE, "r");
    fseek(fp, RRN, SEEK_SET);
    student = readStudentFromFile(fp);
    fclose(fp);
    return student;
}

void setStudentByRRN(long int RRN, Student *student) {
    FILE *fp;
    fp = fopen(DATA_FILE, "r+");
    fseek(fp, RRN, SEEK_SET);
    writeSudentToFile(fp, student);
    fclose(fp);
}

long int saveNewStudent(Student *student) {
    FILE *fp;
    long int rrn;
    fp = fopen(DATA_FILE, "r+");
    fseek(fp, 0, SEEK_END);
    writeSudentToFile(fp, student);
    rrn = ftell(fp);
    fclose(fp);
    return rrn;
}

void printStudent(Student *student) {
    printf("-------------------------------\n");
    printf("%d\n", student->nUSP);
    printf("%s\n", student->name);
    printf("%s\n", student->surname);
    printf("%s\n", student->course);
    printf("%.2f\n", student->grade);
    printf("-------------------------------\n");
}
// Quebra a linha de entrada e retorna parte por parte
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
            student_destroy(student_aux);
            return NULL;
        }
    }
    else {
        free(entrada_aux);
        student_destroy(student_aux);
        return NULL;
    }


    char *nome = strtok(NULL, ",");
    if (nome) {
        strlcpy(student_aux->name, nome, FIELD_LEN);
    }
    else {
        free(entrada_aux);
        student_destroy(student_aux);
        return NULL;
    }


    char *sobrenome = strtok(NULL, ",");
    if (nome) {
        strlcpy(student_aux->surname, sobrenome, FIELD_LEN);
    }
    else {
        free(entrada_aux);
        student_destroy(student_aux);
        return NULL;
    }


    char *curso = strtok(NULL, ",");
    if (nome) {
        strlcpy(student_aux->course, curso, FIELD_LEN);
    }
    else {
        free(entrada_aux);
        student_destroy(student_aux);
        return NULL;
    }

    char *nota = strtok(NULL, ",");
    if (nota) {

        char *pt_aux;
        student_aux->grade = strtol(nota, &pt_aux, 10);

        if (nota == pt_aux) {
            free(entrada_aux);
            student_destroy(student_aux);
            return NULL;
        }
    }
    else {
        free(entrada_aux);
        student_destroy(student_aux);
        return NULL;
    }

    free(entrada_aux);
    return student_aux;
}
