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