// @file   : symbol.h
// @author : John Ed Quinn
// @desc   : declares the symbol struct
// @notes  : NA

#ifndef SYMBOL_H
#define SYMBOL_H

#include "type.h"
#include <stdlib.h>
#include <string.h>

typedef enum {
	SYMBOL_LOCAL,
	SYMBOL_PARAM,
	SYMBOL_GLOBAL
} symbol_t;

struct symbol {
	symbol_t kind;
	struct type *type;
	char *name;
	int which;
};

struct symbol * symbol_create( symbol_t kind, struct type *type, char *name );


#endif