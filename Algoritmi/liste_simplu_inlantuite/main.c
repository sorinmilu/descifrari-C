// main.c

#include "list_functions.h"
#include <stdio.h>

// extern struct Node* head;

// Function to display the menu and get user input
char displayMenu(struct LinkedList* list) {
    char choice;
    printf("\nCurrent Linked List: ");
    printList(list);

    printf("\nMenu:\n");
    printf("A - Create new list\n");
    if (list->head != NULL) {
        printf("B - Add a node to the end of the list\n");
        printf("C - Add a node to the beginning of the list\n");
        printf("D - Add a node after a certain node index\n");
        printf("E - Add a given number of nodes\n");
        printf("F - Delete a node by index\n");
        printf("G - Delete all nodes after a certain node index\n");
        printf("H - Reverse the list\n");
        printf("I - Print statistics\n");
        printf("J - Sort the list\n");
        printf("K - Remove duplicates\n");
    }

    printf("Q - Quit\n");
    printf("Enter your choice: ");
    scanf(" %c", &choice);
    return choice;
}

int main() {
    char choice;
    struct LinkedList list = { .head = NULL };
    do {
        choice = displayMenu(&list);

        switch (choice) {
            case 'A':
            case 'a':
                {
                    int numNodes;
                    printf("Enter the number of nodes for the new list: ");
                    scanf("%d", &numNodes);
                    createNewList(&list, numNodes);
                }
                break;
            case 'B':
            case 'b':
                {
                    int data;
                    printf("Enter the data for the new node: ");
                    scanf("%d", &data);
                    addNode(&list, data);
                    printf("Node added to the end of the list.\n");
                }
                break;

            case 'C':
            case 'c':
                {
                    int data;
                    printf("Enter the data for the new node: ");
                    scanf("%d", &data);
                    addNodeAtBeginning(&list, data);
                    printf("Node added to the beginning of the list.\n");
                }
                break;

            case 'D':
            case 'd':
                {
                    int index, data;
                    printf("Enter the index after which to add the node: ");
                    scanf("%d", &index);
                    printf("Enter the data for the new node: ");
                    scanf("%d", &data);
                    addNodeAfterIndex(&list, index, data);
                    printf("Node added after index %d.\n", index);
                }
                break;

            case 'E':
            case 'e':
                {
                    int count;
                    printf("Enter the number of nodes to add: ");
                    scanf("%d", &count);

                    int data[count];  // Declare an array to store data values

                    printf("Enter the data for the new nodes separated by spaces: ");
                    for (int i = 0; i < count; i++) {
                        scanf("%d", &data[i]);
                    }

                    for (int i = 0; i < count; i++) {
                        addNode(&list, data[i]);
                    }

                    printf("%d nodes added to the list.\n", count);
                }
                break;

            case 'F':
            case 'f':
                {
                    int index;
                    printf("Enter the index of the node to delete: ");
                    scanf("%d", &index);
                    deleteNodeByIndex(&list, index);
                    printf("Node at index %d deleted.\n", index);
                }
                break;

            case 'G':
            case 'g':
                {
                    int index;
                    printf("Enter the index after which to delete all nodes: ");
                    scanf("%d", &index);
                    deleteAllNodesAfterIndex(&list, index);
                    printf("All nodes after index %d deleted.\n", index);
                }
                break;
            case 'H':
            case 'h':
                reverseList(&list);
                printf("List reversed.\n");
                break;
            case 'I':
            case 'i':
                printStatistics(&list);
                break;
            case 'J':
            case 'j':
                sortList(&list);
                break;
            case 'K':
            case 'k':
                removeDuplicates(&list);
                break;

            case 'Q':
            case 'q':
                printf("Quitting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 'Q' && choice != 'q');

    freeList(&list); // Free the memory

    return 0;
}
