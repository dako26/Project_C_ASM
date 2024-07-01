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
    int dc;
    int isData;
    struct Label *next;
} Label;
typedef struct externLabel {
    char *name;
    int address;
    struct externLabel *next;
} externLabel;
typedef struct entryLabel {
    char *name;
    int address;
    struct entryLabel *next;
} entryLabel;




MacroNames* createMacroNameNode(const char *name);
void freeMacroNameNode(MacroNames *node);
void addMacroName(MacroNames **head, const char *name);
int isMacroNameExists(MacroNames *head, const char *name);

Label* createLabelNode(const char *name, int ic, int dc, int isData);
void freeLabelNode(Label *node);
void addLabel(Label **head, const char *name, int ic, int dc, int isData);
int isLabelExists(Label *head, const char *name);

externLabel* createExternLabelNode(const char *name);
void freeExternLabelNode(externLabel *node);
void addExternLabel(externLabel **head, const char *name);
int isExternLabelExists(externLabel *head, const char *name);

entryLabel* createEntryLabelNode(const char *name);
void freeEntryLabelNode(entryLabel *node);
void addEntryLabel(entryLabel **head, const char *name);
int isEntryLabelExists(entryLabel *head, const char *name);

#endif //PROJECT_C_ASM_TABLE_H
