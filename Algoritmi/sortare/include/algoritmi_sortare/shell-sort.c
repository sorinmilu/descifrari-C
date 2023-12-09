

void shell_sort(int arr[], int len) {
    // Start with a large gap and reduce it over multiple passes
    for (int gap = len / 2; gap > 0; gap /= 2) {
        // Perform gapped insertion sort for this gap size
        for (int i = gap; i < len; i++) {
            int temp = arr[i];
            int j;

            // Shift elements that are greater than temp to the right
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }

            // Place temp in its correct position
            arr[j] = temp;
        }
    }
}
