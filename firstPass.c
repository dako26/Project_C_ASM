//
// Created by dako6 on 18/06/2024.
//

#include "firstPass.h"

int firstPass(char *fileName) {
    int ic, dc;
    char *temp;
    FILE *file;
    int flag;
    flag = FALSE;
    ic = 0;
    dc = 0;
    char line[80];
    file = fopen(fileName, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: file not found\n");
        return 0;
    }
    while (fgets(line, sizeof(line), file) != NULL) {
        if (line[0] == ';') {
            continue;
        }
        if (line[0] == '\n') {
            continue;
        }
        temp = strtok(line, ":");
        if (temp != NULL) {
            if (checkLabel(line) == FALSE) {
                return 0;
            }
        }
    }
    if (line[0] == '.') {
        if (checkInstruction(line) == FALSE) {
            return 0;
        }
    }
}

}

}

int checkLabel(char *line) {
    char *label;
    label = strtok(line, ":");
    if (label == NULL) {
        label = line;
    } else if (strlen(line) > 31) {
        fprintf(stderr, "The label is more the 31 characters\n");
        return FALSE;
    } else if ((label[0] < 'A' || label[0] > 'Z') || label[0] < 'a' || label[0] > 'z') {
        fprintf(stderr, "The label must start with a latin letters\n");
        return FALSE;
    } else if (strcmp(label, "data") == 0 || strcmp(label, "string") == 0 || strcmp(label, "entry") == 0 ||
               strcmp(label, "extern") == 0) {
        fprintf(stderr, "The label can't be a reserved word\n");
        return FALSE;
    } else if (strcmp(label, "r0") == 0 || strcmp(label, "r1") == 0 || strcmp(label, "r2") == 0 ||
               strcmp(label, "r3") == 0 || strcmp(label, "r4") == 0 || strcmp(label, "r5") == 0 ||
               strcmp(label, "r6") == 0 || strcmp(label, "r7") == 0) {
        fprintf(stderr, "The label can't be a register name\n");
        return FALSE;
    } else if (strcmp(label, "mov") == 0 || strcmp(label, "cmp") == 0 || strcmp(label, "add") == 0 ||
               strcmp(label, "sub") == 0 || strcmp(label, "lea") == 0 || strcmp(label, "clr") == 0 ||
               strcmp(label, "not") == 0 || strcmp(label, "inc") == 0 || strcmp(label, "dec") == 0 ||
               strcmp(label, "jmp") == 0 || strcmp(label, "bne") == 0 || strcmp(label, "red") == 0 ||
               strcmp(label, "prn") == 0 || strcmp(label, "jsr") == 0 || strcmp(label, "rts") == 0 ||
               strcmp(label, "stop") == 0) {
        fprintf(stderr, "The label can't be an instruction name\n");
        return FALSE;
    } else return TRUE;
    //TODO: check if the label == macro name in the macro table check if have in table of entry

}

checkInstruction(char *line) {
    char *instruction;
    char *temp;
    instruction = line;


    if (strncmp(line, ".data", strlen(".data"))==0){
        instruction += strlen(".data");
        removeSpaces(instruction);
        temp = strtok(instruction, ",");
        while (temp != NULL){
            removeSpaces(temp);
            if (checkNumber(temp) == FALSE){
                return FALSE;
            }
            instruction+= strlen(temp);
            temp = strtok(NULL, ",");
        }
        removeSpaces(instruction);
        if (checkNumber(instruction) == FALSE|| strlen(instruction) == 0){
            return FALSE;
        }
        return TRUE;

    }
    else if  (strncmp(line,".entry",strlen(".entry"))==0){
        instruction += strlen(".entry");
        removeSpaces(instruction);
        if (strlen(instruction) == 0){
            fprintf(stderr,"The entry instruction is missing a label\n");
            return FALSE;
        }
        if (checkLabel(instruction) == FALSE){
            return FALSE;
        }
        return TRUE;
    }
    else if (strncmp(line,".extern",strlen(".extern"))==0){
        instruction += strlen(".extern");
        removeSpaces(instruction);
        if (strlen(instruction) == 0){
            fprintf(stderr,"The extern instruction is missing a label\n");
            return FALSE;
        }
        if (checkLabel(instruction) == FALSE){
            return FALSE;
        }
        return TRUE;
    }
    else if (strncmp(line,".string",strlen(".string"))==0) {
        instruction += strlen(".string");
        removeSpaces(instruction);
        if (instruction[0] != '"') {
            fprintf(stderr, "The string instruction is missing a \"\n");
            return FALSE;
        }
        instruction++;
        while (instruction[0] != '"') {
            instruction++;
        }
        if (instruction[0] != '"') {
            fprintf(stderr, "The string instruction is missing a \"\n");
            return FALSE;
        }
        instruction++;
        if (instruction[0] != '\0') {
            fprintf(stderr, "The string instruction has extra characters\n");
            return FALSE;
        }
        return TRUE;
    }
    else if ((strncmp(line,".entry",strlen(".entry"))==0)||(strncmp(line,".extern",strlen(".extern"))==0)){
        if (strncmp(line,".entry",strlen(".entry"))==0)
            instruction+= strlen(".entry");
        else
            instruction += strlen(".extern");
        removeSpaces(instruction);
        if (checkLabel(instruction)==FALSE){
            fprintf(stderr,"The label is not valid\n");
            return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}


