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

void freeLabelNode(Label *node) {
    if (node != NULL) {
        free(node->name);
        free(node);
    }
}
void addLabel(Label **head, const char *name, int ic, int dc, int isData) {
    // Create a new node
    if (isLabelExists(*head, name)) {
        fprintf(stderr, "Error: label %s already exists\n", name);
        return;
    }
    Label *newNode = (Label *) malloc(sizeof(Label));
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

    // Initialize ic, dc, isData
    newNode->ic = ic;
    newNode->dc = dc;
    newNode->isData = isData;

    // Initialize next pointer
    newNode->next = NULL;

    // If the list is empty, make the new node as the head
    if (*head == NULL) {
        *head = newNode;
    } else {
        // Traverse to the end of the list and append the new node
        Label *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}
int isLabelExists(Label *head, const char *name) {
    Label *current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return TRUE; // Label exists
        }
        current = current->next;
    }
    return FALSE; // Label does not exist
}

externLabel *createExternLabelNode(const char *name, int address) {
    // Allocate memory for the externLabel structure
    externLabel *newNode = (externLabel *) malloc(sizeof(externLabel));
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

    newNode->address = address;
    newNode->next = NULL; // Initialize next pointer to NULL
    return newNode;
}
void freeExternLabelNode(externLabel *node) {
    if (node != NULL) {
        free(node->name);
        free(node);
    }
}
void addExternLabel(externLabel **head, const char *name, int address) {
    // Create a new node
    externLabel *newNode = (externLabel *) malloc(sizeof(externLabel));
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

    newNode->address = address;

    // Initialize next pointer
    newNode->next = NULL;

    // If the list is empty, make the new node as the head
    if (*head == NULL) {
        *head = newNode;
    } else {
        // Traverse to the end of the list and append the new node
        externLabel *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}
int isExternLabelExists(externLabel *head, const char *name) {
    externLabel *current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return TRUE; // Name exists
        }
        current = current->next;
    }
    return FALSE; // Name does not exist
}
entryLabel *createEntryLabelNode(const char *name, int address) {
    // Allocate memory for the entryLabel structure
    entryLabel *newNode = (entryLabel *) malloc(sizeof(entryLabel));
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

    newNode->address = address;
    newNode->next = NULL; // Initialize next pointer to NULL
    return newNode;
}
void freeEntryLabelNode(entryLabel *node) {
    if (node != NULL) {
        free(node->name);
        free(node);
    }
}
void addEntryLabel(entryLabel **head, const char *name, int address) {
    // Create a new node
    entryLabel *newNode = (entryLabel *) malloc(sizeof(entryLabel));
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

    newNode->address = address;

    // Initialize next pointer
    newNode->next = NULL;

    // If the list is empty, make the new node as the head
    if (*head == NULL) {
        *head = newNode;
    } else {
        // Traverse to the end of the list and append the new node
        entryLabel *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}
int isEntryLabelExists(entryLabel *head, const char *name) {
    entryLabel *current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return TRUE; // Name exists
        }
        current = current->next;
    }
    return FALSE; // Name does not exist
}



