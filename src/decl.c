// @file   : decl.c
// @author : John Ed Quinn
// @desc   : defines the decl struct
// @notes  : NA

#include "../include/decl.h"

// @name : decl_create
// @desc : creates a declaration pointer
struct decl * decl_create (char * name, struct type * type,
    struct expr * value, struct stmt * code,
    struct decl * next) {
        struct decl * decl = malloc(sizeof(*decl));
        decl->name = strdup(name);
        decl->type = type;
        decl->code = code;
        decl->next = next;
        decl->max_local = 0;
        if (value) decl->value = value;
        else {
            if (type->kind == TYPE_STRING) decl->value = expr_create_string_literal("");
            else decl->value = expr_create_integer_literal(0);
        }
        return decl;
}

// @name : decl_print
// @desc : prints a declarations information
void decl_print (struct decl * d, int indent) {
    if (!d) return;
    // Print indentation
    int i;
    for (i = 0; i < indent; i++) {
        printf("\t");
    }

    // Print declaration
    printf("%s", d->name);
    printf(": ");
    type_print(d->type); // Includes subtype

    // If value inside or not
    if (d->value) {
        printf(" = ");
        expr_print(d->value);
        printf(";\n");
    } else if (d->type->kind == TYPE_FUNCTION) {
        printf(" = {\n");
        stmt_print(d->code, indent + 1);
        printf("}\n");
    } else {
        printf(";\n");
    }
}

// @func : decl_resolve
// @desc : name resolution for decls
void decl_resolve (struct decl * d, struct hash_table * head) {
    if(!d) return;
    symbol_t kind = scope_level(head) > 1 ? SYMBOL_LOCAL : SYMBOL_GLOBAL;
    d->symbol = symbol_create(kind, d->type, d->name);
    scope_bind(head, d->name,d->symbol);
    expr_resolve(d->value, head);
    if (d->code) {
        MAX_LOCAL = 0;
        scope_enter(&head);
        param_list_resolve(d->type->params, head);
        stmt_resolve(d->code, head);
        scope_exit(&head);
        d->max_local = MAX_LOCAL;
    }
    decl_resolve(d->next, head);
}

// @func : decl_typecheck
// @desc : typechecking for decls
void decl_typecheck (struct decl * d) {
    if (!d) return;
    struct type *t;
    // Check function return types
    if (d->code) {
        stmt_typecheck(d->code, d);
    }
    else if (d->value) {
        t = expr_typecheck(d->value);
        // Check Auto
        if (d->symbol->type->kind == TYPE_AUTO) d->symbol->type = t;
        // Check Array
        if (d->symbol->type->kind == TYPE_ARRAY) {
            struct expr * temp = d->value;
            while (temp) {
                struct type * type_temp = expr_typecheck(temp);
                if (type_temp->kind != d->symbol->type->subtype->kind) {
                    fprintf(stderr, AC_RED "type error: " AC_RESET "cannot initialize array of type ");
                    type_t_print_err(d->symbol->type->subtype->kind);
                    fprintf(stderr, " with values of type ");
                    type_t_print_err(t->kind);
                    fprintf(stderr, ".\n");
                    NUM_TYPECHECK_ERRORS++;
                    break;
                }
                temp = temp->right;
            }
            return;
        }
        // Check initialization
        if (!type_equals(t,d->symbol->type)) {
            fprintf(stderr, AC_RED "type error: " AC_RESET "initializing ");
            type_t_print_err(d->symbol->type->kind);
            fprintf(stderr, " (");
            fprintf(stderr, "%s", d->symbol->name);
            fprintf(stderr, ") as ");
            type_t_print_err(t->kind);
            fprintf(stderr, " (");
            expr_print_err(d->value);
            fprintf(stderr, ") is not possible\n");
            NUM_TYPECHECK_ERRORS++;
        }
    }
}

// @func : decl_codegen
// @desc : generate code for declarations
void decl_codegen (struct decl * d, int scratch_table [], FILE * stream) {
    if (!d) return;
    switch (d->symbol->kind) {
        case SYMBOL_GLOBAL:
            if (d->type->kind == TYPE_FUNCTION) {
                fprintf(stream, ".globl %s\n", d->name);
                fprintf(stream, "%s:\n", d->name);
                fprintf(stream, "\tPUSHQ %rbp\n");
                fprintf(stream, "\tMOVQ %rsp, %rbp\n");

                // handle arguments
                param_list_codegen(d->type->params, scratch_table, stream);

                // ALLOCATE LOCAL REGISTERS
                fprintf(stream, "\tSUBQ $%d, %rsp\n", (d->max_local + 1) * 8);

                // Store Calle-Saved Registers
                fprintf(stream, "\tPUSHQ %rbx\n");
                fprintf(stream, "\tPUSHQ %r12\n");
                fprintf(stream, "\tPUSHQ %r13\n");
                fprintf(stream, "\tPUSHQ %r14\n");
                fprintf(stream, "\tPUSHQ %r15\n");

                // BODY & RETURNS
                stmt_codegen(d->code, scratch_table, stream);

                // Restore Calle-Saved Registers
                fprintf(stream, "\tPOPQ %r15\n");
                fprintf(stream, "\tPOPQ %r14\n");
                fprintf(stream, "\tPOPQ %r13\n");
                fprintf(stream, "\tPOPQ %r12\n");
                fprintf(stream, "\tPOPQ %rbx\n");

                // Returning
                fprintf(stream, "\tMOVQ %rbp, %rsp\n");
                fprintf(stream, "\tPOPQ %rbp\n");
                fprintf(stream, "\tRET\n");
                fprintf(stream, ".text\n");
            }
            else if (d->type->kind == TYPE_STRING) {
                fprintf(stream, ".data\n");
                fprintf(stream, "%s: .string \"%s\"\n", d->name, d->value->string_literal);
                fprintf(stream, ".text\n");
            } else if (d->type->kind == TYPE_ARRAY) {
                /// @TODO: Array
                fprintf(stream, ".globl %s\n", d->name);
                fprintf(stream, ".data\n");
                fprintf(stream, "%s:\n", d->name);
                struct expr * e = d->value;
                while (e) {
                    fprintf(stream, ".quad %d\n", e->literal_value);
                    e = e->right;
                }
                fprintf(stream, ".text\n");
                
            }else {
                fprintf(stream, ".data\n");
                fprintf(stream, "%s: .quad %d\n", d->name, d->value->literal_value);
                fprintf(stream, ".text\n");
            }
            break;
        case SYMBOL_LOCAL:
            if (d->type->kind == TYPE_STRING) {
                fprintf(stream, ".data\n");
                fprintf(stream, "%s:\n", string_label_name(d->value->symbol->string_index));
                fprintf(stream, ".string \"%s\"\n", d->value->string_literal);
                fprintf(stream, ".text\n");
                fprintf(stream, "\tMOVQ $%s, %s\n", string_label_name(d->value->symbol->string_index), symbol_codegen(d->symbol));
            } else {
                if (d->value) {
                    expr_codegen(d->value, scratch_table, stream);
                    fprintf(stream, "\tMOVQ %s, %s\n", scratch_name(d->value->reg), symbol_codegen(d->symbol));
                    scratch_free(scratch_table, d->value->reg);
                }
            }
            break;
        case SYMBOL_PARAM:
            break;
        default:
            break;
    }
}