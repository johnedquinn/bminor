// @file   : stmt.h
// @author : John Ed Quinn
// @desc   : declares the stmt struct
// @notes  : NA

#ifndef STMT_H
#define STMT_H

#include "decl.h"
//#include "library.h"
#include "hash_table.h"
#include "library.h"
#include <stdlib.h>

typedef enum {
	STMT_DECL=0,
	STMT_EXPR,
	STMT_IF_ELSE,
	STMT_FOR,
	STMT_PRINT,
	STMT_RETURN,
	STMT_BLOCK
} stmt_t;

struct stmt {
	stmt_t kind;
	struct decl *decl;
	struct expr *init_expr;
	struct expr *expr;
	struct expr *next_expr;
	struct stmt *body;
	struct stmt *else_body;
	struct stmt *next;
};

struct stmt * stmt_create( stmt_t kind, struct decl *decl, struct expr *init_expr, struct expr *expr, struct expr *next_expr, struct stmt *body, struct stmt *else_body, struct stmt *next );
void stmt_print( struct stmt *s, int indent );
void stmt_resolve (struct stmt * s, struct hash_table * head);
void stmt_typecheck (struct stmt * s, struct decl * d);

#endif
