// @file   : expr.c
// @author : John Ed Quinn
// @desc   : defines the expr struct
// @notes  : NA

#include "../include/expr.h"

// @name : expr_create
// @desc : creates an expr struct
struct expr * expr_create (expr_t kind, struct expr * left, struct expr * right) {
    struct expr * e = malloc(sizeof(*e));
    e->kind = kind;
    e->left = left;
    e->right = right;
}

// @name : expr_create_name
// @desc : creates the name of an expr
struct expr * expr_create_name (const char * n) {
    struct expr * e = expr_create(EXPR_NAM, NULL, NULL);
    e->name = strdup(n);
    return e;
}

// @name : expr_create_integer_literal
// @desc : creates an integer literal expression
struct expr * expr_create_integer_literal (int c) {
    struct expr * e = expr_create(EXPR_INT, NULL, NULL);
    e->literal_value = c;
    return e;
}
// @name : expr_create_boolean_literal
// @desc : creates a boolean literal expression
struct expr * expr_create_boolean_literal (int c) {
    struct expr * e = expr_create(EXPR_BUL, NULL, NULL);
    e->literal_value = c;
    return e;
}

// @name : expr_create_char_literal
// @desc : creates a char literal expression
struct expr * expr_create_char_literal (char c) {
    struct expr * e = expr_create(EXPR_CHR, NULL, NULL);
    e->literal_value = c;
    return e;
}

// @name : expr_create_string_literal
// @desc : creates a string literal expression
struct expr * expr_create_string_literal (const char * str) {
    struct expr * e = expr_create(EXPR_STR, NULL, NULL);
    e->string_literal = strdup(str);
    return e;
}

void expr_t_print_stmt (struct expr * e, FILE * stream) {
    //if (!e) return;
    expr_t t = e->kind;
    switch (t) {
        case EXPR_INT:
        case EXPR_ADD:
	    case EXPR_SUB:
	    case EXPR_MUL:
	    case EXPR_MOD:
	    case EXPR_DIV:
        case EXPR_NEG:
        case EXPR_POS:
        case EXPR_POW:
        case EXPR_INC:
        case EXPR_DEC:
            fprintf(stream, "CALL print_integer\n");
            break;
        case EXPR_BUL:
        case EXPR_NOT:
        case EXPR_LES:
        case EXPR_GRE:
        case EXPR_EQL:
        case EXPR_NEQ:
        case EXPR_LEQ:
        case EXPR_GEQ:
        case EXPR_AND:
        case EXPR_ORR:
            fprintf(stream, "CALL print_boolean\n");
            break;
        case EXPR_CHR:
            fprintf(stream, "CALL print_character\n");
            break;
        case EXPR_STR:
            fprintf(stream, "CALL print_string\n");
            break;
	    case EXPR_FNC:
            expr_t_print_stmt(e->left, stream);
            break;
        case EXPR_PRN:
            expr_t_print_stmt(e->left, stream);
            break;
        case EXPR_ASN:
            expr_t_print_stmt(e->left, stream);
            break;
        case EXPR_IND:
            type_t_print_stmt(e->left->symbol->type, stream);
            break;
        case EXPR_ARG:
            break;
        case EXPR_NAM:
            type_t_print_stmt(e->symbol->type, stream);
            break;
        default:
            fprintf(stderr, AC_RED "codegen error: " AC_RESET "cannot print passed type\n");
            break;
    }
}

