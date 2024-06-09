//
// Created by Daniel on 09/06/2024.
//
#include "macro.h"

void initializeDatabase(Macro database[]) {
    int i, j;
    for (i = 0; i < MAX_MACRO; i++) {
        for (j = 0; j < 80; j++) {
            database[i].name[j] = '\0';
        }
        for (j = 0; j < 1000; j++) {
            database[i].code[j] = '\0';
        }
    }
}

void addMacro(Macro database[], char name[], char code[]) {
    int i;
    for (i = 0; i < MAX_MACRO; ++i) {
        if (strcmp(database[i].name, name) == 0) {
            printf("Macro %s already exists\n", name);
            return;
        }
    }

    for (i = 0; i < MAX_MACRO; i++) {
        if (database[i].name[0] == '\0') {
            int j;
            for (j = 0; j < 50 && name[j] != '\0'; ++j) {
                database[i].name[j] = name[j];
            }
            for (j = 0; j < 1000 && code[j] != '\0'; ++j) {
                database[i].code[j] = code[j];
            }
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

int removeMacro() {
// TODO add macro name checker
    int flag = FALSE;
    char buffer[100];
    char name[80];
    char code[1000];
    FILE *file = fopen("ps.as", "r+");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (strncmp(buffer, START_MACRO, strlen(START_MACRO)) == 0) {
            flag = TRUE;
            sscanf(buffer + strlen(START_MACRO), "%s", name);
        }
        while (flag == TRUE) {
            if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                printf("Error reading file\n");
                return 1;
            }
            if (strncmp(buffer, END_MACRO, strlen(END_MACRO)) != 0) {


            } else {
                flag = FALSE;
                break;
            }
        }
    }
}

}


}