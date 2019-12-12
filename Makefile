# File: Makefile
# Author: John Ed Quinn
# Description: NA

##### RULES #####
OBJECTS = bin/bminor.o bin/scanner.o bin/parser.o bin/expr.o bin/param_list.o bin/decl.o bin/stmt.o bin/type.o bin/symbol.o bin/hash_table.o bin/scope.o bin/library.o bin/scratch.o

## Create Program
bminor: $(OBJECTS)
	gcc $^ -o $@ -lm

## Create all object files #TODO : Add -Wall flag
bin/%.o: src/%.c include/*.h
	gcc -Iinclude -c $< -o $@

# Create object files for library files
bin/%.o: src/%.c include/%.h
	gcc -Iinclude -c $< -o $@

## Create scanner files
src/scanner.c: src/scanner.flex include/parser.h include/token.h
	flex -o $@ $<

## Create parser files
src/parser.c include/parser.h: src/parser.bison include/token.h
	bison --defines=include/parser.h --output=src/parser.c -v $<

temp: x.bminor bminor
	./bminor -codegen x.bminor out.s
	gcc -c out.s -o out.o
	gcc out.o bin/library.o -o program

## Make clean
clean:
	rm -f  bminor src/parser.output src/parser.c include/parser.h src/scanner.c src/lex.yy.c bin/*.o

## Random 
.PHONY: clean
