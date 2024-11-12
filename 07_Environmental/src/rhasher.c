#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "RHash/rhash.h"
#include <ctype.h>
#include <stdbool.h>

#ifdef READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif

enum
{
	MAX_ALGO_LEN = 4,
	MAX_STR_LEN = 1000000,
	NULL_TERM = 1,
	NEWLINE_SYM = '\n',
	STR_END = '\0',
	EQ = 0,
	INCORRECT_ALGO = -1,
	STR_FLAG = '"',
	STR_TYPE = 0,
	FILE_TYPE = 1,
	MAX_DIGEST_LEN = 64,
	MAX_HASH_LEN = 130,
	QUOTE_SYM = 1
};

void check_errno(char *function) {
	if (errno != 0) {
		perror(function);
		exit(EXIT_SUCCESS);
	}
}

void str_to_lower(char *input, char *output) {
	for(int i = 0; input[i] != STR_END; ++i){
		output[i] = (isalpha(input[i]) ? (char) tolower(input[i]) : input[i]);
	}
}

void name_to_id(char *algo_name, int *algo_id) {
	char str_lower[MAX_STR_LEN];
	str_to_lower(algo_name, str_lower);

	if (strcmp(str_lower, "md5") == EQ) {
		*algo_id = RHASH_MD5;
	} else if (strcmp(str_lower, "sha1") == EQ) {
		*algo_id = RHASH_SHA1;
	} else if (strcmp(str_lower, "tth") == EQ) {
		*algo_id = RHASH_TTH;
	} else {
		*algo_id = INCORRECT_ALGO;
	}
}

void detect_format(char *algo_name, int *format) {
	if (isupper(algo_name[0])) {
		*format = RHPR_HEX;
	} else {
		*format = RHPR_BASE64;
	}
}

void detect_type(char *str, int *type) {
	if (*str == STR_FLAG) {
		*type = STR_TYPE;
	} else {
		*type = FILE_TYPE;
	}
}

int main(int argc, char **argv) {
	const char delim[] = " ";
	const char invite_msg[] = ">> ";
	unsigned char digest[MAX_DIGEST_LEN];
	char output_hash[MAX_HASH_LEN];
	char *input_str; 
	char *input_hash;
	char *algo_name;
	int type, format;
	int algo_id;
	int res;

#ifdef READLINE
	puts("readline mode: ON");
	using_history();
#else
	size_t len;
	puts("readline mode: OFF");
#endif

	rhash_library_init();

#ifdef READLINE
	while((input_str = readline(invite_msg)) != NULL) {
		add_history(input_str);
#else
	len = MAX_ALGO_LEN + MAX_STR_LEN + NULL_TERM;
	errno = 0;
	input_str = calloc(len, sizeof(char));
	check_errno("calloc");

	while(printf("%s", invite_msg) && getline(&input_str, &len, stdin) != EOF) {
#endif
		algo_name = strtok(input_str, delim);
		input_hash = strtok(NULL, delim);

		if (algo_name == STR_END || *algo_name == NEWLINE_SYM || input_hash == STR_END) {
			fprintf(stderr, "Incorrect input! Usage: <Hash algorithm> <File/String>\n");
			continue;
		}

		if (input_hash[strlen(input_hash) - 1] == NEWLINE_SYM) {
			input_hash[strlen(input_hash) - 1] = STR_END;
		}

		name_to_id(algo_name, &algo_id);

		if (algo_id == INCORRECT_ALGO) {
			fprintf(stderr, "Unidentified argument\n");
			continue;
		}

		detect_format(algo_name, &format);
		detect_type(input_hash, &type);

		if (type == STR_TYPE) {
			res = rhash_msg(algo_id, input_hash + QUOTE_SYM, strlen(input_hash) - QUOTE_SYM, digest);

			if (res < 0) {
				fprintf(stderr, "Calculation error\n");
				puts(invite_msg);
				continue;
			}
		} else {
			res = rhash_file(algo_id, input_hash, digest);

			if (res < 0) {
				fprintf(stderr, "%s: %s\n", input_hash, strerror(errno));
				continue;
			}
		}

		rhash_print_bytes(output_hash, digest, rhash_get_digest_size(algo_id), format | RHPR_UPPERCASE); 

		puts(output_hash);

#ifdef READLINE
		errno = 0;
		free(input_str);
		check_errno("free");
#endif
	}

#ifndef READLINE
		errno = 0;
		free(input_str);
		check_errno("free");
#endif

	exit(EXIT_SUCCESS);
}
