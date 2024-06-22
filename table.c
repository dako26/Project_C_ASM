//
// Created by dako6 on 21/06/2024.
//
#include "table.h"
MacroNames *createMacroNameNode(const char *name) {
    // Allocate memory for the MacroNames structure
    MacroNames *newNode = (MacroNames *) malloc(sizeof(MacroNames));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Allocate memory for the name string and copy 'name' into it
    newNode->name = (char *) malloc(strlen(name) + 1);
    if (newNode->name == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(newNode); // Clean up if allocation fails
        return NULL;
    }

    // Copy the contents of 'name' into newNode->name
    strcpy(newNode->name, name);

    newNode->next = NULL; // Initialize next pointer to NULL
    return newNode;
}


void freeMacroNameNode(MacroNames *node) {
    if (node != NULL) {
        free(node->name);
        free(node);
    }
}
void addMacroName(MacroNames **head, const char *name) {
    // Create a new node
    MacroNames *newNode = (MacroNames *) malloc(sizeof(MacroNames));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    // Allocate memory for the name string and copy 'name' into it
    newNode->name = (char *) malloc(strlen(name) + 1);
    if (newNode->name == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(newNode);
        return;
    }
    strcpy(newNode->name, name);

    // Initialize next pointer
    newNode->next = NULL;

    // If the list is empty, make the new node as the head
    if (*head == NULL) {
        *head = newNode;
    } else {
        // Traverse to the end of the list and append the new node
        MacroNames *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}
int isMacroNameExists(MacroNames *head, const char *name) {
    MacroNames *current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return TRUE; // Name exists
        }
        current = current->next;
    }
    return FALSE; // Name does not exist
}
