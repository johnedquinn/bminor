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
    //debug("P_LIST: %s", p->name);
    struct decl * d = decl_create(p->name, p->type, NULL, NULL, NULL);
    d->symbol = symbol_create(SYMBOL_PARAM, p->type, p->name);
    scope_bind(head, d->name, d->symbol);
    //decl_resolve(d, head);
    //debug("P_LIST: %s", p->name);
    param_list_resolve(p->next, head);
}