//
// Created by dako6 on 29/06/2024.
//

#ifndef PROJECT_C_ASM_MEMORY_H
#define PROJECT_C_ASM_MEMORY_H
#include "main.h"

#define binaryLength 15
#define startAddress 100

typedef struct Memory {
    int address;
    char *label;
    int binary;
    struct Memory *next;
} Memory;


Memory *createMemory(int address, char *label, int binary);
void addMemory(Memory **head, int address, char *label, int binary);
void freeMemory(Memory *memory);




#endif //PROJECT_C_ASM_MEMORY_H
