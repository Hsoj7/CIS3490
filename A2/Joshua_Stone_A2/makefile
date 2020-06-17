all: P11.o P11 P12.o P12 P21.o P21 P22.o P22

P11.o: P11.c
	gcc -Wall -pedantic -c P11.c -o P11.o

P11: P11.o
	gcc -Wall -pedantic P11.o -o P11

P12.o: P12.c
	gcc -Wall -pedantic -c P12.c -o P12.o

P12: P12.o
	gcc -Wall -pedantic P12.o -o P12

P21.o: P21.c
	gcc -Wall -pedantic -g -c P21.c -o P21.o

P21: P21.o
	gcc -Wall -pedantic -g P21.o -o P21 -lm

P22.o: P22.c
	gcc -Wall -pedantic -c P22.c -o P22.o

P22: P22.o
	gcc -Wall -pedantic P22.o -o P22

clean:
	rm *.o
