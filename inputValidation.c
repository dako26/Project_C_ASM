//
// Created by dako6 on 20/06/2024.
//
#include "inputValidation.h"

int validateLine(char *line) {
    size_t size;
    char *temp;
    temp = line;

    while (isspace(temp[0]))
        temp++;
    if (temp[0] == ';') {
        return EmptyLine;
    }
    if (temp[0] == '\n') {
        return EmptyLine;
    }
    if (temp[0] == '.') {
        if (strncmp(temp, ".data", strlen(".data")) == 0) {
            if (checkData(temp) == FALSE) {
                return ErrorLine;
            }
            return DataLine;
        }
        if (strncmp(temp, ".string", strlen(".string")) == 0) {
            if (checkString(temp) == FALSE) {
                return ErrorLine;
            }
            return StringLine;
        }
        if (strncmp(temp, ".entry", strlen(".entry")) == 0) {
            if (checkEntryAndExtern(temp) == FALSE) {
                return ErrorLine;
            }
            return EntryLine;
        }
        if (strncmp(temp, ".extern", strlen(".extern")) == 0) {
            if (checkEntryAndExtern(temp) == FALSE) {
                return ErrorLine;
            }
            return ExternLine;
        }
    }
    sscanf(temp, "%s", temp);
    size = strlen(temp);
    if (temp[size - 1] == ':') {
        if (checkLabel(temp) == FALSE) {
            return ErrorLine;
        }
        temp =line + size;
        if(validateLine(temp)==ErrorLine)
            return ErrorLine;
        return LabelLine;
    }

}

int checkCommand(char *line) {
    char *temp;
    temp = line;
    while (isspace(temp[0]))
        temp++;
    if (strncmp(temp, "mov", strlen("mov")) == 0||strncmp(temp,"add",strlen("add"))==0||strncmp(temp,"sub",strlen("sub"))==0||strncmp(temp,"cmp",strlen("cmp"))==0) {
        
        return TRUE;
    }
    
}
int checkCommandIfTwoOperands(char *line){
    char *temp;
    int flagSecondOperand, i;
    flagSecondOperand = FALSE ;
    temp = line;
    while (isspace(temp[0]))
        temp++;
    temp+=3;
    if (temp[0] != ' ') {
        fprintf(stderr, "The command is missing a space in line %s\n",line);
        return FALSE;
    }
    removeSpaces(temp);
    for ( i = 0; i <1 ; i++) {
        if ((flagSecondOperand && strncmp(line, "cmp", strlen("cmp")) == 0)||!flagSecondOperand) {
            if (temp[0]=='#'){
                temp++;
                if (checkNumber(temp) == 1) {
                    temp = strtok(NULL, ",");
                    continue;
                }else{
                    fprintf(stderr, "Wrong first operand in line %s \n",line);
                    return FALSE;
                }

            }
        }

    }
};
int checkLabel(char *line) {
    char *instruction;
    instruction = line;
    while (isspace(instruction[0]))
        instruction++;
    while ((instruction[0] >= 'a' && instruction[0] <= 'z') || (instruction[0] >= 'A' && instruction[0] <= 'Z')||(instruction[0]>='0' && instruction[0] <= '9'))
        instruction++;
    if (instruction[0] != ':') {
        fprintf(stderr, "The label is missing a colon\n");
        return FALSE;
    }
    instruction++;
    if (instruction[0] != '\0') {
        fprintf(stderr, "The label has extra characters\n");
        return FALSE;
    }
    return TRUE;
}

int checkEntryAndExtern(char *line) {
    char *instruction;
    instruction = line;
    while (isspace(instruction[0]))
        instruction++;
    if (strncmp(line, ".entry", strlen(".entry")) == 0) {
        instruction += strlen(".entry");
    } else {
        instruction += strlen(".extern");
    }
    removeSpaces(instruction);
    if (strlen(instruction) == 0) {
        fprintf(stderr, "The entry/extern instruction is missing a label\n");
        return FALSE;
    }
    while ((instruction[0] >= 'a' && instruction[0] <= 'z') || (instruction[0] >= 'A' && instruction[0] <= 'Z') ||
           (instruction[0] >= '0' && instruction[0] <= '9'))
        instruction++;
    if (instruction[0] != '\0') {
        fprintf(stderr, "The entry/extern instruction has extra characters\n");
        return FALSE;
    }
    return TRUE;
}

int checkData(char *line) {
    char *instruction;
    char *temp;
    instruction = line;

    while (isspace(instruction[0]))
        instruction++;

    instruction += strlen(".data");
    if (instruction[0] != ' ') {
        fprintf(stderr, "The data instruction is missing a space\n");
        return FALSE;
    }

    if (instruction[0] == '\0') {
        fprintf(stderr, "The data instruction is missing a number\n");
        return FALSE;
    }

    removeSpaces(instruction);

    if (checkNumber(instruction) == FALSE)
        return FALSE;
    return TRUE;
}

int checkString(char *line) {
    char *instruction;
    instruction = line;
    while (isspace(instruction[0]))
        instruction++;
    instruction += strlen(".string");
    if (instruction[0] != ' ') {
        fprintf(stderr, "The string instruction is missing a space\n");
        return FALSE;
    }
    removeSpaces(instruction);
    if (instruction[0] != '"') {
        fprintf(stderr, "The string instruction is missing a quote\n");
        return FALSE;
    }
    while ((instruction[0] >= 'a' && instruction[0] <= 'z') || (instruction[0] >= 'A' && instruction[0] <= 'Z'))
        instruction++;
    if (instruction[0] != '"') {
        fprintf(stderr, "The string instruction is missing a quote\n");
        return FALSE;
    }
    instruction++;

    if (instruction[0] != '\0') {
        fprintf(stderr, "The string instruction has extra characters\n");
        return FALSE;
    }
    return TRUE;
}






