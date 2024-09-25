#include <curses.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	// initialise variables
	WINDOW *win;
	int c;

	// set locale encoding
	setlocale(LC_ALL, ""); // your default locale

	// check input
	if (argc < 2) {
		fprintf(stderr, "Usage: Show <filename>\n");
		return 1;
	}

	// initialisate curses functions
	// disable cooked mode
	initscr(); // initialise start of TUI
	echo(); // no echo mode/not visualise all user input keys
	cbreak(); // all keys ncurses analyse

	win = newwin(LINES - 5, COLS - 5, 3, 6); // input window
	wmove(win, 0, 1);
	printw("Window:");
	refresh();
	keypad(win, TRUE); // transfer key to int in curses
	scrollok(win, TRUE); // enable scroll 
	box(win, 0, 0); // board

	// while input symbol != ESC (int 27)
	while((c = wgetch(win)) != 27) {
		wprintw(win, "  %d: %s\n", c, keyname(c)); // keyname - ID of symbol
		box(win, 0, 0);
		wrefresh(win);
	}
	endwin(); // end of TUI
	return 0;
}

// Appendix:
// Wait ESC beacuse all symbols - ESCAPE-sequances

