// @file   : type.c
// @author : John Ed Quinn
// @desc   : defines the type struct
// @notes  : NA

#include "type.h"
#include <stdlib.h>

// @name : type_create
// @desc : creates a type struct
struct type * type_create (type_t kind, struct type * subtype, struct param_list * params) {
    struct type * type = malloc(sizeof(*type));
    type->kind = kind;
    type->subtype = subtype;
    type->params = params;
    return type;
}

// @name : type_print
// @desc : prints the type information
void type_print (struct type * t) {
    if (!t) return;
    type_t_print(t->kind);
    if (t->subtype) {
        printf(" ");
        type_print(t->subtype);
    }
    if (t->kind == TYPE_FUNCTION) {
        printf(" ");
        printf("(");
        param_list_print(t->params);
        printf(")");
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
        case 7: printf("auto"); break;
        default: printf("unknown"); break; // @TODO: Determine error
    }
}

// @name : type_t_print_err
// @desc : prints the type_t string translation
void type_t_print_err (type_t kind) {
    switch (kind) {
        case 0: fprintf(stderr, "void"); break;
        case 1: fprintf(stderr, "boolean"); break;
        case 2: fprintf(stderr, "char"); break;
        case 3: fprintf(stderr, "integer"); break;
        case 4: fprintf(stderr, "string"); break;
        case 5: fprintf(stderr, "array"); break;
        case 6: fprintf(stderr, "function"); break;
        case 7: fprintf(stderr, "auto"); break;
        default: fprintf(stderr, "unknown"); break;
    }
}

// @name : type_equals
// @desc : return true if equals
bool type_equals (struct type * a, struct type * b) {
    if (a->kind == b->kind) {
        if (type_is_atomic(a) && type_is_atomic(b)) {
            return true;
        } else if (a->kind == TYPE_ARRAY && b->kind == TYPE_ARRAY) {
            return type_equals(a->subtype, b->subtype);
        } else if (a->kind == TYPE_FUNCTION && b->kind == TYPE_FUNCTION) {
            bool sub_equal = type_equals(a->subtype, b->subtype);
            bool param_equal = param_list_equals(a->params, b->params);
            return sub_equal && param_equal;
        }
    } else {
        return false;
    }
}

// @name : type_copy
// @desc : returns copy of type
struct type * type_copy (struct type * t) {
    return type_create(t->kind, type_copy(t->subtype), param_list_copy(t->params));
}

// @name : type_delete
// @desc : deletes type recursively
void type_delete (struct type * t) {
    if (!t) return;
    param_list_delete(t->params);
    type_delete(t->subtype);
    free(t);
}

// @name : type_delete
// @desc : deletes type recursively
bool type_is_atomic (struct type * t) {
	type_t kind = t->kind;
	return kind == TYPE_BOOLEAN || kind == TYPE_CHARACTER
	|| kind == TYPE_INTEGER || kind == TYPE_STRING || kind == TYPE_AUTO;
}