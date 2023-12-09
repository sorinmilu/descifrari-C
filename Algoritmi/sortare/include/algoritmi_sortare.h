
#ifndef SORT_ALGOS_H
#define SORT_ALGOS_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>


void data_swap(void *data1, void *data2, size_t item_size);

void bubble_sort(int a[], int len);
void cocktail_sort(int a[], int len);
void insertion_sort(int a[], int len);
void quick_sort(int a[], int len);
void selection_sort(int a[], int len);
void heap_sort(int a[], int len);
void radix_sort(int a[], int len);
void shell_sort(int a[], int len);
void counting_sort(int a[], int len);
void bucket_sort(int a[], int len);
void merge_sort(int a[], int len);


#endif //SORT_ALGOS_H