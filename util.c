//
// Created by dako6 on 18/06/2024.
#include "util.h"

int checkNumber(char *number) {
    int  count, flagComma;
    count = 0;
    char *temp;
    temp = number;

    while (*temp != '\0') {
        removeSpaces(temp);
        if (temp[0] == '-'||temp[0]=='+') {
            temp++;
        }
        if (isdigit(temp[0]) == 0) {
            fprintf(stderr, "Error: invalid number\n");
            return FALSE;
        }

        while (isdigit(temp[0]) != 0) {
            flagComma = FALSE;
            temp++;
        }
        if (temp[0] == ',') {
            flagComma = TRUE;
            temp++;
        }
        if (temp[0] == '\0'  && flagComma == TRUE) {
            fprintf(stderr, "Error: invalid number\n");
            return FALSE;
        }
        if (temp[0] == ',' && flagComma == TRUE) {
            fprintf(stderr, "Error: invalid number\n");
            return FALSE;


        }
        count++;
    }

    return count;
}


void removeSpaces(char *str) {
    char *src, *dst;
    src = str;
    dst = str;
    while (*src != '\0') {
        if (!isspace(*src)) {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}

int numberOfWords(char *line) {
    int count;
    count = 0;
    while (*line != '\0') {
        if (isspace(*line)) {
            count++;
        }
        line++;
    }
    return count + 1;
}
int decimalToBinary(int num) {
    int binary, base, remainder;
    binary = 0;
    base = 1;
    while (num > 0) {
        remainder = num % 2;
        binary = binary + remainder * base;
        num = num / 2;
        base = base * 10;
    }
    return binary;
}
//
