# File: Makefile
# Author: John Ed Quinn
# Description: NA

##### RULES #####
OBJECTS = bin/bminor.o bin/scanner.o bin/parser.o bin/expr.o bin/param_list.o bin/decl.o bin/stmt.o bin/type.o bin/symbol.o bin/hash_table.o bin/scope.o bin/scratch.o library.o

## Create Program
bminor: $(OBJECTS)
	gcc $^ -o $@ -lm

# Library
library.o: library.c include/*.h
	gcc -c $< -o $@

## Create all object files #TODO : Add -Wall flag
bin/%.o: src/%.c include/*.h
	gcc -c $< -o $@

## Create scanner files
src/scanner.c: src/scanner.flex include/parser.h include/token.h
	flex -o $@ $<

## Create parser files
src/parser.c include/parser.h: src/parser.bison include/token.h
	bison --defines=include/parser.h --output=src/parser.c -v $<

## Make clean
clean:
	rm -f  bminor src/parser.output src/parser.c include/parser.h src/scanner.c src/lex.yy.c bin/*.o *.o *.s

## Random 
.PHONY: clean
