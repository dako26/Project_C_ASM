//
// Created by dako6 on 18/06/2024.
#include "util.h"

int checkNumber(char *number) {
    int i;
    if (number[0] == '-' || number[0] == '+') {
        i = 1;
    } else {
        i = 0;
    }
    for (;i < strlen(number); i++) {
        if (!isdigit(number[i])) {
            return FALSE;
        }
    }
    return TRUE;
}
void removeSpaces(char *str) {
    char *src, *dst;
    src = str;
    dst = str;
    while (*src != '\0'){
        if (!isspace(*src)){
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}
//
