
#ifndef BMINOR_LIB_H
#define BMINOR_LIB_H

#include <stdio.h>
#include <stdint.h>

void print_integer (long x);
void print_string (const char *s);
void print_boolean (int b);
void print_character (char c);
long integer_power (long x, long y);
void print_indents (int indent);

#endif