#include <curses.h>
#include <locale.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	// initialise variables
	WINDOW *win;
	struct stat info;
	FILE *fp;
	int nlines, tmp;
	char c, *buf;

	// set locale encoding
	setlocale(LC_ALL, ""); // default locale

	// check input
	if (argc < 2) {
		fprintf(stderr, "Usage: Show <filename>\n");
		return 1;
	}

	// allocate heap memory for buf
	buf = calloc(info.st_size + 1, sizeof(char));
	if (buf == NULL) {
		fprintf(stderr, "Not allocating buf\n");
		return 1;
	} else {
		// parse file
		fp = fopen(argv[1], "r");
		// check file validity
		if (fp == NULL) {
			fprintf(stderr, "File not exist\n");
			return 1;
		} else {
		for (size = nlines = 0; (c = fgetc(fp)) != EOF; ++size) {
			if (c == '\n') {
				++nlines;
				c = '\0'; // end of sentence in buf
			}
			buf[size] = c;
		}
		}
	}
	fclose(fp);
	
	// parse begin of sentences
	lines = calloc(nlines, sizeof(char *));
	for (count = nlines; count > 0; --count)
	{
		lines




	initscr(); // initialise curses
	noecho(); // no echo user keys
	cbreak(); // analyse ESC-seq
	


	return 0;
}

