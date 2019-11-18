
#ifndef BMINOR_LIB_H
#define BMINOR_LIB_H

/* Includes */
#include "type.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

/* DEBUG Function */
#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...)   fprintf(stderr, "[%5d] DEBUG %10s:%-4d " M "\n", getpid(), __FILE__, __LINE__, ##__VA_ARGS__)
#endif

/* Define Error Colors */
#define AC_RED     "\x1b[31m"
#define AC_GREEN   "\x1b[32m"
#define AC_YELLOW  "\x1b[33m"
#define AC_BLUE    "\x1b[34m"
#define AC_MAGENTA "\x1b[35m"
#define AC_CYAN    "\x1b[36m"
#define AC_RESET   "\x1b[0m"

void print_integer (long x);
void print_string (const char *s);
void print_boolean (int b);
void print_character (char c);
long integer_power (long x, long y);
void print_indents (int indent);

#endif