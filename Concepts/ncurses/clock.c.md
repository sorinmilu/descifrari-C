# Clock - program care afiseaza un ceas digital in consola folosind ncurses

Include bibliotecile utilizate: 
unistd.h - pentru functia sleep
ncurses.h - pentru functiile de afisare
time.h - pentru functiile care implkica data si timp (localtime, timeinfo si time_t)

```c
#include <unistd.h>
#include <ncurses.h>
#include <time.h>
```

in continuare se defineste cate o functie pentru fiecare cifra care utilizeaza in mod repetat functia mvprintw
Functia mvprintw este o functie combinata care muta cursorul la coordonatele specificate si imprima sirul de caractere (posibil insotit de variabile in modul in care functioneaza si printf).

```c
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

```

In continuare se defineste o functie de tip dispecer care va executa una dintre functiile de afisare a numerelor la coordonatele x si y in functie de numarul primit in parametrul in 

```c

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

```

```c

int main(void){
    initscr();
    attron(A_BOLD);
    int row, col; 

```
time_t este un tip de date special pentru stocarea timpului in secunde trecute de la 1 ian 1970, cunoscut si sub numele de epoch. Codul defineste variabila timedump de tip time_t. Se defineste de asemenea variabila timeinfo ca un pointer catre o structura de tip tm, care contine toate elementele unei date/ore. 

```c

    time_t timedump;
    struct tm* timeinfo;
```

```c

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

```

stdscr este o variabila predefinita in ncurses care este un pointer catre o structura de tip WINDOW care acopera intreaga suprafata a terminalului. Pentru cazurile in care nu se definesc ferestre specifice, se poate folosi aceasta. 

getmaxyx este un macro definit de ncurses care pozitioneaza in variabilele col si row dimensiunile in caractere ale ferestrei stdscr. Urmatoarele instructiuni apeleaza functia numeral de mai multe ori (de 6 ori, doua pentru ora, doua pentru minute, doua pentru secunde). 

```c
        getmaxyx(stdscr, row, col); 
        numeral((row / 2) - 4, (col / 2) + 21, sec);
        numeral((row / 2) - 4, (col / 2) + 12, sec2);
        numeral((row / 2) - 4, (col / 2 ), min);
        numeral((row / 2) - 4, (col / 2) - 9, min2);
        numeral((row / 2) - 4, (col / 2) - 21, hour);
        numeral((row / 2) - 4, (col / 2) - 30, hour2);
```

Functia move mota cursorul la pozitia 0,0 pentru ca urmatoarea iteratie sa permita recalcularea coordonatelor cifrelor cu acelasi algoritm.   

```c

        move(0, 0);
        refresh();
        sleep(1);
    }
}