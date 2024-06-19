//
// Created by Daniel on 09/06/2024.
//
#include "macro.h"

unsigned int hashFunction(const char *str, int size) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash << 5) + *str++;
    }
    return hash % size;
}

MacroTable* createTable(int size) {
    int i;
    MacroTable *table= (MacroTable *) malloc(sizeof(MacroTable));
    if (table == NULL){
        fprintf(stderr,"Error allocating memory\n");
        return NULL;
    }
    table->size = size;
    table->count = 0;
    table->table = (Macro **) malloc(size * sizeof(Macro *));
    if (table->table == NULL){
        fprintf(stderr,"Error allocating memory\n");
        free(table);
        return NULL;
    }
    for (i = 0; i < size; i++){
        table->table[i] = NULL;
    }
    return table;

}
void freeTable(MacroTable *table){
    int i;
    Macro *current, *temp;
    for (i = 0; i < table->size; i++){
        current = table->table[i];
        while (current != NULL){
            temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(table->table);
    free(table);
}
void resizeTable(MacroTable *table){
    int oldSize, i;
    oldSize = table->size;
    table->size *=2;
    Macro **newTable = (Macro **) malloc(table->size * sizeof(Macro *));
    for (i = 0; i < table -> size; i++) {
        newTable[i] = NULL;
    }
    for (i = 0; i < oldSize; i++){
        Macro *current = table->table[i];
        while (current != NULL){
            unsigned int hashIndex;
            Macro *next = current->next;
            hashIndex = hashFunction(current->name, table->size);
            current->next = newTable[hashIndex];
            newTable[hashIndex] = current;
            current = next;
        }
    }
    free(table->table);
    table->table = newTable;
}
void addMacro(MacroTable *table, char name[], const char code[]) {
    unsigned int hashIndex;

    if (table->count+1 > table->size * 0.75) {
        resizeTable(table);
    }
    hashIndex= hashFunction(name, table->size);
    Macro *current = table->table[hashIndex];
    while (current != NULL){
        if (strcmp(current->name, name)== 0){
            fprintf(stderr,"Macro %s already exists\n", name);
            return ;
        }
        current = current->next;
    }
Macro *newMacro = (Macro *) malloc(sizeof(Macro));
    if (newMacro == NULL){
        fprintf(stderr,"Error allocating memory\n");
        return;
    }
    strncpy(newMacro->name, name, sizeof(newMacro->name) - 1);
    newMacro ->name[sizeof(newMacro->name)-1] = '\0';
    strncpy(newMacro->code, code, sizeof(newMacro->code)-1);
    newMacro->code[sizeof(newMacro->code)-1] = '\0';
    newMacro->next = table->table[hashIndex];
    table->table[hashIndex] = newMacro;
}

char *findMacroCode(MacroTable *table, char name[]) {
    unsigned int hashIndex;
    hashIndex= hashFunction(name, table->size);
    Macro *current = table->table[hashIndex];
    while (current != NULL){
        if (strcmp(current->name, name)== 0){
            return current->code;
        }
        current = current->next;
    }
    return NULL;
}
int checkValidMacroName(char *name) {
    if (strlen(name) > 31) {
        fprintf(stderr,"The macro name is more than 31 characters\n");
        return FALSE;
    }
    if ((name[0] < 'A' || name[0] > 'Z') && (name[0] < 'a' || name[0] > 'z')) {
        fprintf(stderr,"The macro name must start with a latin letter\n");
        return FALSE;
    }
    return TRUE;
}
char *removeMacro(char *fileName) {
    MacroTable *table;
    FILE *writeFile, *readFile;
    int flag;
    char name[80];
    char code[1000];
    char macroName[80];
    char *existing_code;
    char buffer[100];
    char *newFileName;
    char *dot_position;
    char temp[100];
    temp[0] = '\0';
    newFileName = (char *) malloc(100*sizeof(char));
    if (newFileName == NULL) {
        fprintf(stderr,"Error allocating memory\n");
        return NULL;
    }
    dot_position = strrchr(fileName, '.');
    if (dot_position == NULL) {
        fprintf(stderr,"Error finding file extension\n");
        free(newFileName);
        return NULL;
    }
    strncpy(newFileName, fileName, dot_position - fileName);
    strcpy(newFileName + (dot_position - fileName), ".ps");

    table = createTable(INITIAL_SIZE);
    if (table == NULL) {
        fprintf(stderr,"Error creating table\n");
        free(newFileName);
        return NULL;
    }
    flag = FALSE;
    readFile = fopen(fileName, "r");
    if (readFile == NULL) {
        fprintf(stderr,"Error opening readFile\n");
        free(newFileName);
        freeTable(table);
        return NULL;
    }
    writeFile = fopen(newFileName, "w+");
    if (writeFile == NULL) {
        fprintf(stderr,"Error opening writeFile\n");
        freeTable(newFileName);
        freeTable(table);
        fclose(readFile);
        return NULL;
    }

    while (fgets(buffer, sizeof(buffer), readFile) != NULL) {
        if (strncmp(buffer, START_MACRO, strlen(START_MACRO)) == 0) {
            flag = TRUE;
            if (sscanf(buffer + strlen(START_MACRO), "%s", name)!= 1) {
                fprintf(stderr,"Error in macro name\n");
                free(newFileName);
                fclose(readFile);
                fclose(writeFile);
                freeTable(table);
                return NULL;
            }
            if (!checkValidMacroName(name)) {
                free(newFileName);
                fclose(readFile);
                fclose(writeFile);
                freeTable(table);
                return NULL;
            }
            removeSpaces(buffer);
            sscanf(buffer + strlen(START_MACRO) + strlen(name), "%s", temp);
            if (temp[0] != '\0')
            {
                fprintf(stderr,"Error in macro name\n");
                free(newFileName);
                fclose(readFile);
                fclose(writeFile);
                freeTable(table);
                return NULL;
            }
            fgets(buffer, sizeof(buffer), readFile);
        } while (flag) {
            if (strncmp(buffer, END_MACRO, strlen(END_MACRO)) == 0) {
                if(sscanf(buffer + strlen(END_MACRO), "%s", temp)==1)
                {
                    fprintf(stderr,"Error in macro name\n");
                    free(newFileName);
                    fclose(readFile);
                    fclose(writeFile);
                    freeTable(table);
                    return NULL;
                }
                addMacro(table, name, code);
                flag = FALSE;
                fgets(buffer, sizeof(buffer), readFile);
            } else {
                strncat(code, buffer, sizeof(code) - strlen(code) - 1);
                fgets(buffer, sizeof(buffer), readFile);

            }
        }
        sscanf(buffer, "%s", macroName);
        existing_code = findMacroCode(table, macroName);
        if (existing_code != NULL) {
            fprintf(writeFile, "%s", existing_code);
        } else {
            fprintf(writeFile, "%s", buffer);

        }
    }
    fclose(readFile);
    fclose(writeFile);
    freeTable(table);
    return newFileName;
}





