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
	if (s->kind == STMT_BLOCK || s->kind == STMT_IF_ELSE || s->kind == STMT_FOR) {
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

// @name: stmt_typecheck
// @desc: typecheck for statements
void stmt_typecheck (struct stmt * s, struct decl * d) {
	struct type *t;
	if (!s) return;
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
			stmt_typecheck(s->body, d);
			stmt_typecheck(s->else_body, d);
			break;
		case STMT_BLOCK:
			stmt_typecheck(s->body, d);
			break;
		case STMT_DECL:
			decl_typecheck(s->decl);
			break;
		case STMT_PRINT:
			expr_typecheck(s->expr);
			break;
		case STMT_RETURN:
			// Grab expression return type
			if (s->expr) t = expr_typecheck(s->expr);
			else t = type_create(TYPE_VOID, NULL, NULL);

			// Make sure inside function scope
			if (!d) {
                fprintf(stderr, AC_RED "type error: " AC_RESET " cannot return outside of function.\n", s->expr->name);
				NUM_TYPECHECK_ERRORS++;
				break;
			}

			// Update auto function
			if (d->symbol->type->subtype->kind == TYPE_AUTO) {
				d->symbol->type->subtype = t;
			}

			// Make sure to not return auto
			if (t->kind == TYPE_AUTO && d->symbol->type->subtype->kind == TYPE_AUTO) {
                fprintf(stderr, AC_RED "type error: " AC_RESET "cannot infer type of %s\n", s->expr->name);
			}

			// Check return type of function with type of return expression
			if (!type_equals(t, d->symbol->type->subtype)) {
                fprintf(stderr, AC_RED "type error: " AC_RESET "cannot return type ");
                type_t_print_err(t->kind);
                fprintf(stderr, " in function of return type ");
                type_t_print_err(d->symbol->type->subtype->kind);
                fprintf(stderr, ".\n");
				NUM_TYPECHECK_ERRORS++;
			}
			break;
		case STMT_FOR:
			expr_typecheck(s->init_expr);
			expr_typecheck(s->expr);
			expr_typecheck(s->next_expr);
			stmt_typecheck(s->body, d);
			break;
		default:
			break;
	}
	stmt_typecheck(s->next, d);
}

// @name: stmt_codegen
// @desc: generate code for statements
void stmt_codegen (struct stmt * s, int scratch_table [], FILE * stream) {
	if (!s) return;
	int else_label, done_label, begin_label;
	struct expr * e;
	switch(s->kind) {
		case STMT_EXPR:
			expr_codegen(s->expr, scratch_table, stream);
			scratch_free(scratch_table, s->expr->reg);
			break;
		case STMT_IF_ELSE:
			else_label = label_create();
			done_label = label_create();
			expr_codegen(s->expr, scratch_table, stream);
			fprintf(stream, "CMP $0, %s\n", scratch_name(s->expr->reg));
			scratch_free(scratch_table, s->expr->reg);
			fprintf(stream, "JE %s\n", label_name(else_label));
			stmt_codegen(s->body, scratch_table, stream);
			fprintf(stream, "JMP %s\n", label_name(done_label));
			fprintf(stream, "%s:\n", label_name(else_label));
			stmt_codegen(s->else_body, scratch_table, stream);
			fprintf(stream, "%s:\n", label_name(done_label));
			break;
		case STMT_BLOCK:
			stmt_codegen(s->body, scratch_table, stream);
			break;
		case STMT_DECL:
			decl_codegen(s->decl, scratch_table, stream);
			break;
		case STMT_PRINT:
			e = s->expr;
			while (e) {
            	expr_codegen(e->left, scratch_table, stream);
            	fprintf(stream, "MOVQ %s, %rdi\n", scratch_name(e->left->reg));
				if (e->left->kind == EXPR_NAM) {
					type_t_print_stmt(e->left->symbol->type->kind, stream);
				} else {
					expr_t_print_stmt(e->left->kind, stream);
				}
            	scratch_free(scratch_table, e->left->reg);
				e = e->right;
			}
			break;
		/// @TODO: Check
		case STMT_RETURN:
			expr_codegen(s->expr, scratch_table, stream);
			fprintf(stream, "\tMOVQ %s, %rax\n", scratch_name(s->expr->reg));
            fprintf(stream, "\tPOPQ %r15\n");
            fprintf(stream, "\tPOPQ %r14\n");
            fprintf(stream, "\tPOPQ %r13\n");
            fprintf(stream, "\tPOPQ %r12\n");
            fprintf(stream, "\tPOPQ %rbx\n");
            fprintf(stream, "\tMOVQ %rbp, %rsp\n");
            fprintf(stream, "\tPOPQ %rbp\n");
            fprintf(stream, "\tRET\n");
			scratch_free(scratch_table, s->expr->reg);
			break;
		case STMT_FOR:
			begin_label = label_create();
			done_label = label_create();
			expr_codegen(s->init_expr, scratch_table, stream);
			scratch_free(scratch_table, s->init_expr->reg);
			fprintf(stream, "%s:\n", label_name(begin_label));
			expr_codegen(s->expr, scratch_table, stream);
			fprintf(stream, "CMP $0, %s\n", scratch_name(s->expr->reg));
			fprintf(stream, "JE %s\n", label_name(done_label));
			stmt_codegen(s->body, scratch_table, stream);
			expr_codegen(s->next_expr, scratch_table, stream);
			scratch_free(scratch_table, s->next_expr->reg);
			fprintf(stream, "JMP %s\n", label_name(begin_label));
			fprintf(stream, "%s:\n", label_name(done_label));
			break;
		/// @TODO: Errors
		default:
			break;
	}
	stmt_codegen(s->next, scratch_table, stream);
}