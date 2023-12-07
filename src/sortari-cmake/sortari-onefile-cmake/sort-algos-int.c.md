
```c
#include <stdlib.h>
#include <sys/time.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
```
```c
#define ARR_SIZE 20000
```

Declaram un nou tip de date numit cmp_int_func_t care reprezinta un pointer catre o functie care asteapta doua argumente, ambele fiind pointeri catre int

```c
typedef bool (*cmp_int_func_t) (const int*, const int*);
```

Functia cmp este o functie de comparare care va fi folosita pentru verificarea sortarii. Functiile de comparare sunt esentiale in sortare - acestea primesc doua elemente dintre cele care se vor sorta si le compara. Daca primul este mai mic decat al doilea si functia returneaza "true" atunci sortarea va fi in ordine crescatoare.  

```c
bool cmp(const int *a, const int *b) {
    return *a <= *b;
}
```

Urmatoarele doua functii reprezinta implementarea unui cronometru folosing structura timeval. Cu ajutorul acestor functii se poate masura timpul scurs intre doua puncte din cod.  

create_start_point aloca memorie pentru o structura de tip timeval utilizand malloc. Apoi, capteaza momentul de timp curent folosind functia gettimeofday() si il stocheaza in structura t, returnand t

```c
struct timeval *create_start_point() {
    struct timeval *t = (struct timeval *) malloc(sizeof(struct timeval));
    gettimeofday(t, NULL);
    return t;
}
```

Functia stop_watch_us primeste un pointer catre o structura de tip timeval (care reprezinta momentul initial al masurarii). Capteaza momentul curent in t2, obtine valorile ambelor momente in microsecunde si returneaza diferenta dintre ele. 

uint64_t este un tip de numere intregi definit in stdint.h care reprezinta un unsigned int pe 64 de biti, echivalent in cele mai multe cazuri cu un unsigned long long

```c
uint64_t stop_watch_us(const struct timeval *t1) {
    struct timeval t2;
    gettimeofday(&t2, NULL);


    uint64_t timestamp1 = (uint64_t) t1->tv_sec * 1000000 + t1->tv_usec;
    uint64_t timestamp2 = (uint64_t) t2.tv_sec * 1000000 + t2.tv_usec;

    return timestamp2 - timestamp1;
}
```
Schimba valorile a doua variabile intre ele


```c
/*schimba valoarea a doua variabile*/

void data_swap(void *data1, void *data2, size_t item_size) {
    void *tmp = malloc(item_size);
    memcpy(tmp, data1, item_size);
    memcpy(data1, data2, item_size);
    memcpy(data2, tmp, item_size);
    free(tmp);
}

```

Urmatoarele functii implementeaza algoritmi de sortare

```c
/* Functii care implementeaza algoritmi de sortare*/

/* Bubble sort */
void bubble_sort(int a[], int len) {
    for (int stop = len - 1; stop > 0; stop--) {
        for (int i = 0; i < stop; i++) {
            if (a[i] > a[i + 1]) {
                data_swap(a + i, a + i + 1, sizeof(int));
            }
        }
    }
}

/* Quick sort */
void quick_sort(int a[], int len) {
    if (len <= 1)
        return;
    int mid = a[len - 1];
    int left = 0;
    int right = len - 2;
    while (left < right) {
        while (a[left] <= mid && left < right)
            ++left;
        while ( a[right] > mid && left < right)
            --right;
        data_swap(a + left, a + right, sizeof(int));
    }
    if ( a[len - 1] < a[left] ) {
        data_swap(a + left, a + len - 1, sizeof(int));
    } else {
        ++left;
        data_swap(a + left, a + len - 1, sizeof(int));
    }
    if (left)
        quick_sort(a, left);
    quick_sort(a + left + 1, len - left - 1);
}

/* Cocktail sort */
void cocktail_sort(int a[], int len) {
    int i, left = 0, right = len - 1;
    int temp;
    while (left < right) {
        for (i = left; i < right; i++)
            if (a[i] > a[i + 1]) {
                temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
            }
        right--;
        for (i = right; i > left; i--)
            if (a[i - 1] > a[i]) {
                temp = a[i];
                a[i] = a[i - 1];
                a[i - 1] = temp;
            }
        left++;
    }
}

/* Insertion sort */
void insertion_sort(int a[], int len) {
    for (int left = 0; left < len; left++) {
        int min_p = left;
        for (int cur = min_p + 1; cur < len; cur++) {
            if ( a[cur] < a[min_p] ) {
                min_p = cur;
            }
        }
        int tmp = a[min_p];
        for (int cursor = min_p - 1; cursor >= left; cursor--) {
            a[cursor + 1] = a[cursor];
        }
        a[left] = tmp;
    }
}

/* Selection sort */
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


```

