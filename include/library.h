
#ifndef BMINOR_LIB_H
#define BMINOR_LIB_H

#include <stdio.h>
#include <stdint.h>

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...)   fprintf(stderr, "[%5d] DEBUG %10s:%-4d " M "\n", getpid(), __FILE__, __LINE__, ##__VA_ARGS__)
#endif

/* Define Error Colors */
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void print_integer (long x);
void print_string (const char *s);
void print_boolean (int b);
void print_character (char c);
long integer_power (long x, long y);
void print_indents (int indent);

#endif