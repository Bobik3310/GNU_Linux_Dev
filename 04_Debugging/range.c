#include <stdio.h>
#include <stdlib.h>

enum { BASE = 10 };

int main(int argc, char *argv[]) {
  long i, M, N, S;
  char *endptr;
  if (argc == 1) {
    fprintf(stdout,
            "Input pattern must be: <file> [M] [N] [S], where M/N/S - "
            "integers\n");  // Как выводить help?
    return 0;
  } else if (argc == 2) {
    // parse
    N = (long)strtol(argv[1], &endptr, BASE);
	S = 1;

    // print
    for (i = 0; i < N; ++i) {
      fprintf(stdout, "%ld\n", i);
    }
  } else if (argc == 3) {
    // parse
    M = (long)strtol(argv[1], &endptr, BASE);
    N = (long)strtol(argv[2], &endptr, BASE);
	S = 1;

    // print
    for (i = M; i < N; ++i) {
      fprintf(stdout, "%ld\n", i);
    }
  } else if (argc == 4) {
    // parse
    M = (long)strtol(argv[1], &endptr, BASE);
    N = (long)strtol(argv[2], &endptr, BASE);
    S = (long)strtol(argv[3], &endptr, BASE);

    // print
    for (i = M; i < N; i += S) {
      fprintf(stdout, "%ld\n", i);
    }
  } else {
    fprintf(stderr, "Incorrect input\n");
    return 1;
  }

  return 0;
}
