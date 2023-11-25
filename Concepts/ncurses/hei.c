#include <curses.h>

const chtype BLOCK = ' ' | A_REVERSE;

WINDOW *title_win;

const char TITLE[] =
	"11  11  222222  33\n"
	"11  11  22      33\n"
	"111111  22222   33\n"
	"11  11  22      33\n"
	"11  11  222222  33\n";


void draw_text(void) {
	initscr();
	curs_set(0);           /* nu afisa cursorul */

	/* initializarea culorilor */
	use_default_colors();
	start_color();
	init_pair(1, COLOR_RED, -1);
	init_pair(2, COLOR_YELLOW, -1);
	init_pair(3, COLOR_BLUE, -1);

	title_win = newwin(5 ,44, 1, 1);

	const char *c;

	for (c = TITLE; *c != '\0'; c++) {
		if (*c == '\n' || *c == ' ') {
			waddch(title_win, (chtype) *c);
		} else {
			wattron(title_win, COLOR_PAIR(*c - 48));
			waddch(title_win, BLOCK);
			wattroff(title_win, COLOR_PAIR(*c - 48));
		}
	}

	wrefresh(title_win);
}


int main(void) {
	draw_text();
	for (;;) {
		//tine fereastra ncurses deschisa
				
	}
}

