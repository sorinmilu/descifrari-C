cmake_minimum_required(VERSION 3.10)
project(sort-algos C)
project(sort-algos-int C)
project(sort-algos-int-with-func C)

set(CMAKE_C_STANDARD 11)

include_directories("./include")

add_executable(algoritmi_sortare

        include/algoritmi_sortare/selection-sort.c
        include/algoritmi_sortare/bubble-sort.c
        include/algoritmi_sortare/insertion-sort.c
        include/algoritmi_sortare/quick-sort.c
        include/algoritmi_sortare/cocktail-sort.c
        include/algoritmi_sortare/heap-sort.c        
        include/algoritmi_sortare/radix-sort.c           
        include/algoritmi_sortare/shell-sort.c           
        include/algoritmi_sortare/counting-sort.c        
        include/algoritmi_sortare/bucket-sort.c
        include/algoritmi_sortare/merge-sort.c        
        include/data-swap.c
        include/algoritmi_sortare.h
        algoritmi_sortare.c)

