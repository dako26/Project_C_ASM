//
// Created by dako6 on 18/06/2024.
//

#include "firstPass.h"

void firstPass(char *fileName){
    FILE *file;
    file = fopen(fileName, "r");
    if (file == NULL){
        fprintf(stderr,"Error: file not found\n");
        exit(1);
    }


}