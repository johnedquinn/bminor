// @file   : expr.h
// @author : John Ed Quinn
// @desc   : declares the expr struct
// @notes  : NA

#ifndef EXPR_H
#define EXPR_H

#include "symbol.h"

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
	EXPR_IND	// Index []
	/* many more kinds of exprs to add here */
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
};

struct expr * expr_create( expr_t kind, struct expr *left, struct expr *right );

struct expr * expr_create_name( const char *n );
struct expr * expr_create_integer_literal( int c );
struct expr * expr_create_boolean_literal( int c );
struct expr * expr_create_char_literal( char c );
struct expr * expr_create_string_literal( const char *str );

void expr_print( struct expr *e );

#endif
