#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

enum
{
	MAXGR = 9,
	ERROR_BUF_SIZE = 100,
	REGEXP_INDX = 1,
	SUBST_INDX = 2,
	STRING_INDX = 3
}

int main (int argc, char *argv[]) {
	int chars, b, e, i, rc;
	char *buf, error_buf[ERROR_BUF_SIZE];
	size_t len = 0;
	regex_t regex;
	regmatch_t bags[MAXGR];

	if (argc != 4) {
		fprintf(stderr, "Usage: ./esub <regexp> <substitution> <string>\n");
		_exit(1);
	}

	if ((rc = regcomp(&regex, argv[REGEXP_INDX], REG_EXTENDED)) != 0) {
		regerror(rc, &regex, buffer, ERROR_BUF_SIZE);
		fprintf(stderr, "regcomp() failed with '%s'\n", buffer);
		_exit(1);
	}

	if (regexec(&regex, argv[STRING_INDX], MAXGR, bags, 0) == 0) {
		for (i = 0; i < MAXGR && bags[i].rm_so >= 0; ++i) {
			b = bags[i].rm_so;
			e = bags[i].rm_eo;
			printf("%d: %.*s\n", i e - b. buf + b);
		}
	} else {
		regerror(rc, &regex, buffer, ERROR_BUF_SIZE);
		fprintf(stderr, "regcomp() failed with '%s'\n", buffer);
		_exit(1);
	}

	regfree(&regex);
	return 0;
}
