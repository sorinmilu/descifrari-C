#include <curses.h>

WINDOW *title_win;

const char TITLE[] =
	"11  11  222222  33\n"
	"11  11  22      33\n"
	"111111  22222   33\n"
	"11  11  22      33\n"
	"11  11  222222  33\n";


int main(void) {
	initscr();

	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);

	title_win = newwin(5 ,44, 2, 10);

	const char *c;

	for (c = TITLE; *c != '\0'; c++) {
		if (*c == '\n' || *c == ' ') {
			waddch(title_win, (chtype) *c);
		} else {
			wattron(title_win, COLOR_PAIR(*c - 48));
			waddch(title_win, ' ' | A_REVERSE);
			wattroff(title_win, COLOR_PAIR(*c - 48));
		}
	}
	wgetch(title_win);

	endwin();
}

