// @file   : expr.h
// @author : John Ed Quinn
// @desc   : declares the expr struct
// @notes  : NA

#ifndef EXPR_H
#define EXPR_H

#include "symbol.h"
#include "scope.h"
#include "hash_table.h"
#include "scratch.h"

extern int NUM_RESOLVE_ERRORS;
extern int NUM_TYPECHECK_ERRORS;

typedef enum {
	EXPR_ADD,	// +
	EXPR_SUB,	// -
	EXPR_MUL,	// *
	EXPR_MOD,	// %
	EXPR_DIV,	// /
	EXPR_NOT,	// !
	EXPR_NEG,	// Unary Minus
	EXPR_POS,	// Unary Plus
	EXPR_FNC,	// Function
	EXPR_PRN,	// ( expr )
	EXPR_POW,	// Power : x^2
	EXPR_INC,	// Increment ++
	EXPR_DEC,	// Decrement --
	EXPR_LES,	// <
	EXPR_GRE,	// >
	EXPR_LEQ,	// <=
	EXPR_GEQ,	// >=
	EXPR_EQL,	// ==
	EXPR_NEQ,	// !=
	EXPR_AND,	// &&
	EXPR_ORR,	// OR
	EXPR_ASN,	// Assign =
	EXPR_IND,	// Index []
	EXPR_ARG,	// Args list
	EXPR_NAM,	// Name literal
	EXPR_INT,	// Int literal
	EXPR_BUL,	// Bool literal
	EXPR_CHR,	// Char literal
	EXPR_STR,	// String Literal
	EXPR_NUL	// Null
} expr_t;

struct expr {
	/* used by all kinds of exprs */
	expr_t kind;
	struct expr *left;
	struct expr *right;

	/* used by various leaf exprs */
	const char *name;
	int literal_value;
	const char * string_literal;
	struct symbol *symbol;
	int reg;
};

struct expr * expr_create( expr_t kind, struct expr *left, struct expr *right );
struct expr * expr_create_name( const char *n );
struct expr * expr_create_integer_literal( int c );
struct expr * expr_create_boolean_literal( int c );
struct expr * expr_create_char_literal( char c );
struct expr * expr_create_string_literal( const char *str );
void expr_print( struct expr *e );
void expr_resolve (struct expr * e, struct hash_table * head);
struct type * expr_typecheck (struct expr * e);
void expr_codegen (struct expr * e, int scratch_table [], FILE * stream);

#endif
