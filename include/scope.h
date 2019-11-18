// @file   : symbol.h
// @author : John Ed Quinn
// @desc   : declares the symbol struct
// @notes  : NA

#ifndef SCOPE_H
#define SCOPE_H

#include "type.h"
#include "hash_table.h"
#include "symbol.h"
#include "library.h"
#include "param_list.h"
#include <stdlib.h>
#include <string.h>

extern int NUM_RESOLVE_ERRORS;

void scope_enter (struct hash_table ** head);
void scope_exit (struct hash_table ** head);
int scope_level (struct hash_table * head);
struct symbol * scope_lookup (struct hash_table * head, const char * name);
struct symbol * scope_lookup_current (struct hash_table * head, const char * name);
void scope_bind (struct hash_table * head, const char * name, struct symbol * sym);


#endif