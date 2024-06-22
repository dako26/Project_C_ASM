//
// Created by dako6 on 21/06/2024.
//

#ifndef PROJECT_C_ASM_TABLE_H
#define PROJECT_C_ASM_TABLE_H
#include "main.h"

typedef struct MacroNames {
    char *name;
    struct MacroNames *next;
} MacroNames;
typedef struct Label {
    char *name;
    int ic;
    char *type;
    int *external;
    int *entry;
    struct Label *next;
} Label;
typedef struct {
    int size;
    int count;
    Label **table;
} LabelTable;




MacroNames* createMacroNameNode(const char *name);
void freeMacroNameNode(MacroNames *node);
void addMacroName(MacroNames **head, const char *name);
int isMacroNameExists(MacroNames *head, const char *name);



#endif //PROJECT_C_ASM_TABLE_H
