// @file   : decl.h
// @author : John Ed Quinn
// @desc   : declares the decl struct
// @notes  : NA

#ifndef DECL_H
#define DECL_H

#include "type.h"
#include "stmt.h"
#include "expr.h"
#include "symbol.h"
#include "library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern unsigned int NUM_TYPECHECK_ERRORS;
extern unsigned int MAX_LOCAL;
extern unsigned int STRING_COUNTER;

struct decl {
	char *name;
	struct type *type;
	struct expr *value;
	struct stmt *code;
	struct symbol *symbol;
	struct decl *next;
	unsigned int max_local;
};

struct decl * decl_create( char *name, struct type *type, struct expr *value, struct stmt *code, struct decl *next );
void decl_print( struct decl *d, int indent );
void decl_resolve (struct decl * d, struct hash_table * head);
void decl_typecheck (struct decl * d);
void decl_codegen(struct decl * d, int scratch_table [], FILE * stream);

#endif


