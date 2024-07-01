//
// Created by dako6 on 18/06/2024.
//

#include "firstPass.h"

int firstPass(char *fileName) {
    entryLabel *entryHead = NULL;
    externLabel *externHead = NULL;
    Memory *memoryHead = NULL;
    Label *labelHead = NULL;
    int labelFlag, lineFlag, errorFlag, tempDc, i;
    int num;
    size_t labelSize;
    char *temp;
    char *nameTemp;
    char *endptr;

    errorFlag = FALSE;
    FILE *file;
    labelFlag = FALSE;
    ic = 0;
    dc = 0;
    char line[90];
    file = fopen(fileName, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: file not found %s\n", fileName);
        return FALSE;
    }
    while (fgets(line, 90, file) != NULL) {
        labelFlag = FALSE;
        if (strlen(line) > 80) {
            fprintf(stderr, "Error: line exceeds 80 characters: %s\n", line);
            errorFlag = TRUE;
            continue;
        }
        temp = strdup(line); // Make a copy of the line for processing
        if (temp == NULL) {
            fprintf(stderr, "Error: memory allocation failed\n");
            errorFlag = TRUE;
            continue;
        }
        lineFlag = validateLine(temp);
        if (lineFlag == ErrorLine) {
            errorFlag = TRUE;
            continue;
        } else if (lineFlag == EmptyLine) {
            continue;
        } else if (lineFlag == CommentLine) {
            continue;
        } else if (lineFlag == LabelLine) {
            labelSize = strcspn(temp, ":");
            if (labelSize == strlen(temp) - 1) {
                fprintf(stderr, "Error: invalid label %s\n", line);
                errorFlag = TRUE;
                continue;
            }
            labelFlag = TRUE;
            tempDc = 0;
            if (validateLine(temp + labelSize + 1) == DataLine)
                tempDc = checkData(temp + labelSize + 1);
            else if (validateLine(temp + labelSize + 1) == StringLine)
                tempDc = checkString(temp + labelSize + 1);
            if (tempDc == 0) {
                addLabel(&labelHead, temp, ic + 100, tempDc, FALSE);
            } else {
                addLabel(&labelHead, temp, ic + 100, tempDc, TRUE);
            }
            temp = labelSize + 1 + temp;
        }
        if (lineFlag == EntryLine) {
            while (isspace(*temp)) {
                temp++;
            }
            temp += strlen(".entry");
            while (isspace(*temp)) {
                temp++;
            }
            addEntryLabel(&entryHead, temp, ic + 100);

        }
        if (lineFlag == ExternLine) {
            while (isspace(*temp)) {
                temp++;
            }
            temp += strlen(".extern");
            while (isspace(*temp)) {
                temp++;
            }
            addExternLabel(&externHead, temp, ic + 100);
        }
        if (lineFlag == DataLine) {
            tempDc = checkData(temp);
            if (tempDc == 0) {
                fprintf(stderr, "Error: invalid data line %s\n", line);
                errorFlag = TRUE;
                continue;
            }
            for (i = 0; i < tempDc; i++) {
                while (isspace(*temp)) {
                    temp++;
                }
                temp += strlen(".data");
                num = strtol(temp, &temp, 10);

                addMemory(&memoryHead, ic + 100, "NO", decimalToBinary((num)));
                ic++;
            }
            dc += tempDc;
        }
        if (lineFlag == StringLine) {
            tempDc = checkString(temp);
            if (tempDc == 0) {
                fprintf(stderr, "Error: invalid string line %s\n", line);
                errorFlag = TRUE;
                continue;
            }
            while (isspace(*temp)) {
                temp++;
            }
            temp += strlen(".string");
            for (i = 0; i < tempDc; i++) {
                num = (int) temp[i];
                addMemory(&memoryHead, ic + 100, "NO", decimalToBinary((num)));
                ic++;
            }
            dc += tempDc;
        }
        if (lineFlag == InstructionLine) {
            pressesLine(temp);
        }
        if (lineFlag ==ExternLine){
            while(isspace(temp[0]))
                temp++;
            temp+= strlen(".extern");
            sscanf(temp,"%s",nameTemp);
            addExternLabel(&externHead,nameTemp);
            continue;
        }
        if (lineFlag ==EntryLine) {
            while (isspace(temp[0]))
                temp++;
            temp+= strlen(".entry");
            sscanf(temp,"%s",nameTemp);
            addEntryLabel(&entryHead,nameTemp);
        }
        continue;


        free(temp);
    }
    if (errorFlag == TRUE)
        return FALSE;
    fclose(file);
    return TRUE;
}






