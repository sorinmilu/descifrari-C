#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

void one(int y, int x){  
    mvprintw(y, x,   "  ____   ");
    mvprintw(y+1, x, " |    |  ");
    mvprintw(y+2, x, "   |  |  ");
    mvprintw(y+3, x, "   |  |  ");
    mvprintw(y+4, x, "   |  |  ");
    mvprintw(y+5, x, "   |  |  ");
    mvprintw(y+6, x, "   |__|  ");
}

void two(int y, int x){
    mvprintw(y, x,   " _______ "); 
    mvprintw(y+1, x, "|       |");
    mvprintw(y+2, x, "|____   |");
    mvprintw(y+3, x, " ____|  |");
    mvprintw(y+4, x, "| ______|");
    mvprintw(y+5, x, "| |_____ ");
    mvprintw(y+6, x, "|_______|");
}

void three(int y, int x){
    mvprintw(y, x,   " _______ "); 
    mvprintw(y+1, x, "|       |");
    mvprintw(y+2, x, "|___    |");
    mvprintw(y+3, x, " ___|   |");
    mvprintw(y+4, x, "|___    |");
    mvprintw(y+5, x, " ___|   |");
    mvprintw(y+6, x, "|_______|");
}

void four(int y, int x){
    mvprintw(y, x,   " _   ___ ");
    mvprintw(y+1, x, "| | |   |");
    mvprintw(y+2, x, "| |_|   |");
    mvprintw(y+3, x, "|       |");
    mvprintw(y+4, x, "|___    |");
    mvprintw(y+5, x, "    |   |");
    mvprintw(y+6, x, "    |___|");
}

void five(int y, int x){
    mvprintw(y, x,   " _______ "); 
    mvprintw(y+1, x, "|       |");
    mvprintw(y+2, x, "|   ____|");
    mvprintw(y+3, x, "|  |____ ");
    mvprintw(y+4, x, "|_____  |");
    mvprintw(y+5, x, " _____| |");
    mvprintw(y+6, x, "|_______|");
}

void six(int y, int x){
    mvprintw(y, x,   " ___     "); 
    mvprintw(y+1, x, "|   |    ");
    mvprintw(y+2, x, "|   |___ ");
    mvprintw(y+3, x, "|    _  |");
    mvprintw(y+4, x, "|   | | |");
    mvprintw(y+5, x, "|   |_| |");
    mvprintw(y+6, x, "|_______|");
}

void seven(int y, int x ){
    mvprintw(y, x,   " _______ ");
    mvprintw(y+1, x, "|       |");
    mvprintw(y+2, x, "|___    |");
    mvprintw(y+3, x, "    |   |");
    mvprintw(y+4, x, "    |   |");
    mvprintw(y+5, x, "    |   |");
    mvprintw(y+6, x, "    |___|");
}

void eight(int y, int x){
    mvprintw(y, x,   "  _____  ");
    mvprintw(y+1, x, " |  _  | ");
    mvprintw(y+2, x, " | |_| | ");
    mvprintw(y+3, x, "|   _   |");
    mvprintw(y+4, x, "|  | |  |");
    mvprintw(y+5, x, "|  |_|  |");
    mvprintw(y+6, x, "|_______|");
}

void nine(int y, int x){
    mvprintw(y, x,   " _______ ");
    mvprintw(y+1, x, "|  _    |");
    mvprintw(y+2, x, "| | |   |");
    mvprintw(y+3, x, "| |_|   |");
    mvprintw(y+4, x, "|___    |");
    mvprintw(y+5, x, "    |   |");
    mvprintw(y+6, x, "    |___|");
}

void zero(int y, int x){
    mvprintw(y, x,   " _______ ");
    mvprintw(y+1, x, "|  _    |");
    mvprintw(y+2, x, "| | |   |");
    mvprintw(y+3, x, "| | |   |");
    mvprintw(y+4, x, "| |_|   |");
    mvprintw(y+5, x, "|       |");
    mvprintw(y+6, x, "|_______|");
}

void numeral(int y, int x, int in){
    switch (in){
        case 1:
            one(y, x);
            break;
        case 2:
            two(y, x);
            break;
        case 3:
            three(y, x);
            break;
        case 4:
            four(y, x);
            break;
        case 5:
            five(y, x);
            break;
        case 6:
            six(y, x);
            break;
        case 7:
            seven(y, x);
            break;
        case 8:
            eight(y, x);
            break;
        case 9:
            nine(y, x);
            break;
        case 0:
            zero(y, x);
            break;
    }
}



int main(void){
    initscr();
    attron(A_BOLD);
    int row, col; 
    time_t timedump;
    struct tm* timeinfo;
    for (;;){
        clear();
        time(&timedump);
        timeinfo = localtime(&timedump);
        int sec = (*timeinfo).tm_sec % 10;
        int sec2 = (*timeinfo).tm_sec / 10;
        int min = (*timeinfo).tm_min % 10;
        int min2 = (*timeinfo).tm_min / 10;
        int hour = (*timeinfo).tm_hour % 10;
        int hour2 = (*timeinfo).tm_hour / 10;
        getmaxyx(stdscr, row, col); 
        numeral((row / 2) - 4, (col / 2) + 21, sec);
        numeral((row / 2) - 4, (col / 2) + 12, sec2);
        numeral((row / 2) - 4, (col / 2 ), min);
        numeral((row / 2) - 4, (col / 2) - 9, min2);
        numeral((row / 2) - 4, (col / 2) - 21, hour);
        numeral((row / 2) - 4, (col / 2) - 30, hour2);
        move(0, 0);
        refresh();
        sleep(1);
    }
}