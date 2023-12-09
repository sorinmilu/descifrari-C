
#include <algoritmi_sortare.h>

void selection_sort(int a[], int len) {
    for (int left = 0; left < len; left++) {
        int min_p = left;
        for (int cur = left + 1; cur < len; cur++) {
            if ( a[cur] < a[min_p] ) {
                min_p = cur;
            }
        }
        int tmp = a[min_p];
        a[min_p] = a[left];
        a[left] = tmp;
    }
}