data_equal primeste doua pointere catre baza a doua blocuri de memorie (matrici) si un parametru dimensional de tip size_t (care este in realitate tot un unsigned long long). Functia va compara, octet cu octet, continutul celor doua blocuri de memorie si va returna false la identificarea primei diferente. 

Comparatia se face cu conditionalul: ` *((unsigned char *)data1 + i) != *((unsigned char *)data2 + i)` care foloseste aritmetica pointerilor pentru a se pozitiona pe al i-lea octet de la cele doua adrese de baza (data1 si data2). Astfel: 

- `(unsigned char *)data1` si `(unsigned char *)data2` modifica tipul de date ale pointerilor data1 si data2 astfel incat sa fie de tip unsigned char (operatiile urmatoare sa il mute octet cu octet)

- `(unsigned char *)data1 + i` si `(unsigned char *)data2 + i` inseamna adunarea lui i la pointerii de baza (acum de tip char) adica mutarea pointerilor cu i octeti mai la dreapta. 

- `*((unsigned char *)data1 + i)` si `*((unsigned char *)data2 + i)` inseamna dereferentiaza pointerul, obtinand valoarea octetilor de la adresele de memorie respective (data1 + i si data2 + i)

```c
/* Verifica daca doua blocuri de memorie sunt identice*/

bool data_equal(const void *data1, const void *data2, size_t item_size) {
    for (size_t i = 0; i < item_size; i++) {
        if ( *((unsigned char *)data1 + i) != *((unsigned char *)data2 + i) ) {
            return false;
        }
    }
    return true;
}
```


sorted_assert verifica daca o matrice este corect sortata. Argumentele sunt: 

- raw_data_start - pointer catre baza vectorului de date nesortate
- raw data end - pointer catre finalul vectorului de date nesortate
- sorted_data_start - pointer catre baza vectorului de date sortate
- sorted_data_end - pointer catre finalul vectorului de date sortate
- item_size - dimensiunea in octeti a datelor sortate (char, int, etc.)
- cmp_func - functia de sortare. 

In continuare functia va aloca un vector de date de tip boolean care are aceeasi dimensiune cu numarul de elemente din vectorul nesortat si se va asigura ca toate elementele acestuia sunt false: 

```c
size_t count = (raw_data_end - raw_data_start) / item_size;
bool *used = (bool *) malloc(sizeof(bool) * count);
for (int i = 0; i < count; i++) {
        used[i] = false;
}
```
urmatorul ciclu while verifica daca toate elementele din vectorul nesortat se regasesc in vectorul sortat. 

Ultima verificare preia perechi de elemente succesive din matricea sortata si verifica daca acestea corespund functiei de comparare utilizata. 

```c

bool sorted_assert(
        const void *raw_data_start, const void *raw_data_end,
        const void *sorted_data_start, const void *sorted_data_end,
        size_t item_size,
        cmp_func_t cmp_func) {

    size_t count = (raw_data_end - raw_data_start) / item_size;
    bool *used = (bool *) malloc(sizeof(bool) * count);
    void *cursor;

    /* Check if all raw_data are the same with sorted_data (no data loose, no data append) */
    for (int i = 0; i < count; i++) {
        used[i] = false;
    }
    cursor = (void *) sorted_data_start;
    while (cursor < sorted_data_end) {
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (!used[i] && data_equal(cursor, raw_data_start + i * item_size, item_size)) {
                used[i] = true;
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
        cursor += item_size;
    }

    /* Check if every pair of adjacent is satisfied  **cmp_func()** */
    cursor = (void *)sorted_data_start;
    cursor += item_size;
    while (cursor < sorted_data_end) {
        if (!cmp_func(cursor - item_size, cursor)) {
            return false;
        }
        cursor += item_size;
    }

    free(used);
    return true;
}

```

