# File: Makefile
# Author: John Ed Quinn
# Description: NA

##### RULES #####

## Create Program
bminor: bminor.o scanner.o parser.o
	gcc $^ -o $@ -lm

## Create all object files #TODO : Add -Wall flag
%.o: %.c *.h
	gcc -c $< -o $@

## Create scanner files
scanner.c: scanner.flex parser.h
	flex -o $@ $<

## Create parser files
parser.c parser.h: parser.bison
	bison --defines=parser.h --output=parser.c -v $<

## Make clean
clean:
	rm -f  bminor parser.output parser.c parser.h scanner.c lex.yy.c *.o

## Random 
.PHONY: clean