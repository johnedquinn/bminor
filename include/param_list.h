// @file   : param_list.h
// @author : John Ed Quinn
// @desc   : declares the param_list struct
// @notes  : NA

#ifndef PARAM_LIST_H
#define PARAM_LIST_H

#include "type.h"
#include "library.h"
#include "hash_table.h"
#include "decl.h"
#include "symbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct expr;

struct param_list {
	char *name;
	struct type *type;
	struct symbol *symbol;
	struct param_list *next;
};

struct param_list * param_list_create (char * name, struct type * type, struct param_list * next);
void param_list_print (struct param_list * a);


void param_list_resolve (struct param_list * p, struct hash_table * head);
struct param_list * param_list_copy (struct param_list * target);
void param_list_delete (struct param_list * p);
bool param_list_equals (struct param_list * a, struct param_list * b);
#endif
