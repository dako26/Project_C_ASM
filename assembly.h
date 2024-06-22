//
// Created by dako6 on 21/06/2024.
//

#ifndef PROJECT_C_ASM_ASSEMBLY_H
#define PROJECT_C_ASM_ASSEMBLY_H
#include "main.h"

#define START_ADDRESS 100
struct command {
    char *name;
    int numOfOperands;
    int opcode;
}commond[] = {
    {"mov", 2, 0},
    {"cmp", 2, 1},
    {"add", 2, 2},
    {"sub", 2, 3},
    {"lea", 2, 4},
    {"clr", 1, 5},
    {"not", 1, 6},
    {"inc", 1, 7},
    {"dec", 1, 8},
    {"jmp", 1, 9},
    {"bne", 1, 10},
    {"red", 1, 11},
    {"prn", 1, 12},
    {"jsr", 1, 13},
    {"rts", 0, 14},
    {"stop", 0, 15},
};
typedef struct addressMachineCode{
    int address;
    char machineCode;
    struct addressMachineCode *next;
}addressMachineCode;



#endif //PROJECT_C_ASM_ASSEMBLY_H
