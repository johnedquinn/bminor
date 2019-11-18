// @file   : expr.c
// @author : John Ed Quinn
// @desc   : defines the expr struct
// @notes  : NA

#include "expr.h"

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
            if (lt->kind != TYPE_INTEGER || rt->kind != TYPE_INTEGER) {
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
            if (lt->kind != TYPE_BOOLEAN) {
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
            if (lt->kind != TYPE_INTEGER) {
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
            result = type_create(TYPE_INTEGER,0,0);
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
            result = type_create(TYPE_INTEGER,0,0);
            break;
        case EXPR_NEQ:
            if (!type_equals(lt, rt)) {
                fprintf(stderr, AC_RED "type error: " AC_RESET "cannot perform equality operations on (%s) with (%s)", e->left->name, e->right->name);
                NUM_TYPECHECK_ERRORS++;
            }
            if (lt->kind == TYPE_VOID || lt->kind == TYPE_ARRAY || lt->kind == TYPE_FUNCTION) {
                fprintf(stderr, AC_RED "type error: " AC_RESET "cannot perform equality operations on (%s) with (%s)", e->left->name, e->right->name);
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
            //debug("lt->kind = %d", lt->kind);
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
            result = type_create(TYPE_INTEGER,0,0);
            break;
        case EXPR_ARG:
            result = type_create(TYPE_INTEGER,0,0);
            break;
        case EXPR_NAM:
            result = type_create(e->symbol->type->kind,0,0);
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
    type_delete(lt);
    type_delete(rt);
    return result;
}