// @file   : param_list.c
// @author : John Ed Quinn
// @desc   : defines the param_list struct
// @notes  : NA

#include "param_list.h"

// @name : param_list_create
// @desc : creates a param_list struct
struct param_list * param_list_create (char *name, struct type * type, struct param_list * next) {
    struct param_list * p = malloc(sizeof(*p));
    p->name = strdup(name);
    p->type = type;
    p->next = next;
    return p;
}

// @name : param_list_print
// @desc : prints the param_list struct
void param_list_print (struct param_list * p) {
    if (!p) return;
    print_string(p->name);
    printf(": ");
    type_print(p->type);
    if (p->next) {
        printf(", ");
        param_list_print(p->next);
    }
}

// @name : param_list_resolve
// @desc : resolves the param_list struct
void param_list_resolve (struct param_list * p, struct hash_table * head) {
    if (!p) return;
    struct decl * d = decl_create(p->name, p->type, NULL, NULL, NULL);
    d->symbol = symbol_create(SYMBOL_PARAM, p->type, p->name);
    scope_bind(head, d->name, d->symbol);
    param_list_resolve(p->next, head);
}

// @name : param_list_copy
// @desc : returns copy of param_list
struct param_list * param_list_copy (struct param_list * target) {
    if (!target) return NULL;
    struct param_list * p = param_list_create(target->name, type_copy(target->type), param_list_copy(target->next));
    p->symbol = symbol_copy(target->symbol);
    return p;
}

// @name : param_list_typecheck
// @desc : typechecks the param_list
bool param_list_typecheck (struct param_list * target, struct param_list * baseline) {
    // Make sure param_list lengths are the same
    if (!target && baseline || target && !baseline) return false;

    // Reached end of param_list
    if (!target && !baseline) return true;

    // Recursively go down parameter list
    if (target->type->kind == baseline->type->kind) {
        return param_list_typecheck(target->next, baseline->next);
    } else {
        return false;
    }
}

void param_list_delete (struct param_list * p) {
    if (!p) return;
    type_delete(p->type);
    symbol_delete(p->symbol);
    param_list_delete(p->next);
    if (!p) free(p);
}

bool param_list_equals (struct param_list * a, struct param_list * b) {
    if (a && !b || !a && b) return false;
    if (!a && !b) return true;
    bool param_equal = param_list_equals(a->next, b->next);
    bool type_equal = type_equals(a->type, b->type);
    return param_equal && type_equal;
}

void param_list_codegen (struct param_list * p, int scratch_table [], FILE * stream) {
    if (!p) return;
    unsigned int param_index = 0;
    while (p) {
        fprintf(stream, "PUSHQ %s\n", arg_name(param_index));
        param_index++;
        p = p->next;
    }
}