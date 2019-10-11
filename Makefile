

.PHONY: clean

bminor: bminor.o scanner.o
	gcc -std=c99 bminor.o scanner.o -o bminor

bminor.o: bminor.c token.h
	gcc -std=c99 bminor.c -c -o bminor.o

scanner.o: scanner.c token.h
	gcc -std=gnu99 scanner.c -c -o scanner.o

scanner.c: scanner.flex
	flex -o scanner.c scanner.flex

clean:
	rm -f scanner.c scanner.o bminor.o bminor lex.yy.c

