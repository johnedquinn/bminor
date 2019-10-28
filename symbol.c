
#include "symbol.h"

// @name: symbol_create
// @desc: creates a symbol
struct symbol * symbol_create (symbol_t kind, struct type * type, char * name) {
    struct symbol * symbol = malloc(sizeof(*symbol));
    symbol->kind = kind;
    symbol->type = type;
    symbol->name = strdup(name);
    symbol->which = 0; // @TODO: Figure this out
    return symbol;
}