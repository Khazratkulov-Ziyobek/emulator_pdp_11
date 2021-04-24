CC=gcc
CFLAGS=-I.
DEPS=pdp_11.h


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
all: pdp
pdp: main.o main_function.o
	$(CC) -o pdp main.o main_function.o
clean:
	rm -rf *.o pdp