//
// Created by dako6 on 29/06/2024.
//
#include "memory.h"

Memory *createMemory(int address, char *label, int binary) {
    Memory *memory = (Memory *) malloc(sizeof(Memory));
    if (memory == NULL) {
        fprintf(stderr, "Error allocating memory\n");
        return NULL;
    }

    memory->address = address;
    memory->label = label;
    memory->binary = binary;
    memory->next = NULL;

    return memory;
}

void addMemory(Memory **head, int address, char *label, int binary) {
    Memory *newMemory = createMemory(address, label, binary);
    if (newMemory == NULL) {
        return;
    }

    if (*head == NULL) {
        *head = newMemory;
    } else {
        Memory *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newMemory;
    }
}

        void freeMemory(Memory *memory) {
    if (memory != NULL) {
        free(memory->label);
        free(memory);
    }
}


