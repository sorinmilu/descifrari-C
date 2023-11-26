#include <ncurses.h>

int main()
{	
	initscr();			/* Start curses mode 		  */
	mvprintw(4, 4, "Hello World !!!");	/* Print Hello World		  */
	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */

	return 0;
}