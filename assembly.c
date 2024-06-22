//
// Created by dako6 on 21/06/2024.
//

#include "assembly.h"

addressMachineCode *createAddressMachineCodeNode(int address, char machineCode) {
    // Allocate memory for the addressMachineCode structure
    addressMachineCode *newNode = (addressMachineCode *) malloc(sizeof(addressMachineCode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    newNode->address = address;
    newNode->machineCode = machineCode;
    newNode->next = NULL; // Initialize next pointer to NULL
    return newNode;
}
void addAddressMachineCodeNode(addressMachineCode **head, int *currentAddress, char machineCode) {
    addressMachineCode *newNode = createAddressMachineCodeNode(*currentAddress, machineCode);
    if (newNode == NULL) {
        return; // Memory allocation failed
    }

    (*currentAddress)++; // Increment the address for the next node

    // If the list is empty, make the new node the head
    if (*head == NULL) {
        *head = newNode;
    } else {
        // Traverse to the end of the list and append the new node
        addressMachineCode *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}
void freeAddressMachineCodeList(addressMachineCode *head) {
    addressMachineCode *current = head;
    addressMachineCode *temp;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
}
void printAddressMachineCodeList(addressMachineCode *head) {
    addressMachineCode *current = head;
    while (current != NULL) {
        printf("%d %c\n", current->address, current->machineCode);
        current = current->next;
    }
}






