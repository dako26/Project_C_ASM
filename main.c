#include "main.h"

int main(int argc, char *argv[]) {
    int i;
    char *fileName;
    if (argc < 2) {
        printf("no file added\n");
        return 1;
    }
    for (i = 1; i < argc; i++) {
         fileName = removeMacro(argv[i]);
         if (fileName == NULL){
             fprintf(stderr,"Error: in pre macro code\n");
             free(fileName);
             continue;
         }
         printf("%s",fileName);
         free(fileName);
    }
    return 0;
}
