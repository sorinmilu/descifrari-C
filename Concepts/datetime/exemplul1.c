/* Cate zile au ramas pana la cel mai apropiat craciun? */

//incorect

#include <stdio.h>
#include <time.h>

int main() {
    // Get the current time
    time_t currentTime;
    time(&currentTime);

    // Set the date for the next Christmas (December 25)
    struct tm nextChristmas = {0};
    nextChristmas.tm_mon = 11;           // December (0-based month)
    nextChristmas.tm_mday = 25;          // Day of the month
    nextChristmas.tm_hour = 0;           // Reset hours, minutes, and seconds
    nextChristmas.tm_min = 0;
    nextChristmas.tm_sec = 0;

    // If Christmas has already passed in the current year, calculate for the next year
    if (currentTime >= mktime(&nextChristmas)) {
        nextChristmas.tm_year++; // Move to the next year
    }

    // Calculate the time difference in seconds using local time
    time_t timeDiff = mktime(&nextChristmas) - currentTime;

    // Convert seconds to days
    int daysRemaining = (int)(timeDiff / (60 * 60 * 24));

    // Print the result
    printf("Days remaining until the next Christmas: %d\n", daysRemaining);

    return 0;
}

