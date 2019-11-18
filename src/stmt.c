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
    if (!s) return;
	switch (s->kind) {
		case STMT_DECL:
			decl_print(s->decl, indent);
			break;
		case STMT_EXPR:
			print_indents(indent);
			expr_print(s->expr);
			printf(";\n");
			break;
		case STMT_IF_ELSE:
			print_indents(indent);
			printf("if (");
			expr_print(s->expr);
			printf(") {\n");
			stmt_print(s->body, indent + 1);
			print_indents(indent);
			printf("}");
			if (!s->else_body) { printf("\n"); break; }
			printf(" else {\n");
			stmt_print(s->else_body, indent + 1);
			print_indents(indent);
			printf("}\n");
			break;
		case STMT_FOR:
			print_indents(indent);
			printf("for (");
			expr_print(s->init_expr); printf("; ");
			expr_print(s->expr); printf("; ");
			expr_print(s->next_expr);
			printf(") {\n");
			stmt_print(s->body, indent + 1);
			print_indents(indent);
			printf("}\n");
			break;
		case STMT_PRINT:
			print_indents(indent);
			printf("print");
			if (s->expr) { printf(" "); expr_print(s->expr); }
			printf(";\n");
			break;
		case STMT_RETURN:
			print_indents(indent);
			printf("return");
			if (s->expr) { printf(" "); expr_print(s->expr); }
			printf(";\n");
			break;
		case STMT_BLOCK:
			stmt_print(s->body, indent);
			break;
		default:
			if (s->body) stmt_print(s->body, indent);
			break;
	}
	stmt_print(s->next, indent);
}

// @name: stmt_resolve
// @desc: name resolution for stmt
void stmt_resolve (struct stmt * s, struct hash_table * head) {
	if (!s) return;

	// Resolve all bodies
	decl_resolve(s->decl, head);
	expr_resolve(s->init_expr, head);
	expr_resolve(s->expr, head);
	expr_resolve(s->next_expr, head);

	// Check for embedded scopes
	if (s->kind == STMT_BLOCK || s->kind == STMT_IF_ELSE) {
		scope_enter(&head);
		stmt_resolve(s->body, head);
		scope_exit(&head);
	}
	if (s->else_body) {
		scope_enter(&head);
		stmt_resolve(s->else_body, head);
		scope_exit(&head);
	}

	// Keep recursing
	stmt_resolve(s->next, head);
}

void stmt_typecheck (struct stmt * s) {
	struct type *t;
	if (!s) return;
    //debug("IN TYPE CHECK: KIND = %d", s->kind);
	switch(s->kind) {
		case STMT_EXPR:
			t = expr_typecheck(s->expr);
			type_delete(t);
			break;
		case STMT_IF_ELSE:
			t = expr_typecheck(s->expr);
			if(t->kind!=TYPE_BOOLEAN) {
				fprintf(stderr, AC_RED "type error: " AC_RESET " if statement requires boolean expression\n");
                NUM_TYPECHECK_ERRORS++;
			}
			type_delete(t);
			stmt_typecheck(s->body);
			stmt_typecheck(s->else_body);
			break;
		case STMT_BLOCK:
			stmt_typecheck(s->body);
			break;
		case STMT_DECL:
			decl_typecheck(s->decl);
			break;
		case STMT_PRINT:
			expr_typecheck(s->expr);
			break;
		case STMT_RETURN:
			expr_typecheck(s->expr);
			break;
		case STMT_FOR:
			expr_typecheck(s->init_expr);
			expr_typecheck(s->expr);
			expr_typecheck(s->next_expr);
			stmt_typecheck(s->body);
			break;
		default:
			break;
	}
	stmt_typecheck(s->next);
}