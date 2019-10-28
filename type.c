// @file   : type.c
// @author : John Ed Quinn
// @desc   : defines the type struct
// @notes  : NA

#include "type.h"

// @name : type_create
// @desc : creates a type struct
struct type * type_create (type_t kind, struct type * subtype, struct param_list * params) {
    struct type * type = malloc(sizeof(*type));
    type->kind = kind;
    type->subtype = subtype;
    type->param_list = params;
    return type;
}

// @name : type_print
// @desc : prints the type information
void type_print (struct type * t) {
    type_t_print(t->kind);
    if (t->subtype) {
        printf(" ");
        type_print(t->subtype);
    }
    if (t->params) {
        printf(" ");
        param_list_print(t->params);
    }
}

// @name : type_t_print
// @desc : prints the type_t string translation
void type_t_print (type_t kind) {
    switch (kind) {
        case 0: printf("void"); break;
        case 1: printf("boolean"); break;
        case 2: printf("char"); break;
        case 3: printf("integer"); break;
        case 4: printf("string"); break;
        case 5: printf("array"); break;
        case 6: printf("function"); break;
        default: printf("unknown"); break; // @TODO: Determine error
    }
}