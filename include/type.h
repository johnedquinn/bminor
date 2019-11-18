// @file   : type.h
// @author : John Ed Quinn
// @desc   : declares the type struct
// @notes  : NA

#ifndef TYPE_H
#define TYPE_H

#include "param_list.h"
#include <stdbool.h>

typedef enum {
	TYPE_VOID=0,
	TYPE_BOOLEAN,
	TYPE_CHARACTER,
	TYPE_INTEGER,
	TYPE_STRING,
	TYPE_ARRAY,
	TYPE_FUNCTION,
	TYPE_AUTO
} type_t;

struct type {
	type_t kind;
	struct param_list *params;
	struct type *subtype;
};

struct type * type_create( type_t kind, struct type *subtype, struct param_list *params );
void          type_print( struct type *t );
void type_t_print_err (type_t kind);
void type_t_print (type_t kind);
struct type * type_copy (struct type * t);
void type_delete (struct type * t);
bool type_equals (struct type * a, struct type * b);
bool type_is_atomic (struct type * t);

#endif
