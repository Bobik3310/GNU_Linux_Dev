#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

enum
{
	ARGC_OK = 3,
	INFILE_INDX = 1,
	OUTFILE_INDX = 2,
	NULL_TERM = 1,
	FAILURE_GETLINE_READ = -1,
	ERROR_FLAG = 1
};

void check_errno(char *func, FILE *in, FILE *out, char *path_out, char *error_message)
{
	if (errno != 0) {
		if (error_message != NULL) {
			printf("%s", error_message);
		} else { 
			perror(func);
		}
		if (in != NULL && out != NULL && path_out != NULL)
		{
			errno = 0;
			fclose(in);
			fclose(out);
			remove(path_out);
			if (errno != 0) {
				fprintf(stderr, "Error when close files and remove outfile\n");
			}
		}
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[]) {
	const char write_flag[] = "w", read_flag[] = "r";
	FILE *in, *out;
	struct stat info;
	char *buf;
	size_t len, size;
	errno = 0;

	if (argc != ARGC_OK)
	{
		fprintf(stderr, "Arguments: ./move <infile> <outfile>\n");
		exit(EXIT_FAILURE);
	}

	in = fopen(argv[INFILE_INDX], read_flag);
	check_errno("fopen(in)", NULL, NULL, argv[OUTFILE_INDX], NULL); 

	out = fopen(argv[OUTFILE_INDX], write_flag); 
	check_errno("fopen(out)", in, NULL, argv[OUTFILE_INDX], NULL); 

	stat(argv[INFILE_INDX], &info); 
	size = info.st_size;
	check_errno("stat", in, out, argv[OUTFILE_INDX], NULL); 

	len = info.st_size + NULL_TERM;
	buf = calloc(len, sizeof(char)); 
	check_errno("calloc", in, out, argv[OUTFILE_INDX], NULL); 

	while(getline(&buf, &len, in) != FAILURE_GETLINE_READ) {
		fprintf(out, "%s", buf);
		check_errno("fprintf", in, out, argv[OUTFILE_INDX], "Problem with fprintf\n"); 
		size -= strlen(buf);
	}

	if (size != 0) {
		errno = ERROR_FLAG;
		check_errno("getline", in, out, argv[OUTFILE_INDX], "insize != outsize\n"); 
	}

	// set errno = 0 after EOF of getline()
	errno = 0;

	fclose(in); 
	check_errno("fclose(in)", NULL, out, argv[OUTFILE_INDX], NULL); 

	fclose(out); 
	check_errno("fclose(out)", NULL, NULL, argv[OUTFILE_INDX], NULL); 

	free(buf); 
	check_errno("free", NULL, NULL, argv[OUTFILE_INDX], NULL); 

	remove(argv[INFILE_INDX]);
	check_errno("remove(in)", NULL, NULL, argv[OUTFILE_INDX], NULL);

	printf("SUCCESS\n");

	exit(EXIT_SUCCESS);
}
