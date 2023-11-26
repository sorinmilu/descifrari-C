#include <ncurses.h>

int main()
{	int ch;
	initscr();			/* Start curses mode 		*/
	noecho();			/* Don't echo() while we do getch */

    printw("Scrieti un caracter si va fi afisat in culori inversate\n");
	ch = getch();
	printw("Caracterul introdus este ");
	attron(A_REVERSE);
	printw("%c", ch);
	attroff(A_REVERSE);

    getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */
	return 0;
}