#include <stdio.h>
#include <stdlib.h>

// Utility function to find the maximum value in an array
int find_max(int arr[], int len) {
    int max = arr[0];
    for (int i = 1; i < len; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// A utility function to do counting sort of arr[] based on the digit represented by exp.
void r_counting_sort(int arr[], int len, int exp) {
    const int BASE = 10;

    // Dynamically allocate memory for count array
    int *count = (int *)malloc(BASE * sizeof(int));
    if (count == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Initialize count array
    for (int i = 0; i < BASE; i++) {
        count[i] = 0;
    }

    // Store count of occurrences in count[]
    for (int i = 0; i < len; i++) {
        count[(arr[i] / exp) % BASE]++;
    }

    // Change count[i] so that count[i] now contains actual position of this digit in output[]
    for (int i = 1; i < BASE; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    int *output = (int *)malloc(len * sizeof(int));
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(count);
        exit(EXIT_FAILURE);
    }

    for (int i = len - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % BASE] - 1] = arr[i];
        count[(arr[i] / exp) % BASE]--;
    }

    // Copy the output array to arr[]
    for (int i = 0; i < len; i++) {
        arr[i] = output[i];
    }

    // Free dynamically allocated memory
    free(output);
    free(count);
}

// The main function to implement radix sort
void radix_sort(int arr[], int len) {
    // Find the maximum number to know the number of digits
    int max = find_max(arr, len);

    // Do counting sort for every digit
    for (int exp = 1; max / exp > 0; exp *= 10) {
        r_counting_sort(arr, len, exp);
    }
}