functia sort_test aplica un anumit algoritm de sortare asupra unui vector. Primeste urmatoarele argumente

- data[] - datele care trebuie sortate
- len - numarul de elemente din vector
- void (*sort_func)(int [], int), pointer catre functia de sortare 
- cmp_func_t cmp_func numele functiei de sortare

`int *sort_data = (int *) malloc(sizeof(int) * len );` aloca memorie pentru un nou vector, sort_data
`memcpy(sort_data, data, sizeof(int) * len);` copiaza tot ce se afla in data in noul vector, sort_data
`struct timeval *start_point = create_start_point();` creaza un punct de pornire al cronometrului
`sort_func(sort_data, len);` lanseaza functia de sortare 

Dupa executia functiei de sortare, se opreste cronometrul (`stop_watch_us(start_point)`) si se afiseaza rezultatele, impartite la 1000 (cronometrul opereaza cu microsecunde)

vectorii in aceasta functie (data si sort_data) sunt pointeri deci pot fi transmisi direct catre alte functii. Pentru a testa corectitudinea algoritmului de sortare, se apeleaza in continuare functia `sorted_assert(data, data + len, sort_data, sort_data + len, sizeof(int), cmp_func)` care returneaza false sau true. 

Dupa aceea se elibereaza memoria alocata manual in interiorul functiei (start point si sort_data)

```c

/*functie dispatch care aplica algoritmul de sortare ales*/

void sort_test(
        int data[],
        int len,
        void (*sort_func)(int [], int),
        char *sort_func_name,
        cmp_func_t cmp_func
) {
    /* Copy data from raw to selection_sort_data */
    int *sort_data = (int *) malloc(sizeof(int) * len );
    memcpy(sort_data, data, sizeof(int) * len);

    /* Sort array **sort_data** with **sort_func()** algorithm */
    struct timeval *start_point = create_start_point();
    sort_func(sort_data, len);
    printf("Time elapse[%s]: %.2lf ms\n", sort_func_name, stop_watch_us(start_point) / 1000.0);

    /* Assert sort result */
    if (sorted_assert(data, data + len, sort_data, sort_data + len, sizeof(int), cmp_func)) {
        printf("Successfully.\n\n");
    } else {
        printf("Unsuccessfully.\n\n");
    }

    free(sort_data);
    free(start_point);
}

```

Functia main a programului care genereaza un vector de ARR_SIZE cu elemente aleatoare iar apoi cheama succesiv functia sort_test folosind fiecare algoritm de sortare. 

Prin utilizarea numelor de functii fara paranteze si fara sa fie definite ca siruri de caractere (nu sunt puse intre ghilimele) ne asiguram ca functiile se transforma in pointeri.

```c

int main() {
    srandom((unsigned) time(NULL));

    /* Generate raw_data[ARR_SIZE] */
    int raw_data[ARR_SIZE];
    for (int i = 0; i < ARR_SIZE; i++) {
        raw_data[i] = (int) (random() % 1000);
    }

    sort_test(raw_data, ARR_SIZE, selection_sort, "selection_sort", (cmp_func_t) cmp);
    sort_test(raw_data, ARR_SIZE, bubble_sort   , "bubble_sort"   , (cmp_func_t) cmp);
    sort_test(raw_data, ARR_SIZE, cocktail_sort , "cocktail_sort" , (cmp_func_t) cmp);
    sort_test(raw_data, ARR_SIZE, insertion_sort, "insertion_sort", (cmp_func_t) cmp);
    sort_test(raw_data, ARR_SIZE, quick_sort    , "quick_sort"    , (cmp_func_t) cmp);

    return 0;
}
