# Sort Algos in C
Sorting Algorithms General Implementations in C Programming Language


- `sort-algos-int.c` is the most naive version. Every C programming language beginner could understand it.
- `sort-algos-int-with-func.c` is the more advanced version based on `sort-algos-int.c`. In this sort of sorting algorithms, we implement the sorting algorithms with `cmp_func` to define the sorting rules.
- `sort-algos.c` is the most general version to sort any kind of data type with any kind of sorting rules. For more information or usage of the most general version of sorting algorithms, you may find it in `sort-algos/sort-test.c`



---

Tested Platform:

- macOS 10.15
- Ubuntu

# Comentarii

## Prezentare generala

[https://github.com/ismdeep/sort-algos-c](https://github.com/ismdeep/sort-algos-c)

Proiectul foloseste sistemul de constructie Cmake. Compilarea va produce trei fisiere executabile (sort-algos  sort-algos-int  sort-algos-int-with-func) care implementeaza urmatorii algoritmi de sortare: 

### selection sort

Selection Sort împarte lista de elemente în două părți: o parte sortată (care la inceput este reprezentata de intregul vector) și o parte nesortată (care la inceput este goala). Algoritmul este: 

1. Găsirea cel mai mic (sau cel mai mare, în funcție de direcția sortării) element din partea nesortată
2. Schimbarea acestuia cu primul element din partea nesortată. 
3. Incrementarea contorului care permite separarea partii sortate de partea nesortata. 

Procesul se repetă până când toate elementele sunt sortate.

### bubble sort

Bubble Sort este un alt algoritm simplu de sortare care compară repetitiv perechi de elemente adiacente și le schimbă pozițiile dacă nu sunt în ordine. Procesul continuă până când niciun element nu mai trebuie schimbat, ceea ce indică că lista este sortată.

### cocktail sort

Cocktail Sort, cunoscut și sub denumirea de Shaker Sort, este o variantă a Bubble Sort care încearcă să îmbunătățească performanța acestuia prin sortarea în ambele direcții. Acesta îmbunătățește Bubble Sort prin adăugarea unei faze inverse, în care se parcurge lista de la sfârșit către început, pentru a plasa cel mai mic și cel mai mare element la pozițiile lor corecte într-un singur pas. 

### insertion sort

Insertion Sort este un alt algoritm care împarte lista inițială în două părți: o parte sortată și o parte nesortată. Algoritmul alege un element din partea nesortată și îl inserează la locul potrivit în partea sortată, extinzând astfel lista sortată. 

### quick_sort

Quick sort este un algoritm care imparte recursiv vectorul in doua parti, sortand acele parti. Impartirea se face prin alegerea unui element din vector numnit pivot si separarea tuturor elementelor mai mici decat pivotul intr-o lista si a celor mai mari in alta lista. Vectorul se recombina la final. 

## Cod

Proiectul are trei implementari distincte ale fiecaruia din cei 5 algoritmi. Fiecare functie este implementata intr-un fisier c separat iar fiecare fisier c separat are propriul fisier h. Fisierele .h au in debut [include guards](https://en.wikipedia.org/wiki/Include_guard) - constructii care permit includerea lor in mai multe fisiere .h fara consecinte (definitii duble, etc.). 

```
#ifndef SORT_ALGOS_C_TIME_UTILS_H
#define SORT_ALGOS_C_TIME_UTILS_H

// include content

#endif //SORT_ALGOS_C_TIME_UTILS_H
```

### Cod comun

Cateva functii sunt utilizate in multe functii de sortare sau comparare: 

#### time-utils.h

Functie care porneste/opreste un cronometru pentru masurarea timpului scurs intr-o anumita operatie de sortare

```
struct timeval *create_start_point();
uint64_t stop_watch_us(const struct timeval *t1);
```

#### sorted-assert.h

Functie care verifica daca un vector este sortat

```
bool sorted_assert(
        const void *raw_data_start, const void *raw_data_end,
        const void *sorted_data_start, const void *sorted_data_end,
        size_t item_size,
        cmp_func_t cmp_func);
```

#### data-swap.h

Functie care schimba intre ele valorile a doua variabile

```
void data_swap(void *data1, void *data2, size_t item_size);
```

#### sort-base.h

sort-base.h nu defineste functii ci o serie de structuri care sunt folosite in program

```
typedef void (*sort_func_t)(void*, void*, size_t, bool (*)(const void*, const void*));
typedef void (*sort_int_func_t)(int[], int, bool (*)(const int*, const int*));
typedef bool (*cmp_func_t) (const void*, const void*);
typedef bool (*cmp_int_func_t) (const int*, const int*);
```

### Sort test

Toate functiile de sortare sunt apelate prin intermediul unei functii principale numita sort_test. Aceasta functie (desi se numeste la fel) este diferita in cele trei programe: 

sort-algos.c

```
sort_test(raw_data, raw_data + ARR_SIZE, sizeof(double), selection_sort, "selection_sort", (cmp_func_t) cmp);
```
sort-algos-int.c

```
sort_test(raw_data, ARR_SIZE, selection_sort, "selection_sort", (cmp_func_t) cmp);
```

sort-algos-int-with-func.c

```
sort_test(raw_data, ARR_SIZE, selection_sort, "selection_sort", cmp);
```
