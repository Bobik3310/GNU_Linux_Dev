CC = gcc
CFLAGS = -Wall -O0 -g
GENERATES = range *.out

all: range

test-%: range
	gdb $< -x ./gdb_script_$(subst test-,,$@).txt | grep "@@@" | sed 's/@@@ //g' | sed 's/\[.*\]//g' > $@.out
	cmp $@.out standart_$(subst test-,,$@).txt

clean:
	rm -f $(GENERATES)

test: test-1 test-2
