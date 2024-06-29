//
// Created by dako6 on 21/06/2024.
//

#ifndef PROJECT_C_ASM_ASSEMBLY_H
#define PROJECT_C_ASM_ASSEMBLY_H
#include "main.h"

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
enum addressingModes {
    AddressImmediately= 0,
    AddressDirect = 1,
    RegisterIndirect = 2,
    RegisterDirect = 3
};
struct commandMachineCode{
    unsigned opcode:4;
    unsigned sourceAddressImmediately:1;
    unsigned sourceAddressDirect:1;
    unsigned sourceRegisterIndirect:1;
    unsigned sourceRegisterDirect:1;
    unsigned destinationAddressImmediately:1;
    unsigned destinationAddressDirect:1;
    unsigned destinationRegisterIndirect:1;
    unsigned destinationRegisterDirect:1;
    unsigned A:1;
    unsigned R:1;
    unsigned E:1;
};
struct operandMachineCode{
    unsigned int address:12;
    unsigned int A:1;
    unsigned int R:1;
    unsigned int E:1;
};
struct RegisterMachineCode{
    unsigned int NONE:6;
    unsigned int Source:3;
    unsigned int Destination:3;
    unsigned int A:1;
    unsigned int R:1;
    unsigned int E:1;
};
int buildCommandMachineBinary(char commandName[5], int opCode, int numberOfOperands, char operand1[30], char operand2[30]);
int buildOperandMachineBinary(char *operand1,char *operand2,int operandNumber);
void pressesLine(char *line);
int TypeOfOperand( char *operand);
#endif //PROJECT_C_ASM_ASSEMBLY_H
