CC = gcc
GENERATES = prog prog-a prog-so README libout* outfile*
TRASH = *.o *~ o.*
CFLAGS = -Wall -fPIC
LIB_FILES = fun.o const.o
O_FILES = const.o fun.o prog.o

all: README prog prog-a prog-so liboutput_static.a liboutput.so test

.SECONDARY:
	fun.o const.o

.INTERMEDIATE:
	liboutput_static.a(fun.o const.o)

README: prog
	./$< 2> $@

prog: $(O_FILES)
	$(CC) $^ -o $@

prog-a: prog.o liboutput_static.a
	$(CC) $^ -o $@

prog-so: prog.o liboutput.so
	$(CC) $< -L. -loutput -o $@

fun.o prog.o: outlib.h

liboutput_static.a: liboutput_static.a(fun.o const.o)
	
liboutput.so: $(LIB_FILES)
	$(CC) $^ -shared -o $@

test: prog prog-a prog-so
	./prog > outfile1 2>&1
	./prog-a > outfile2 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so > outfile3 2>&1
	cmp outfile1 outfile2
	cmp outfile3 outfile2
	./prog param > outfile1 2>&1
	./prog-a param > outfile2 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so param > outfile3 2>&1
	cmp outfile1 outfile2
	cmp outfile3 outfile2
	./prog param1 param2 param3 > outfile1 2>&1
	./prog-a param1 param2 param3 > outfile2 2>&1
	LD_LIBRARY_PATH=`pwd` ./prog-so param1 param2 param3 > outfile3 2>&1
	cmp outfile1 outfile2
	cmp outfile3 outfile2

clean:
	rm -f $(TRASH) $(GENERATES)
