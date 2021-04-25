CC=gcc
CFLAGS=-I.
DEPS=pdp_11.h


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
all: pdp
pdp: main.o main_function.o commands.o pdp_run.o
	$(CC) -o pdp main.o main_function.o commands.o pdp_run.o
valgrind:
	valgrind ./pdp
clean:
	rm -rf *.o pdp