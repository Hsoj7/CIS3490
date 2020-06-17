all: P11.o P11 P21.o P21 P12.o P12 P22.o P22 P23.o P23

P11.o: P11.c
	gcc -Wall -pedantic -g -c P11.c -o P11.o -lm

P11: P11.o
	gcc -Wall -pedantic -g P11.o -o P11 -lm

P21.o: P21.c
	gcc -Wall -pedantic -g -c P21.c -o P21.o

P21: P21.o
	gcc -Wall -pedantic -g P21.o -o P21

P12.o: P12.c
	gcc -Wall -pedantic -g -c P12.c -o P12.o -lm

P12: P12.o
	gcc -Wall -pedantic -g P12.o -o P12 -lm

P22.o: P22.c
	gcc -Wall -pedantic -g -c P22.c -o P22.o

P22: P22.o
	gcc -Wall -pedantic -g P22.o -o P22

P23.o: P23.c
	gcc -Wall -pedantic -g -c P23.c -o P23.o

P23: P23.o
	gcc -Wall -pedantic -g P23.o -o P23

clean:
	rm *.o
