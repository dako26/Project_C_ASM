// macro.h
//
// Created by Daniel on 09/06/2024.
//
#ifndef MACRO_H
#define MACRO_H

#include "main.h"

#define START_MACRO "macr"
#define END_MACRO "endmacr"
#define INITIAL_SIZE  101

typedef struct Macro {
    char name[80];
    char code[1000];
    struct Macro *next;
} Macro;

typedef struct {
    int size;
    int count;
    Macro **table;
} MacroTable;



unsigned int hashFunction(const char *str, int size);
MacroTable* createTable(int size);
void freeTable(MacroTable *table);
void resizeTable(MacroTable *table);
void addMacro(MacroTable *table, char name[], const char code[]);
char *findMacroCode(MacroTable *table, char name[]);
int checkValidMacroName(char *name);
char *removeMacro(char *fileName);



#endif // MACRO_H
