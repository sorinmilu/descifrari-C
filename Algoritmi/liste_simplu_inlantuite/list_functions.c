// list_functions.c

#include "list_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void createNewList(struct LinkedList* list, int numNodes) {
    // Seed the random number generator
    srand((unsigned int)time(NULL));

    // Create a new list with random nodes
    for (int i = 0; i < numNodes; i++) {
        addNode(list, rand() % 100); // Random data between 0 and 99
    }

    printf("%d nodes added to the list.\n", numNodes);
}

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void addNode(struct LinkedList* list, int data) {
    struct Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        struct Node* temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void deleteNode(struct LinkedList* list, int data) {
    struct Node* current = list->head;
    struct Node* previous = NULL;

    while (current != NULL && current->data != data) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Node with data %d not found\n", data);
        return;
    }

    if (previous == NULL) {
        // Node to be deleted is the head
        list->head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
}

struct Node* findNode(struct LinkedList* list, int data) {
    struct Node* current = list->head;

    while (current != NULL) {
        if (current->data == data) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

int countNodes(struct LinkedList* list) {
    struct Node* current = list->head;
    int count = 0;

    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

void printList(struct LinkedList* list) {
    struct Node* current = list->head;
    int index = 0;

    while (current != NULL) {
        printf("[%d]%d -> ", index, current->data);
        current = current->next;
        index++;
    }

    printf("NULL\n");
}

void freeList(struct LinkedList* list) {
    struct Node* current = list->head;
    struct Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
}

void addNodeAtBeginning(struct LinkedList* list, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = list->head;
    list->head = newNode;
}

void addNodeAfterIndex(struct LinkedList* list, int index, int data) {
    if (index < 0) {
        printf("Invalid index\n");
        return;
    }

    struct Node* newNode = createNode(data);

    if (index == 0) {
        // Insert at the beginning
        newNode->next = list->head;
        list->head = newNode;
        return;
    }

    struct Node* current = list->head;
    int i = 0;

    while (i < index - 1 && current != NULL) {
        current = current->next;
        i++;
    }

    if (current == NULL) {
        printf("Index out of bounds\n");
        free(newNode);
        return;
    }

    newNode->next = current->next;
    current->next = newNode;
}

void addMultipleNodes(struct LinkedList* list, int count, int data) {
    for (int i = 0; i < count; i++) {
        addNode(list, data);
    }
}

void deleteNodeByIndex(struct LinkedList* list, int index) {
    if (index < 0) {
        printf("Invalid index\n");
        return;
    }

    struct Node* current = list->head;
    struct Node* previous = NULL;
    int i = 0;

    while (i < index && current != NULL) {
        previous = current;
        current = current->next;
        i++;
    }

    if (current == NULL) {
        printf("Index out of bounds\n");
        return;
    }

    if (previous == NULL) {
        // Node to be deleted is the head
        list->head = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
}

void deleteAllNodesAfterIndex(struct LinkedList* list, int index) {
    if (index < 0) {
        printf("Invalid index\n");
        return;
    }

    struct Node* current = list->head;
    int i = 0;

    while (i < index && current != NULL) {
        current = current->next;
        i++;
    }

    if (current == NULL) {
        printf("Index out of bounds\n");
        return;
    }

    struct Node* next;
    while (current->next != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    current->next = NULL;
}

void reverseList(struct LinkedList* list) {
    struct Node* prev = NULL;
    struct Node* current = list->head;
    struct Node* next = NULL;

    while (current != NULL) {
        next = current->next;  // Save the next node
        current->next = prev;  // Reverse the pointer
        prev = current;        // Move to the next pair of nodes
        current = next;
    }

    list->head = prev;  // Update the head of the list
}

void printStatistics(struct LinkedList* list) {
    if (isListEmpty(list)) {
        printf("The list is empty. No statistics to display.\n");
        return;
    } 

    struct Node* current = list->head;
    int count = 0;
    int sum = 0;

    // Calculate the number of nodes and the sum of values
    while (current != NULL) {
        count++;
        sum += current->data;
        current = current->next;
    }

    // Calculate the average
    double average = (double)sum / count;

    // Print the statistics
    printf("Statistics:\n");
    printf("Number of nodes: %d\n", count);
    printf("Sum of values: %d\n", sum);
    printf("Average of values: %.2f\n", average);
}

int isListEmpty(struct LinkedList* list) {
    return list->head == NULL;
}

void sortList(struct LinkedList* list) {
    if (isListEmpty(list)) {
        printf("The list is empty. Nothing to sort.\n");
        return;
    }

    struct Node* current = list->head;
    struct Node* index = NULL;
    int temp;

    // Selection sort algorithm
    while (current != NULL) {
        index = current->next;

        while (index != NULL) {
            if (current->data > index->data) {
                temp = current->data;
                current->data = index->data;
                index->data = temp;
            }
            index = index->next;
        }
        current = current->next;
    }

    printf("List sorted in ascending order.\n");
}

void removeDuplicates(struct LinkedList* list) {
    if (isListEmpty(list)) {
        printf("The list is empty. No duplicates to remove.\n");
        return;
    }

    struct Node* current = list->head;
    struct Node* temp = NULL;

    while (current != NULL) {
        int currentValue = current->data;
        temp = current->next;
        struct Node* previous = current;

        while (temp != NULL) {
            if (temp->data == currentValue) {
                // Duplicate found, remove the node
                previous->next = temp->next;
                free(temp);
                temp = previous->next;
            } else {
                previous = temp;
                temp = temp->next;
            }
        }

        current = current->next;
    }

    printf("Duplicates removed from the list.\n");
}