#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

enum
{
	REGEXP_INDX = 1,
	SUBST_INDX = 2,
	STRING_INDX = 3,
	MAXGR = 10,
	ERROR_BUF_SIZE = 1024,
	MAX_STRING_LEN = 1024
};

void reg_subst(char *str, char *subst, regmatch_t bags[], char out[]) {
	char part1[MAX_STRING_LEN], part3[MAX_STRING_LEN], buf[MAX_STRING_LEN]; 
	int b, e, len_subst, indx_subst, num_bag, indx_buf;

	// split string on three parts
	b = bags[0].rm_so; e = bags[0].rm_eo;
	len_subst = strlen(subst);

	strncpy(part1, str, b); part1[b] = '\0';
	strncpy(part3, str + e, strlen(str) - e); part3[strlen(str) - e] = '\0'; 

	// analyse substitution string
	indx_buf = indx_subst = 0;
	while (indx_subst < len_subst && indx_buf < MAX_STRING_LEN) {
		if (subst[indx_subst] == '\\') {
			if (isdigit(subst[indx_subst + 1])) { // \[bag_num]
				num_bag = subst[indx_subst + 1] - '0';
				if (bags[num_bag].rm_so != -1) {
					b = bags[num_bag].rm_so; e = bags[num_bag].rm_eo;
					strncpy(buf + indx_buf, str + bags[num_bag].rm_so, e - b);
					indx_subst += 2; indx_buf += e - b;
				} else { // [bag_num] not exist
					fprintf(stderr, "Bag %c not exist\n", subst[indx_subst + 1]);
					_exit(1);
				}
			} else if (subst[indx_subst + 1] == '\\') { // "\\"
				buf[indx_buf] = '\\';
				++indx_buf; indx_subst += 2;
			}
		} else {
			buf[indx_buf] = subst[indx_subst];
			++indx_buf; ++indx_subst;
		}
	}
	buf[indx_buf] = '\0';
	out[strlen(part1) + indx_buf + strlen(part3)] = '\0';
	sprintf(out, "%s%s%s", part1, buf, part3);
}

int main (int argc, char *argv[]) {
	char error_buf[ERROR_BUF_SIZE], proc_str[MAX_STRING_LEN];
	int rc;
	regex_t regex;
	regmatch_t bags[MAXGR];

	if (argc != 4) {
		fprintf(stderr, "Usage: ./esub <regexp> <substitution> <string> (%d bytes)\n", MAX_STRING_LEN);
		_exit(1);
	}

	if (strlen(argv[STRING_INDX]) > MAX_STRING_LEN) {
		fprintf(stderr, "Error: length of third argument must be less than %d (author lazy and he don't want use dynamic memmory)\n", MAX_STRING_LEN);
		_exit(1);
	}

	if ((rc = regcomp(&regex, argv[REGEXP_INDX], REG_EXTENDED)) != 0) {
		regerror(rc, &regex, error_buf, ERROR_BUF_SIZE);
		fprintf(stderr, "regcomp() failed with message:'%s'\n", error_buf);
		_exit(1);
	}

	if (regexec(&regex, argv[STRING_INDX], MAXGR, bags, 0) == 0) {
		reg_subst(argv[3], argv[2], bags, proc_str);
		printf("%s\n", proc_str);
	} else {
		// Как использовать regexec с regerror?
		fprintf(stderr, "regexec() failed'\n");
		_exit(1);
	}

	regfree(&regex);
	return 0;
}
