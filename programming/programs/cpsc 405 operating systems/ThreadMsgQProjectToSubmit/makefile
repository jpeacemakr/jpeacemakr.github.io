CC=gcc
CFLAGS=-I.
DEPS = zemaphore.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
main: main.o zemaphore.o
	$(CC) -pthread -o main main.o zemaphore.o