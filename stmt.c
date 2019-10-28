// @file   : stmt.c
// @author : John Ed Quinn
// @desc   : defines the stmt struct
// @notes  : NA

#include "stmt.h"

// @name: stmt_create
// @desc: creates a statement structure
struct stmt * stmt_create (stmt_t kind, struct decl * decl, struct expr * init_expr, struct expr * expr, struct expr * next_expr, struct stmt * body, struct stmt * else_body, struct stmt * next) {
    struct stmt * stmt = malloc(sizeof(*stmt));
	stmt->kind = kind;
	stmt->decl = decl;
	stmt->init_expr = init_expr;
	stmt->expr = expr;
	stmt->next_expr = next_expr;
	stmt->body = body;
	stmt->else_body = else_body;
	stmt->next = next;
    return stmt;
}

// @name: stmt_print
// @desc: prints the statement struct information
void stmt_print (struct stmt * s, int indent) {
    // @TODO
}