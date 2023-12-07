cmake_minimum_required(VERSION 3.10)
project(sort-algos C)
project(sort-algos-int C)
project(sort-algos-int-with-func C)

set(CMAKE_C_STANDARD 11)

include_directories("./include")

add_executable(sort-algos-int

        include/sort-algos-int/selection-sort-int.c
        include/sort-algos-int/bubble-sort-int.c
        include/sort-algos-int/insertion-sort-int.c
        include/sort-algos-int/quick-sort-int.c
        include/sort-algos-int/cocktail-sort-int.c
        include/sorted-assert.c
        include/data-swap.c
        include/sort-algos-int/sort-test.c
        include/time-utils.c
        include/sorting_algs.h
        sort-algos-int.c)

