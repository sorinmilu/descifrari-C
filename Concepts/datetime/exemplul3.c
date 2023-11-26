#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    // Verificăm dacă sunt furnizate suficiente argumente de la linia de comandă
    if (argc != 3) {
        printf("Usage: %s start_year end_year\n", argv[0]);
        return 1;
    }

    // Convertim anii de la linia de comandă la formate întregi
    int startYear = atoi(argv[1]);
    int endYear = atoi(argv[2]);

    // Pentru fiecare an în intervalul specificat
    for (int year = startYear; year <= endYear; ++year) {
        // Setăm data la 15 ianuarie și obținem ziua săptămânii
        struct tm date = {0};
        date.tm_year = year - 1900; // Anul - 1900
        date.tm_mon = 0;            // Ianuarie (0-based month)
        date.tm_mday = 15;          // Ziua lunii

        // Obținem ziua săptămânii (0 = duminică, 1 = luni, ..., 6 = sâmbătă)
        mktime(&date); // Actualizăm structura timp
        int dayOfWeek = date.tm_wday;

        // Verificăm dacă ziua de 15 este miercuri (3)
        if (dayOfWeek == 3) {
            printf("In year %d, the 15th day of some month is a Wednesday.\n", year);
        }
    }

    return 0;
}
