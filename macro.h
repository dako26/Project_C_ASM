// macro.h
//
// Created by Daniel on 09/06/2024.
//
#ifndef MACRO_H
#define MACRO_H

#include "main.h"

#define START_MACRO "macr"
#define END_MACRO "endmacr"
#define MAX_MACRO 100

typedef struct {
    char name[80];
    char code[1000];
} Macro;
void removeMacro();
char* findMacroCode(Macro database[], char name[]);
void addMacro(Macro database[], char name[], const char code[]);
void initializeDatabase(Macro database[]);


#endif // MACRO_H
