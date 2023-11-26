#include <ncurses.h>

int main()
{	
	initscr();			/* Start curses mode 		  */
    start_color(); // Enable color support
    init_pair(1, COLOR_RED, COLOR_BLACK);
    attron(COLOR_PAIR(1)); // Turn on color pair 1
	mvprintw(4, 4, "Hello World !!!");	/* Print Hello World		  */
    attroff(COLOR_PAIR(1)); // Turn off color pair 1
	// refresh();			/* Print it on to the real screen */
	getch();			/* Wait for user input */
	endwin();			/* End curses mode		  */

	return 0;
}