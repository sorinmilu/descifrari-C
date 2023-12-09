#include <stdio.h>
#include <stdlib.h>

void counting_sort(int arr[], int len) {
    // Find the maximum value in the array
    int max = arr[0];
    for (int i = 1; i < len; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    // Create a count array to store the count of each element
    int* count = (int*)malloc((max + 1) * sizeof(int));
    if (count == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the count array to zeros
    for (int i = 0; i <= max; i++) {
        count[i] = 0;
    }

    // Count the occurrences of each element in the input array
    for (int i = 0; i < len; i++) {
        count[arr[i]]++;
    }

    // Update the count array to store the cumulative count
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    // Create an output array to store the sorted elements
    int* output = (int*)malloc(len * sizeof(int));
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(count);
        exit(EXIT_FAILURE);
    }

    // Build the output array using the count array
    for (int i = len - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // Copy the sorted elements back to the original array
    for (int i = 0; i < len; i++) {
        arr[i] = output[i];
    }

    // Free dynamically allocated memory
    free(count);
    free(output);
}
