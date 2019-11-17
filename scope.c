#include "scope.h"

// @name: scope_enter
// @desc: create a new hash table
void scope_enter (struct hash_table * head) {
    if (!head) {
        head = hash_table_create(0, 0);
        return;
    }
    struct hash_table * temp = head;
    head = hash_table_create(0, 0);
    head->next = temp;
}

// @name: scope_exit
// @desc: remove a hash table
void scope_exit (struct hash_table * head) {
    if (!head) return;
    struct hash_table * temp = head->next;
    hash_table_delete(head);
    head = temp;
}

// @name: scope_level
// @desc: returns the number of hash tables
int scope_level (struct hash_table * head) {
    int level = 0;
    struct hash_table * current = head;
    while (current) {
        level++;
        current = current->next;
    }
    return level;
}

// @name: scope_bind
// @desc: adds a variable to the top hash table
void scope_bind (struct hash_table * head, const char * name, struct symbol * sym) {
    int result = hash_table_insert(head, name, sym);
    if (result != 1) {
        fprintf(stderr, "Scope Error: Unable to bind variable: %s", name);
    }
}

// @name: symbol_create
// @desc: creates a symbol
struct symbol * scope_lookup (struct hash_table * head, const char * name) {
    struct hash_table * current = head;
    struct symbol * sym = (struct symbol *) NULL;
    while (current && !sym) {
        sym = scope_lookup_current(current, name);
        current = current->next;
    }
    //if (!sym) {
    //    fprintf(stderr, "Variable %s undeclared", name);
    //}
    return sym;
}

// @name: symbol_create
// @desc: creates a symbol
struct symbol * scope_lookup_current (struct hash_table * head, const char * name) {
    struct symbol * sym = hash_table_lookup(head, name);
    return sym;
}