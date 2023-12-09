//
// Created by ismdeep on 2020/1/28.
//

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include <algoritmi_sortare.h>

#define ARR_SIZE 20000

void print_vector(int vector[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", vector[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

struct timeval *start_time() {
    struct timeval *tst = (struct timeval *) malloc(sizeof(struct timeval));
    gettimeofday(tst, NULL);
    return tst;
}

uint64_t stop_time(const struct timeval *tst) {
    struct timeval tstp;
    gettimeofday(&tstp, NULL);

    uint64_t timestamp1 = (uint64_t) tst->tv_sec * 1000000 + tst->tv_usec;
    uint64_t timestamp2 = (uint64_t) tstp.tv_sec * 1000000 + tstp.tv_usec;

    return timestamp2 - timestamp1;
}

void sort_test(
        int data[],
        int len,
        void (*sort_func)(int [], int),
        char *sort_func_name
) {
    /* Copy data from raw to selection_sort_data */
    int *sort_data = (int *) malloc(sizeof(int) * len );
    memcpy(sort_data, data, sizeof(int) * len);

    /* Sort array **sort_data** with **sort_func()** algorithm */
    struct timeval *start_point = start_time();
    sort_func(sort_data, len);

    float elapsed = stop_time(start_point) / 1000.0;


    printf("Sortare cu: [%s]: %.2lf ms\n", sort_func_name, elapsed);
    // print_vector(sort_data, len);

    free(sort_data);
    free(start_point);
}

int main() {
    srandom((unsigned) time(NULL));

    /* Generate raw_data[ARR_SIZE] */
    int raw_data[ARR_SIZE];
    for (int i = 0; i < ARR_SIZE; i++) {
        raw_data[i] = (int) (random() % 10000);
    }

    // print_vector(raw_data, ARR_SIZE);

    sort_test(raw_data, ARR_SIZE, selection_sort, "selection_sort");
    sort_test(raw_data, ARR_SIZE, bubble_sort   , "bubble_sort"   );
    sort_test(raw_data, ARR_SIZE, cocktail_sort , "cocktail_sort" );
    sort_test(raw_data, ARR_SIZE, insertion_sort, "insertion_sort");
    sort_test(raw_data, ARR_SIZE, quick_sort    , "quick_sort"    );
    sort_test(raw_data, ARR_SIZE, heap_sort     , "heap_sort"    );    
    sort_test(raw_data, ARR_SIZE, radix_sort    , "radix_sort"    );    
    sort_test(raw_data, ARR_SIZE, shell_sort    , "shell_sort"    );    
    sort_test(raw_data, ARR_SIZE, counting_sort , "counting_sort"    );      
    sort_test(raw_data, ARR_SIZE, bucket_sort   , "bucket_sort"    );     
    sort_test(raw_data, ARR_SIZE, merge_sort    , "merge_sort"    );   

    return 0;
}
