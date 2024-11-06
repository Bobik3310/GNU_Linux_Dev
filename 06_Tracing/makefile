CC = gcc
CFLAGS = -Wall -g
GENERATES = move *.out infile outfile remove_custom.so PROTECT_infile

all: move remove_custom.so

remove_custom.so: remove_custom.c
	$(CC) -shared -o $@ $<

move: move.c prepare
	$(CC) $(CFLAGS) -o $@ $<

prepare:
	cp ethalon_infile infile
	cp ethalon_infile PROTECT_infile

clean:
	rm -f $(GENERATES)