// @name : expr_print
// @desc : prints an expr's information
void expr_print (struct expr * e) {
    if (!e) return;
    switch (e->kind) {
        case EXPR_ADD:
            expr_print(e->left);
            printf("+");
            expr_print(e->right);
            break;
        case EXPR_SUB:
            expr_print(e->left);
            printf("-");
            expr_print(e->right);
            break;
        case EXPR_MUL:
            expr_print(e->left);
            printf("*");
            expr_print(e->right);
            break;
        case EXPR_MOD:
            expr_print(e->left);
            printf("%");
            expr_print(e->right);
            break;
        case EXPR_DIV:
            expr_print(e->left);
            printf("/");
            expr_print(e->right);
            break;
        case EXPR_NOT:
            printf("!");
            expr_print(e->right);
            break;
        case EXPR_NEG:
            printf("-");
            expr_print(e->right);
            break;
        case EXPR_POS:
            printf("+");
            expr_print(e->right);
            break;
        case EXPR_FNC:
            expr_print(e->left);
            printf("(");
            expr_print(e->right);
            printf(")");
            break;
        case EXPR_PRN:
            if (e->left && e->left->kind != EXPR_PRN) {
                printf("(");
                expr_print(e->left);
                printf(")");
            } else {
                expr_print(e->left);
            }
            break;
        case EXPR_POW:
            expr_print(e->left);
            printf("^");
            expr_print(e->right);
            break;
        case EXPR_INC:
            expr_print(e->left);
            printf("++");
            break;
        case EXPR_DEC:
            expr_print(e->left);
            printf("--");
            break;
        case EXPR_LES:
            expr_print(e->left);
            printf("<");
            expr_print(e->right);
            break;
        case EXPR_GRE:
            expr_print(e->left);
            printf(">");
            expr_print(e->right);
            break;
        case EXPR_LEQ:
            expr_print(e->left);
            printf("<=");
            expr_print(e->right);
            break;
        case EXPR_GEQ:
            expr_print(e->left);
            printf(">=");
            expr_print(e->right);
            break;
        case EXPR_EQL:
            expr_print(e->left);
            printf("==");
            expr_print(e->right);
            break;
        case EXPR_NEQ:
            expr_print(e->left);
            printf("!=");
            expr_print(e->right);
            break;
        case EXPR_AND:
            expr_print(e->left);
            printf("&&");
            expr_print(e->right);
            break;
        case EXPR_ORR:
            expr_print(e->left);
            printf("||");
            expr_print(e->right);
            break;
        case EXPR_ASN:
            expr_print(e->left);
            printf("=");
            expr_print(e->right);
            break;
        case EXPR_IND:
            expr_print(e->left);
            printf("[");
            expr_print(e->right);
            printf("]");
            break;
        case EXPR_ARG:
            expr_print(e->left);
            if (e->right) printf(", ");
            expr_print(e->right);
            break;
        case EXPR_NAM:
            printf("%s", e->name);
            break;
        case EXPR_INT:
            print_integer(e->literal_value);
            break;
        case EXPR_BUL:
            print_boolean(e->literal_value);
            break;
        case EXPR_CHR:
            printf("\'%c\'", e->literal_value);
            break;
        case EXPR_STR:
            printf("\"%s\"", e->string_literal);
            break;
        case EXPR_NUL:
            break;
        default:
            break;
    } 
}

// @name : expr_print
// @desc : prints an expr's information
void expr_print_err (struct expr * e) {
    if (!e) return;
    switch (e->kind) {
        case EXPR_ADD:
            expr_print_err(e->left);
            fprintf(stderr, "+");
            expr_print_err(e->right);
            break;
        case EXPR_SUB:
            expr_print_err(e->left);
            fprintf(stderr, "-");
            expr_print_err(e->right);
            break;
        case EXPR_MUL:
            expr_print_err(e->left);
            fprintf(stderr, "*");
            expr_print_err(e->right);
            break;
        case EXPR_MOD:
            expr_print_err(e->left);
            fprintf(stderr, "%");
            expr_print_err(e->right);
            break;
        case EXPR_DIV:
            expr_print_err(e->left);
            fprintf(stderr, "/");
            expr_print_err(e->right);
            break;
        case EXPR_NOT:
            fprintf(stderr, "!");
            expr_print_err(e->right);
            break;
        case EXPR_NEG:
            fprintf(stderr, "-");
            expr_print_err(e->right);
            break;
        case EXPR_POS:
            fprintf(stderr, "+");
            expr_print_err(e->right);
            break;
        case EXPR_FNC:
            expr_print_err(e->left);
            fprintf(stderr, "(");
            expr_print_err(e->right);
            fprintf(stderr, ")");
            break;
        case EXPR_PRN:
            if (e->left && e->left->kind != EXPR_PRN) {
                fprintf(stderr, "(");
                expr_print_err(e->left);
                fprintf(stderr, ")");
            } else {
                expr_print_err(e->left);
            }
            break;
        case EXPR_POW:
            expr_print_err(e->left);
            fprintf(stderr, "^");
            expr_print_err(e->right);
            break;
        case EXPR_INC:
            expr_print_err(e->left);
            fprintf(stderr, "++");
            break;
        case EXPR_DEC:
            expr_print_err(e->left);
            fprintf(stderr, "--");
            break;
        case EXPR_LES:
            expr_print_err(e->left);
            fprintf(stderr, "<");
            expr_print_err(e->right);
            break;
        case EXPR_GRE:
            expr_print_err(e->left);
            fprintf(stderr, ">");
            expr_print_err(e->right);
            break;
        case EXPR_LEQ:
            expr_print_err(e->left);
            fprintf(stderr, "<=");
            expr_print_err(e->right);
            break;
        case EXPR_GEQ:
            expr_print_err(e->left);
            fprintf(stderr, ">=");
            expr_print_err(e->right);
            break;
        case EXPR_EQL:
            expr_print_err(e->left);
            fprintf(stderr, "==");
            expr_print_err(e->right);
            break;
        case EXPR_NEQ:
            expr_print_err(e->left);
            fprintf(stderr, "!=");
            expr_print_err(e->right);
            break;
        case EXPR_AND:
            expr_print_err(e->left);
            fprintf(stderr, "&&");
            expr_print_err(e->right);
            break;
        case EXPR_ORR:
            expr_print_err(e->left);
            fprintf(stderr, "||");
            expr_print_err(e->right);
            break;
        case EXPR_ASN:
            expr_print_err(e->left);
            fprintf(stderr, "=");
            expr_print_err(e->right);
            break;
        case EXPR_IND:
            expr_print_err(e->left);
            fprintf(stderr, "[");
            expr_print_err(e->right);
            fprintf(stderr, "]");
            break;
        case EXPR_ARG:
            expr_print_err(e->left);
            if (e->right) fprintf(stderr, ", ");
            expr_print_err(e->right);
            break;
        case EXPR_NAM:
            fprintf(stderr, "%s", e->name);
            break;
        case EXPR_INT:
            print_integer_err(e->literal_value);
            break;
        case EXPR_BUL:
            print_boolean_err(e->literal_value);
            break;
        case EXPR_CHR:
            fprintf(stderr, "\'%c\'", e->literal_value);
            break;
        case EXPR_STR:
            fprintf(stderr, "\"%s\"", e->string_literal);
            break;
        case EXPR_NUL:
            break;
        default:
            break;
    } 
}

