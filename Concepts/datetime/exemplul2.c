#include <stdio.h>
#include <time.h>


//numarul de minute pana la sfarcitul anului
//incorect

int main() {
    // Get the current time
    time_t currentTime;
    time(&currentTime);

    // Get the current year
    struct tm *currentDate = localtime(&currentTime);
    int currentYear = currentDate->tm_year + 1900;

    // Set the date for the end of the current year (December 31)
    struct tm endOfYear = {0};
    endOfYear.tm_year = currentYear; // Assuming we're in the current year
    endOfYear.tm_mon = 11;           // December (0-based month)
    endOfYear.tm_mday = 31;          // Last day of the month

    // Calculate the time difference
    time_t timeDiff = mktime(&endOfYear) - currentTime;

    // Convert seconds to minutes
    int minutesRemaining = (int)(timeDiff / 60);

    // Print the result
    printf("Minutes remaining until the end of the current year: %d\n", minutesRemaining);

    return 0;
}
