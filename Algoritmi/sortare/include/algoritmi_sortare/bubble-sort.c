
#include <algoritmi_sortare.h>



void bubble_sort(int a[], int len) {
    for (int stop = len - 1; stop > 0; stop--) {
        for (int i = 0; i < stop; i++) {
            if (a[i] > a[i + 1]) {
                data_swap(a + i, a + i + 1, sizeof(int));
            }
        }
    }
}

