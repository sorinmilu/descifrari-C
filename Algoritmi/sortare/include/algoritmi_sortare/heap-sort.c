#include <stdio.h>

void heapify(int a[], int len, int i) {
    int largest = i;       // Initialize largest as root
    int left = 2 * i + 1;  // Left child
    int right = 2 * i + 2; // Right child

    // If left child is larger than root
    if (left < len && a[left] > a[largest]) {
        largest = left;
    }

    // If right child is larger than largest so far
    if (right < len && a[right] > a[largest]) {
        largest = right;
    }

    // If largest is not root, swap and heapify the affected subtree
    if (largest != i) {
        int temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;

        // Recursively heapify the affected subtree
        heapify(a, len, largest);
    }
}

void build_heap(int a[], int len) {
    // Build heap (rearrange array)
    for (int i = len / 2 - 1; i >= 0; i--) {
        heapify(a, len, i);
    }
}

void heap_sort(int a[], int len) {
    // Build max heap
    build_heap(a, len);

    // Extract elements from the heap one by one
    for (int i = len - 1; i > 0; i--) {
        // Swap the root (maximum element) with the last element
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;

        // Heapify the reduced heap
        heapify(a, i, 0);
    }
}

