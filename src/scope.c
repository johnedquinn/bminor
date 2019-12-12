#include "scope.h"

// @name: scope_enter
// @desc: create a new hash table
void scope_enter (struct hash_table ** head) {
    //debug("SCOPE ENTER = %ld", *head);
    if (!*head) {
        *head = hash_table_create(0, 0);
        return;
    }
    struct hash_table * temp = *head;
    *head = hash_table_create(0, 0);
    (*head)->next = temp;
}

// @name: scope_exit
// @desc: remove a hash table
void scope_exit (struct hash_table ** head) {
    if (!*head) return;
    //debug("SCOPE EXIT = %ld", *head);
    struct hash_table * temp = (*head)->next;
    hash_table_delete(*head);
    *head = temp;
}

// @name: scope_level
// @desc: returns the number of hash tables
int scope_level (struct hash_table * head) {
    int level = 0;
    struct hash_table * current = head;
    while (current) {
        //debug("SCOPE Level  = %d; CURRENT = %ld", level, current);
        level++;
        current = current->next;
    }
    return level;
}

// @name: scope_bind
// @desc: adds a variable to the top hash table
void scope_bind (struct hash_table * head, const char * name, struct symbol * sym) {
    
    // Check if Global scope
    if (!head->next) {
        sym->which = hash_table_size(head);
    } else {

        // Check how many of the same type are in the stack
        char * key; struct symbol * val;
        int size = 0; struct hash_table * current = head;
        while (current->next) {
            hash_table_firstkey(current);
            while (hash_table_nextkey(current, &key, (void*)&val)) {
                if (val->kind == sym->kind) size++;
            }
            current = current->next;
        }
        sym->which = size;
    }

    // Attempt to insert
    int result = hash_table_insert(head, name, sym);
    if (result != 1) {
        fprintf(stderr, AC_RED "resolve error: " AC_RESET "redeclaration of %s.\n", name);
        NUM_RESOLVE_ERRORS++;
    }
    
    // Print resolution message
    if (sym->kind == SYMBOL_LOCAL)
        fprintf(stdout, "%s resolves to local %d\n", sym->name, sym->which);
    else if (sym->kind == SYMBOL_GLOBAL)
        fprintf(stdout, "%s resolves to global %s\n", sym->name, sym->name);
    else
        fprintf(stdout, "%s resolves to param %d\n", sym->name, sym->which);

    MAX_LOCAL = sym->which;
}
// @name: scope_lookup
// @desc: searches the entire stack for a variable
struct symbol * scope_lookup (struct hash_table * head, const char * name) {
    struct hash_table * current = head;
    struct symbol * sym = (struct symbol *) NULL;
    while (current && !sym) {
        sym = scope_lookup_current(current, name);
        current = current->next;
    }
    return sym;
}

// @name: scope_lookup_current
// @desc: searches the top of the stack for a variable
struct symbol * scope_lookup_current (struct hash_table * head, const char * name) {
    struct symbol * sym = hash_table_lookup(head, name);
    return sym;
}