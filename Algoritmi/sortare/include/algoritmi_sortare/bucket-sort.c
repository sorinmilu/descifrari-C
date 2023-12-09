#include <stdio.h>
#include <stdlib.h>

// Define a structure for a bucket (linked list)
struct Node {
    int data;
    struct Node* next;
};

void b_insertion_sort(struct Node** bucket) {
    // Perform insertion sort on the linked list (bucket)
    struct Node* current = *bucket;
    struct Node* sorted = NULL;

    while (current != NULL) {
        struct Node* next = current->next;

        // Insert current node into the sorted linked list
        if (sorted == NULL || sorted->data >= current->data) {
            current->next = sorted;
            sorted = current;
        } else {
            struct Node* temp = sorted;
            while (temp->next != NULL && temp->next->data < current->data) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    // Update the bucket with the sorted linked list
    *bucket = sorted;
}

void bucket_sort(int arr[], int len, int num_buckets) {
    // Create an array of buckets (linked lists)
    struct Node* buckets[num_buckets];
    for (int i = 0; i < num_buckets; i++) {
        buckets[i] = NULL;
    }

    // Distribute elements into buckets based on their value
    for (int i = 0; i < len; i++) {
        int bucket_index = arr[i] / num_buckets;
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        if (newNode == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        newNode->data = arr[i];
        newNode->next = buckets[bucket_index];
        buckets[bucket_index] = newNode;
    }

    // Sort each bucket using insertion sort
    for (int i = 0; i < num_buckets; i++) {
        b_insertion_sort(&buckets[i]);
    }

    // Concatenate the buckets to get the sorted array
    int index = 0;
    for (int i = 0; i < num_buckets; i++) {
        struct Node* current = buckets[i];
        while (current != NULL) {
            arr[index++] = current->data;
            struct Node* temp = current;
            current = current->next;
            free(temp); // Free the memory of the node
        }
    }
}
