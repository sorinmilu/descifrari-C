# Ncurses

Ncurses este o biblioteca software utilizata pentru a emula o interfata similara cu cele grafice in terminalele text. 

Denumirea ncurses este prescurtarea de la "new curses" care marcheaza o noua versiune a bibliotecii "curses" dezvoltata pentru vechile sisteme de tip UNIX, incepand cu anii 1980 la Berkeley. Denumirea "curses" este un joc de cuvinte pornind de la "cursor optimization".  

Eric Raymond si altii au implementat ncurses pe baza bibliotecii existente ca parte din miscarea "free software" - care a implicat rescrierea multor instrumente traditionale UNIX. 

Ideea principala din curses/ncurses este utilizarea caracterelor din setul ASCII extins pentru a construi interfete grafice cu care se poate interactiona in mod similar cu interfetele din mediul grafic. 

# Exemplul 1

Cel mai simplu program ncurses 

Ncurses este o biblioteca separata al carui header trebuie importat in program penru a avea la dispozitie functiile si structurile acesteia. 

```c
#include <ncurses.h>
```

```c
int main()
{	
```
initscr() este prima functie apelata intr-un program care utilizeaza ncurses si este cea care determina tipul de terminal si initializeaza toate structurile de date pe care ncurses le va utiliza in continuare

```c
	initscr();			/* Start curses mode 		  */
```

mvprintw muta cursorul la pozitia 4,4 si apoi afiseaza mesajul "Hello World !!!" 
```c
	mvprintw(4, 4, "Hello World !!!");	
```
Functia getch asteapta o comanda (apasarea unei taste) de la utilizator. Asteptarea implica o bucla infinita care mentine mesajul pe ecran.

```c

	getch();			/* Wait for user input */

```c

functia endwin() reface terminalul dupa utilizarea modyului ncurses. In lipsa acestei functii terminalul poate ramene intr-o stare neutilizabila, fie nu mai reactioneaza la comenzi, fie nu mai afiseaza ceea ce scrie utilizatorul, etc. 

```c
	endwin();			/* End curses mode		  */

	return 0;
}
```


# Exemplul 2

Exemplul 2 este similar cu exemplul 1 cu deosebirea ca mesajul Hello World se va imprima cu litere colorate in rosu. Functiile 

```c
#include <ncurses.h>

int main()
{	
	initscr();			/* Start curses mode 		  */
```

start_color() este o functie a ncurses care initializeaza sistemul de culori al ncurses, initializeaza 8 culor de baza (black, red, green, yellow, blue, magenta, cyan, and white), si doua variabile globale, COLORS si COLOR_PAIRS. start_colors trebuie apelat inainte de utilizarea oricarei comenzi care foloseste o culoare (de obicei imediat dupa initscr).  

init_pair modifica definitia unei perechi de culori (foreground si background) folosind constantele de tipul COLOR_RED pentru rosu... etc. Daca dorim culori suplimentare se poate folosi functia init_color pentru a modifica definitia uneia dintre constante. 

attron seteaza diverse atribute ale terminalului ncurses, in acest caz seteaza perechea de culori cu care se vor scrie mesajele de aici inainte. Atributele care se pot seta cu ajutorul attron sunt urmatoarele:

- A_NORMAL        Normal display (no highlight)
- A_STANDOUT      Best highlighting mode of the terminal
- A_UNDERLINE     Underlining
- A_REVERSE       Reverse video
- A_BLINK         Blinking
- A_DIM           Half bright
- A_BOLD          Extra bright or bold
- A_PROTECT       Protected mode
- A_INVIS         Invisible or blank mode
- A_ALTCHARSET    Alternate character set
- A_CHARTEXT      Bit-mask to extract a character
- COLOR_PAIR(n)   Color-pair number n

```c
    start_color(); // Enable color support
    init_pair(1, COLOR_RED, COLOR_BLACK);
    attron(COLOR_PAIR(1)); // Turn on color pair 1
```
```c
	mvprintw(4, 4, "Hello World !!!");	/* Print Hello World		  */
```
attroff este opusul lui attron - reseteaza anumite atribute ale ecranului. 

```c    
    attroff(COLOR_PAIR(1)); // Turn off color pair 1
```
```c
	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */

	return 0;
}
```