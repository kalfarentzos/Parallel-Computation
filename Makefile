CC = gcc
CFLAGS = -O3 -Wall
LIBS = -lpthread -lm

all: ex1 ex2 ex3

ex1: ex1.o
	$(CC) $(CFLAGS) -o ex1 ex1.o $(LIBS)

ex2: ex2.o
	$(CC) $(CFLAGS) -o ex2 ex2.o $(LIBS)

ex3: ex3.o
	$(CC) $(CFLAGS) -o ex3 ex3.o $(LIBS)

clean:
	rm -f *.o core* ex1 ex2 ex3
