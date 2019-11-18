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
void expr_resolve (struct expr * e, struct hash_table * head) {
    if (!e) return;
    if (e->kind == EXPR_NAM) {
        e->symbol = scope_lookup(head, e->name);
        if (!e->symbol) fprintf(stderr, "resolve error: %s is not defined.\n", e->name);
    } else {
        expr_resolve(e->left, head);
        expr_resolve(e->right, head);
    }
}