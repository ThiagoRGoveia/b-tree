#include "Includes.h"

// Realiza a leitura do stream de dados, char por char até encontrar
// o char delimitador, um \n ou o fim do arquivo
char *getField(char delimiter) {
	char charHolder;
    int stringIndex = 0;
    char *string;

    string = (char *) malloc(sizeof(char));
    charHolder = fgetc(stdin);

    while (!feof(stdin) && charHolder != delimiter && charHolder != '\n')
    {
        if (charHolder != '"') {
            string[stringIndex++] = charHolder;
            string = (char *) realloc(string, sizeof(char) * stringIndex + 1);
        }
        charHolder = fgetc(stdin);
    }
    string[stringIndex] = '\0';
    return string;
}

// Lê campo tipo int
int getIntField() {
    char *string;
    int parsedNumber;
    string = getField(DELIMITERCHAR);
    parsedNumber = atoi(string);
    free(string);
    return parsedNumber;
}

// Lê campo tipo float
float getFloatField() {
    char *string;
    float parsedNumber;
    string = getField(DELIMITERCHAR);
    parsedNumber = (float) atof(string);
    free(string);
    return parsedNumber;
}

char *getStringField() {
    return getField(DELIMITERCHAR);
}


char *getOptionFromCSV() {
    char *option;
    option = getField(' ');
    return option;
}

// Lê registros de estudantes do stdin no formato CSV
Student *readStudentFromCSV() {
    Student *student;
    char* stringHolder;
    student = (Student *) malloc(sizeof(Student));
    // printf("%s\n", "Inicio");
    student->nUSP = getIntField();
    // printf("%d\n", student->nUSP);
    stringHolder =  getStringField();
    strcpy(student->name, stringHolder);
    // printf("%s\n", student->name);
    free(stringHolder);
    stringHolder =  getStringField();
    strcpy(student->surname, stringHolder);
    // printf("%s\n", student->surname);
    free(stringHolder);
    stringHolder =  getStringField();
    strcpy(student->course, stringHolder);
    // printf("%s\n", student->course);
    free(stringHolder);
    student->grade = getFloatField();
    // printf("%f\n", student->grade);
    // printf("%s\n", "FIM");

    return student;
}

