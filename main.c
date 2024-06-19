#include "main.h"

int main(int argc, char *argv[]) {
    int i;
    if (argc < 2) {
        printf("no file added\n");
        return 1;
    }
    for (i = 1; i < argc; i++) {
        removeMacro(argv[i]);

    }

    return 0;
}
