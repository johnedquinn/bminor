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
			stmt_print(s->next, indent);
			break;
		default:
			if (s->body) stmt_print(s->body, indent);
			break;
	}
}