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
        struct decl * decl = calloc(sizeof(*decl));
        decl->name = strdup(name);
        decl->type = type;
        if (!value)
            decl->symbol = symbol_create(0,0,0);
        else
            decl->symbol = symbol_create(0,0,0);
        decl->value = value;
        decl->code = code;
        decl->next = next;
        return decl;
}

// @name : decl_print
// @desc : prints a declarations information
void decl_print (struct decl * d, int indent) {
    // Print indentation
    int i;
    for (i = 0; i < indent; i++) {
        printf('\t');
    }

    // Print declaration
    printf("%s", decl->name);
    printf(" : ");
    type_print(decl->type); // Includes subtype
    printf(" (");
    param_list_print(decl->type->params);
    printf(")");
    
    // If value inside or not
    if (value) {
        printf(" = {\n");
        expr_print(decl->expr); // @TODO: Figure this out
        printf("}");
    } else {
        printf(";");
    }
}