// @name : expr_print
// @desc : prints an expr's information
void expr_resolve (struct expr * e, struct hash_table * head) {
    if (!e) return;
    if (e->kind == EXPR_NAM) {
        e->symbol = scope_lookup(head, e->name);
        if (!e->symbol) {
            fprintf(stderr, AC_RED "resolve error:" AC_RESET " %s is not defined.\n", e->name);
            NUM_RESOLVE_ERRORS++;
        }
    } else if (e->kind == EXPR_STR) {
        e->symbol = symbol_create(SYMBOL_GLOBAL, type_create(TYPE_STRING, 0, 0), "_S_");
        e->symbol->string_index = STRING_COUNTER++;
    } else {
        expr_resolve(e->left, head);
        expr_resolve(e->right, head);
    }
}

// @name : expr_typecheck
// @desc : typecheck for expr's
struct type * expr_typecheck (struct expr * e) {
    if(!e) return 0;
    struct type *lt = expr_typecheck(e->left);
    struct type *rt = expr_typecheck(e->right);
    struct type *result;
    switch(e->kind) {
        case EXPR_ADD:
        case EXPR_POW:
        case EXPR_SUB:
        case EXPR_MUL:
        case EXPR_MOD:
        case EXPR_DIV:
            if (lt->kind == TYPE_INTEGER && (rt->kind == TYPE_INTEGER || rt->kind == TYPE_ARRAY)){// && rt->subtype->kind == TYPE_INTEGER)) {

            } else {
                fprintf(stderr, AC_RED "type error: " AC_RESET "cannot perform arithmetic operations on ");
                type_t_print_err(lt->kind);
                fprintf(stderr, " (");
                expr_print_err(e->left);
                fprintf(stderr,") with ");
                type_t_print_err(rt->kind);
                fprintf(stderr, " (");
                expr_print_err(e->right);
                fprintf(stderr, ")\n");
                NUM_TYPECHECK_ERRORS++;
            }
            result = type_create(TYPE_INTEGER, 0, 0);
            break;
        case EXPR_NOT:
            if (rt->kind != TYPE_BOOLEAN) {
                fprintf(stderr, AC_RED "type error: " AC_RESET "cannot perform boolean operations on ");
                type_t_print_err(lt->kind);
                fprintf(stderr, " (");
                expr_print_err(e->left);
                fprintf(stderr, ")\n");
                NUM_TYPECHECK_ERRORS++;
            }
            result = type_create(TYPE_BOOLEAN,0,0);
            break;
        case EXPR_NEG:
        case EXPR_POS:
            if (rt->kind != TYPE_INTEGER) {
                fprintf(stderr, AC_RED "type error: " AC_RESET "cannot perform unary operations on ");
                type_t_print_err(lt->kind);
                fprintf(stderr, " (");
                expr_print_err(e->left);
                fprintf(stderr, ")\n");
                NUM_TYPECHECK_ERRORS++;
            }
            result = type_create(TYPE_INTEGER,0,0);
            break;
        case EXPR_FNC:
            result = type_create(lt->subtype->kind,0,0);
            break;
        case EXPR_PRN:
            result = type_create(lt->kind,0,0);
            break;
        case EXPR_INC:
        case EXPR_DEC:
            if (lt->kind != TYPE_INTEGER) {
                fprintf(stderr, AC_RED "type error: " AC_RESET "cannot perform increment/decrement on ");
                type_t_print_err(lt->kind);
                fprintf(stderr, " (");
                expr_print_err(e->left);
                fprintf(stderr, ")\n");
                NUM_TYPECHECK_ERRORS++;
            }
            result = type_create(TYPE_INTEGER,0,0);
            break;
        case EXPR_LES:
        case EXPR_GRE:
        case EXPR_LEQ:
        case EXPR_GEQ:
        case EXPR_EQL:
        case EXPR_NEQ:
            if (!type_equals(lt, rt)) {
                fprintf(stderr, AC_RED "type error: " AC_RESET "cannot perform comparison operations between ");
                type_t_print_err(lt->kind);
                fprintf(stderr, " (");
                expr_print_err(e->left);
                fprintf(stderr,") and ");
                type_t_print_err(rt->kind);
                fprintf(stderr, " (");
                expr_print_err(e->right);
                fprintf(stderr, ")\n");
                NUM_TYPECHECK_ERRORS++;
            }
            if (lt->kind == TYPE_VOID || lt->kind == TYPE_ARRAY || lt->kind == TYPE_FUNCTION) {
                fprintf(stderr, AC_RED "type error: " AC_RESET "cannot perform comparison operations between ");
                type_t_print_err(lt->kind);
                fprintf(stderr, " (");
                expr_print_err(e->left);
                fprintf(stderr,") and ");
                type_t_print_err(rt->kind);
                fprintf(stderr, " (");
                expr_print_err(e->right);
                fprintf(stderr, ")\n");
                NUM_TYPECHECK_ERRORS++;
            }
            result = type_create(TYPE_BOOLEAN,0,0);
            break;
        case EXPR_AND:
        case EXPR_ORR:
            if (lt->kind != TYPE_BOOLEAN || rt->kind != TYPE_BOOLEAN) {
                fprintf(stderr, AC_RED "type error: " AC_RESET "cannot perform boolean comparisons on ");
                type_t_print_err(lt->kind);
                fprintf(stderr, " (");
                expr_print_err(e->left);
                fprintf(stderr,") with ");
                type_t_print_err(rt->kind);
                fprintf(stderr, " (");
                expr_print_err(e->right);
                fprintf(stderr, ")\n");
                NUM_TYPECHECK_ERRORS++;
            }
            result = type_create(TYPE_BOOLEAN,0,0);
            break;
        case EXPR_ASN:
            if (lt->kind == TYPE_AUTO) {
                lt->kind = rt->kind;
            }
            if (lt->kind != rt->kind) {
                fprintf(stderr, AC_RED "type error: " AC_RESET "cannot assign value of ");
                type_t_print_err(rt->kind);
                fprintf(stderr, " (");
                expr_print_err(e->right);
                fprintf(stderr, ") to ");
                type_t_print_err(lt->kind);
                fprintf(stderr, " (");
                expr_print_err(e->left);
                fprintf(stderr, ")\n");
                NUM_TYPECHECK_ERRORS++;
            }
            result = type_create(lt->kind,0,0);
            break;
        case EXPR_IND:
            if (lt->kind != TYPE_ARRAY) {
                fprintf(stderr, AC_RED "type error: " AC_RESET "cannot index non-array.\n");
                NUM_TYPECHECK_ERRORS++;
            }
            if (rt->kind != TYPE_INTEGER) {
                fprintf(stderr, AC_RED "type error: " AC_RESET "cannot index array with non-integer.\n");
                NUM_TYPECHECK_ERRORS++;
            }
            result = type_create(lt->subtype->kind,0,0);
            break;
        case EXPR_ARG:
            result = type_copy(lt);
            break;
        case EXPR_NAM:
            result = type_create(e->symbol->type->kind,e->symbol->type->subtype,e->symbol->type->params);
            break;
        case EXPR_INT:
            result = type_create(TYPE_INTEGER,0,0);
            break;
        case EXPR_BUL:
            result = type_create(TYPE_BOOLEAN,0,0);
            break;
        case EXPR_CHR:
            result = type_create(TYPE_CHARACTER,0,0);
            break;
        case EXPR_STR:
            result = type_create(TYPE_STRING,0,0);
            break;
        default:
        case EXPR_NUL:
            result = type_create(TYPE_VOID,0,0);
            break;
    }
    return result;
}

