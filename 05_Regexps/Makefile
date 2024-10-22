CC = cc
CFLAGS = -g -O0 -Wall

esub: esub.c
	$(CC) $(CFLAGS) $< -lncursesw -o $@

check: esub
	./esub "([[:digit:]]{4}) +([[:digit:]]{1, 2}) +([[:alpha:]]+) +([[:alpha:]]+)" "\4, \2 \3 year of \1" "2024 17 October Thursday" > esub.out
	echo "2024 17 October Thursday" | sed -E "s/([[:digit:]]{4}) +([[:digit:]]{1, 2}) +([[:alpha:]]+) +([[:alpha:]]+)/\4, \2 \3 year of \1/g" > sed.out
	./esub # blank path
	./esub a(b ab ab
	./esub ab a\1b ab
	./esub ab BA eabc
	./esub a(b)c \1_\1 DabcE
	./esub (a)b(c)d(e) <\3\2\1> _abcdef_
	./esub "([[:digit:]]{4}) +([[:digit:]]{1, 2}) +([[:alpha:]]+) +([[:alpha:]]+)" "\4, \2 \3 year of \1" "2024 17 October Thursday" > esub.out
	diff -us esub.out sed.out

clean:
	rm -f esub *.out
