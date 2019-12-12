
#include "scratch.h"

// @func : scratch_alloc
// @desc : allocate a register
int scratch_alloc (int scratch_table []) {
    int i;
    for (i = 0; i < 6; i++) {
        if (scratch_table[i] == 0) {
            scratch_table[i] = 1;
            return i;
        }
    }
    fprintf(stderr, AC_RED "codegen error: " AC_RESET "cannot find an available scratch register.\n");
    exit(1);
}

// @func : scratch_free
// @desc : frees a scratch register
void scratch_free (int scratch_table [], int r) {
    if (r < 0 || r > 5) return;
    scratch_table[r] = 0;
}

const char * scratch_name (int r) {
    switch (r) {
        case 0:
            return "%rbx";
        case 1:
            return "%r10";
        case 2:
            return "%r11";
        case 3:
            return "%r12";
        case 4:
            return "%r13";
        case 5:
            return "%r14";
        default:
            return NULL;
    }
    return NULL;
}

// @func : label_create
// @desc : returns a new label
int label_create () {
    SCRATCH_COUNTER++;
    return SCRATCH_COUNTER;
}

// @func : label_name
// @desc : returns the label name
const char * label_name (int label) {
    char s [4];
    sprintf(s, ".L%d", label);
    char * new_s = strdup(s);
    return new_s;
}

/// @func: arg_name
/// @desc: returns the name of the argument register
const char * arg_name (int arg) {
       switch (arg) {
        case 0:
            return "%rdi";
        case 1:
            return "%rsi";
        case 2:
            return "%rdx";
        case 3:
            return "%rcx";
        case 4:
            return "%r8";
        case 5:
            return "%r9";
        default:
            return NULL;
    }
    return NULL; 
}

// @func : label_name
// @desc : returns the label name
const char * string_label_name (int label) {
    char s [6];
    sprintf(s, "_S%d", label);
    char * new_s = strdup(s);
    return new_s;
}