// @func : expr_codegen
// @desc : generate assembly code for expressions
void expr_codegen (struct expr * e, int scratch_table [], FILE * stream) {

    if (!e) return;

    int done_label, true_label, fail_label, success_label, extra_scratch;

    switch (e->kind) {
        case EXPR_ADD:
            expr_codegen(e->left, scratch_table, stream);
            expr_codegen(e->right, scratch_table, stream);
            fprintf(stream, "ADDQ %s, %s\n", scratch_name(e->left->reg), scratch_name(e->right->reg));
            e->reg = e->right->reg;
            scratch_free(scratch_table, e->left->reg);
            break;
        case EXPR_SUB:
            expr_codegen(e->left, scratch_table, stream);
            expr_codegen(e->right, scratch_table, stream);
            fprintf(stream, "SUBQ %s, %s\n", scratch_name(e->left->reg), scratch_name(e->right->reg));
            e->reg = e->right->reg;
            scratch_free(scratch_table, e->left->reg);
            break;
        case EXPR_MUL:
            expr_codegen(e->left, scratch_table, stream);
            expr_codegen(e->right, scratch_table, stream);
            fprintf(stream, "MOVQ %s, %rax\n", scratch_name(e->left->reg));
            fprintf(stream, "IMULQ %s\n", scratch_name(e->right->reg));
            fprintf(stream, "MOVQ %rax, %s\n", scratch_name(e->right->reg));
            e->reg = e->right->reg;
            scratch_free(scratch_table, e->left->reg);
            break;
        case EXPR_POW:
            expr_codegen(e->left, scratch_table, stream);
            expr_codegen(e->right, scratch_table, stream);
            fprintf(stream, "MOVQ %s, %rdi\n", scratch_name(e->left->reg));
            fprintf(stream, "MOVQ %s, %rsi\n", scratch_name(e->right->reg));
            fprintf(stream, "CALL integer_power\n");
            e->reg = e->right->reg;
            fprintf(stream, "MOVQ %rax, %s\n", scratch_name(e->reg));
            scratch_free(scratch_table, e->left->reg);
            break;
        case EXPR_MOD:
            expr_codegen(e->left, scratch_table, stream);
            expr_codegen(e->right, scratch_table, stream);
            fprintf(stream, "MOVQ %s, %rax\n", scratch_name(e->left->reg));
            fprintf(stream, "CQO\n");
            fprintf(stream, "IDIVQ %s\n", scratch_name(e->right->reg));
            fprintf(stream, "MOVQ %rdx, %s\n", scratch_name(e->right->reg));
            e->reg = e->right->reg;
            scratch_free(scratch_table, e->left->reg);
            break;
        case EXPR_DIV:
            expr_codegen(e->left, scratch_table, stream);
            expr_codegen(e->right, scratch_table, stream);
            fprintf(stream, "MOVQ %s, %rax\n", scratch_name(e->left->reg));
            fprintf(stream, "CQO\n");
            fprintf(stream, "IDIVQ %s\n", scratch_name(e->right->reg));
            fprintf(stream, "MOVQ %rax, %s\n", scratch_name(e->right->reg));
            e->reg = e->right->reg;
            scratch_free(scratch_table, e->left->reg);
            break;
        case EXPR_NOT:
            success_label = label_create();
            done_label = label_create();
            expr_codegen(e->right, scratch_table, stream);
            fprintf(stream, "CMP $0, %s\n", scratch_name(e->right->reg));
            fprintf(stream, "JE %s\n", label_name(success_label));
            fprintf(stream, "MOVQ $0, %s\n", scratch_name(e->right->reg));
            fprintf(stream, "JMP %s\n", label_name(done_label));
            fprintf(stream, "%s:\n", label_name(success_label));
            fprintf(stream, "MOVQ $1, %s\n", scratch_name(e->right->reg));
            fprintf(stream, "%s:\n", label_name(done_label));
            break;
        case EXPR_NEG:
            expr_codegen(e->right, scratch_table, stream);
            extra_scratch = scratch_alloc(scratch_table);
            fprintf(stream, "MOVQ %s, %rax\n", scratch_name(e->right->reg));
            fprintf(stream, "MOVQ $-1, %s\n", scratch_name(extra_scratch));
            fprintf(stream, "IMULQ %s\n", scratch_name(extra_scratch));
            fprintf(stream, "MOVQ %rax, %s\n", scratch_name(e->right->reg));
            scratch_free(scratch_table, extra_scratch);
            e->reg = e->right->reg;
            break;
        case EXPR_POS:
            expr_codegen(e->right, scratch_table, stream);
            e->reg = e->right->reg;
            break;
        case EXPR_FNC:
            // Print Arguments
            expr_codegen(e->right, scratch_table, stream);
            // Function Call
            fprintf(stream, "PUSHQ %r10\n");
            fprintf(stream, "PUSHQ %r11\n");
            fprintf(stream, "CALL %s\n", e->left->name);
            fprintf(stream, "POPQ %r11\n");
            fprintf(stream, "POPQ %r10\n");
            e->reg = scratch_alloc(scratch_table);
            fprintf(stream, "MOVQ %rax, %s\n", scratch_name(e->reg));
            break;
        case EXPR_ARG:
            expr_codegen(e->left, scratch_table, stream);
            fprintf(stream, "MOVQ %s, %s\n", scratch_name(e->left->reg), arg_name(ARG_COUNTER++));
            scratch_free(scratch_table, e->left->reg);
            expr_codegen(e->right, scratch_table, stream);
            ARG_COUNTER = 0;
            break;
        case EXPR_PRN:
            expr_codegen(e->left, scratch_table, stream);
            e->reg = e->left->reg;
            break;
        case EXPR_INC:
            expr_codegen(e->left, scratch_table, stream);
            e->reg = scratch_alloc(scratch_table);
            fprintf(stream, "MOVQ %s, %s\n", scratch_name(e->left->reg), scratch_name(e->reg));
            fprintf(stream, "ADDQ $1, %s\n", scratch_name(e->reg));
            if (e->left->kind == EXPR_NAM)
                fprintf(stream, "MOVQ %s, %s\n", scratch_name(e->reg), symbol_codegen(e->left->symbol));
            scratch_free(scratch_table, e->reg);
            e->reg = e->left->reg;
            break;
        case EXPR_DEC:
            expr_codegen(e->left, scratch_table, stream);
            e->reg = scratch_alloc(scratch_table);
            fprintf(stream, "MOVQ %s, %s\n", scratch_name(e->left->reg), scratch_name(e->reg));
            fprintf(stream, "SUBQ $1, %s\n", scratch_name(e->reg));
            if (e->left->kind == EXPR_NAM)
                fprintf(stream, "MOVQ %s, %s\n", scratch_name(e->reg), symbol_codegen(e->left->symbol));
            scratch_free(scratch_table, e->reg);
            e->reg = e->left->reg;
            break;
        case EXPR_LES:
            true_label = label_create();
            done_label = label_create();
            expr_codegen(e->left, scratch_table, stream);
            expr_codegen(e->right, scratch_table, stream);
            e->reg = e->right->reg;
            fprintf(stream, "CMP %s, %s\n", scratch_name(e->left->reg), scratch_name(e->right->reg));
            fprintf(stream, "JG %s\n", label_name(true_label));
            fprintf(stream, "MOVQ $0, %s\n", scratch_name(e->reg));
            fprintf(stream, "JMP %s\n", label_name(done_label));
            fprintf(stream, "%s:\n", label_name(true_label));
            fprintf(stream, "MOVQ $1, %s\n", scratch_name(e->reg));
            fprintf(stream, "%s:\n", label_name(done_label));
            scratch_free(scratch_table, e->left->reg);
            break;
        case EXPR_GRE:
            true_label = label_create();
            done_label = label_create();
            expr_codegen(e->left, scratch_table, stream);
            expr_codegen(e->right, scratch_table, stream);
            e->reg = e->right->reg;
            fprintf(stream, "CMP %s, %s\n", scratch_name(e->left->reg), scratch_name(e->right->reg));
            fprintf(stream, "JL %s\n", label_name(true_label));
            fprintf(stream, "MOVQ $0, %s\n", scratch_name(e->reg));
            fprintf(stream, "JMP %s\n", label_name(done_label));
            fprintf(stream, "%s:\n", label_name(true_label));
            fprintf(stream, "MOVQ $1, %s\n", scratch_name(e->reg));
            fprintf(stream, "%s:\n", label_name(done_label));
            scratch_free(scratch_table, e->left->reg);
            break;
        case EXPR_LEQ:
            true_label = label_create();
            done_label = label_create();
            expr_codegen(e->left, scratch_table, stream);
            expr_codegen(e->right, scratch_table, stream);
            e->reg = e->right->reg;
            fprintf(stream, "CMP %s, %s\n", scratch_name(e->left->reg), scratch_name(e->right->reg));
            fprintf(stream, "JGE %s\n", label_name(true_label));
            fprintf(stream, "MOVQ $0, %s\n", scratch_name(e->reg));
            fprintf(stream, "JMP %s\n", label_name(done_label));
            fprintf(stream, "%s:\n", label_name(true_label));
            fprintf(stream, "MOVQ $1, %s\n", scratch_name(e->reg));
            fprintf(stream, "%s:\n", label_name(done_label));
            scratch_free(scratch_table, e->left->reg);
            break;
        case EXPR_GEQ:
            true_label = label_create();
            done_label = label_create();
            expr_codegen(e->left, scratch_table, stream);
            expr_codegen(e->right, scratch_table, stream);
            e->reg = e->right->reg;
            fprintf(stream, "CMP %s, %s\n", scratch_name(e->left->reg), scratch_name(e->right->reg));
            fprintf(stream, "JLE %s\n", label_name(true_label));
            fprintf(stream, "MOVQ $0, %s\n", scratch_name(e->reg));
            fprintf(stream, "JMP %s\n", label_name(done_label));
            fprintf(stream, "%s:\n", label_name(true_label));
            fprintf(stream, "MOVQ $1, %s\n", scratch_name(e->reg));
            fprintf(stream, "%s:\n", label_name(done_label));
            scratch_free(scratch_table, e->left->reg);
            break;
        case EXPR_EQL:
            true_label = label_create();
            done_label = label_create();
            expr_codegen(e->left, scratch_table, stream);
            expr_codegen(e->right, scratch_table, stream);
            e->reg = e->right->reg;
            fprintf(stream, "CMP %s, %s\n", scratch_name(e->left->reg), scratch_name(e->right->reg));
            fprintf(stream, "JE %s\n", label_name(true_label));
            fprintf(stream, "MOVQ $0, %s\n", scratch_name(e->reg));
            fprintf(stream, "JMP %s\n", label_name(done_label));
            fprintf(stream, "%s:\n", label_name(true_label));
            fprintf(stream, "MOVQ $1, %s\n", scratch_name(e->reg));
            fprintf(stream, "%s:\n", label_name(done_label));
            scratch_free(scratch_table, e->left->reg);
            break;
        case EXPR_NEQ:
            true_label = label_create();
            done_label = label_create();
            expr_codegen(e->left, scratch_table, stream);
            expr_codegen(e->right, scratch_table, stream);
            e->reg = e->right->reg;
            fprintf(stream, "CMP %s, %s\n", scratch_name(e->left->reg), scratch_name(e->right->reg));
            fprintf(stream, "JNE %s\n", label_name(true_label));
            fprintf(stream, "MOVQ $0, %s\n", scratch_name(e->reg));
            fprintf(stream, "JMP %s\n", label_name(done_label));
            fprintf(stream, "%s:\n", label_name(true_label));
            fprintf(stream, "MOVQ $1, %s\n", scratch_name(e->reg));
            fprintf(stream, "%s:\n", label_name(done_label));
            scratch_free(scratch_table, e->left->reg);
            break;
        case EXPR_AND:
            done_label = label_create();
            fail_label = label_create();
            expr_codegen(e->left, scratch_table, stream);
            expr_codegen(e->right, scratch_table, stream);
            e->reg = e->right->reg;
            fprintf(stream, "CMP $0, %s\n", scratch_name(e->left->reg));
            fprintf(stream, "JE %s\n", label_name(fail_label));
            fprintf(stream, "CMP $0, %s\n", scratch_name(e->right->reg));
            fprintf(stream, "JE %s\n", label_name(fail_label));
            fprintf(stream, "MOVQ $1, %s\n", scratch_name(e->reg));
            fprintf(stream, "JMP %s\n", label_name(done_label));
            fprintf(stream, "%s:\n", label_name(fail_label));
            fprintf(stream, "MOVQ $0, %s\n", scratch_name(e->reg));
            fprintf(stream, "%s:\n", label_name(done_label));
            scratch_free(scratch_table, e->left->reg);
            break;
        case EXPR_ORR:
            done_label = label_create();
            success_label = label_create();
            expr_codegen(e->left, scratch_table, stream);
            expr_codegen(e->right, scratch_table, stream);
            e->reg = e->right->reg;
            fprintf(stream, "CMP $1, %s\n", scratch_name(e->left->reg));
            fprintf(stream, "JE %s\n", label_name(success_label));
            fprintf(stream, "CMP $1, %s\n", scratch_name(e->right->reg));
            fprintf(stream, "JE %s\n", label_name(success_label));
            fprintf(stream, "MOVQ $0, %s\n", scratch_name(e->reg));
            fprintf(stream, "JMP %s\n", label_name(done_label));
            fprintf(stream, "%s:\n", label_name(success_label));
            fprintf(stream, "MOVQ $1, %s\n", scratch_name(e->reg));
            fprintf(stream, "%s:\n", label_name(done_label));
            scratch_free(scratch_table, e->left->reg);
            break;
        case EXPR_ASN:
            expr_codegen(e->left, scratch_table, stream);
            expr_codegen(e->right, scratch_table, stream);
            fprintf(stream, "MOVQ %s, %s\n", scratch_name(e->right->reg), scratch_name(e->left->reg));
            if (e->left->kind == EXPR_NAM) {
                fprintf(stream, "MOVQ %s, %s\n", scratch_name(e->left->reg), symbol_codegen(e->left->symbol));
            }
            e->reg = e->left->reg;
            scratch_free(scratch_table, e->right->reg);
            break;
        /// @TODO: Indexing
        case EXPR_IND:
            expr_codegen(e->right, scratch_table, stream);
            e->reg = scratch_alloc(scratch_table);
            extra_scratch = scratch_alloc(scratch_table);
            fprintf(stream, "LEAQ %s, %s\n", symbol_codegen(e->left->symbol), scratch_name(extra_scratch));
            fprintf(stream, "MOVQ -530(%s, %s, 8), %s\n", scratch_name(extra_scratch), scratch_name(e->right->reg), scratch_name(e->reg));

            //fprintf(stream, "MOVQ %s, %rdi\n", scratch_name(e->reg));
            //fprintf(stream, "CALL print_integer\n");

            //fprintf(stream, "MOVQ %s, %rdi\n", scratch_name(extra_scratch));
            //fprintf(stream, "CALL print_integer\n");

            scratch_free(scratch_table, extra_scratch);
            scratch_free(scratch_table, e->right->reg);
            break;
        case EXPR_NAM:
            e->reg = scratch_alloc(scratch_table);
                fprintf(stream, "MOVQ %s, %s\n", symbol_codegen(e->symbol), scratch_name(e->reg));
            break;
        case EXPR_INT:
        case EXPR_BUL:
        case EXPR_CHR:
            e->reg = scratch_alloc(scratch_table);
            fprintf(stream, "MOVQ $%d, %s\n", e->literal_value, scratch_name(e->reg));
            break;
        case EXPR_STR:
            fprintf(stream, ".data\n");
            fprintf(stream, "%s:\n", string_label_name(e->symbol->string_index));
            fprintf(stream, ".string \"%s\"\n", e->string_literal);
            fprintf(stream, ".text\n");
            break;
        /// @TODO: Error
        case EXPR_NUL:
        default:
            break;
    }
}

void args_codegen (struct expr * e, int scratch_table [], FILE * stream) {
    if (!e) return;
    expr_codegen(e->left, scratch_table, stream);
    fprintf(stream, "MOVQ %s, %s\n", scratch_name(e->left->reg), arg_name(ARG_COUNTER++));
    scratch_free(scratch_table, e->left->reg);
    expr_codegen(e->right, scratch_table, stream);
    ARG_COUNTER = 0;
}