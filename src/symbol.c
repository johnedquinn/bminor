// @file   : symbol.c
// @author : John Ed Quinn
// @desc   : defines the symbol struct
// @notes  : NA

#include "../include/symbol.h"

// @name: symbol_create
// @desc: creates a symbol
struct symbol * symbol_create (symbol_t kind, struct type * type, char * name) {
    struct symbol * symbol = malloc(sizeof(*symbol));
    symbol->kind = kind;
    symbol->type = type;
    symbol->name = strdup(name);
    symbol->string_index = 0;
    symbol->which = 0;
    return symbol;
}

// @name: symbol_create
// @desc: creates a symbol
void symbol_delete (struct symbol * s) {
    if (!s) return;
    type_delete(s->type);
    if (s->name) free(s->name);
    free(s);
}

// @name: symbol_copy
// @desc: return copy of symbol
struct symbol * symbol_copy(struct symbol * s) {
    struct symbol * sym = symbol_create(s->kind, type_copy(s->type), s->name);
    sym->which = s->which;
    return sym;
}

// @name: symbol_copy
// @desc: return copy of symbol
// @TODO: check if param stuff needed
const char * symbol_codegen (struct symbol * s) {
    // Global variables
    if (s->kind == SYMBOL_GLOBAL) {
        return s->name;
    }

    // Local variables
    int offset = 8 + s->which * 8;
    char position [4];
    sprintf(position, "-%d(\%rbp)", offset);
    char * new_position = strdup(position);
    return new_position;
}