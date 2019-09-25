


scan: main.o scanner.o
	gcc -std=c99 main.o scanner.o -o scan	

main.o: main.c main.h token.h
	gcc -std=c99 main.c -c -o main.o

scanner.o: scanner.c token.h
	gcc -std=gnu99 scanner.c -c -o scanner.o

scanner.c: scanner.flex scanner.h
	flex -o scanner.c scanner.flex

clean:
	rm -f scanner.c scanner.o main.o scan
