//
// Created by Daniel on 09/06/2024.
//
#include "macro.h"

void initializeDatabase(Macro database[]) {
    int i;
    for (i = 0; i < MAX_MACRO; i++) {
        database[i].name[0] = '\0';
        database[i].code[0] = '\0';
    }
}

void addMacro(Macro database[], char name[], const char code[]) {
    int i;
    for (i = 0; i < MAX_MACRO; ++i) {
        if (strcmp(database[i].name, name) == 0) {
            printf("Macro %s already exists\n", name);
            return;
        }
    }

    for (i = 0; i < MAX_MACRO; i++) {
        if (database[i].name[0] == '\0') {
            strncpy(database[i].name, name, sizeof(database[i].name) - 1); // Change: Used strncpy for safer string copying
            strncpy(database[i].code, code, sizeof(database[i].code) - 1); // Change: Used strncpy for safer string copying
            return;
        }

    }
    printf("Macro database is full\n");
}

char *findMacroCode(Macro database[], char name[]) {
    int i;
    for (i = 0; i < MAX_MACRO; ++i) {
        if (strcmp(database[i].name, name) == 0) {
            return database[i].code;
        }
    }
    return NULL;
}
// TODO add macro name checker
void removeMacro() {
    Macro database[MAX_MACRO];
    initializeDatabase(database);
    int flag = FALSE;
    char name[80];
    char code[1000];
    char macroName[80];
    char *existing_code;
    char buffer[100];
    FILE *file = fopen("ps.as", "w+");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (strncmp(buffer, START_MACRO, strlen(START_MACRO)) == 0) {
            flag = TRUE;
            sscanf(buffer + strlen(START_MACRO), "%s", name);
            code[0] = '\0';
            fgets(buffer, sizeof(buffer), stdin);
        } while (flag == TRUE) {
            if (strncmp(buffer, END_MACRO, strlen(END_MACRO)) == 0) {
                addMacro(database, name, code);
                flag = FALSE;
                fgets(buffer, sizeof(buffer), stdin);
            } else {
                strncat(code, buffer, sizeof(code) - strlen(code) - 1);
                fgets(buffer, sizeof(buffer), stdin);

            }
        }
        sscanf(buffer, "%s", macroName);
        existing_code = findMacroCode(database, macroName);
        if (existing_code != NULL) {
            fprintf(file, "%s", existing_code);
        } else {
            fprintf(file, "%s", buffer);

        }
    }
    fclose(file);
}




