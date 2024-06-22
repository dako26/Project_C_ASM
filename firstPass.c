//
// Created by dako6 on 18/06/2024.
//

#include "firstPass.h"

int firstPass(char *fileName) {
    int ic, dc, labelFlag,errorFlag;
    size_t labelSize;
    errorFlag = FALSE;
    char *temp;
    FILE *file;
    labelFlag = FALSE;
    ic = 0;
    dc = 0;
    char line[80];
    file = fopen(fileName, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: file not found\n");
        errorFlag = TRUE;
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
            labelFlag = TRUE;
            if (checkLabel(line) == FALSE) {
                errorFlag = TRUE;
            }
            labelSize = strlen(temp);
            temp = line + labelSize + 1;
            removeSpaces(temp);
            if (temp[0] == '.') {
                if (checkInstruction(temp) == FALSE) {
                    errorFlag = TRUE;
                }
                if (temp[1] == 'd'||temp[1]=='s') {

                    if (temp[1] == 'd') {
                        dc += checkNumber(temp);
                    }
                    if (temp[1] == 's') {
                        dc += numberOfWords(temp);
                    }

                }
            }

        }
    if (line[0] == '.') {
        if (checkInstruction(line) == FALSE) {
            errorFlag = TRUE;
        }
    }
}

}






