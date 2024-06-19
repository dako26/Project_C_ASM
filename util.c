//
// Created by dako6 on 18/06/2024.
#include "util.h"

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
