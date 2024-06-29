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
        return CommentLine;
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
    if (checkCommand(temp) == TRUE) {
        return InstructionLine;
    }
    sscanf(temp, "%s", temp);
    size = strlen(temp);
    if (temp[size - 1] == ':') {
        if (checkLabel(temp) == FALSE) {
            return ErrorLine;
        }
        temp = line;
        while(isspace(temp[0]))
            temp++;
        temp += size;
        if (temp[0] == '\0') {
            return LabelLine;
        }
        return (validateLine(temp) == ErrorLine) ? ErrorLine : LabelLine;
    }
    fprintf(stderr, "Error: invalid line %s\n" , line);
    return ErrorLine;
}

int checkCommand(char *line) {
    char *temp;
    temp = line;

    while (isspace(temp[0]))
        temp++;
    if (strncmp(temp, "mov", strlen("mov")) == 0 || strncmp(temp, "cmp", strlen("cmp")) == 0 ||
        strncmp(temp, "add", strlen("add")) == 0 || strncmp(temp, "sub", strlen("sub")) == 0) {
        if (checkCommandIfTwoOperands(line) == FALSE) {
            return FALSE;
        }
        return TRUE;
    }
    if (strncmp(temp, "clr", strlen("clr")) == 0 || strncmp(temp, "not", strlen("not")) == 0 ||
        strncmp(temp, "inc", strlen("inc")) == 0 || strncmp(temp, "dec", strlen("dec")) == 0 ||
        strncmp(temp, "jmp", strlen("jmp")) == 0 ||
        strncmp(temp, "bne", strlen("bne")) == 0 || strncmp(temp, "red", strlen("red")) == 0 ||
        strncmp(temp, "prn", strlen("prn")) == 0 || strncmp(temp, "jsr", strlen("jsr")) == 0) {
        if (checkCommandIfOneOperand(line) == FALSE) {
            return FALSE;
        }
        return TRUE;
    }
    if (strncmp(temp, "rts", strlen("rts")) == 0 || strncmp(temp, "stop", strlen("stop")) == 0) {
        if (checkCommandIfZeroOperand(line) == FALSE) {
            return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}

int checkCommandIfTwoOperands(char *line) {
    char *temp;
    int flagSecondOperand, i;
    flagSecondOperand = FALSE;
    temp = line;
    while (isspace(line[0]))
        line++;
    while (isspace(temp[0]))
        temp++;
    temp += 3;
    if (temp[0] != ' ') {
        fprintf(stderr, "The command is missing a space in line %s\n", line);
        return FALSE;
    }
    for (i = 0; i < 1; i++) {
        while (isspace(temp[0]))
            temp++;
        if (!flagSecondOperand && strncmp(line, "lea", strlen("lea")) == 0) {
            temp += 3;
            while (isspace(temp[0]))
                temp++;
            if (temp[0] >= 'a' || temp[0] <= 'z' || temp[0] >= 'A' || temp[0] <= 'Z') {
                temp++;
                while ((temp[0] >= 'a' && temp[0] <= 'z') || (temp[0] >= 'A' && temp[0] <= 'Z') ||
                       (temp[0] >= '0' && temp[0] <= '9'))
                    temp++;
                while (isspace(temp[0]))
                    temp++;
                if (temp[0] != ',') {
                    fprintf(stderr, "The command is missing a comma in line %s\n", line);
                    return FALSE;
                }
                temp = strtok(NULL, ",");
                if (temp == NULL) {
                    fprintf(stderr, "The command is missing a second operand in line %s\n", line);
                    return FALSE;
                }
                flagSecondOperand = TRUE;
                continue;
            } else {
                fprintf(stderr, "Wrong operand in line %s \n", line);
                return FALSE;
            }
        }
        if ((flagSecondOperand && strncmp(line, "cmp", strlen("cmp")) == 0) || !flagSecondOperand) {
            if (temp[0] == '#') {
                temp++;
                if (temp[0] == '-' || temp[0] == '+' || isdigit(temp[0]) == 0) {
                    temp++;
                    while (isdigit(temp[0]) == 0)
                        temp++;
                    while (isspace(temp[0]))
                        temp++;
                    if (temp[0] != ',' && flagSecondOperand == FALSE) {
                        fprintf(stderr, "The command is missing a comma in line %s\n", line);
                        return FALSE;
                    }
                    if (flagSecondOperand == FALSE) {
                        temp = strtok(NULL, ",");
                        if (temp == NULL) {
                            fprintf(stderr, "The command is missing a second operand in line %s\n", line);
                            return FALSE;
                        }
                    }
                    flagSecondOperand = TRUE;
                    continue;
                } else {
                    fprintf(stderr, "Wrong operand in line %s \n", line);
                    return FALSE;
                }
            }
        }
        if ((temp[0] >= 'a') && (temp[0] <= 'z') || (temp[0] >= 'A') && (temp[0] <= 'Z')) {
            temp++;
            while ((temp[0] >= 'a') && (temp[0] <= 'z') || (temp[0] >= 'A') && (temp[0] <= 'Z') ||
                   (temp[0] >= '0' && temp[0] <= '9'))
                temp++;
            while (isspace(temp[0]))
                temp++;
            if (temp[0] != ',' && flagSecondOperand == FALSE) {
                fprintf(stderr, "The command is missing a comma in line %s\n", line);
                return FALSE;
            }
            if (flagSecondOperand == FALSE) {
                temp = strtok(NULL, ",");
                if (temp == NULL) {
                    fprintf(stderr, "The command is missing a second operand in line %s\n", line);
                    return FALSE;
                }
            }
            flagSecondOperand = TRUE;
            continue;
        }

        if (temp[0] == '*')
            temp++;
        if (temp[0] == 'r' && (temp[1] >= '0' && temp[1] <= '7')) {
            temp += 2;
            while (isspace(temp[0]))
                temp++;
            if (temp[0] != ',' && flagSecondOperand == FALSE) {
                fprintf(stderr, "The command is missing a comma in line %s\n", line);
                return FALSE;
            }
            if (flagSecondOperand == FALSE) {
                temp = (strtok(NULL, ","));
                if (temp == NULL) {
                    fprintf(stderr, "The command is missing a second operand in line %s\n", line);
                    return FALSE;
                }
            }
            flagSecondOperand = TRUE;
            continue;
        }
        fprintf(stderr, "Wrong operand in line %s \n", line);
        return FALSE;
    }
    if (temp[0] != '\0') {
        fprintf(stderr, "The command has extra characters in line %s\n", line);
        return FALSE;
    }
    return TRUE;
}

int checkCommandIfOneOperand(char *line) {
    char *temp;
    int count;
    temp = line;
    while (isspace(line[0]))
        line++;
    while (isspace(temp[0]))
        temp++;
    temp += 3;
    if (temp[0] != ' ') {
        fprintf(stderr, "The command is missing a space in line %s\n", line);
        return FALSE;
    }
    while (isspace(temp[0]))
        temp++;
    if (strncmp(line, "prn", strlen("prn")) == 0 && temp[0] == '#') {
        if (temp[0] == '#') {
            temp++;
            if (temp[0] == '-' || temp[0] == '+' || isdigit(temp[0]) == 0) {
                temp++;
                while (isdigit(temp[0]) == 0) {
                    temp++;
                }
                if (temp[0] != '\0') {
                    fprintf(stderr, "The command has extra characters in line %s\n", line);
                    return FALSE;
                }
            } else {
                fprintf(stderr, "Wrong operand in line %s \n", line);
                return FALSE;
            }
            return TRUE;

        }
    }
    if ((strncmp(line, "prn", strlen("prn")) == 0 || strncmp(line, "clr", strlen("clr")) == 0 ||
         strncmp(line, "not", strlen("not")) == 0 || strncmp(line, "inc", strlen("inc")) == 0 ||
         strncmp(line, "dec", strlen("dec")) == 0) && (temp[0] == 'r' && (temp[1] >= '0' && temp[1] <= '7'))) {
        temp + 2;
        while (isspace(temp[0]))
            temp++;
        if (temp[0] != '\0') {
            fprintf(stderr, "The command has extra characters in line %s\n", line);
            return FALSE;
        }
        return TRUE;
    }
    if (temp[0] == '#') {
        temp++;
        if (temp[0] == '-' || temp[0] == '+' || isdigit(temp[0]) == 0) {
            temp++;
            while (isdigit(temp[0]) == 0)
                temp++;
            while (isspace(temp[0]))
                temp++;
            if (temp[0] != '\0') {
                fprintf(stderr, "The command has extra characters in line %s\n", line);
                return FALSE;
            }
            return TRUE;
        } else {
            fprintf(stderr, "Wrong operand in line %s \n", line);
            return FALSE;
        }
    }
    if (temp[0] == '*') {
        temp++;
        if (temp[0] == 'r' && (temp[1] >= '0' && temp[1] <= '7')) {
            temp += 2;
            while (isspace(temp[0]))
                temp++;
            if (temp[0] != '\0') {
                fprintf(stderr, "The command has extra characters in line %s\n", line);
                return FALSE;
            }
            return TRUE;

        }
    }
    if ((temp[0] >= 'a' && temp[0] <= 'z') || (temp[0] >= 'A' && temp[0] <= 'Z')) {
        if (strlen(temp) > 31) {
            fprintf(stderr, "The label is too long\n");
            return FALSE;
        }
        temp++;
        while ((temp[0] >= 'a' && temp[0] <= 'z') || (temp[0] >= 'A' && temp[0] <= 'Z') ||
               (temp[0] >= '0' && temp[0] <= '9'))
            temp++;
        while (isspace(temp[0]))
            temp++;
        if (temp[0] != '\0') {
            fprintf(stderr, "The command has extra characters in line %s\n", line);
            return FALSE;
        }
        return TRUE;
    }
    fprintf(stderr, "Wrong operand in line %s \n", line);
    return FALSE;
}

int checkCommandIfZeroOperand(char *line) {
    char *temp;
    temp = line;
    while (isspace(temp[0]))
        temp++;
    while (isspace(line[0]))
        line++;
    if (strncmp(temp, "rts", strlen("rts")) == 0) {
        temp += 3;
        while (isspace(temp[0]))
            temp++;
        if (temp[0] != '\0') {
            fprintf(stderr, "The command has extra characters in line %s\n", line);
            return FALSE;
        }
        return TRUE;
    }
    if (strncmp(temp, "stop", strlen("stop")) == 0) {
        temp += 4;
        while (isspace(temp[0]))
            temp++;
        if (temp[0] != '\0') {
            fprintf(stderr, "The command has extra characters in line %s\n", line);
            return FALSE;
        }
        return TRUE;
    }
    fprintf(stderr, "Wrong operand in line %s \n", line);
    return FALSE;
}

int checkLabel(char *line) {
    char *instruction;
    instruction = line;
    if (strlen(instruction) > 31) {
        fprintf(stderr, "The label is too long\n");
        return FALSE;
    }
    if ((instruction[0] >= 'a' && instruction[0] <= 'z') || (instruction[0] >= 'A' && instruction[0] <= 'Z')) {
        fprintf(stderr, "The label must start with a letter\n");
        return FALSE;
    }
    while (isspace(instruction[0]))
        instruction++;
    while ((instruction[0] >= 'a' && instruction[0] <= 'z') ||
           (instruction[0] >= 'A' && instruction[0] <= 'Z') ||
           (instruction[0] >= '0' && instruction[0] <= '9'))
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
    while ((instruction[0] >= 'a' && instruction[0] <= 'z') ||
           (instruction[0] >= 'A' && instruction[0] <= 'Z') ||
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






