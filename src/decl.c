// @file   : decl.c
// @author : John Ed Quinn
// @desc   : defines the decl struct
// @notes  : NA

#include "decl.h"

// @name : decl_create
// @desc : creates a declaration pointer
struct decl * decl_create (char * name, struct type * type,
    struct expr * value, struct stmt * code,
    struct decl * next) {
        struct decl * decl = malloc(sizeof(*decl));
        decl->name = strdup(name);
        decl->type = type;
        decl->value = value;
        decl->code = code;
        decl->next = next;
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
        scope_enter(&head);
        param_list_resolve(d->type->params, head);
        stmt_resolve(d->code, head);
        scope_exit(&head);
    }
    decl_resolve(d->next, head);
}