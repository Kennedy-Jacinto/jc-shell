CFLAGS = -g -c -Wall -Wpedantic -Wextra

all: jc-shell fibonacci

jc-shell: commandlinereader.o jc-shell.o
	gcc -o jc-shell jc-shell.o commandlinereader.o

commandlinereader.o: commandlinereader.c commandlinereader.h
	gcc $(CFLAGS) commandlinereader.c

fibonacci: fibonacci.o
	gcc -o fibonacci fibonacci.o

fibonacci.o: fibonacci.c
	gcc $(CFLAGS) fibonacci.c 

jc-shell.o: jc-shell.c
	gcc $(CFLAGS) jc-shell.c 

clean:
	rm -f *.o jc-shell fibonacci