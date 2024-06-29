//
// Created by dako6 on 21/06/2024.
//

#include "assembly.h"

void pressesLine(char *line) {
    extern Memory *memoryHead;
    int i, numberOfOperands, opCode;
    char commandName[5];
    numberOfOperands = 0;
    char operand1[30], operand2[30];
    operand1[0] = '\0';
    operand2[0] = '\0';
    opCode = 0;
    char *temp;
    temp = strdup(line);
    if (temp == NULL) {
        fprintf(stderr, "Error: memory allocation failed\n");
        return;
    }
    sscanf(temp, "%s", commandName);
    for (i = 0; i < sizeof(commond) / sizeof(commond[0]); i++) {
        if (strcmp(commond[i].name, commandName) == 0) {
            numberOfOperands = commond[i].numOfOperands;
            opCode = commond[i].opcode;
            break;
        }
    }
    if (numberOfOperands == 2) {
        sscanf(temp, "%s %29[^,], %29s", commandName, operand1, operand2);
        addMemory(&memoryHead, ic + 100, "NO",
                  buildCommandMachineBinary(commandName, opCode, numberOfOperands, operand1, operand2));
        ic++;
        if (TypeOfOperand(operand2) == RegisterIndirect || TypeOfOperand(operand2) == RegisterDirect) {
            addMemory(&memoryHead, ic + 100, "NO",
                      buildOperandMachineBinary(operand1, operand2, 1));
            ic++;
        } else {
            addMemory(&memoryHead, ic + 100, "NO",
                      buildOperandMachineBinary(operand1, operand2, 1));
            ic++;
            addMemory(&memoryHead, ic + 100, "NO",
                      buildOperandMachineBinary(operand1, operand2, 2));
            ic++;
        }
    } else if (numberOfOperands == 1) {
        sscanf(temp, "%s %29s", commandName, operand1);
        addMemory(&memoryHead, ic + 100, "NO",
                  buildCommandMachineBinary(commandName, opCode, numberOfOperands, operand1, operand2));
        ic++;
        addMemory(&memoryHead, ic + 100, "NO",
                  buildOperandMachineBinary(operand1, operand2, 2));
        ic++;
    } else {
        sscanf(temp, "%s", commandName);
        addMemory(&memoryHead, ic + 100, "NO",
                  buildCommandMachineBinary(commandName, opCode, numberOfOperands, operand1, operand2));
        ic++;
    }


    free(temp);
}

int buildOperandMachineBinary(char *operand1, char *operand2, int operandNumber) {
    int typeOfOperand1, typeOfOperand2;
    char *ptr;
    struct operandMachineCode code = {0};
    struct RegisterMachineCode regCode = {0};
    int binary;
    typeOfOperand1 = TypeOfOperand(operand1);
    typeOfOperand2 = TypeOfOperand(operand2);
    switch (typeOfOperand1) {
        case AddressImmediately:
            code.address = decimalToBinary(strtol(operand1 + 1, NULL, 10));
            code.A = 1;
            binary = *(int *) &code;
            return binary;
        case AddressDirect:
            binary = *(int *) &code;
            return binary;
        case RegisterIndirect:
        case RegisterDirect:
            if (typeOfOperand2 == RegisterDirect || typeOfOperand2 == RegisterIndirect) {
                if (operandNumber == 1) {
                    if (typeOfOperand1 == RegisterDirect) {
                        regCode.Source = strtol(operand1 + 1, NULL, 10);
                    } else {
                        regCode.Source = strtol(operand1 + 2, NULL, 10);
                    }
                    if (typeOfOperand2 == RegisterDirect) {
                        regCode.Destination = strtol(operand2 + 1, NULL, 10);
                    } else {
                        regCode.Destination = strtol(operand2 + 2, NULL, 10);
                    }


                    regCode.A = 1;
                    binary = *(int *) &regCode;
                    return binary;
                }
            }
            if (operandNumber == 1) {
                if (typeOfOperand1 == RegisterDirect) {
                    regCode.Source = strtol(operand1 + 1, NULL, 10);
                } else {
                    regCode.Source = strtol(operand1 + 2, NULL, 10);
                }
            } else {
                if (typeOfOperand1 == RegisterIndirect) {
                    regCode.Destination = strtol(operand1 + 1, NULL, 10);
                } else {
                    regCode.Destination = strtol(operand1 + 2, NULL, 10);
                }
            }
            regCode.A = 1;
            binary = *(int *) &regCode;
            return binary;
        default:
            break;
    }
    return 0;
}

int
buildCommandMachineBinary(char commandName[5], int opCode, int numberOfOperands, char operand1[30], char operand2[30]) {
    int typeOfOperand1, typeOfOperand2, binary;
    struct commandMachineCode code = {0};
    binary = 0;
    if (numberOfOperands == 2) {
        typeOfOperand1 = TypeOfOperand(operand1);
        typeOfOperand2 = TypeOfOperand(operand2);
        code.opcode = decimalToBinary(opCode);
        switch (typeOfOperand1) {
            case AddressImmediately:
                code.sourceAddressImmediately = 1;
                break;
            case AddressDirect:
                code.sourceAddressDirect = 1;
                break;
            case RegisterIndirect:
                code.sourceRegisterIndirect = 1;
                break;
            case RegisterDirect:
                code.sourceRegisterDirect = 1;
                break;
            default:
                break;
        }
        switch (typeOfOperand2) {
            case AddressImmediately:
                code.destinationAddressImmediately = 1;
                break;
            case AddressDirect:
                code.destinationAddressDirect = 1;
                break;
            case RegisterIndirect:
                code.destinationRegisterIndirect = 1;
                break;
            case RegisterDirect:
                code.destinationRegisterDirect = 1;
                break;
            default:
                break;
        }
        code.A = 1;
        binary = *(int *) &code;
        return binary;
    } else if (numberOfOperands == 1) {
        typeOfOperand1 = TypeOfOperand(operand1);
        code.opcode = decimalToBinary(opCode);
        switch (typeOfOperand1) {
            case AddressImmediately:
                code.sourceAddressImmediately = 1;
                break;
            case AddressDirect:
                code.sourceAddressDirect = 1;
                break;
            case RegisterIndirect:
                code.sourceRegisterIndirect = 1;
                break;
            case RegisterDirect:
                code.sourceRegisterDirect = 1;
                break;
            default:
                break;
        }
        code.A = 1;
        binary = *(int *) &code;
        return binary;
    } else {
        code.opcode = decimalToBinary(opCode);
        code.A = 1;
        binary = *(int *) &code;
        return binary;
    }
}

int TypeOfOperand(char *operand) {
    if (operand[0] == '#') {
        return AddressImmediately;
    } else if (operand[0] == 'r' && (operand[1] >= '0' && operand[1] <= '7')) {
        return RegisterDirect;
    } else if (operand[0] == '*')
        return RegisterIndirect;
    else if (checkLabel(operand) == TRUE)
        return AddressDirect;
    else
        return -1;
}







