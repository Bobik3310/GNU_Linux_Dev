CC = gcc
CFLAGS = -Wall -g -c
LDFLAGS = -L.
LDLIBS = -lrhash -lreadline
GENERATES = *.out rhasher.o rhasher

.PHONY: all

all: rhasher

rhasher.o: rhasher.c
	$(CC) -DREADLINE $(CFLAGS) $< -o $@

rhasher: rhasher.o
	$(CC) $< -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(GENERATES)
