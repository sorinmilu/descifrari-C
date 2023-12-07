
#ifndef SORT_ALGOS_H
#define SORT_ALGOS_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>


struct timeval *create_start_point();

uint64_t stop_watch_us(const struct timeval *t1);

void bubble_sort(int a[], int len);
void cocktail_sort(int a[], int len);
void insertion_sort(int a[], int len);
void quick_sort(int a[], int len);
void selection_sort(int a[], int len);


typedef void (*sort_func_t)(void*, void*, size_t, bool (*)(const void*, const void*));

typedef void (*sort_int_func_t)(int[], int, bool (*)(const int*, const int*));

typedef bool (*cmp_func_t) (const void*, const void*);

typedef bool (*cmp_int_func_t) (const int*, const int*);


void sort_test(
        int a[],
        int len,
        void (*sort_func)(int [], int),
        char *sort_func_name,
        cmp_func_t cmp_func
);

void data_swap(void *data1, void *data2, size_t item_size);

bool sorted_assert(
        const void *raw_data_start, const void *raw_data_end,
        const void *sorted_data_start, const void *sorted_data_end,
        size_t item_size,
        cmp_func_t cmp_func);

#endif //SORT_ALGOS_H