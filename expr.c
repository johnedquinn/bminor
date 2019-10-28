// @file   : expr.c
// @author : John Ed Quinn
// @desc   : defines the expr struct
// @notes  : NA

#include "expr.h"

// @name : expr_create
// @desc : creates an expr struct
struct expr * expr_create (expr_t kind, struct expr * left, struct expr * right) {
    // @TODO
}

// @name : expr_create_name
// @desc : creates the name of an expr
struct expr * expr_create_name (const char * n) {
    // @TODO
}

// @name : expr_create_integer_literal
// @desc : creates an integer literal expression
struct expr * expr_create_integer_literal (int c) {
    // @TODO
}
// @name : expr_create_boolean_literal
// @desc : creates a boolean literal expression
struct expr * expr_create_boolean_literal (int c) {
    // @TODO
}

// @name : expr_create_char_literal
// @desc : creates a char literal expression
struct expr * expr_create_char_literal (char c) {
    // @TODO
}

// @name : expr_create_string_literal
// @desc : creates a string literal expression
struct expr * expr_create_string_literal (const char * str) {
    // @TODO
}

// @name : expr_print
// @desc : prints an expr's information
void expr_print (struct expr * e) {
    // @TODO
}