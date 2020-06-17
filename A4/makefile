all: Q1.o Q1 Q2.o Q2

Q1.o: Q1.c
	gcc -Wall -pedantic -g -c Q1.c -o Q1.o

Q1: Q1.o
	gcc -Wall -pedantic -g Q1.o -o Q1

Q2.o: Q2.c
	gcc -Wall -pedantic -g -c Q2.c -o Q2.o

Q2: Q2.o
	gcc -Wall -pedantic -g Q2.o -o Q2

clean:
	rm *.o
